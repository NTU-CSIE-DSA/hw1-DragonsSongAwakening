#include "testlib.h"
using namespace std;

const int MAXN = 1'000'000;
const int MAXT = 500'000;
const int MAXM = 500'000;
const int MAXp = 1'000'000'000;
const long long MAXq = 1000'000'000'000'000'000;

int main() {
	registerValidation();
	int N = inf.readInt(1, MAXN, "N");
	inf.readSpace();
	int T = inf.readInt(1, MAXT, "T");
	inf.readSpace();
	int M = inf.readInt(1, MAXM, "M");
	inf.readEoln();

	inf.readInts(N, 0, MAXp, "p_i");
	inf.readEoln();

	while (T--) {
		int incident = inf.readInt(1, 4, "incident");
		if (incident == 1) {
			inf.readSpace();
			inf.readInt(1, N, "a_i");
		} else if (incident == 3) {
			inf.readSpace();
			inf.readLong((long long)0, MAXq, "q_i");
		} else if (incident == 4) {
			inf.readSpace();
			inf.readInt(1, N, "b_i");
			inf.readSpace();
			inf.readInt(M, M, "m_i");
		}
		inf.readEoln();
	}

	inf.readEof();
	return 0;
}
