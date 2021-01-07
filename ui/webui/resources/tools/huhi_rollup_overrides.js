const path = require('path');

module.exports = {
  huhiResolveId: function (params, source, origin, relativePath, joinPaths, combinePaths, chromeResourcesUrl, schemeRelativeResourcesUrl) {
    const {srcPath, genPath, excludes} = params;
    const resourcesSrcPath = joinPaths(srcPath, 'ui/webui/resources/');
    const resourcesGenPath = joinPaths(genPath, 'ui/webui/resources/');
    const huhiResourcesUrl = 'chrome://huhi-resources/';
    // sources not referencing `huhi-resources`
    if (source.startsWith(chromeResourcesUrl) ||
        source.startsWith(schemeRelativeResourcesUrl) ||
       (!!origin && origin.startsWith(resourcesSrcPath) && source.indexOf(huhiResourcesUrl) === -1) ||
       (!!origin && origin.startsWith(resourcesGenPath) && source.indexOf(huhiResourcesUrl) === -1))
    {
      return undefined;
    }
    // sources referencing `huhi-resources`
    const huhiResourcesSrcPath = joinPaths(srcPath, 'huhi/ui/webui/resources/')
    const huhiResourcesGenPath = joinPaths(genPath, 'huhi/ui/webui/resources/')
    let pathFromHuhiResources = ''
    if (source.startsWith(huhiResourcesUrl)) {
      pathFromHuhiResources = source.slice(huhiResourcesUrl.length)
    } else if (!!origin && origin.startsWith(huhiResourcesSrcPath)) {
      pathFromHuhiResources = combinePaths(relativePath(huhiResourcesSrcPath, origin), source);
    } else if (!!origin && origin.startsWith(huhiResourcesGenPath)) {
      pathFromHuhiResources = combinePaths(relativePath(huhiResourcesGenPath, origin), source);
    } else {
      return undefined;
    }
    // avoid excludes and non-generated files
    const fullPath = chromeResourcesUrl + pathFromHuhiResources;
    if (excludes.includes(fullPath)) {
      return {id: fullPath, external: true};
    }
    // JS compiled into gen directory
    if (pathFromHuhiResources.endsWith('.js')) {
      return joinPaths(huhiResourcesGenPath, pathFromHuhiResources);
    }
    return joinPaths(huhiResourcesSrcPath, pathFromHuhiResources);
  }
}
