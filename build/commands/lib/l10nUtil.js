/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */


/**
 * This file manages the following:
 * - Lists of files needed to be translated (Which is all top level GRD and JSON files)
 * - All mappings for auto-generated Huhi files from the associated Chromium files.
 * - Top level global string replacements, such as replacing Chromium with Huhi
 */

const path = require('path')
const fs = require('fs')
const chalk = require('chalk')
const { JSDOM } = require("jsdom")
const rootDir = require('./root')

// Change to `true` for verbose console log output of GRD traversal
const verboseLogFindGrd = false
const srcDir = path.join(rootDir, 'src')

// chromium_strings.grd and any of its parts files that we track localization for in transifex
// These map to huhi/app/resources/chromium_strings*.xtb
const chromiumStringsPath = path.resolve(path.join(srcDir, 'chrome', 'app', 'chromium_strings.grd'))
const huhiStringsPath = path.resolve(path.join(srcDir, 'huhi', 'app', 'huhi_strings.grd'))
const chromiumSettingsPartPath = path.resolve(path.join(srcDir, 'chrome', 'app', 'settings_chromium_strings.grdp'))
const huhiSettingsPartPath = path.resolve(path.join(srcDir, 'huhi', 'app', 'settings_huhi_strings.grdp'))

//Replace android strings.
const androidChromeStringsPath = path.resolve(path.join(srcDir, 'chrome', 'browser', 'ui', 'android', 'strings', 'android_chrome_strings.grd'))
const huhiAndroidChromeStringsPath = path.resolve(path.join(srcDir, 'huhi', 'browser', 'ui', 'android', 'strings', 'android_chrome_strings.grd'))

// component_chromium_strings.grd and any of its parts files that we track localization for in transifex
// These map to huhi/app/strings/components_chromium_strings*.xtb
const chromiumComponentsChromiumStringsPath = path.resolve(path.join(srcDir, 'components', 'components_chromium_strings.grd'))
const huhiComponentsHuhiStringsPath = path.resolve(path.join(srcDir, 'huhi', 'components', 'components_huhi_strings.grd'))

// components/component_strings.grd and any of its parts files that we track localization for in transifex
// These map to huhi/components/component_strings*.xtb
const chromiumComponentsStringsPath = path.resolve(path.join(srcDir, 'components', 'components_strings.grd'))
const huhiComponentsStringsPath = path.resolve(path.join(srcDir, 'huhi', 'components', 'components_strings.grd'))

// generated_resources.grd and any of its parts files that we track localization for in transifex
// There is also chromeos_strings.grdp, but we don't need to track it here because it is explicitly skipped in transifex.py
// These map to huhi/app/resources/generated_resoruces*.xtb
const chromiumGeneratedResourcesPath = path.resolve(path.join(srcDir, 'chrome', 'app', 'generated_resources.grd'))
const huhiGeneratedResourcesPath = path.resolve(path.join(srcDir, 'huhi', 'app', 'generated_resources.grd'))
const chromiumGeneratedResourcesExcludes = new Set(["chromeos_strings.grdp"])

// The following are not generated files but still need to be tracked so they get sent to transifex
// These xtb files don't need to be copied anywhere.
// huhi_generated_resources.grd maps to huhi/app/resources/huhi_generated_resources*.xtb,
// huhi_components_strings.grd maps to huhi/components/resources/strings/huhi_components_resources*.xtb
// messages.json localization is handled inside of huhi-extension.
const huhiSpecificGeneratedResourcesPath = path.resolve(path.join(srcDir, 'huhi', 'app', 'huhi_generated_resources.grd'))
const huhiResourcesComponentsStringsPath = path.resolve(path.join(srcDir, 'huhi', 'components', 'resources', 'huhi_components_strings.grd'))
const huhiExtensionMessagesPath = path.resolve(path.join(srcDir, 'huhi', 'components', 'huhi_extension', 'extension', 'huhi_extension', '_locales', 'en_US', 'messages.json'))
const huhiRewardsExtensionMessagesPath = path.resolve(path.join(srcDir, 'huhi', 'components', 'huhi_rewards', 'resources', 'extension', 'huhi_rewards', '_locales', 'en_US', 'messages.json'))
const huhiAndroidHuhiStringsPath = path.resolve(path.join(srcDir, 'huhi', 'browser', 'ui', 'android', 'strings', 'android_huhi_strings.grd'))

const srcGit = path.resolve(path.join(srcDir, '.git'))

// Helper function to find all grdp parts in a grd.
function getGrdPartsFromGrd(path) {
  const grd = new JSDOM(fs.readFileSync(path, 'utf8'))
  const partTags = grd.window.document.getElementsByTagName("part")
  let parts = new Array()
  for (const partTag of partTags) {
    parts.push(partTag.getAttribute('file'));
  }
  return parts
}

// Helper function to create a mapping for grd and all of its grdp parts.
function AddGrd(chromiumPath, huhiPath, exclude = new Set()) {
  if (!fs.existsSync(srcGit)) {
    // Chromium repository has not been initialized yet.
    return
  }
  if (verboseLogFindGrd)
    console.log("Adding mappings for GRD: " + chromiumPath)
  let mapping = {
    [chromiumPath]: huhiPath
  }
  if (!fs.existsSync(chromiumPath)) {
    const err = new Error(`AddGrd: Error. File not found at path "${chromiumPath}"`)
    console.error(err)
    return
  }
  const grdps = getGrdPartsFromGrd(chromiumPath)
  if (grdps.length) {
    const chromiumDir = path.dirname(chromiumPath)
    const huhiDir = path.dirname(huhiPath)
    for (const grdp of grdps) {
      if (exclude.has(grdp)) {
        continue
      }
      mapping[path.resolve(path.join(chromiumDir, grdp))] = path.resolve(path.join(huhiDir, grdp))
    }
    if (verboseLogFindGrd)
      console.log("  - Added " + (Object.keys(mapping).length - 1) + " GRDP.")
  }
  return mapping
}

// Add all GRD mappings here.
// Huhi specific only grd and grdp files should NOT be added.
// Using AddGrd will add GRD and all of its GRDPs.
// TODO(petemill): Do not do this file processing in the module root, do it behind a function.
console.log(chalk.italic('Recursing through GRD to find GRDP files...'))
const grdsWithAutoAddedGrdps = {
  ...AddGrd(chromiumComponentsStringsPath, huhiComponentsStringsPath),
  ...AddGrd(chromiumGeneratedResourcesPath, huhiGeneratedResourcesPath, chromiumGeneratedResourcesExcludes),
  ...AddGrd(androidChromeStringsPath, huhiAndroidChromeStringsPath)
}
console.log(chalk.italic('Done recursing through GRD to find GRDP files.'))

// When adding new grd or grdp files, never add a grdp part path without a parent grd path.
// Group them with a leading and trailing newline to keep this file organized.
// The first 3 are added explicitly because we change the file names.
const chromiumToAutoGeneratedHuhiMapping = {
  [chromiumStringsPath]: huhiStringsPath,
  [chromiumSettingsPartPath]: huhiSettingsPartPath,

  [chromiumComponentsChromiumStringsPath]: huhiComponentsHuhiStringsPath,

  ...grdsWithAutoAddedGrdps
}

// Same as with chromiumToAutoGeneratedHuhiMapping but maps in the opposite direction
module.exports.autoGeneratedHuhiToChromiumMapping = Object.keys(chromiumToAutoGeneratedHuhiMapping)
    .reduce((obj, key) => ({ ...obj, [chromiumToAutoGeneratedHuhiMapping[key]]: key }), {})

// All paths which are not generated
module.exports.huhiNonGeneratedPaths = [
  huhiSpecificGeneratedResourcesPath, huhiResourcesComponentsStringsPath, huhiExtensionMessagesPath, huhiRewardsExtensionMessagesPath, huhiAndroidHuhiStringsPath
]

// All paths which are generated
module.exports.huhiAutoGeneratedPaths = Object.values(chromiumToAutoGeneratedHuhiMapping)

// Huhi specific strings and Chromium mapped Huhi strings will be here.
// But you only need to add the Huhi specific strings manually here.
module.exports.allHuhiPaths = module.exports.huhiNonGeneratedPaths.concat(module.exports.huhiAutoGeneratedPaths)

// Get all GRD and JSON paths whether they are generatd or not
// Push and pull scripts for l10n use this.
// Transifex manages files per grd and not per grd or grdp.
// This is because only 1 xtb is created per grd per locale even if it has multiple grdp files.
module.exports.huhiTopLevelPaths = module.exports.allHuhiPaths.filter((x) => ['grd', 'json'].includes(x.split('.').pop()))

// ethereum-remote-client path relative to the Huhi paths
module.exports.ethereumRemoteClientPaths = [
  '../../../ethereum-remote-client/app/_locales/en/messages.json',
  '../../../ethereum-remote-client/huhi/app/_locales/en/messages.json'
]

// Helper functions that's, for a given pair of chromium to huhi GRD mapping
// from the supplied map, determines which GRDP parts are no longer present in
// the chromium GRD file.
function getRemovedGRDParts(mapping) {
  let removedMap = new Map()
  for (const [sourcePath, destPath] of Object.entries(mapping)) {
    if (path.extname(destPath) === ".grd") {
      const huhiGRDPs = getGrdPartsFromGrd(destPath)
      const chromiumGRDPs = getGrdPartsFromGrd(sourcePath)
      let removed = new Set()
      for (i = 0; i < huhiGRDPs.length; i++) {
        if (!chromiumGRDPs.includes(huhiGRDPs[i])) {
          removed.add(huhiGRDPs[i])
        }
      }
      if (removed.size) {
        removedMap.set(destPath, removed)
      }
    }
  }
  return removedMap
}

// Helper function to pretty print removed GRDP file names.
module.exports.logRemovedGRDParts = function (mapping) {
  if (mapping.size) {
    console.log("\n**************************************************************************")
    console.log("The following GRDP files are no longer in the corresponding Chromium GRDs:\n")
    for (const [grd, grdps] of mapping.entries()) {
      console.log("  From " + grd + ":")
      for (const grdp of grdps) {
        console.log("    - " + grdp)
      }
    }
  }
}

// This simply reads Chromium files that are passed to it and replaces branding strings
// with Huhi specific branding strings.
// Do not use this for filtering XML, instead use chromium-rebase-l10n.py.
// Only add idempotent replacements here (i.e. don't append replace A with AX here)
module.exports.rebaseHuhiStringFilesOnChromiumL10nFiles = async function (path) {
  const removedMap = getRemovedGRDParts(grdsWithAutoAddedGrdps)
  const ops = Object.entries(chromiumToAutoGeneratedHuhiMapping).map(async ([sourcePath, destPath]) => {
    let contents = await new Promise(resolve => fs.readFile(sourcePath, 'utf8', (err, data) => resolve(data)))
    await new Promise(resolve => fs.writeFile(destPath, contents, 'utf8', resolve))
  })
  await Promise.all(ops)
  return removedMap
}
