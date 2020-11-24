# Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Huhi Software
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/. */

import os

HUHI_THIRD_PARTY_DIRS = [
    'vendor',
]

ANDROID_ONLY_PATHS = []

DESKTOP_ONLY_PATHS = []


def AddHuhiCredits(prune_paths, special_cases, prune_dirs, additional_paths):
    # Exclude these specific paths from needing a README.chromium file.
    prune_paths.update([
        # Formerly external Huhi code which has moved to huhi-core
        # (i.e these are already covered by the Huhi Browser license notice).
        os.path.join('huhi', 'vendor', 'bat-native-ads'),
        os.path.join('huhi', 'vendor', 'bat-native-ledger'),
        os.path.join('huhi', 'vendor', 'huhi-ios'),
        os.path.join('huhi', 'vendor', 'huhi_base'),

        # Huhi overrides to third-party code, also covered by main notice.
        os.path.join('huhi', 'third_party', 'android_deps'),
        os.path.join('huhi', 'third_party', 'blink'),
        os.path.join('huhi', 'third_party', 'libaddressinput'),

        # Build dependencies which don't end up in the binaries.
        os.path.join('huhi', 'vendor', 'depot_tools'),
        os.path.join('huhi', 'vendor', 'gn-project-generators')
    ])

    # Add the licensing info that would normally be in a README.chromium file.
    # This is for when we pull in external repos directly.
    special_cases.update({
        os.path.join('huhi', 'vendor', 'adblock_rust_ffi'): {
            "Name": "adblock-rust-ffi",
            "URL": "https://github.com/huhisoftware/adblock-rust-ffi",
            "License": "MPL-2.0",
        },
        os.path.join('huhi', 'vendor', 'bat-native-anonize'): {
            "Name": "bat-native-anonize",
            "URL": "https://github.com/huhisoftware/bat-native-anonize",
            "License": "Apache-2.0",
            "License File": "/huhi/vendor/bat-native-anonize/LICENSE.txt",
        },
        os.path.join('huhi', 'vendor', 'bat-native-rapidjson'): {
            "Name": "RapidJSON",
            "URL": "https://github.com/huhisoftware/bat-native-rapidjson",
            "License": "MIT",
            "License File": "/huhi/vendor/bat-native-rapidjson/license.txt",
        },
        os.path.join('huhi', 'vendor', 'bat-native-tweetnacl'): {
            "Name": "TweetNaCl",
            "URL": "https://github.com/huhisoftware/bat-native-tweetnacl",
            "License": "MPL-2.0",
        },
        os.path.join('huhi', 'vendor', 'bat-native-usermodel'): {
            "Name": "BAT Native User Model",
            "URL": "https://github.com/huhisoftware/bat-native-usermodel",
            "License": "MPL-2.0",
        },
        os.path.join('huhi', 'vendor', 'bip39wally-core-native'): {
            "Name": "libwally-core",
            "URL": "https://github.com/huhisoftware/bat-native-bip39wally-core",
            "License": "MIT",
        },
        os.path.join('huhi', 'vendor', 'boto'): {
            "Name": "boto",
            "URL": "https://github.com/boto/boto",
            "License": "MIT",
        },
        os.path.join('huhi', 'vendor', 'huhi-extension'): {
            "Name": "Huhi Only Extension",
            "URL": "https://github.com/huhisoftware/huhi-extension",
            "License": "MPL-2.0",
        },
        os.path.join('huhi', 'vendor', 'challenge_bypass_ristretto_ffi'): {
            "Name": "challenge-bypass-ristretto-ffi",
            "URL": "https://github.com/huhisoftware/challenge-bypass-ristretto-ffi",
            "License": "MPL-2.0",
        },
        os.path.join('huhi', 'vendor', 'extension-whitelist'): {
            "Name": "extension-whitelist",
            "URL": "https://github.com/huhisoftware/extension-whitelist",
            "License": "MPL-2.0",
        },
        os.path.join('huhi', 'vendor', 'hashset-cpp'): {
            "Name": "Hash Set",
            "URL": "https://github.com/huhisoftware/hashset-cpp",
            "License": "MPL-2.0",
        },
        os.path.join('huhi', 'vendor', 'omaha'): {
            "Name": "Omaha",
            "URL": "https://github.com/huhisoftware/omaha",
            "License": "Apache-2.0",
            "License File": "/huhi/vendor/omaha/LICENSE.txt",
        },
        os.path.join('huhi', 'vendor', 'python-patch'): {
            "Name": "Python Patch",
            "URL": "https://github.com/huhisoftware/python-patch",
            "License": "MIT",
            "License File": "/huhi/vendor/python-patch/doc/LICENSE",
        },
        os.path.join('huhi', 'vendor', 'requests'): {
            "Name": "Requests",
            "URL": "https://github.com/psf/requests",
            "License": "Apache-2.0",
        },
        os.path.join('huhi', 'vendor', 'sparkle'): {
            "Name": "Sparkle",
            "URL": "https://github.com/huhisoftware/Sparkle",
            "License": "MIT",
        },
    })

    # Don't recurse into these directories looking for third-party code.
    prune_list = list(prune_dirs)
    prune_list += [
        'chromium_src',  # Huhi's overrides, covered by main notice.
        'node_modules',  # See huhi/third_party/npm-* instead.
    ]
    prune_dirs = tuple(prune_list)

    # Look for a README.chromium file directly inside these directories.
    # This is for directories which include third-party code that isn't
    # contained under a "third_party" or "vendor" directory.
    additional_list = list(additional_paths)
    additional_list += [
        os.path.join('huhi', 'components', 'huhi_prochlo'),
        os.path.join('huhi', 'components', 'huhi_new_tab_ui', 'data'),
    ]
    additional_paths = tuple(additional_list)

    return (prune_dirs, additional_paths)


def CheckHuhiMissingLicense(target_os, path, error):
    if path.startswith('huhi'):
        if (target_os == 'android'):
            if path in DESKTOP_ONLY_PATHS:
                return  # Desktop failures are not relevant on Android.
        else:
            if path in ANDROID_ONLY_PATHS:
                return  # Android failures are not relevant on desktop.
        raise error
