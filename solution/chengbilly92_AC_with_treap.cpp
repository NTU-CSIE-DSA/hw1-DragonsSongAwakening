#include <stdio.h>
#include <stdlib.h>
#define maxn 1000000
#define ll long long

typedef struct Player{
  ll power;
  int last_upd;
  int idx;
} player;

typedef struct Treap{
  struct Treap *l, *r;
  int key, pri;
  ll val, sum;
} treap;

int n, t, M;
int rank[maxn];
int upd_num = 0;
player p[maxn];
treap *add_list[maxn];
int treap_sz[maxn] = {};

void pull(treap **a) {
  if(a == NULL) return;
  ll suml = ((*a) -> l)? (*a) -> l -> sum: 0;
  ll sumr = ((*a) -> r)? (*a) -> r -> sum: 0;
  (*a) -> sum = suml + sumr + (*a) -> val;
}

treap *merge(treap *a, treap *b) {
  if(a == NULL) return b;
  if(b == NULL) return a;
  if(a -> pri > b -> pri) {
    a -> r = merge(a -> r, b);
    pull(&a);
    return a;
  }
  b -> l = merge(a, b -> l);
  pull(&b);
  return b;
}

void split(treap *a, treap **b, treap **c, int k) {
  if (!a) {
    *b = NULL;
    *c = NULL;
    return;
  }
  if (a -> key <= k) {
    *b = a;
    split(a -> r, &((*b) -> r), c, k);
    pull(b);
  }
  else {
    *c = a;
    split(a -> l, b, &((*c) -> l), k);
    pull(c);
  }
}

void update(int rk) {
  p[rk].power += (long long) (n - 1 - rk) * (upd_num - p[rk].last_upd);
  p[rk].last_upd = upd_num;
}

void add(int idx) {
  int rk = rank[idx];
  if(rk == 0) return;
  update(rk - 1);
  update(rk);
  treap_sz[idx]++;
  treap *node = (treap*) malloc(sizeof(treap));
  node -> l = NULL;
  node -> r = NULL;
  node -> key = treap_sz[idx];
  node -> pri = rand();
  node -> val = node -> sum = p[rk - 1].power - p[rk].power;
  add_list[idx] = merge(add_list[idx], node);
  rank[p[rk - 1].idx]++;
  rank[idx]--;
  p[rk].power = p[rk - 1].power;
  player tmp = p[rk];
  p[rk] = p[rk - 1];
  p[rk - 1] = tmp;
}

void search(ll q) {
  int l = -1, r = n;
  while(l + 1 < r) {
    int m = (l + r) >> 1;
    update(m);
    if(p[m].power >= q) {
      l = m;
    }
    else r = m;
  }
  if(l == -1) {
    printf("0 0\n");
  }
  else {
    printf("%d %d\n", l + 1, p[l].idx + 1);
  }
}

void query(int idx, int m) {
  treap *b, *c;
  split(add_list[idx], &b, &c, treap_sz[idx] - m);
  printf("%lld\n", c? c -> sum: 0);
  add_list[idx] = merge(b, c);
}

int main() {

  scanf("%d%d%d", &n, &t, &M);
  for(int i = 0; i < n; i++) {
    scanf("%lld", &p[i].power);
    rank[i] = i;
    p[i].last_upd = 0;
    p[i].idx = i;
    add_list[i] = NULL;
  }

  for(int i = 1; i <= t; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int a;
      scanf("%d", &a);
      a--;
      add(a);
    }
    else if(op == 2) {
      upd_num++;
    }
    else if(op == 3) {
      ll q;
      scanf("%lld", &q);
      search(q);
    }
    else {
      int b, m;
      scanf("%d%d", &b, &m);
      b--;
      query(b, m);
    }
  }
  printf("\n");
  for(int i = 0; i < n; i++) {
    printf("%d ", treap_sz[i]);
    treap *b, *c;
    for(int j = 0; j < treap_sz[i]; j++) {
      split(add_list[i], &b, &c, j + 1);
      add_list[i] = c;
      printf("%lld ", b -> val);
    }
    printf("\n");
  }

  return 0;
}
