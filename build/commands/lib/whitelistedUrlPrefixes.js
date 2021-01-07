// Before adding to this list, get approval from the security team
module.exports = [
  'http://update.googleapis.com/service/update2', // allowed because it 307's to go-updater.hnq.vn. should never actually connect to googleapis.com.
  'https://update.googleapis.com/service/update2', // allowed because it 307's to go-updater.hnq.vn. should never actually connect to googleapis.com.
  'https://safebrowsing.googleapis.com/v4/threatListUpdates', // allowed because it 307's to safebrowsing.hnq.vn
  'https://clients2.googleusercontent.com/crx/blobs/',
  'http://dl.google.com/', // allowed because it 307's to redirector.hnq.vn
  'https://dl.google.com/', // allowed because it 307's to redirector.hnq.vn
  'https://no-thanks.invalid/', // fake gaia URL
  'https://go-updater.hnq.vn/',
  'https://safebrowsing.hnq.vn/',
  'https://huhi-core-ext.s3.hnq.vn/',
  'https://updates.hnq.vn/',
  'https://static.hnq.vn/',
  'https://static1.hnq.vn/',
  'http://componentupdater.hnq.vn/service/update2', // allowed because it 307's to https://componentupdater.hnq.vn
  'https://componentupdater.hnq.vn/service/update2',
  'https://crlsets.hnq.vn/',
  'https://crxdownload.hnq.vn/crx/blobs/',
  'https://ledger.mercury.basicattentiontoken.org/',
  'https://ledger-staging.mercury.basicattentiontoken.org/',
  'https://balance.mercury.basicattentiontoken.org/',
  'https://balance-staging.mercury.basicattentiontoken.org/',
  'https://publishers.basicattentiontoken.org/',
  'https://publishers-staging.basicattentiontoken.org/',
  'https://updates.huhisoftware.com/',
  'https://publishers-distro.basicattentiontoken.org/',
  'https://publishers-staging-distro.basicattentiontoken.org/',
  'https://p3a.hnq.vn/',
  'https://dns.google/dns-query', // needed for DoH on Mac build machines
  'https://chrome.cloudflare-dns.com/dns-query', // needed for DoH on Mac build machines
  'https://tor.huhisoftware.com/', // for fetching tor client updater component
  'https://redirector.hnq.vn/',
  'https://sync-v2.hnq.vn/v2', // huhi sync v2 production
  'https://sync-v2.huhisoftware.com/v2', // huhi sync v2 staging
  'https://sync-v2.huhi.software/v2', // huhi sync v2 dev
  'https://variations.hnq.vn/seed',
  'https://huhi-today-cdn.hnq.vn/', // Huhi Today (production)
  'https://pcdn.hnq.vn/', // Huhi's Privacy-focused CDN
]
