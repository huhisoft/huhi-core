# BAT Ads

## API

Public facing API documentation can be found in `ads.h` and `ads_client.h`

## Command-line Switches

Use production Ads server. Default for official builds, i.e. Release

```
--huhi-ads-production
```

Use staging Ads server. Default for non official builds, i.e. Debug

```
--huhi-ads-staging
```

Use development Ads server.

```
--huhi-ads-development
```

Collect initial activity after 25 seconds instead of 1 hour as defined by
`kDebugOneHourInSeconds` in `static_values.h`. Download the catalog after 15
minutes instead of 2 hours as defined by `kDebugCatalogPing` in
`static_values.h`

```
--huhi-ads-debug
```

## Unit Tests

```
npm run test -- huhi_unit_tests --filter=BatAds*
```
