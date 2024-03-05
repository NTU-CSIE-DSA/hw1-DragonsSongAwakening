#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAXN 1000006
typedef long long ll;
int N, T, M;
int n_up = 0;

typedef struct Classmate {
  ll p;
  ll *record;
  int n_record;
  int rank; // classmate -> rank
  int last_up;
} Classmate;

Classmate *player;
int *rank_table; // rank -> classmate

void player_init(int i, int p, int rank) {
  player[i].p = p;
  player[i].record = (ll *) calloc((T+2), sizeof(ll));
  player[i].record[0] = 0;
  player[i].n_record = 0;
  player[i].rank = rank;
  player[i].last_up = 0;
}
ll update(int i) {
  player[i].p += (ll)(N - player[i].rank) * (n_up - player[i].last_up);
  assert((ll)(N - player[i].rank) * (n_up - player[i].last_up) >= 0);
  player[i].last_up = n_up;
  return player[i].p;
}
void top_up(int i, ll power) {
  player[i].p += power;
  player[i].record[player[i].n_record+1] = player[i].record[player[i].n_record] + power;
  player[i].n_record++;
}

void swap_rank(int a, int b) {
  int tmp = player[a].rank;
  player[a].rank = player[b].rank;
  player[b].rank = tmp;
  rank_table[player[a].rank] = a;
  rank_table[player[b].rank] = b;
}

int binary_search(ll q) {
  if (q > update(rank_table[1])) return -1;
  int l = 1, r = N+1;
  while (r-l > 1) {
    int m = (l+r)/2;
    ll power = update(rank_table[m]);
    // cout << m << ": " << rank_table[m] << "(" << power << ")\n";
    if (power < q) r = m;
    else l = m;
  }
  return l;
}

void incident() {
  int type;
  scanf("%d", &type);
  if (type == 1) {
    int a;
    scanf("%d", &a);
    int rank = player[a].rank;
    if (rank == 1) return;
    int pre_rank = rank-1;
    int pre = rank_table[pre_rank];
    ll diff = update(pre) - update(a);
    top_up(a, diff);
    swap_rank(a, pre);
  } else if (type == 2) {
    n_up++;
  } else if (type == 3) {
    ll q;
    scanf("%lld", &q);
    int rank = binary_search(q);
    if (rank == -1) printf("0 0\n");
    else printf("%d %d\n", rank, rank_table[rank]);
  } else if (type == 4) {
    int b, m;
    scanf("%d", &b);
    scanf("%d", &m);
    int n_record = player[b].n_record;
    int l = (n_record >= m) ? (n_record-m) : 0;
    printf("%lld\n", player[b].record[n_record] - player[b].record[l]);
  }
}

int main() {
  scanf("%d%d%d", &N, &T, &M);
  player = (Classmate *) malloc((N+1)*sizeof(Classmate));
  rank_table = (int *) malloc((N+1)*sizeof(int));
  for (int i = 1; i <= N; i++) {
    int p;
    scanf("%d", &p);
    player_init(i, p, i);
    rank_table[i] = i;
  }
  while (T--) {
    incident();
  }
  printf("\n");
  for (int i = 1; i <= N; i++) {
    printf("%d", player[i].n_record);
    for (int j = 1; j <= (int)player[i].n_record; j++)
      printf(" %lld", player[i].record[j]-player[i].record[j-1]);
    printf("\n");
  }
  return 0;
}
