use_relative_paths = True

deps = {
  "vendor/adblock_rust_ffi": "https://github.com/huhisoftware/adblock-rust-ffi.git@779287f88a9bd8a3bd02968f6962e1a1b96d0d50",
  "vendor/extension-whitelist": "https://github.com/huhisoftware/extension-whitelist.git@90724fdfaffdbae218f42092136d70477327ea14",
  "vendor/hashset-cpp": "https://github.com/huhisoftware/hashset-cpp.git@addf4e6fbb165e73f382307e4cd690e39739f6b4",
  "vendor/requests": "https://github.com/kennethreitz/requests@e4d59bedfd3c7f4f254f4f5d036587bcd8152458",
  "vendor/boto": "https://github.com/boto/boto@f7574aa6cc2c819430c1f05e9a1a1a666ef8169b",
  "vendor/python-patch": "https://github.com/huhisoftware/python-patch@0608039ee4ca09edc6da9db7900f2a661643b065",
  "vendor/omaha":  "https://github.com/huhisoftware/omaha.git@0b28fca323c226ba058f781d9c49639619f406a9",
  "vendor/sparkle": "https://github.com/huhisoftware/Sparkle.git@ddeeb6058826b2e32e736b4935c4ecdfc183418f",
  "vendor/bat-native-rapidjson": "https://github.com/huhisoftware/bat-native-rapidjson.git@0fc530efce2122d2939b94e38e38a814d17b54bd",
  "vendor/bip39wally-core-native": "https://github.com/huhisoftware/bip39wally-core-native.git@4b380f91b731e3adac5b14b1ff2c11265fd7d12b",
  "vendor/bat-native-anonize": "https://github.com/huhisoftware/bat-native-anonize.git@fa5dd7ec683a970c956f60b16cd6750ccc1660de",
  "vendor/bat-native-tweetnacl": "https://github.com/huhisoftware/bat-native-tweetnacl.git@ef298e422debded00301a6a6981793fa3d440c54",
  "vendor/bat-native-usermodel": "https://github.com/huhisoftware/bat-native-usermodel.git@a9d6e8bdc4039f5dd6ec8e3ff2bafb016f76a5c0",
  "vendor/challenge_bypass_ristretto_ffi": "https://github.com/huhisoftware/challenge-bypass-ristretto-ffi.git@0637db85bda3beb7d5905871a74f324c34753002",
  "vendor/gn-project-generators": "https://github.com/huhisoftware/gn-project-generators.git@62e9e1989bb13f2334fea476658ca36fc6c9a740",
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
    # Download rust deps if necessary for iOS
    'name': 'download_rust_deps',
    'pattern': '.',
    'condition': 'checkout_ios',
    'action': ['vpython3', 'script/download_rust_deps.py', '--platform', 'ios'],
  },
  {
    # Download rust deps if necessary for Linux, macOS, Windows
    'name': 'download_rust_deps',
    'pattern': '.',
    'condition': 'not checkout_android and not checkout_ios',
    'action': ['vpython3', 'script/download_rust_deps.py'],
  },
  {
    'name': 'generate_licenses',
    'pattern': '.',
    'action': ['python', 'script/generate_licenses.py'],
  },
]
