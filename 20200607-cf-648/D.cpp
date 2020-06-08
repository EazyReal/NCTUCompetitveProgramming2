#include <bits/stdc++.h>
#define LOCAL
using namespace std;

#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
#define rep(i, st, n) for (int i = (st); i < (n); ++i)
#define repinv(i, st, n) for (int i = ((n)-1); i >= (st); --i)
#define MEM(a, b) memset(a, b, sizeof(a));
#ifdef LOCAL
#define debug(x) std::cerr << #x << ": " << x << endl
#else
#define debug(x) 860111
#endif
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define fileIO(in, out) freopen(in, "r", stdin); freopen(out, "w", stdout)

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double ld;

//mt19937 mrand(random_device{}());
//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll mod=1e9+7;
//int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
pii operator+(const pii&x, const pii&y) { return mp(x.X+y.X, x.Y+y.Y);}
pii operator-(const pii&x, const pii&y) { return mp(x.X-y.X, x.Y-y.Y);}
//INT_MAX, ULLONG_MAX, LLONG_MAX or numeric_limits<int>::min()

inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

//------------------------------------------------------------------------//
int T;
const int maxn = 50+7;
int n, m;
char a[maxn][maxn];
bool vis[maxn][maxn];
int G, B;

pii d[4] = {{0,1},{1,0}, {-1,0}, {0, -1}};

bool inr(pii xy)
{
  return xy.X >=0 && xy.Y>=0 && xy.X<n &&xy.Y<m;
}

void dfs(pii u)
{
  vis[u.X][u.Y] = 1;
  if(a[u.X][u.Y] == 'G') G++;
  if(a[u.X][u.Y] == 'B') B++;
  rep(i, 0, 4)
  {
    pii v = u+d[i];
    if(!inr(v) || a[v.X][v.Y] == '#' || vis[v.X][v.Y] == 1) continue;
    dfs(v);
  }
}


//check T
void solve()
{
  cin >> n >> m;
  int good = 0;
  rep(i, 0, n)rep(j, 0, m)
  {
    cin >> a[i][j];
    if(a[i][j]=='G') good++;
  }
  //bool suc = 1;
  //set B aside to wall
  rep(i, 0, n)rep(j, 0, m)if(a[i][j] == 'B')
  {
    rep(di, 0, 4)
    {
      pii nxy = pii({i,j}) + d[di];
      if(inr(nxy))
      {
        //if(a[nx][ny] == '#' || a[nx][ny] == 'B' || a[nx][ny] == ) continue;
        //else
        if(a[nxy.X][nxy.Y] == '.') a[nxy.X][nxy.Y] = '#'; 
      }
    }
  }
  //see if stisfy
  rep(i, 0, n)rep(j, 0, m) vis[i][j] = 0;
  G = 0;
  B = 0;
  if(a[n-1][m-1] != '#') dfs({n-1,m-1});
  cout << (G== good && B == 0 ? "Yes" : "No" ) << endl;

  return;
}


//g++ -o out -std=c++11 A.cpp

signed main()
{
  fastIO();
  T = 1;
  cin >> T; //this
  rep(tc, 1, T+1)
  {
    //cout << "Case #" << tc << ": ";
    solve();
  }
  return 0;
}
