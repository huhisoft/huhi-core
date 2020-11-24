// Before adding to this list, get approval from the security team
module.exports = [
  'http://update.googleapis.com/service/update2', // allowed because it 307's to go-updater.huhisoft.com. should never actually connect to googleapis.com.
  'https://update.googleapis.com/service/update2', // allowed because it 307's to go-updater.huhisoft.com. should never actually connect to googleapis.com.
  'https://safebrowsing.googleapis.com/v4/threatListUpdates', // allowed because it 307's to safebrowsing.huhisoft.com
  'https://clients2.googleusercontent.com/crx/blobs/',
  'http://dl.google.com/', // allowed because it 307's to redirector.huhisoft.com
  'https://dl.google.com/', // allowed because it 307's to redirector.huhisoft.com
  'https://no-thanks.invalid/', // fake gaia URL
  'https://go-updater.huhisoft.com/',
  'https://safebrowsing.huhisoft.com/',
  'https://huhi-core-ext.s3.huhisoft.com/',
  'https://laptop-updates.huhisoft.com/',
  'https://static.huhisoft.com/',
  'https://static1.huhisoft.com/',
  'http://componentupdater.huhisoft.com/service/update2', // allowed because it 307's to https://componentupdater.huhisoft.com
  'https://componentupdater.huhisoft.com/service/update2',
  'https://crlsets.huhisoft.com/',
  'https://crxdownload.huhisoft.com/crx/blobs/',
  'https://ledger.mercury.basicattentiontoken.org/',
  'https://ledger-staging.mercury.basicattentiontoken.org/',
  'https://balance.mercury.basicattentiontoken.org/',
  'https://balance-staging.mercury.basicattentiontoken.org/',
  'https://publishers.basicattentiontoken.org/',
  'https://publishers-staging.basicattentiontoken.org/',
  'https://updates.huhisoft.com/',
  'https://publishers-distro.basicattentiontoken.org/',
  'https://publishers-staging-distro.basicattentiontoken.org/',
  'https://p3a.huhisoft.com/',
  'https://dns.google/dns-query', // needed for DoH on Mac build machines
  'https://chrome.cloudflare-dns.com/dns-query', // needed for DoH on Mac build machines
  'https://tor.huhisoft.com/', // for fetching tor client updater component
  'https://redirector.huhisoft.com/',
  'https://sync-v2.huhisoft.com/v2', // huhi sync v2 production
  'https://sync-v2.huhisoft.com/v2', // huhi sync v2 staging
  'https://sync-v2.huhi.software/v2', // huhi sync v2 dev
]
