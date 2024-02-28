#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct SkipNode {
    int key;
    long long sum;
    struct SkipNode **next;
} SkipNode;

typedef struct SkipList {
    int max_level;
    int level;
    SkipNode *header;
} SkipList;

SkipNode* createNode(int key, long long sum, int level) {
    SkipNode *new_node = (SkipNode*)malloc(sizeof(SkipNode));
    new_node->key = key;
    new_node->sum = sum;
    new_node->next = (SkipNode**)malloc(sizeof(SkipNode*) * (level + 1));
    return new_node;
}

SkipList* createSkipList(int max_level) {
    SkipList *list = (SkipList*)malloc(sizeof(SkipList));
    list->max_level = max_level;
    list->level = 0;
    list->header = createNode(-1, 0, max_level);
    for (int i = 0; i <= max_level; i++) {
        list->header->next[i] = NULL;
    }
    return list;
}

int GetLevel(int key) {
    int level = 0;
    while (key % 2 == 1) {
        level++;
        key = key / 2;
    }
    return level;
}

void insertNode(SkipList *list, int key, long long sum) {
    SkipNode *update[list->max_level + 1];
    SkipNode *current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->next[i] != NULL && key > current->next[i]->key) {
            current = current->next[i];
        }
        update[i] = current;
    }
    current = current->next[0];
    if (current == NULL || current->key != key) {
        int new_level = GetLevel(key);
        if (new_level > list->level) {
            for (int i = list->level + 1; i <= new_level; i++) {
                update[i] = list->header;
            }
            list->level = new_level;
        }
        SkipNode *new_node = createNode(key, sum, new_level);
        for (int i = 0; i <= new_level; i++) {
            new_node->next[i] = update[i]->next[i];
            update[i]->next[i] = new_node;
        }
    }
}

long long fast_get(SkipList *list, long long k){ // fast get the first element >= k
    SkipNode *current = list->header;
    for (int i = list->level; i >= 0; i--){
        while (current->next[i] != NULL && k >= current->next[i]->key) {
            current = current->next[i];
        }
    }
    return current->sum;
}

typedef struct Classmate{
    long long power;
    int attack;
    int label;
    SkipList *ans;
    long long tmp_sum;
}classmate;

classmate C[1000001];
int label2rank[1000001];
long long lazy_tag = 0;
int N, T, M;

int binarySearch(long long target) {
    int low = -1, high = N, mid = (high + low) / 2;
    while(low + 1 < high){
        mid = low + (high - low) / 2;
        if(C[mid].power + lazy_tag * (N - 1 - mid) >= target) low = mid;
        else high = mid;
    }
    return low + 1;
}

void op1(int label){
    if(label2rank[label] == 0) return;
    int rank = label2rank[label];
    // deal with power list
    C[rank].tmp_sum += (C[rank - 1].power - C[rank].power + lazy_tag);
    insertNode(C[rank].ans, C[rank].attack + 1, C[rank].tmp_sum);
    // deal with power
    C[rank].power = C[rank - 1].power;
    C[rank - 1].power += lazy_tag;
    // deal with attack
    C[rank].attack += 1;
    // deal with label and rank
    label2rank[label] -= 1;
    label2rank[C[rank - 1].label] += 1;
    classmate tmp_c = C[rank];
    C[rank] = C[rank - 1];
    C[rank - 1] = tmp_c;
    return;
}

void op2(){
    lazy_tag += 1;
    return;
}

void op3(long long q){
    int rank = binarySearch(q);
    // printf("rank = %d, power = %lld\n", rank, C[rank].power);
    if(rank == 0) printf("0 0\n");
    else{
        printf("%d %d\n", rank, C[rank - 1].label);
    }
    return;
}

void op4(int label, int m){
    if(m >= C[label2rank[label]].attack) printf("%lld\n", C[label2rank[label]].tmp_sum);
    else printf("%lld\n", C[label2rank[label]].tmp_sum - fast_get(C[label2rank[label]].ans, C[label2rank[label]].attack - m));
    return;
}

int main(){
    scanf("%d%d%d", &N, &T, &M);
    long long p;
    for(int i = 0; i < N; i++){
        scanf("%lld", &p);
        C[i].power = p;
        C[i].attack = 0;
        C[i].ans = createSkipList(20); // max level = 20
        C[i].label = i + 1;
        C[i].tmp_sum = 0;
        label2rank[i + 1] = i;
    }
    int op;
    for(int i = 0; i < T; i++){
        scanf("%d", &op);
        if(op == 1){
            int label;
            scanf("%d", &label);
            op1(label);
        }
        else if(op == 2){
            op2();
        }
        else if(op == 3){
            long long query;
            scanf("%lld", &query);
            op3(query);
        }
        else{
            int label, m;
            scanf("%d%d", &label, &m);
            op4(label, m);
        }
    }
    printf("\n");
    for(int i = 1; i <= N; i++){
        int rank = label2rank[i];
        printf("%d ", C[rank].attack);
        SkipNode* cur = C[rank].ans->header->next[0];
        long long prev = 0;
        while(cur != NULL){
            printf("%lld ", cur->sum - prev);
            prev = cur->sum;
            cur = cur->next[0];
        }
        printf("\n");
    }
    return 0;
}
