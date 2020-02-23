#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
#define rep(i, st, n) for (int i = (st); i < (n); ++i)
#define repinv(i, st, n) for (int i = ((n)-1); i >= (st); --i)
#define MEM(a, b) memset(a, b, sizeof(a));

#define debug(x) std::cout << #x << ": " << x << endl
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define fileIO(in, out) freopen(in, "r", stdin); freopen(out, "w", stdout)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double ld;

mt19937 mrand(random_device{}());
const ll mod=1e9+7;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
//INT_MAX, ULLONG_MAX, LLONG_MAX or numeric_limits<int>::min()

inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

//------------------------------------------------------------------------//
int T;
const int maxn = 5e4+7;
int n;
//vector<int> es;
set<int> adjc[maxn];
set<int> dupc[maxn];
vector<pair<int,int>> G[maxn];
int tag[maxn];

void add_edge(int a, int b, int c)
{
  if(adjc[a].count(c)) dupc[a].insert(c);
  if(adjc[b].count(c)) dupc[b].insert(c);
  adjc[a].insert(c);
  adjc[b].insert(c);
  G[a].pb(mp(b, c));
  G[b].pb(mp(a, c));
}

bool dfs_dup(int u, int f, int c)
{
  bool ret = 1;
  tag[u] = 1; //from dup edges => not solution, will not mark p btw
  for(pii& e: G[u])if(e.X != f && tag[e.X]!=1) //if not checked by dup, should check
  {
    ret &= (e.Y != c); //bad in cut => no good points
    ret &= dfs_dup(e.X, u, e.Y);
  }
  return ret;
}

bool dfs_all(int u)
{
  bool ret = 1;
  //check dup color edges if wrong, should consider back to u so no mark tag here
  for(pii& e:G[u])if(dupc[u].count(e.Y) && tag[e.X]!=1) ret &= dfs_dup(e.X, u, e.Y); //check vis 1 here : no check => bug
	if(!ret) return 0;
	tag[u] = 2; //2nd phase, check other O(n) on dfs(all)
	for(pii& e:G[u])if(!tag[e.X]) ret &= dfs_all(e.X);
  return ret;
}

signed main()
{
  fastIO();

  cin >> n;
  int a, b, c;
  rep(i, 0, n-1)
  {
    cin >> a >> b >> c;
    add_edge(--a, --b, c);
  }
  bool allnodup = 1;
  rep(i, 0, n) allnodup &= (dupc[i].size() == 0);
  if(allnodup)
  {
    cout << n;
    rep(i, 1, n+1) cout << i << endl;
  }
  else
  {
    memset(tag, 0, sizeof(tag));
		int start = -1;//dup point to start to ensure start point will be checked
		rep(i, 0, n)if(dupc[i].size()) start = i;
    bool ok = dfs_all(start);
    if(ok)
    {
      vector<int> ans;
      rep(i, 0, n) if(tag[i] == 2) ans.pb(i+1);
      //sort(all(ans));
      cout << ans.size() << endl;
      for(int x : ans) cout << x << endl;
    }
    else cout << 0 << endl;
  }

  return 0;
}
