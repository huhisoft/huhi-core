'use strict'
/* todo HNQ config api key */
const path = require('path')
const fs = require('fs')
const assert = require('assert')
const { spawnSync } = require('child_process')
const rootDir = require('./root')

let npmCommand = 'npm'
if (process.platform === 'win32') {
  npmCommand += '.cmd'
}
let NpmConfig = null

const run = (cmd, args = []) => {
  const prog = spawnSync(cmd, args)
  if (prog.status !== 0) {
    console.log(prog.stdout && prog.stdout.toString())
    console.error(prog.stderr && prog.stderr.toString())
    process.exit(1)
  }
  return prog
}

// this is a huge hack because the npm config doesn't get passed through from huhi-browser .npmrc/package.json
var packageConfig = function(key){
  let packages = { config: {}}
  if (fs.existsSync(path.join(rootDir, 'package.json'))) {
    packages = require(path.relative(__dirname, path.join(rootDir, 'package.json')))
  }

  // packages.config should include version string.
  let obj = Object.assign({}, packages.config, { version: packages.version })
  for (var i = 0, len = key.length; i < len; i++) {
    if (!obj) {
      return obj
    }
    obj = obj[key[i]]
  }
  return obj
}

const getNPMConfig = (key) => {
  if (!NpmConfig) {
    const list = run(npmCommand, ['config', 'list', '--json'], {cwd: rootDir})
    NpmConfig = JSON.parse(list.stdout.toString())
  }

  return NpmConfig[key.join('-').replace(/_/g, '-')] || packageConfig(key)
}

const parseExtraInputs = (inputs, accumulator, callback) => {
  for (let input of inputs) {
    let separatorIndex = input.indexOf(':')
    if (separatorIndex < 0) {
      separatorIndex = input.length
    }

    const key = input.substring(0, separatorIndex);
    const value = input.substring(separatorIndex + 1);
    callback(accumulator, key, value)
  }
}

const Config = function () {
  this.defaultBuildConfig = 'Component'
  this.buildConfig = this.defaultBuildConfig
  this.signTarget = 'sign_app'
  this.buildTarget = 'huhi'
  this.rootDir = rootDir
  this.isUniversalBinary = false
  this.scriptDir = path.join(this.rootDir, 'scripts')
  this.srcDir = path.join(this.rootDir, 'src')
  this.chromeVersion = this.getProjectVersion('chrome')
  this.chromiumRepo = getNPMConfig(['projects', 'chrome', 'repository', 'url'])
  this.huhiCoreDir = path.join(this.srcDir, 'huhi')
  this.huhiCoreRepo = getNPMConfig(['projects', 'huhi-core', 'repository', 'url'])
  this.buildToolsDir = path.join(this.srcDir, 'build')
  this.resourcesDir = path.join(this.rootDir, 'resources')
  this.depotToolsDir = path.join(this.huhiCoreDir, 'vendor', 'depot_tools')
  this.defaultGClientFile = path.join(this.rootDir, '.gclient')
  this.gClientFile = process.env.HUHI_GCLIENT_FILE || this.defaultGClientFile
  this.gClientVerbose = getNPMConfig(['gclient_verbose']) || false
  this.targetArch = getNPMConfig(['target_arch']) || 'x64'
  this.targetOS = getNPMConfig(['target_os'])
  this.gypTargetArch = 'x64'
  this.targetApkBase ='classic'
  this.huhiGoogleApiKey = getNPMConfig(['huhi_google_api_key']) || 'AIzaSyAQfxPJiounkhOjODEO5ZieffeBv6yft2Q'
  this.googleApiEndpoint = getNPMConfig(['huhi_google_api_endpoint']) || 'https://www.googleapis.com/geolocation/v1/geolocate?key='
  this.googleDefaultClientId = getNPMConfig(['google_default_client_id']) || ''
  this.googleDefaultClientSecret = getNPMConfig(['google_default_client_secret']) || ''
  this.huhiServicesKey = getNPMConfig(['huhi_services_key']) || ''
  this.infuraProjectId = getNPMConfig(['huhi_infura_project_id']) || ''
  this.binanceClientId = getNPMConfig(['binance_client_id']) || ''
  this.geminiClientId = getNPMConfig(['gemini_client_id']) || ''
  this.geminiClientSecret = getNPMConfig(['gemini_cliehuhi_stringsnt_secret']) || ''
  this.huhiSyncEndpoint = getNPMConfig(['huhi_sync_endpoint']) || ''
  this.safeBrowsingApiEndpoint = getNPMConfig(['safebrowsing_api_endpoint']) || ''
  this.updaterProdEndpoint = getNPMConfig(['updater_prod_endpoint']) || ''
  this.updaterDevEndpoint = getNPMConfig(['updater_dev_endpoint']) || ''
  this.webcompatReportApiEndpoint = getNPMConfig(['webcompat_report_api_endpoint']) || 'https://webcompat.hnq.vn/1/webcompat'
  this.chromePgoPhase = 0
  // this.buildProjects()
  this.huhiVersion = getNPMConfig(['version']) || '0.0.0'
  this.androidOverrideVersionName = this.huhiVersion
  this.releaseTag = this.huhiVersion.split('+')[0]
  this.mac_signing_identifier = getNPMConfig(['mac_signing_identifier'])
  this.mac_installer_signing_identifier = getNPMConfig(['mac_installer_signing_identifier']) || ''
  this.mac_signing_keychain = getNPMConfig(['mac_signing_keychain']) || 'login'
  this.sparkleDSAPrivateKeyFile = getNPMConfig(['sparkle_dsa_private_key_file']) || ''
  this.sparkleEdDSAPrivateKey = getNPMConfig(['sparkle_eddsa_private_key']) || ''
  this.sparkleEdDSAPublicKey = getNPMConfig(['sparkle_eddsa_public_key']) || ''
  this.notary_user = getNPMConfig(['notary_user']) || ''
  this.notary_password = getNPMConfig(['notary_password']) || ''
  this.channel = 'development'
  this.git_cache_path = getNPMConfig(['git_cache_path'])
  this.sccache = getNPMConfig(['sccache'])
  this.huhiStatsApiKey = getNPMConfig(['huhi_stats_api_key']) || ''
  this.huhiStatsUpdaterUrl = getNPMConfig(['huhi_stats_updater_url']) || ''
  this.ignore_compile_failure = false
  this.enable_hangout_services_extension = true
  this.widevineVersion = getNPMConfig(['widevine', 'version'])
  this.sign_widevine_cert = process.env.SIGN_WIDEVINE_CERT || ''
  this.sign_widevine_key = process.env.SIGN_WIDEVINE_KEY || ''
  this.sign_widevine_passwd = process.env.SIGN_WIDEVINE_PASSPHRASE || ''
  this.signature_generator = path.join(this.srcDir, 'third_party', 'widevine', 'scripts', 'signature_generator.py') || ''
  this.extraGnArgs = {}
  this.extraNinjaOpts = []
  this.huhiSafetyNetApiKey = getNPMConfig(['huhi_safetynet_api_key']) || ''
  this.huhiAndroidDeveloperOptionsCode = getNPMConfig(['huhi_android_developer_options_code']) || ''
  this.huhiAndroidKeystorePath = getNPMConfig(['huhi_android_keystore_path'])
  this.huhiAndroidKeystoreName = getNPMConfig(['huhi_android_keystore_name'])
  this.huhiAndroidKeystorePassword = getNPMConfig(['huhi_android_keystore_password'])
  this.huhiAndroidKeyPassword = getNPMConfig(['huhi_android_key_password'])
  this.huhiVariationsServerUrl = getNPMConfig(['huhi_variations_server_url']) || ''
}

Config.prototype.isOfficialBuild = function () {
  return this.buildConfig === 'Release'
}

Config.prototype.isComponentBuild = function () {
  return this.buildConfig === 'Debug' || this.buildConfig === 'Component'
}

Config.prototype.isDebug = function () {
  return this.buildConfig === 'Debug'
}

Config.prototype.isDcheckAlwaysOn = function () {
  return this.buildConfig !== 'Release'
}

Config.prototype.enableCDMHostVerification = function () {
  const enable = this.buildConfig === 'Release' &&
                 process.platform !== 'linux' &&
                 this.sign_widevine_cert !== "" &&
                 this.sign_widevine_key !== "" &&
                 this.sign_widevine_passwd !== "" &&
                 fs.existsSync(this.signature_generator)
  if (enable) {
    console.log('Widevine cdm host verification is enabled')
  } else {
    console.log('Widevine cdm host verification is disabled')
  }
  return enable
}

Config.prototype.isAsan = function () {
  if (this.is_asan) {
    return true
  }
  return false
}

Config.prototype.buildArgs = function () {
  const version = this.huhiVersion
  let version_parts = version.split('+')[0]
  version_parts = version_parts.split('.')

  const chrome_version_parts = this.chromeVersion.split('.')

  let args = {
    is_asan: this.isAsan(),
    enable_full_stack_frames_for_profiling: this.isAsan(),
    v8_enable_verify_heap: this.isAsan(),
    fieldtrial_testing_like_official_build: true,
    safe_browsing_mode: 1,
    huhi_services_key: this.huhiServicesKey,
    root_extra_deps: ["//huhi"],
    // TODO: Re-enable when chromium_src overrides work for files in relative
    // paths like widevine_cmdm_compoennt_installer.cc
    // use_jumbo_build: !this.officialBuild,
    is_component_build: this.isComponentBuild(),
    is_universal_binary: this.isUniversalBinary,
    proprietary_codecs: true,
    ffmpeg_branding: "Chrome",
    branding_path_component: "huhi",
    enable_nacl: false,
    enable_widevine: true,
    target_cpu: this.targetArch,
    is_official_build: this.isOfficialBuild() && !this.isAsan(),
    is_debug: this.isDebug(),
    dcheck_always_on: this.isDcheckAlwaysOn(),
    huhi_channel: this.channel,
    huhi_google_api_key: this.huhiGoogleApiKey,
    huhi_google_api_endpoint: this.googleApiEndpoint,
    google_default_client_id: this.googleDefaultClientId,
    google_default_client_secret: this.googleDefaultClientSecret,
    huhi_infura_project_id: this.infuraProjectId,
    binance_client_id: this.binanceClientId,
    gemini_client_id: this.geminiClientId,
    gemini_client_secret: this.geminiClientSecret,
    huhi_product_name: getNPMConfig(['huhi_product_name']) || "huhi-core",
    huhi_project_name: getNPMConfig(['huhi_project_name']) || "huhi-core",
    huhi_version_major: version_parts[0],
    huhi_version_minor: version_parts[1],
    huhi_version_build: version_parts[2],
    chrome_version_string: this.chromeVersion,
    chrome_version_major: chrome_version_parts[0],
    huhi_sync_endpoint: this.huhiSyncEndpoint,
    safebrowsing_api_endpoint: this.safeBrowsingApiEndpoint,
    huhi_variations_server_url: this.huhiVariationsServerUrl,
    updater_prod_endpoint: this.updaterProdEndpoint,
    updater_dev_endpoint: this.updaterDevEndpoint,
    webcompat_report_api_endpoint: this.webcompatReportApiEndpoint,
    huhi_stats_api_key: this.huhiStatsApiKey,
    huhi_stats_updater_url: this.huhiStatsUpdaterUrl,
    enable_hangout_services_extension: this.enable_hangout_services_extension,
    enable_cdm_host_verification: this.enableCDMHostVerification(),
    skip_signing: !this.shouldSign(),
    chrome_pgo_phase: this.chromePgoPhase,
    sparkle_dsa_private_key_file: this.sparkleDSAPrivateKeyFile,
    sparkle_eddsa_private_key: this.sparkleEdDSAPrivateKey,
    sparkle_eddsa_public_key: this.sparkleEdDSAPublicKey,
    ...this.extraGnArgs,
  }

  if (this.shouldSign()) {
    if (process.platform === 'darwin') {
      args.mac_signing_identifier = this.mac_signing_identifier
      args.mac_installer_signing_identifier = this.mac_installer_signing_identifier
      args.mac_signing_keychain = this.mac_signing_keychain
      if (this.notarize) {
        args.notarize = true
        args.notary_user = this.notary_user
        args.notary_password = this.notary_password
      }
    } else if (this.targetOS === 'android') {
      args.huhi_android_keystore_path = this.huhiAndroidKeystorePath
      args.huhi_android_keystore_name = this.huhiAndroidKeystoreName
      args.huhi_android_keystore_password = this.huhiAndroidKeystorePassword
      args.huhi_android_key_password = this.huhiAndroidKeyPassword
    }
  }

  if (process.platform === 'win32' && this.build_omaha) {
    args.build_omaha = this.build_omaha
    args.tag_ap = this.tag_ap
  }

  if ((process.platform === 'win32' || process.platform === 'darwin') && this.build_delta_installer) {
    assert(this.last_chrome_installer, 'Need last_chrome_installer args for building delta installer')
    args.build_delta_installer = true
    args.last_chrome_installer = this.last_chrome_installer
  }

  if (this.isDebug() &&
      this.targetOS !== 'ios' &&
      this.targetOS !== 'android') {
    if (process.platform === 'darwin') {
      args.enable_stripping = false
    }
    args.symbol_level = 2
    args.enable_profiling = true
  }

  if (this.sccache && process.platform === 'win32') {
    args.clang_use_chrome_plugins = false
    args.enable_precompiled_headers = false
    args.use_thin_lto = true
  }

  if (this.targetArch === 'x86' && process.platform === 'linux') {
    // Minimal symbols for target Linux x86, because ELF32 cannot be > 4GiB
    args.symbol_level = 1
  }

  if (this.targetArch === 'x64' &&
      process.platform === 'linux' &&
      this.targetOS !== 'android') {
    // Include vaapi support
    args.use_vaapi = true
  }

  if (this.targetOS === 'android') {
    args.target_os = 'android'
    args.android_channel = this.channel
    if (!this.isOfficialBuild()) {
      args.android_channel = 'default'
      args.chrome_public_manifest_package = 'com.huhi.browser_default'
    } else if (this.channel === '') {
      args.android_channel = 'stable'
      args.chrome_public_manifest_package = 'com.huhi.browser'
    } else if (this.channel === 'beta') {
      args.chrome_public_manifest_package = 'com.huhi.browser_beta'
    } else if (this.channel === 'dev') {
      args.chrome_public_manifest_package = 'com.huhi.browser_dev'
    } else if (this.channel === 'nightly') {
      args.android_channel = 'canary'
      args.chrome_public_manifest_package = 'com.huhi.browser_nightly'
    }

    args.target_apk_base = this.targetApkBase
    args.android_override_version_name = this.androidOverrideVersionName

    args.huhi_android_developer_options_code = this.huhiAndroidDeveloperOptionsCode
    args.huhi_safetynet_api_key = this.huhiSafetyNetApiKey
    args.enable_widevine = false
    args.safe_browsing_mode = 2

    if (this.buildConfig !== 'Release') {
      // treat non-release builds like Debug builds
      args.treat_warnings_as_errors = false
    } else {
      // otherwise there is build error
      // ld.lld: error: output file too large: 5861255936 bytes
      args.symbol_level = 1
    }

    // Feed is not used in Huhi
    args.enable_feed_v1 = false
    args.enable_feed_v2 = false

    // TODO(fixme)
    args.enable_tor = false

    // These do not exist on android
    // TODO - recheck
    delete args.enable_nacl
    delete args.enable_hangout_services_extension
    delete args.huhi_infura_project_id
    // Ideally we'd not pass this on Linux CI and then
    // not have a default value for this. But we'll
    // eventually want it on Android, so keeping CI
    // unchanged and deleting here for now.
    delete args.gemini_client_id
    delete args.gemini_client_secret
  }

  if (this.targetOS === 'ios') {
    args.target_os = 'ios'
    args.enable_dsyms = true
    args.enable_stripping = !this.isDebug()
    args.use_xcode_clang = false
    args.use_clang_coverage = false
    // Component builds are not supported for iOS:
    // https://chromium.googlesource.com/chromium/src/+/master/docs/component_build.md
    args.is_component_build = false
    args.ios_deployment_target = '12.0'
    args.ios_enable_code_signing = false
    args.fatal_linker_warnings = !this.isComponentBuild()
    // DCHECK's crash on Static builds without allowing the debugger to continue
    // Can be removed when approprioate DCHECK's have been fixed:
    // https://github.com/huhisoft/huhi-browser/issues/10334
    args.dcheck_always_on = this.isDebug()

    delete args.safebrowsing_api_endpoint
    delete args.updater_prod_endpoint
    delete args.updater_dev_endpoint
    delete args.safe_browsing_mode
    delete args.proprietary_codecs
    delete args.ffmpeg_branding
    delete args.branding_path_component
    delete args.enable_nacl
    delete args.branding_path_component
    delete args.enable_widevine
    delete args.enable_hangout_services_extension
    delete args.huhi_google_api_endpoint
    delete args.huhi_google_api_key
    delete args.huhi_stats_api_key
    delete args.huhi_stats_updater_url
    delete args.huhi_infura_project_id
    delete args.binance_client_id
    delete args.gemini_client_id
    delete args.gemini_client_secret
    delete args.huhi_services_key
    delete args.webcompat_report_api_endpoint
    delete args.use_blink_v8_binding_new_idl_interface
    delete args.v8_enable_verify_heap
    delete args.huhi_variations_server_url
  }

  if (process.platform === 'win32') {
    args.cc_wrapper = path.join(this.srcDir, 'huhi', 'script', 'redirect-cc.cmd')
  } else {
    args.cc_wrapper = path.join(this.srcDir, 'huhi', 'script', 'redirect-cc.py')
  }
  return args
}

Config.prototype.shouldSign = function () {
  if (this.skip_signing ||
      this.buildConfig !== 'Release' ||
      this.targetOS === 'ios') {
    return false;
  }

  if (this.targetOS === 'android') {
    return this.huhiAndroidKeystorePath !== undefined
  }

  if (process.platform === 'darwin') {
    return this.mac_signing_identifier !== undefined
  }

  if (process.platform === 'win32') {
    return process.env.CERT !== undefined &&
           process.env.SIGNTOOL_ARGS !== undefined
  }

  return false;
}

Config.prototype.prependPath = function (oldPath, addPath) {
  let newPath = oldPath.split(path.delimiter)
  newPath.unshift(addPath)
  newPath = newPath.join(path.delimiter)
  return newPath
}

Config.prototype.appendPath = function (oldPath, addPath) {
  let newPath = oldPath.split(path.delimiter)
  newPath.push(addPath)
  newPath = newPath.join(path.delimiter)
  return newPath
}

Config.prototype.addPathToEnv = function (env, addPath, prepend = false) {
  // cmd.exe uses Path instead of PATH so just set both
  const addToPath = prepend ? this.prependPath : this.appendPath
  env.Path && (env.Path = addToPath(env.Path, addPath))
  env.PATH && (env.PATH = addToPath(env.PATH, addPath))
  return env
}

Config.prototype.addPythonPathToEnv = function (env, addPath) {
  env.PYTHONPATH = this.appendPath(env.PYTHONPATH || '', addPath)
  return env
}

Config.prototype.getProjectVersion = function (projectName) {
  return getNPMConfig(['projects', projectName, 'tag']) || getNPMConfig(['projects', projectName, 'branch'])
}

Config.prototype.getProjectRef = function (projectName) {
  const tag = getNPMConfig(['projects', projectName, 'tag'])
  if (tag) {
    return `refs/tags/${tag}`
  }

  let branch = getNPMConfig(['projects', projectName, 'branch'])
  if (branch) {
    return `origin/${branch}`
  }

  return 'origin/master'
}

Config.prototype.update = function (options) {
  if (options.universal) {
    this.targetArch = 'arm64'
    this.isUniversalBinary = true
  }

  if (options.target_arch === 'x86') {
    this.targetArch = options.target_arch
    this.gypTargetArch = 'ia32'
  } else if (options.target_arch === 'ia32') {
    this.targetArch = 'x86'
    this.gypTargetArch = options.target_arch
  } else if (options.target_arch) {
    this.targetArch = options.target_arch
  }

  if (options.target_os === 'android') {
    this.targetOS = 'android'
    if (options.target_apk_base) {
      this.targetApkBase = options.target_apk_base
    }
    if (options.android_override_version_name) {
      this.androidOverrideVersionName = options.android_override_version_name
    }
  }

  if (options.target_os) {
    this.targetOS = options.target_os
  }

  if (options.is_asan) {
    this.is_asan = true
  } else {
    this.is_asan = false
  }

  if (options.C) {
    this.__outputDir = options.C
  }

  if (options.gclient_file && options.gclient_file !== 'default') {
    this.gClientFile = options.gclient_file
  }

  if (options.huhi_google_api_key) {
    this.huhiGoogleApiKey = options.huhi_google_api_key
  }

  if (options.huhi_safetynet_api_key) {
    this.huhiSafetyNetApiKey = options.huhi_safetynet_api_key;
  }

  if (options.huhi_google_api_endpoint) {
    this.googleApiEndpoint = options.huhi_google_api_endpoint
  }

  if (options.huhi_infura_project_id) {
    this.infuraProjectId = options.infura_project_id
  }

  if (options.binance_client_id) {
    this.binanceClientId = options.binance_client_id
  }

  if (options.gemini_client_id) {
    this.geminiClientId = options.gemini_client_id
  }

  if (options.gemini_client_secret) {
    this.geminiClientSecret = options.gemini_client_secret
  }

  if (options.safebrowsing_api_endpoint) {
    this.safeBrowsingApiEndpoint = options.safebrowsing_api_endpoint
  }

  if (options.updater_prod_endpoint) {
    this.updaterDevEndpoint = options.updater_prod_endpoint
  }

  if (options.updater_dev_endpoint) {
    this.updaterDevEndpoint = options.updater_dev_endpoint
  }

  if (options.webcompat_report_api_endpoint) {
    this.webcompatReportApiEndpoint = options.webcompat_report_api_endpoint
  }

  if (options.huhi_stats_api_key) {
    this.huhiStatsApiKey = options.huhi_stats_api_key
  }

  if (options.huhi_stats_updater_url) {
    this.huhiStatsUpdaterUrl = options.huhi_stats_updater_url
  }

  if (options.channel) {
    this.channel = options.channel
  } else if (this.buildConfig === 'Release') {
    this.channel = 'release'
  }

  if (this.channel === 'release') {
    // empty for release channel
    this.channel = ''
  }

  if (process.platform === 'win32' && options.build_omaha) {
    this.build_omaha = true
    this.tag_ap = options.tag_ap
  }

  if (options.skip_signing) {
    this.skip_signing = true
  }

  if (options.build_delta_installer) {
    this.build_delta_installer = true
    this.last_chrome_installer = options.last_chrome_installer
  }

  if (options.mac_signing_identifier)
    this.mac_signing_identifier = options.mac_signing_identifier

  if (options.mac_installer_signing_identifier)
    this.mac_installer_signing_identifier = options.mac_installer_signing_identifier

  if (options.mac_signing_keychain)
    this.mac_signing_keychain = options.mac_signing_keychain

  if (options.notarize)
    this.notarize = true

  if (options.gclient_verbose)
    this.gClientVerbose = options.gclient_verbose

  if (options.ignore_compile_failure)
    this.ignore_compile_failure = true

  if (options.xcode_gen) {
    assert(process.platform === 'darwin' || options.target_os === 'ios')
    if (options.xcode_gen === 'ios') {
      this.xcode_gen_target = '//huhi/vendor/huhi-ios:*'
    } else {
      this.xcode_gen_target = options.xcode_gen
    }
  }

  if (options.gn) {
    parseExtraInputs(options.gn, this.extraGnArgs, (args, key, value) => {
      try {
        value = JSON.parse(value)
      } catch (e) {
        // On parse error, leave value as string.
      }
      args[key] = value
    })
  }

  if (options.ninja) {
    parseExtraInputs(options.ninja, this.extraNinjaOpts, (opts, key, value) => {
      opts.push(`-${key}`)
      opts.push(value)
    })
  }
}

Config.prototype.getCachePath = function () {
  return this.git_cache_path || process.env.GIT_CACHE_PATH
}

Object.defineProperty(Config.prototype, 'defaultOptions', {
  get: function () {
    let env = Object.assign({}, process.env)
    env = this.addPathToEnv(env, this.depotToolsDir, true)
    env = this.addPythonPathToEnv(env, path.join(this.srcDir, 'huhi', 'chromium_src', 'python_modules'))
    env = this.addPythonPathToEnv(env, path.join(this.srcDir, 'huhi', 'script'))
    env = this.addPythonPathToEnv(env, path.join(this.srcDir, 'tools', 'grit', 'grit', 'extern'))
    env = this.addPythonPathToEnv(env, path.join(this.srcDir, 'huhi', 'vendor', 'requests'))
    env = this.addPythonPathToEnv(env, path.join(this.srcDir, 'build'))
    env = this.addPythonPathToEnv(env, path.join(this.srcDir, 'third_party', 'depot_tools'))
    env.GCLIENT_FILE = this.gClientFile
    env.DEPOT_TOOLS_WIN_TOOLCHAIN = '0'
    env.PYTHONUNBUFFERED = '1'
    env.TARGET_ARCH = this.gypTargetArch // for huhi scripts
    env.GYP_MSVS_VERSION = env.GYP_MSVS_VERSION || '2017' // enable 2017
    if (this.channel != "") {
      env.HUHI_CHANNEL = this.channel
    }

    if (this.getCachePath()) {
      console.log("using git cache path " + this.getCachePath())
      env.GIT_CACHE_PATH = path.join(this.getCachePath())
    }

    if (this.sccache) {
      env.CC_WRAPPER = this.sccache
      if (path.basename(this.sccache) === 'ccache') {
        console.log('using ccache')
        env.CCACHE_CPP2 = 'yes'
        env.CCACHE_SLOPPINESS = 'pch_defines,time_macros,include_file_mtime'
        env.CCACHE_BASEDIR = this.srcDir
        env = this.addPathToEnv(env, path.join(this.srcDir, 'third_party', 'llvm-build', 'Release+Asserts', 'bin'))
      } else {
        console.log('using sccache')
      }
    }

    if (process.platform === 'linux') {
      env.LLVM_DOWNLOAD_GOLD_PLUGIN = '1'
    }

    return {
      env,
      stdio: 'inherit',
      cwd: this.srcDir,
      shell: true,
      git_cwd: '.',
    }
  },
})

Object.defineProperty(Config.prototype, 'outputDir', {
  get: function () {
    const baseDir = path.join(this.srcDir, 'out')
    if (this.__outputDir)
      return path.join(baseDir, this.__outputDir)
    let buildConfigDir = this.buildConfig
    if (this.targetArch && this.targetArch != 'x64') {
      buildConfigDir = buildConfigDir + '_' + this.targetArch
    }
    if (this.targetOS) {
      buildConfigDir = this.targetOS + "_" + buildConfigDir
    }

    return path.join(baseDir, buildConfigDir)
  },
  set: function (outputDir) { return this.__outputDir = outputDir },
})

module.exports = new Config
