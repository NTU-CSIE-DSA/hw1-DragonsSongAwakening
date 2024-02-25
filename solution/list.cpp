#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

const int MAXN = 1e6+6;
typedef long long ll;
int N, M;
int n_up = 0;

typedef struct Node {
  Node *pre;
  Node *nxt;
  ll value;
} Node;

Node *new_node(ll v) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->value = v;
  node->nxt = NULL;
  node->pre = NULL;
  return node;
}

typedef struct Classmate {
  ll p;
  Node *record_head, *record_tail;
  Node *cursor;
  int n_record;
  int n_summed_record;
  ll spending;
  int rank; // classmate -> rank
  int last_up;
} Classmate;

Classmate player[MAXN+1];
int rank_table[MAXN+1]; // rank -> classmate

void player_init(int i, int p, int rank) {
  player[i].p = p;
  player[i].cursor = player[i].record_head = player[i].record_tail = new_node(-1);
  player[i].n_record = 0;
  player[i].n_summed_record = 0;
  player[i].spending = 0;
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

  player[i].record_tail->nxt = new_node(power);
  player[i].record_tail->nxt->pre = player[i].record_tail;
  player[i].record_tail = player[i].record_tail->nxt;
  
  player[i].spending += power;
  if (player[i].n_summed_record == M) {
    player[i].cursor = player[i].cursor->nxt;
    player[i].spending -= player[i].cursor->value;
  } else player[i].n_summed_record++;
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
    int b;
    scanf("%d", &b);
    printf("%lld\n", player[b].spending);
  };
}

int main() {
  int T;
  scanf("%d%d%d", &N, &T, &M);
  for (int i = 1; i <= N; i++) {
    int p;
    scanf("%d", &p);
    player_init(i, p, i);
    rank_table[i] = i;
  }
  for (int i = 1; i < N; i++) assert(player[i].p >= player[i+1].p);
  while (T--) {
    incident();
  }
  printf("\n");
  for (int i = 1; i <= N; i++) {
    printf("%d", player[i].n_record);
    Node *it = player[i].record_head->nxt;
    while (it != NULL) {
      assert(it->value >= 0);
      printf(" %lld", it->value);
      it = it->nxt;
    }
    printf("\n");
  }
  return 0;
}
