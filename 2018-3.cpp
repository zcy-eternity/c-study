// Created by zhangchaoyan on 2022/3/16.
#include <iostream>
#include <queue>
using namespace std;

typedef struct BiTNode{
    int weight;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void createTree(BiTree &T){
    int n;
    cin>>n;
    if(n==-1) //树的结点数据值为int 用-1表示空结点
        T = nullptr;
    else{
        T = new BiTNode;
        T->weight = n;
        createTree(T->lchild);
        createTree(T->rchild);
    }
}
void preorder(BiTree T){
    if(T){
        cout<<T->weight<<" ";
        preorder(T->lchild);
        preorder(T->rchild);
    }
}
int Depth(BiTree T){
    if(T== nullptr)
        return 0;
    else{
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        return m>n ? m+1 : n+1;
    }
}
//求树上从任意一个结点出发的最大的带权路径和
int max_sum(BiTree T){
    BiTNode *p = T;
    int sum = 0;
    queue<BiTree> q;
    q.push(p);
    while (!q.empty()){ //树的层次遍历 先将跟结点入队列
        // 判队列非空 每次从对头取出一个元素， 如果当前结点的左树为空入队，右树为空入队
        p = q.front();
        q.pop();
        if(sum < p->weight * (Depth(T)-Depth(p))){ //结点的路径长度为整棵树的树高-以当前结点为根结点的树高
            sum = p->weight * (Depth(T)-Depth(p));
        }
        if(p->lchild)
            q.push(p->lchild);
        if(p->rchild)
            q.push(p->rchild);
    }
    return sum;
}

int main(){
    BiTree T;
    //2 3 7 -1 -1 8 -1 -1 5 9 -1 -1 -1
    createTree(T);
    preorder(T);
    cout<<endl;
    cout<<max_sum(T);
}

