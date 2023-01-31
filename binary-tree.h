#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "stdio.h"
#include "stdint.h"

template<typename T,typename T1>
struct b_node {
    b_node(): left(NULL),right(NULL),parent(NULL){ count++; }
    ~b_node(){ count--; }

    b_node * left,* right,* parent;

    T value;
    T1 key;

    static int32_t count;
};

template<typename T,typename T1>
int32_t b_node<T,T1>::count = 0;

template<typename T,typename T1>
struct rb_node {

    rb_node(): left(NULL),right(NULL),parent(NULL){ count++; }
    ~rb_node(){ count--; }

    rb_node * left,* right,* parent;

    T value;
    T1 key;

    bool color;
    static int32_t count;
};

template<typename T,typename T1>
int32_t rb_node<T,T1>::count = 0;

template<typename T,typename T1>
class tree_base{

protected:
    T *m_root;
    T *m_null;
public:

    T * GetRoot(){ return m_root; }
    T * GetNull(){ return m_null; }
    T * Min(){
        if(m_root==m_null) { return NULL; }
        T *current = m_root;
        while(current->left){ current = current->left; }
        return current;
    }
    T * Max(){
        if(m_root==m_null) { return NULL; }
        T *current = m_root;
        while(current->right){ current = current->right; }
        return current;
    }

    T * Get(const  T1& key){

        T *current = m_root;
        if( !current || (current->key==key) ) { return current; }

        while( current){
            if( key < current->key ){ current = current->left; }
            else if( key > current->key) { current = current->right; }
            else{ return current; }
        }
        return current;
    }

    void Clear(){
        if(m_root){
            Delete(m_root);
            m_root=m_null;
        }
    }

private:

    void Delete(T* n) {
        if(n!=m_null){
            Delete(n->left);
            Delete(n->right);
            delete n;
        }
    }

};

template<typename T,typename T1,typename T2 = b_node<T,T1> >
class b_tree : public tree_base<T2,T1>{

public:
    b_tree()  {
        m_root = m_null= NULL;
    }
    ~b_tree(){ Clear(); }

    void insert( const T & value, const T1 & key ){

        T2 * final = NULL;
        T2 * current = m_root;

        while(current){
            final = current;
            if(key<current->key) { current = current->left;}
            else if(key==current->key) {
                current->value = value;
                return;
            }
            else { current = current->right;}
        }

        T2 * A = new T2();
        A->key = key;
        A->value = value;
        A->parent = final;

        if(!final) { m_root = A; }
        else if(A->key<final->key){ final->left = A;  }
        else { final->right = A;  }
    }

};

#define RED   true
#define BLACK false
#define RIGHT false
#define LEFT  true

template< typename T, typename T1, typename T2 = rb_node<T,T1> >
class rb_tree : public tree_base<T2,T1> {

public:
    rb_tree(){
        m_null = new T2();
        m_null->color = BLACK;
        m_root = m_null;
    }
    ~rb_tree(){
        Clear();
        delete m_null;
    }

    void insert( const T & value, const T1 & key ){

        T2 * y = m_null;
        T2 * x = m_root;
        while(x!=m_null){
            y = x;
            if(key<x->key){ x = x->left; }
            else if(key>x->key){ x = x->right; }
            else{
                y->value = value;
                return;
            }
        }
        T2 * z = new T2();
        z->key = key;
        z->value = value;
        z->parent = y;
        z->left = m_null;
        z->right = m_null;
        z->color = RED;

        if(y==m_null){ m_root = z; }
        else if(key<y->key){ y->left = z; }
        else { y->right = z; }

        InsertFixup(z);
    }

private:

    void InsertFixup( T2 * z){
        while(z->parent->color==RED){

            if(z->parent==z->parent->parent->left){

                T2 * y = z->parent->parent->right;
                if(y->color==RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                }
                else if(z==z->parent->right){
                    z = z->parent;
                    Rotate(z,LEFT);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Rotate(z->parent->parent,RIGHT);
            }
            else if(z->parent==z->parent->parent->right) {
                T2 * y = z->parent->parent->left;
                if(y->color==RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                }
                else if(z==z->parent->left){
                    z = z->parent;
                    Rotate(z,RIGHT);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Rotate(z->parent->parent,LEFT);

            }
            else{
                if(z->parent == m_root){ m_root->color = BLACK; }
                else { fprintf(stderr," Errrro! \n"); return; }
            }
        }
    }

    void Rotate (T2 * r, bool dir){

        T2 * child = NULL,*  rotate = r;

        if(dir==RIGHT){
            child = rotate->left;
            rotate->left = child->right;
            if(child->right!=m_null) { child->right->parent = rotate;  }
        }else{
            child = rotate->right;
            rotate->right = child->left;
            if(child->left!=m_null) { child->left->parent = rotate;  }
        }
        child->parent = rotate->parent;
        if(r->parent==m_null){ m_root = child; }
        else if(rotate==rotate->parent->left){ rotate->parent->left = child;  }
        else { rotate->parent->right = child;  }

        if(dir==RIGHT){ child->right = rotate; }
        else { child->left = rotate; }

        r->parent = child;
    }

};



#endif // BINARYTREE_H
