/*
 * Incident 2 occurs t times at first.
 * args: N, T, M, t, subtask, duplicate
 * N should be at least duplicate.
 * T should be at least t.
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

struct Classmate {
  ll p;
  vector<ll> record;
  int rank; // classmate -> rank
  int last_up = 0;
  int c1 = -1, c2 = -1;
  ll spending = 0;
  ll update() {
    p += (ll)(N - rank) * (n_up - last_up);
    assert((ll)(N - rank) * (n_up - last_up) >= 0);
    last_up = n_up;
    return p;
  }
  void top_up(ll power) {
    p += power;
    record.push_back(power);
    
    c1++;
    spending += power;
    if (c1 - c2 > M) {
      spending -= (record[++c2]);
      assert(c1 - c2 == M);
    }
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
		}
  } else if (type == 2) {
    n_up++;
		vec_dup.clear();
  } else if (type == 3) {
		assert(vec_dup.size());
		ll q = rnd.next((ll)0, (ll)(player[rank_table[1]].p*1.05));
		assert(q >= 0);
		cout << ' ' << q;
  } else if (type == 4) {
		assert(r_top_up.size());
		cout << ' ' << rnd.any(r_top_up);
  } else cout << "ERROR\n";
	cout << '\n';
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	int subtask = opt<int>("subtask", 4);
	N = opt<int>("N", (subtask == 1)? 1'000: 1'000'000);
	int T = opt<int>("T", (subtask == 1)? 1'000: 500'000);
	int t = opt<int>("t", (subtask == 1)? 100: 100'000);
	assert(T >= t);
	M = opt<int>("M", (subtask == 3)? 1: rnd.next(0, 500'000));
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

	assert(T >= t);
	for (int i = 0; i < t; i++) gen_incident(2);
	T -= t;
	while (T--) {
		int type;
		if (subtask == 2) {
			if (rnd.next(0, 4)) type = 3;
			else type = 1;
		} else {
			vector<int> types{1, 2};
			if (vec_dup.size()) {
				types.push_back(3);
			}
			if (r_top_up.size()) types.push_back(4);
			type = rnd.any(types);
		}
		gen_incident(type);
	}
	return 0;
}
