#include<bits/stdc++.h>
using namespace std;

#define pb push_back

const int MAXN = 1e6+6;
using ll = long long;
int N, M;
int n_up = 0;

struct Classmate {
  ll p;
  vector<ll> record = vector<ll>(1);
  int rank; // classmate -> rank
  int last_up = 0;
  // Classmate(_p, _rank, _last_up) : p(_p), rank(_rank), last_up(_last_up) {}
  ll update() {
    p += (ll)(N - rank) * (n_up - last_up);
    assert((ll)(N - rank) * (n_up - last_up) >= 0);
    last_up = n_up;
    return p;
  }
  void top_up(ll power) {
    p += power;
    record.pb(record[record.size()-1]+power);
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
    int m; cin >> m;
    int size = player[b].record.size();
    cout << player[b].record[size-1] - player[b].record[max(0, size-m-1)] << '\n';
  } else cout << "ERROR\n";
}

int main() {
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
    cout << player[i].record.size() - 1;
    for (int j = 1; j < (int)player[i].record.size(); j++)
      cout << ' ' << player[i].record[j]-player[i].record[j-1];
    cout << '\n';
  }
  return 0;
}
