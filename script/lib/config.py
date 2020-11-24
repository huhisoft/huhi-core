#!/usr/bin/env python

import errno
import json
import os
import sys

PLATFORM = {
    'cygwin': 'win32',
    'darwin': 'darwin',
    'linux2': 'linux',
    'linux': 'linux',
    'win32': 'win32',
}[sys.platform]

SOURCE_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(__file__), '..', '..'))
CHROMIUM_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(__file__), '..', '..', '..'))
HUHI_CORE_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(__file__), '..', '..'))
HUHI_BROWSER_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(__file__), '..', '..', '..', '..'))
"""
SHALLOW_HUHI_BROWSER_ROOT assumes the huhi-browser directory is in the same
parent directory as huhi-core
"""
SHALLOW_HUHI_BROWSER_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(__file__), '..', '..', '..', 'huhi-browser'))
verbose_mode = False


def dist_dir(target_os, target_arch):
    return os.path.join(output_dir(target_os, target_arch), 'dist')


def output_dir(target_os, target_arch):
    target_os_prefix = ''
    if target_os in ['android', 'ios']:
        target_os_prefix = target_os + '_'

    target_arch_suffix = ''
    if target_arch != 'x64':
        target_arch_suffix = '_' + target_arch

    return os.path.join(CHROMIUM_ROOT, 'out', target_os_prefix + 'Release' + target_arch_suffix)


# Use huhi-browser/package.json version for canonical version definition
def huhi_browser_package():
    try:
        pjson = os.path.join(HUHI_BROWSER_ROOT, 'package.json')
        with open(pjson) as f:
            obj = json.load(f)
            return obj
    except IOError:
        # When IOError exception is caught, try SHALLOW_HUHI_BROWSER_ROOT next
        try:
            """
            SHALLOW_HUHI_BROWSER_ROOT assumes the huhi-browser directory is in the same
            parent directory as huhi-core
            """
            pjson = os.path.join(SHALLOW_HUHI_BROWSER_ROOT, 'package.json')
            with open(pjson) as f:
                obj = json.load(f)
                return obj
        except Exception as e:
            exit("Error: cannot open file package.json: {}".format(e))


def huhi_core_package():
    pjson = os.path.join(HUHI_CORE_ROOT, 'package.json')
    with open(pjson) as f:
        obj = json.load(f)
        return obj


def product_name():
    return (os.environ.get('npm_config_huhi_product_name') or
            huhi_core_package()['name'].split('-')[0])


def project_name():
    return (os.environ.get('npm_config_huhi_project_name') or
            huhi_core_package()['name'].split('-')[0])


def get_chrome_version():
    version = (os.environ.get('npm_config_huhi_version') or
               huhi_browser_package()['config']['projects']['chrome']['tag'])
    return version


def get_huhi_version():
    return 'v' + get_raw_version()


def get_raw_version():
    return (os.environ.get('npm_config_huhi_version') or
            huhi_browser_package()['version'])


def get_platform_key():
    if 'MAS_BUILD' in os.environ:
        return 'mas'
    else:
        return PLATFORM


def get_env_var(name):
    return (os.environ.get('HUHI_' + name) or
            os.environ.get('npm_config_HUHI_' + name, ''))


def enable_verbose_mode():
    print('Running in verbose mode')
    global verbose_mode
    verbose_mode = True


def is_verbose_mode():
    return verbose_mode
