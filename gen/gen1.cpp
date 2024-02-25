/*
 * Incidents and query are random.
 * args: N, T, M, subtask
 */
#include <iostream>
#include <vector>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	int subtask = opt<int>("subtask", 4);
	int N = opt<int>("N", (subtask == 1)? 1'000: 1'000'000);
	int T = opt<int>("T", (subtask == 1)? 1'000: 500'000);
	int M = opt<int>("M", (subtask == 3)? 1: rnd.next(1, 500'000));
	cout << N << ' ' << T << ' ' << M << '\n';

	vector<int> p;
	for (int i = 0; i < N; i++) p.push_back(rnd.next(0, 1'000'000'000));
	sort(p.begin(), p.end(), greater<int>());
	for (int i = 0; i < N; i++) cout << p[i] << " \n"[i+1 == N];
	while (T--) {
		int incident;
		if (subtask == 2) incident = rnd.any(vector<int>{1, 3});
		else incident = rnd.next(1, 4);
		cout << incident;
		if (incident == 1 || incident == 4) cout << ' ' << rnd.next(1, N);
		if (incident == 3) cout << ' ' << rnd.next((ll)0, (ll)1'000'000'000'000'000'000);
		cout << '\n';
	}
	return 0;
}
