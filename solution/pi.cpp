#include<bits/stdc++.h>
using namespace std;

#define pb push_back

using ll = long long;
const int MAXN = 1e6+6;
int N, M;
ll p[MAXN+1];
vector<ll> record[MAXN+1];
int Rank[MAXN+1];

int find_pre(int a) {
  for (int i = 1; i <= N; i++)
    if (Rank[i] == Rank[a]-1) return i;
  return -1;
}

void incident() {
  int type;
  cin >> type;
  if (type == 1) {
    int a; cin >> a;
    int pre = find_pre(a);
    if (pre == -1) return;
    record[a].pb(p[pre] - p[a]);
    assert(p[pre] >= p[a]);
    p[a] = p[pre];
    swap(Rank[a], Rank[pre]);
  } else if (type == 2) {
    for (int i = 1; i <= N; i++) p[i] += N-Rank[i];
  } else if (type == 3) {
    ll q; cin >> q;
    int ans = -1, ans_label = -1;
    for (int i = 1; i <= N; i++) {
      if (p[i] >= q) {
        if (Rank[i] > ans) {
          ans = Rank[i];
          ans_label = i;
        }
      }
    }
    if (ans == -1) cout << "0 0\n";
    else cout << ans << ' ' << ans_label << '\n';
  } else if (type == 4) {
    int b; cin >> b;
    int m; cin >> m;
    ll ans = 0;
    int n_attack = record[b].size();
    for (int i = 1; i <= m && i <= n_attack; i++) ans += record[b][n_attack-i];
    cout << ans << '\n';
  } else cout << "ERROR\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> N >> T >> M;
  for (int i = 1; i <= N; i++) {
    cin >> p[i];
    Rank[i] = i;
  }
  for (int i = 1; i < N; i++) assert(p[i] >= p[i+1]);
  while (T--) {
    incident();
  }
  cout << '\n';
  for (int i = 1; i <= N; i++) {
    cout << record[i].size();
    for (ll j : record[i]) cout << ' ' << j;
    cout << '\n';
  }
  return 0;
}
