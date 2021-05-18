#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;
    ofstream fout("abce.out");

float genPriority()
{
    srand((unsigned int)time(NULL));
    return float(rand())/float((RAND_MAX));
}
struct node{
int v;
float priority;
node *parent,*left,*right;
};
class treap{
private:
node *root;
void rotateLeft(node *n)
{
    node *r=n->right;
    n->right=r->left;
    if(r->left!=NULL){
        r->left->parent=n;
    }
    r->parent=n->parent;
    if (n->parent==NULL){
        this->root=r;
    }else if(n==n->parent->left){
            n->parent->left=r;}
            else{
                n->parent->right=r;
            }
        r->left=n;
        n->parent=r;
}
void rotateRight(node *n)
{
    node *y=n->left;
    n->left=y->right;
    if(y->right!=NULL) y->right->parent=n;
    y->parent=n->parent;
    if(n->parent==NULL) this->root=y;
    else if(n==n->parent->right)
        n->parent->right=y;
    else n->parent->left=y;
    y->right=n;
    n->parent=y;
}
void moveUp(node *n)
{
    while(n->parent!=NULL && n->priority < n->parent->priority)//daca poate si trebuie sa urce
    {
        if(n==n->parent->left)//daca e in stanga parintelui
            rotateRight(n->parent);
        else rotateLeft(n->parent);//daca e in dreapta parintelui
    }
}
node* recSearch(node *n, int data)
{
    if(n==NULL) return NULL;
    if(data==n->v) return n;
    if(data<n->v) return recSearch(n->left,data);
    return recSearch(n->right,data);
}
void moveDown(node *n)
{
    if(n->left||n->right)//daca are unde sa mearga
    {
         if(n->left&&n->right)//daca poate merge in ambele directii
            {
            if(n->left->priority<n->right->priority)//daca prioritatea din dreapta e mai mare
                rotateRight(n);//roteste la dreapta
            else rotateLeft(n);//altfel roteste la stanga
            }
        else if(n->left)//daca poate doar la stanga
            rotateRight(n);//roteste la dreapta
            else rotateLeft(n);//altfel daca poate doar la dreapta roteste la stanga
        moveDown(n);//mai verifica odata
    }
}
void recout(node *n)
{
    if(n->left) {recout(n->left);fout<<' ';}
    fout<<n->v;
    if(n->right){fout<<' '; recout(n->right);}
}
public:
    treap(){this->root=NULL;}
    node* search(int data)
    {
        return recSearch(this->root,data);
    }
    node* succesor(node *n)
    {
        node *t;
        if(n->right!=NULL)
        {
            t=n->right;
        while(t->left!=NULL)t=t->left;
        }
        else
            {
                t=n->parent;
        while(t!=NULL&&n==t->right)
        {
            n=t;
            t=t->parent;
        }
            }
        return t;
    }
    node* predecesor(node *n)
    {
        node *t;
        if(n->left!=NULL)
        {
            t=n->left;
            while(t->right)t=t->right;
        }
        else
        {
            t=n->parent;
            while(t!=NULL&&n==t->left)
            {
                n=t;
                t=t->parent;
            }
        }
        return t;
    }
    void insert(int x)
    {
        node *n=new node;
        n->v=x;
        n->priority=genPriority();
        n->parent=NULL;
        n->left=NULL;
        n->right=NULL;
        node *t=this->root;
        node *parent=NULL;

        while(t!=NULL)
        {
            parent=t;
            if(n->v<t->v)
                t=t->left;
            else t=t->right;
        }
        n->parent=parent;
        if(parent==NULL) this->root=n;
        else
        {if(n->v<parent->v) parent->left=n;
            else parent->right=n;
            }
        if(n!=this->root) moveUp(n);
    }
    void del(int x)
    {
        node *t=search(x);
        moveDown(t);
        if(t==t->parent->left)
            t->parent->left=NULL;
        else t->parent->right=NULL;
        delete t;
    }
    void out()
    {
        if(this->root) recout(this->root);
    }
};
int main()
{
   /* treap t;
    t.insert(12);
    t.insert(4);
    t.insert(32);
    t.del(12);
    t.out();
*/
/*
    ifstream fin("abce.in");
    int n;
    fin>>n;
    int c,nr;
    treap t;
    for(int i=0;i<n;i++)
    {
        fin>>c;
    switch(c)
        {
        case 1:
            {
            fin>>nr;
            t.insert(nr);break;
            }
        case 2:
            {
                fin>>nr;
                t.del(nr);break;
            }
        case 3:
            {
                fin>>nr;
                if(t.search(nr)==NULL)fout<<0;
                else fout<<1;
                fout<<'\n';break;
            }
        case 4:
            {
                fin>>nr;
              if(t.search(nr)==NULL)
              {
                  t.insert(nr);
                  fout<<t.predecesor(t.search(nr))->v<<endl;
                  t.del(nr);
                  break;
              }

                fout<<t.predecesor(t.search(nr))->v<<endl;break;
            }
        case 5:
            {
                fin>>nr;
                              if(t.search(nr)==NULL)
              {
                  t.insert(nr);
                  fout<<t.succesor(t.search(nr))->v<<endl;
                  t.del(nr);
                  break;
              }

                fout<<t.succesor(t.search(nr))->v<<endl;break;
            }
        case 6:
            {
                int lb,rb;
                fin>>lb>>rb;
                t.out(lb,rb);fout<<endl;
                break;
            }
        }
    }
    */
    return 0;
}
