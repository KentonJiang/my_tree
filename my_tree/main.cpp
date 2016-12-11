//
//  main.cpp
//  tree
//
//  Created by Jiang Zhenfei on 2016/11/15.
//  Copyright  2016年 姜震飞. All rights reserved.
//
//this program
#include <iostream>
#define max 100
typedef char datatype;// change type here
//binary tree defined below
struct node {
    struct node *lchild;
    struct node *rchild;
    datatype data;
};
typedef struct node * btree;
//thread binary tree defined below
struct thnode {
    datatype data;
    struct thnode *lchild, *rchild;
    bool ltag, rtag;
};
typedef struct thnode * thtree;
typedef struct thnode * thhead;
void threading(thtree &t);
//1．至少采用两种方法，编写建立二叉树的二叉链表存储结构的程序，并以适当的形式显示并保存二叉树
//preorder create
void pre_createBT(btree &t)
{
    char ch;
    std::cin >> ch;
    if (ch == '#') {
        t = nullptr;
    }
    else {
        t = new struct node;
        t->data = ch;
        pre_createBT(t->lchild);
        pre_createBT(t->rchild);
    }
}

btree CreateBT(datatype v, btree ltree, btree rtree)
{
    btree root;
    root = new struct node;
    root->data = v;
    root->lchild = ltree;
    root->rchild = rtree;
    return root;
}
//2．采用二叉树的二叉链表存储结构，编写程序实现二叉树的先序、中序和后序遍历的递归和非递归算法以及层序遍历算法，以适当的形式显示并保存二叉树和相应的遍历序列；

//A.recursion
//preorder traversal
void preorder_r(btree bt)
{
    if (bt != nullptr) {
        std::cout << bt->data;
        preorder_r(bt->lchild);
        preorder_r(bt->rchild);
    }
}
//inorder traversal
void inorder_r(btree bt) {
    if (bt != nullptr) {
        inorder_r(bt->lchild);
        std::cout << bt->data;
        inorder_r(bt->rchild);
    }
}
//postorder traversal
void postorder_r(btree bt){
    if (bt != nullptr) {
        postorder_r(bt->lchild);
        postorder_r(bt->rchild);
        std::cout << bt->data;
    }
}

//B.none recursion

//preorder traversal
void preorder(btree root) {
    int top;
    btree s[max];
    top = -1;
    while (root != nullptr || top != -1) {
        while (root != nullptr) {
            std::cout << root->data;
            s[++top] = root;
            root = root->lchild;
        }
        if (top != -1) {
            root = s[top--];
            root = root->rchild;
        }
    }
}

//inorder traversal
void inorder(btree root) {
    int top;
    btree s[max];
    top = -1;
    while (root != nullptr || top != -1) {
        while (root != nullptr) {
            s[++top] = root;
            root = root->lchild;
        }
        if (top != -1) {
            root = s[top--];
            std::cout << root->data;
            root = root->rchild;
        }
    }
}

//postorder traversal
void postorder(btree root) {
    int top;
    btree s[max];
    int flag[max];
    top = -1;
    while (root != nullptr || top != -1) {
        while (root != nullptr) {
            top++;
            s[top] = root;
            flag[top] = 1;
            root = root->lchild;
        }
        while (-1 != top && 2 == flag[top]) {
            root = s[top--];
            std::cout << root->data;
        }
        if (top != -1) {
            flag[top] = 2;
            root = s[top]->rchild;
        }
        if (-1 == top) {
            break;
        }
    }
}
//level order traversal
void level_order(btree root)
{
    btree Q[max],q;//queue
    int front,rear;
    front = rear = 0;//顺序队列
    if (root == nullptr) {
        return;
    }
    Q[++rear] = root;
    while (front != rear) {
        q = Q[++front];
        std::cout << q->data;
        if (q->lchild!=nullptr) {
            Q[++rear] = q->lchild;
        }
        if (q->rchild!=nullptr) {
            Q[++rear] = q->rchild;
        }
    }
}
//3．在二叉树的二叉链表存储结构基础上，编写程序实现二叉树的中序线索链表存储结构建立的算法，以适当的形式显示并保存二叉树的相应的线索链表；
//按照先序中序线索化建立二叉树
thtree pre_createthT(thtree &t)
{
    char ch;
    
    std::cin >> ch;
    if (ch == '#') {
        t = nullptr;
    }
    else {
        t = new struct thnode;
        t->data = ch;
        pre_createthT(t->lchild);
        pre_createthT(t->rchild);
    }
    return  t;
}
//将其线索化
thtree pre = nullptr;
void threading(thtree &t)
{
    if (t != NULL) {
        threading(t->lchild);//左子树线索化
        t->ltag = (t->lchild) ? true : false;
        t->rtag = (t->rchild) ? true : false;
        if (pre) {//若前驱存在
            if (pre->rtag == false) {//p的r是线索
                pre->rchild = t;//那就指向中序后继
            }
            if (t->ltag == false)
                t->lchild = pre;
        }
        pre = t;
        threading(t->rchild);
    }
}
//建立并将其线索化
void create_th_tree(thtree &t,thtree &head)
{
    pre_createthT(t);//建立t
    head = new struct thnode;//建立头节点
    head->ltag = true;
    head->rtag = true;//true or false???????
    //右指针回指
    head->rchild = head;
    if (!t) {
        head->lchild = head;
        head->ltag = false;
    }
    else{
        head->lchild = t;
        pre= head;
        threading(t);
        pre->rchild = head;
        pre->rtag = false;
        //head->rchild = pre;
        
    }
}
//4．在二叉树的线索链表存储结构上，编写程序分别实现求二叉树一个结点的先序、中序和
//后序遍历的后继结点算法；
//求中序后继
thtree in_next(thtree p)
{
    thtree q;
    q = p->rchild;
    if (p->rtag == true) {
        while (q->ltag == true) {
            q = q->lchild;
        }
    }
    return q;
}
//先序后继
thtree prenext(thtree p)
{
    thtree q;
    if (p->ltag == true) {
        q = p->lchild;
    }
    else {
        q = p;
        while (q->rtag == false) {
            q = q->rchild;
        }
        q = q->rchild;
    }
    return q;
}
//后续后继
/*
 对于节点p ，利用性质找到其父节点 f
 如果f 的右儿子是 p， 则f 是p后序后继
 如果 f没有右子树 f也是p后继
 如果f的右儿子不是p 那后继就是在右子树里面找后继
 */
thtree post_next(thtree p)
{
    thtree q = NULL,j;
    if (p->rtag != true)
    {
        if (p->rchild->lchild == p)
        {
            if (p->rchild->rtag != true)
            {
                q = p->rchild;
            }
            else
            {
                q = p->rchild;
                while (q->rtag == true)
                {
                    q = q->rchild;
                }
                while (q->ltag == true)
                {
                    q = q->lchild;
                }
            }
        }
        else if (p->rchild->lchild->rchild == p)
        {
            q = p->rchild->lchild;
        }
        else
        {
            q = p->rchild->lchild;
            j = q;
            while (q->rtag == true)
            {
                j = q;
                q = q->rchild;
            }
            while (q->ltag == true)
            {
                j = q;
                q = q->lchild;
            }
            q = j;
        }
    }
    else if (p->rtag == true)
    {
        q = p;
        while (q->rtag == true) {
            q = q->rchild;
        }//找到r指向线索的节点
        while (q->rtag != true) //为了找到他的父节点
        {
            q = q->rchild;
            if(q == q->rchild)
                q = q->lchild;
        }//q是父节点
        if (q->lchild == p)
        {
            q = q->rchild;
            while (q->ltag == true)
            {
                q = q->lchild;
            }
            while (q->rtag == true)
            {
                q = q->rchild;
            }
        }
        else if (q->rchild == p)
        {
            q = q;
        }
        else{
            while (q->rchild !=p) {
                q = q->rchild;
            }
        }
    }
    return q;
}
//5．以上条要求为基础，编写程序实现对中序线索二叉树进行先序、中序和后序遍历的非递归算法，以适当的形式显示并保存二叉树和相应的遍历序列。
//先序遍历 需要有head
void Th_pre_order(thtree head)
{
    thtree tmp;
    tmp = head;
    do {
        if (tmp) {
            tmp = prenext(tmp);
        }
        
        if (tmp != head && tmp) {
            std::cout << tmp->data;
        }
    } while (tmp != head && tmp);
}
//中序遍历 需要有head
void Th_in_order(thtree head)
{
    thtree tmp;
    tmp = head;
    do {
        if (tmp)
            tmp = in_next(tmp);
        if (tmp != head&&tmp) {
            std::cout << tmp->data;
        }
    } while (tmp != head && tmp);
}
//后续遍历 需要有head
void Th_post_order(thtree head)
{
    //找到后续遍历的第一个节点
    thtree tmp;
    tmp = head;
    while (tmp->ltag && tmp->rtag) {
        while (tmp->ltag) {
            tmp = tmp->lchild;
        }
        if (tmp->rtag) {
            tmp = tmp->rchild;
        }
    }
    std::cout << tmp->data;
    do {
        if (tmp)
            tmp = post_next(tmp);
        if (tmp != head&&tmp) {
            std::cout << tmp->data;
        }
    } while (tmp != head->lchild&&tmp);
}
/*
 head->lchild = T head->rchild = head ; head->ltag = TRUE ; head->rtag = TRUE ;
 */
int main(int argc, const char * argv[]){
    // insert code here...
    //std::cout << "Hello, World!\n";
    btree binary_tree;
    thtree th;
    thhead head;//头节点
    std::cout << "输入先序建立二叉树的数据"<<std::endl;
    pre_createBT(binary_tree);
    std::cout <<"这是先序遍历的输出"<<std::endl;
    preorder(binary_tree);std::cout <<std::endl;
    preorder_r(binary_tree);std::cout <<std::endl;
    std::cout <<"这是中序遍历的输出"<<std::endl;
    inorder(binary_tree);std::cout <<std::endl;
    inorder_r(binary_tree);std::cout <<std::endl;
    std::cout <<"这是后序遍历的输出"<<std::endl;
    postorder(binary_tree);std::cout <<std::endl;
    postorder_r(binary_tree);std::cout <<std::endl;
    std::cout <<"这是层序遍历的输出"<<std::endl;
    level_order(binary_tree);std::cout <<std::endl;
    std::cout << "输入先序建立中序线索化二叉树的数据" << std::endl;
    create_th_tree(th,head);
    std::cout << "中序线索二叉树建立完毕" << std::endl;
    std::cout <<"这是先序遍历的输出"<<std::endl;
    Th_pre_order(head);
    std::cout <<std::endl;
    std::cout <<"这是中序遍历的输出"<<std::endl;
    Th_in_order(head);
    std::cout <<std::endl;
    std::cout << "这是后序遍历的输出" << std::endl;
    Th_post_order(head);
    std::cout << std::endl;
    return 0;
}
