const path = require('path')
const config = require('../lib/config')
const util = require('../lib/util')
const {huhiTopLevelPaths, ethereumRemoteClientPaths} = require('./l10nUtil')

const pullL10n = (options) => {
  const cmdOptions = config.defaultOptions
  cmdOptions.cwd = config.huhiCoreDir
  if (options.extension) {
    if (options.extension === 'ethereum-remote-client') {
      ethereumRemoteClientPaths.forEach((sourceStringPath) => {
        util.run('python', ['script/pull-l10n.py', '--source_string_path', sourceStringPath], cmdOptions)
      })
      return
    }
    console.error('Unknown extension: ', options.extension)
    process.exit(1)
  }

  // Revert to originals before string replacement because original grd(p)s are
  // overwritten with modified versions from ./src/huhi during build.
  const srcDir = config.srcDir
  const targetFilesForReset = [ "*.grd", "*.grdp", "*.xtb" ]
  targetFilesForReset.forEach((targetFile) => {
    util.run('git', ['checkout', '--', targetFile], { cwd: srcDir })
  })

  huhiTopLevelPaths.forEach((sourceStringPath) => {
    if (!options.grd_path || sourceStringPath.endsWith(path.sep + options.grd_path))
      util.run('python', ['script/pull-l10n.py', '--source_string_path', sourceStringPath], cmdOptions)
  })
}

module.exports = pullL10n
