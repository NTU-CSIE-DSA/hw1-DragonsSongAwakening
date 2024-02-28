#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    long long power;
    struct Node *next;
}node;

node* create_node(long long p, node* nxt){
    node* tmp = (node *)malloc(sizeof(node));
    tmp->power = p;
    tmp->next = nxt;
    return tmp;
}

typedef struct Classmate{
    long long power;
    int attack;
    int label;
    node *head;
    node *tail;
    // basic ver
    long long ans;
    int counter;
    node *cur;
}classmate;

classmate C[1000001];
int label2rank[1000001];
long long lazy_tag = 0;
int N, T, M;

int binarySearch(long long target) {
    int low = -1, high = N, mid = (high + low) / 2;
    while(low + 1 < high){
        // printf("low = %d, high = %d\n", low, high);
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
    node* tmp_node = create_node(C[rank - 1].power - C[rank].power + lazy_tag, NULL);
    if(C[rank].head == NULL){
        C[rank].head = tmp_node;
        C[rank].tail = C[rank].head;
        C[rank].cur = C[rank].head;
    }
    else{
        C[rank].tail->next = tmp_node;
        C[rank].tail = tmp_node;
    }
    // basic ver
    C[rank].counter += 1;
    C[rank].ans += tmp_node->power;
    if(C[rank].counter > M){
        C[rank].ans -= C[rank].cur->power;
        C[rank].cur = C[rank].cur->next;
    }
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
    //basic ver
    printf("%lld\n", C[label2rank[label]].ans);
    return;
}

int main(){
    scanf("%d%d%d", &N, &T, &M);
    long long p;
    for(int i = 0; i < N; i++){
        scanf("%lld", &p);
        C[i].power = p;
        C[i].attack = 0;
        C[i].head = NULL;
        C[i].tail = NULL;
        C[i].label = i + 1;
        label2rank[i + 1] = i;
        // basic ver
        C[i].cur = NULL;
        C[i].ans = 0;
        C[i].counter = 0;
    }
    int op;
    for(int i = 0; i < T; i++){
        // printf("hi %d\n", i);
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
        node* cur = C[rank].head;
        while(cur != NULL){
            printf("%lld ", cur->power);
            cur = cur->next;
        }
        printf("\n");
    }
    return 0;
}

