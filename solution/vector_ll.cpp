#include<bits/stdc++.h>
#define int long long
using namespace std;

#define pb push_back

const int MAXN = 1e6+6;
using ll = long long;
int N, M;
int n_up = 0;

struct Classmate {
  ll p;
  vector<ll> record;
  int rank; // classmate -> rank
  int last_up = 0;
  int c1 = -1, c2 = -1;
  ll spending = 0;
  // Classmate(_p, _rank, _last_up) : p(_p), rank(_rank), last_up(_last_up) {}
  ll update() {
    p += (ll)(N - rank) * (n_up - last_up);
    assert((ll)(N - rank) * (n_up - last_up) >= 0);
    last_up = n_up;
    return p;
  }
  void top_up(ll power) {
    p += power;
    record.pb(power);
    
    c1++;
    spending += power;
    if (c1 - c2 > M) {
      spending -= (record[++c2]);
      assert(c1 - c2 == M);
    }
  }
};
Classmate player[MAXN+1];
int rank_table[MAXN+1]; // rank -> classmate

void swap_rank(int a, int b) {
  swap(player[a].rank, player[b].rank);
  rank_table[player[a].rank] = a;
  rank_table[player[b].rank] = b;
}

int binary_search(ll q) {
  if (q > player[rank_table[1]].update()) return -1;
  int l = 1, r = N+1;
  while (r-l > 1) {
    int m = (l+r)/2;
    ll power = player[rank_table[m]].update();
    // cout << m << ": " << rank_table[m] << "(" << power << ")\n";
    if (power < q) r = m;
    else l = m;
  }
  return l;
}

void incident() {
  int type;
  cin >> type;
  if (type == 1) {
    int a; cin >> a;
    int rank = player[a].rank;
    if (rank == 1) return;
    int pre_rank = rank-1;
    int pre = rank_table[pre_rank];
    ll diff = player[pre].update() - player[a].update();
    player[a].top_up(diff);
    swap_rank(a, pre);
  } else if (type == 2) {
    n_up++;
  } else if (type == 3) {
    ll q; cin >> q;
    int rank = binary_search(q);
    if (rank == -1) cout << "0 0\n";
    else cout << rank << " " << rank_table[rank] << '\n';
  } else if (type == 4) {
    int b; cin >> b;
    cout << player[b].spending << '\n';
  } else cout << "ERROR\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> N >> T >> M;
  for (int i = 1; i <= N; i++) {
    cin >> player[i].p;
    player[i].rank = i;
    rank_table[i] = i;
  }
  for (int i = 1; i < N; i++) assert(player[i].p >= player[i+1].p);
  while (T--) {
    incident();
  }
  cout << '\n';
  for (int i = 1; i <= N; i++) {
    cout << player[i].record.size();
    for (ll j : player[i].record) cout << ' ' << j;
    cout << '\n';
  }
  return 0;
}
