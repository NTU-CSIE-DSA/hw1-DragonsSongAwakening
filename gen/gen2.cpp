/*
 * After many incident 1, 
 * Incident 3 query powers that many candidates possess.
 * Incident 4 only query record that is not empty.
 * Classmate that has more topping up record will be queried for their record more frequently.
 * incident <freq> will be queried 4 times as other queries
 * args: N, T, M, subtask, duplicate, freq{3, 4}
 * N should be at least duplicate.
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include "testlib.h"
using namespace std;
using ll = long long;

const int MAXN = 1e6+6;
int n_up = 0;
int N, M;
int subtask;
int freq;

struct Classmate {
  ll p;
  vector<ll> record;
  int rank; // classmate -> rank
  int last_up = 0;
  ll update() {
    p += (ll)(N - rank) * (n_up - last_up);
    assert((ll)(N - rank) * (n_up - last_up) >= 0);
    last_up = n_up;
    return p;
  }
  void top_up(ll power) {
    p += power;
    record.push_back(power);
  }
};

vector<int> rank_table(MAXN+1);
vector<Classmate> player(MAXN+1);
vector<int> vec_dup;
vector<int> r_top_up;

void swap_rank(int a, int b) {
  swap(player[a].rank, player[b].rank);
  rank_table[player[a].rank] = a;
  rank_table[player[b].rank] = b;
}

void gen_incident(int type) {
	cout << type;
  if (type == 1) {
		int a = rnd.next(1, N);
		cout << ' ' << a;
    int rank = player[a].rank;
    if (rank != 1) {
			int pre_rank = rank-1;
			int pre = rank_table[pre_rank];
			ll diff = player[pre].update() - player[a].update();
			player[a].top_up(diff);
			swap_rank(a, pre);
			vec_dup.push_back(a);
			r_top_up.push_back(a);
		}
  } else if (type == 2) {
    n_up++;
		vec_dup.clear();
  } else if (type == 3) {
		assert(vec_dup.size());
    int target = rnd.any(vec_dup);
		ll q = -1;
		int shift = rnd.next(0, 2);
		if (shift == 0) { // equal
			q = player[target].update();
		} else if (shift == 1) { // larger
			if (player[target].p != player[rank_table[1]].p) {
				int rank = player[target].rank;
				int pre_rank = rank-1;
				int pre = rank_table[pre_rank];
				while (player[pre].update() == player[target].update()) {
					pre_rank--;
					pre = rank_table[pre_rank];
				}
				if (rnd.next(0, 1)) q = rnd.next(player[target].p, player[pre].p);
				else q = player[pre].p;
			} else q = player[rank_table[1]].p + rnd.next((ll)0, (ll)1e17);
		} else if (shift == 2) { // smaller
			if (player[target].p != player[rank_table[N]].p) {
				int rank = player[target].rank;
				int nxt_rank = rank+1;
				int nxt = rank_table[nxt_rank];
				while (player[nxt].update() == player[target].update()) {
					nxt_rank++;
					nxt = rank_table[nxt_rank];
				}
				q = rnd.next(player[nxt].p, player[target].p);
				if (rnd.next(0, 1)) q = rnd.next(player[nxt].p, player[target].p);
				else q = player[nxt].p;
			} else q = rnd.next((ll)0, player[target].p);
		}
		assert(q >= 0);
		cout << ' ' << q;
  } else if (type == 4) {
		assert(r_top_up.size());
		int b = rnd.any(r_top_up);
		assert(player[b].record.size());
		cout << ' ' << rnd.any(r_top_up);
		if (subtask != 5) cout << ' ' << M;
		else if (rnd.next(0, 1000)) {
			if (rnd.next(0, 4)) cout << ' ' << min(rnd.next(max((int)player[b].record.size()/10*9, 1), (int)player[b].record.size()), M);
			else cout << ' ' << min(rnd.next(1, (int)player[b].record.size()), M);
		} else cout << ' ' << rnd.next(1, M);
  } else cout << "ERROR\n";
	cout << '\n';
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	subtask = opt<int>("subtask", 4);
	freq = opt<int>("freq", 0);
	assert(freq != 2);
	N = opt<int>("N", (subtask == 1)? 1'000: 1'000'000);
	int T = opt<int>("T", (subtask == 1)? 1'000: 500'000);
	M = opt<int>("M", (subtask == 3 || subtask == 2)? 1: rnd.next(1, 500'000));
	cout << N << ' ' << T << ' ' << M << '\n';

	int duplicate = opt<int>("duplicate", 1);
	vector<int> p(1);
	for (int i = 1; i <= N-duplicate; i++) p.push_back(rnd.next(0, 1'000'000'000));
	for (int i = 1; i <= duplicate; i++) {
		int dup_ind = rnd.next(1, N-duplicate);
		do {
			p.push_back(p[dup_ind]);
			vec_dup.push_back(dup_ind);
		} while (rnd.next(0, 2) && ++i <= duplicate);
	}
	assert((int)p.size() == N+1);
	sort(next(p.begin()), p.end(), greater<int>());
	for (int i = 1; i < N; i++) assert(p[i] >= p[i+1]);
	for (int i = 1; i <= N; i++) cout << p[i] << " \n"[i == N];

  for (int i = 1; i <= N; i++) {
    player[i].p = p[i];
    player[i].rank = i;
    rank_table[i] = i;
  }

	while (T--) {
		int type;
		if (subtask == 2) {
			if (rnd.next(0, 4)) type = 3;
			else type = 1;
		} else {
			vector<int> types{1};
			if (!rnd.next(0, T/100)) types.push_back(2);
			if (vec_dup.size()) types.push_back(3);
			if (r_top_up.size()) types.push_back(4);
			type = rnd.any(types);
			if (freq) {
				for (int i = 0; i < 3; i++) types.push_back(freq);
			}
		}
		gen_incident(type);
	}
	return 0;
}
