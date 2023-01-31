#include "binary-tree.h"

#include "stdlib.h"
#include "Windows.h"

unsigned long long ticks_;
inline unsigned int TimerStart(){
    QueryPerformanceCounter((LARGE_INTEGER*)&ticks_);
    return (unsigned int)ticks_;
}
inline unsigned int TimerEnd(unsigned int st){
    QueryPerformanceCounter((LARGE_INTEGER*)&ticks_);
    return (unsigned int)(ticks_ - st);
}


static int tree_cnt;
template <typename T>
void print_tree( T * r, T* null,bool vals){
    if(r!=null){
        print_tree(r->left,null,vals);
        tree_cnt++;
        if(vals){ printf("node value: %c key: %u \n",r->value,r->key); }
        print_tree(r->right,null,vals);
    }
}

template <typename T>
void print(T* root, T* null,bool vals) {
    if(root!=null){
        if(vals) { printf("root_node value: %c key: %u \n",root->value,root->key); }
        tree_cnt=0;
        print_tree(root->left,null,vals);
        printf("root->left cnt : %i \n",tree_cnt);
        tree_cnt=0;
        print_tree(root->right,null,vals);
        printf("root->right cnt: %i \n",tree_cnt);
    }
}

static char alphabet[]= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

#define KEY_COUNT 1000
static int32_t keys[KEY_COUNT];
static int32_t r_keys[KEY_COUNT];

void gen_keys(){


    rb_tree<int32_t,int32_t> tree;

    for(int i = 0;i<KEY_COUNT; i++ ){
        bool pass(false);
        int32_t rnd;
        while(!pass){
            rnd = rand()%1001;
            if(!tree.Get(rnd)){ tree.insert(0,rnd); pass=true; }
        }
        r_keys[i] = rnd;
        keys[i] = i;
    }
}

b_tree<char,uint32_t> btree;
rb_tree<char,uint32_t> rbtree;

void Test(int32_t * keys){

    for(int ii=0,i=0; i<=20; i++){ /* binary tree*/
        btree.insert(alphabet[ii],keys[i]);
        ii = ii>=25?0:ii+1;
    }
    for(int ii=0,i=0; i<=20; i++){ /* red black tree*/
        rbtree.insert(alphabet[ii],keys[i]);
        ii = ii>=25?0:ii+1;
    }

    printf("\nbinary______\n");
    print(btree.GetRoot(),(b_node<char,uint32_t>*)NULL,true);
    printf("\nred black___\n");
    print(rbtree.GetRoot(),rbtree.GetNull(),true);

    char val;
    unsigned int ticks;

    printf("\nbinary______\n");
    ticks=TimerStart();
    val=btree.Get(keys[5])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[5],val);

    ticks=TimerStart();
    val=btree.Get(keys[10])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[10],val);

    ticks=TimerStart();
    val=btree.Get(keys[19])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[19],val);



    printf("\nred black___\n");
    ticks=TimerStart();
    val=rbtree.Get(keys[5])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[5],val);

    ticks=TimerStart();
    val=rbtree.Get(keys[10])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[10],val);

    ticks=TimerStart();
    val=rbtree.Get(keys[19])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[19],val);

    rbtree.Clear();
    btree.Clear();

    for(int ii=0,i=0; i<KEY_COUNT; i++){ /* binary tree*/
        btree.insert(alphabet[ii],keys[i]);
        ii = ii>=25?0:ii+1;
    }
    for(int ii=0,i=0; i<KEY_COUNT; i++){ /* red black tree*/
        rbtree.insert(alphabet[ii],keys[i]);
        ii = ii>=25?0:ii+1;
    }

    printf("\nbinary\n");
    print(btree.GetRoot(),(b_node<char,uint32_t>*)NULL,false);
    printf("\n\nred black\n");
    print(rbtree.GetRoot(),rbtree.GetNull(),false);

    printf("\nbinary______\n");
    ticks=TimerStart();
    val=btree.Get(keys[50])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[50],val);

    ticks=TimerStart();
    val=btree.Get(keys[600])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[600],val);

    ticks=TimerStart();
    val=btree.Get(keys[999])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[999],val);



    printf("\nred black___\n");
    ticks=TimerStart();
    val=rbtree.Get(keys[50])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[50],val);

    ticks=TimerStart();
    val=rbtree.Get(keys[600])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[600],val);

    ticks=TimerStart();
    val=rbtree.Get(keys[999])->value;
    ticks=TimerEnd(ticks);
    printf("Get time: %u, b_node key: %i val: %c \n",ticks,keys[999],val);

    rbtree.Clear();
    btree.Clear();

}

int main() {


    gen_keys();


    /*random---------------------------------------------------------------------*/
    printf("random \n");
    Test(r_keys);

    /*sorted---------------------------------------------------------------------*/
    printf("\n\nsorted \n");
    Test(keys);

    printf("b_node count: %i, rb_node count: %i ",
           b_node<char,uint32_t>::count,rb_node<char,uint32_t>::count);
    return 0;
}
