const path = require('path')

const config = require('../lib/config')
const util = require('../lib/util')

const getTestBinary = (suite) => {
  return (process.platform === 'win32') ? `${suite}.exe` : suite
}

const getTestsToRun = (config, suite) => {
  testsToRun = [suite]
  if (suite === 'huhi_unit_tests') {
    if (config.targetOS !== 'android') {
      testsToRun.push('huhi_installer_unittests')
    } else {
      testsToRun.push('bin/run_huhi_public_test_apk')
    }
  }
  return testsToRun
}

const test = (suite, buildConfig = config.defaultBuildConfig, options) => {
  config.buildConfig = buildConfig
  config.update(options)

  const huhiArgs = [
    '--enable-logging=stderr'
  ]

  // Android doesn't support --v
  if (config.targetOS !== 'android') {
    huhiArgs.push('--v=' + options.v)

    if (options.vmodule) {
      huhiArgs.push('--vmodule=' + options.vmodule)
    }
  }

  if (options.filter) {
    huhiArgs.push('--gtest_filter=' + options.filter)
  }

  if (options.run_disabled_tests) {
    huhiArgs.push('--gtest_also_run_disabled_tests')
  }

  if (options.output) {
    huhiArgs.push('--gtest_output=xml:' + options.output)
  }

  if (options.disable_huhi_extension) {
    huhiArgs.push('--disable-huhi-extension')
  }

  if (options.single_process) {
    huhiArgs.push('--single_process')
  }

  if (options.test_launcher_jobs) {
    huhiArgs.push('--test-launcher-jobs=' + options.test_launcher_jobs)
  }

  // Build the tests
  if (suite === 'huhi_unit_tests' || suite === 'huhi_browser_tests') {
    util.run('ninja', ['-C', config.outputDir, "huhi/test:" + suite], config.defaultOptions)
  } else {
    util.run('ninja', ['-C', config.outputDir, suite], config.defaultOptions)
  }

  if (config.targetOS === 'ios') {
    util.run(path.join(config.outputDir, "iossim"), [
      path.join(config.outputDir, `${suite}.app`),
      path.join(config.outputDir, `${suite}.app/PlugIns/${suite}_module.xctest`)
    ], config.defaultOptions)
  } else {
    // Run the tests
    getTestsToRun(config, suite).forEach((testSuite) => {
      if (options.output) {
        huhiArgs.splice(huhiArgs.indexOf('--gtest_output=xml:' + options.output, 1))
        huhiArgs.push(`--gtest_output=xml:${testSuite}.xml`)
      }
      if (config.targetOS === 'android') {
        // Specify emulator to run tests on
        huhiArgs.push(`--avd-config tools/android/avd/proto/generic_android28.textpb`)
      }
      util.run(path.join(config.outputDir, getTestBinary(testSuite)), huhiArgs, config.defaultOptions)
    })
  }
}

module.exports = test
