use_relative_paths = True

deps = {
  "vendor/adblock_rust_ffi": "https://github.com/huhisoftware/adblock-rust-ffi.git",
  "vendor/extension-whitelist": "https://github.com/huhisoftware/extension-whitelist.git",
  "vendor/hashset-cpp": "https://github.com/huhisoftware/hashset-cpp.git",
  "vendor/requests": "https://github.com/huhisoftware/requests.git",
  "vendor/boto": "https://github.com/huhisoftware/boto.git",
  "vendor/python-patch": "https://github.com/huhisoftware/python-patch",
  "vendor/omaha":  "https://github.com/huhisoftware/omaha.git",
  "vendor/sparkle": "https://github.com/huhisoftware/Sparkle.git",
  "vendor/bat-native-rapidjson": "https://github.com/huhisoftware/bat-native-rapidjson.git",
  "vendor/bip39wally-core-native": "https://github.com/huhisoftware/bip39wally-core-native.git",
  "vendor/bat-native-anonize": "https://github.com/huhisoftware/bat-native-anonize.git",
  "vendor/bat-native-tweetnacl": "https://github.com/huhisoftware/bat-native-tweetnacl.git",
  "vendor/bat-native-usermodel": "https://github.com/huhisoftware/bat-native-usermodel.git",
  "vendor/challenge_bypass_ristretto_ffi": "https://github.com/huhisoftware/challenge-bypass-ristretto-ffi.git",
  "vendor/gn-project-generators": "https://github.com/huhisoftware/gn-project-generators.git",
}

hooks = [
  {
    'name': 'bootstrap',
    'pattern': '.',
    'action': ['python', 'script/bootstrap.py'],
  },
  {
    # Download rust deps if necessary for Android
    'name': 'download_rust_deps',
    'pattern': '.',
    'condition': 'checkout_android',
    'action': ['vpython3', 'script/download_rust_deps.py', '--platform', 'android'],
  },
  {
    # Download rust deps if necessary for macOS, Windows and Linux
    'name': 'download_rust_deps',
    'pattern': '.',
    'condition': 'not checkout_android',
    'action': ['vpython3', 'script/download_rust_deps.py'],
  },
  {
    'name': 'generate_licenses',
    'pattern': '.',
    'action': ['python', 'script/generate_licenses.py'],
  },
]
