#include <iostream>
#include <stack>
using namespace std;

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct TStackNode{
    BiTNode* data;
    struct TStackNode *next;
}TStackNode,*LinkStack;

typedef struct BiThrNode{
    char data;
    struct BiThrNode *lchild,*rchild;
    int lTag,rTag;
}BiThrNode,*BiThrTree;

BiThrNode *pre = nullptr;

typedef struct CSNode{
    char data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

typedef struct BSTNode{
    int key;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

typedef struct{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

void initStack(LinkStack &s){
    s = nullptr;
}
void push(LinkStack &s, BiTNode* x){
    TStackNode *p = new TStackNode;
    p->data = x;
    p->next = s;
    s = p;
}
void pop(LinkStack &s, BiTNode* &x){
    TStackNode *p = s;
    x = p->data;
    s = p->next;
    delete p;
}
bool StackEmpty(LinkStack s){
    if(!s)
        return true;
    else
        return false;
}
void initBiTree(BiTree &T){
    T = nullptr;
}
//ABC##DE#G##F###
//先序遍历的顺序建立二叉链表
void createBiTree(BiTree &T){
    char ch;
    cin>>ch;
    if(ch=='#')
        T = nullptr;
    else{
        T = new BiTNode;
        T->data = ch;
        createBiTree(T->lchild);
        createBiTree(T->rchild);
    }
}
//先序遍历的顺序建立线索二叉树
//ABC##DE#G##F###
void createBiThrTree(BiThrTree &T){
    char ch;
    cin>>ch;
    if(ch=='#'){
        T = nullptr;
    } else{
        T = new BiThrNode;
        T->data = ch;
        createBiThrTree(T->lchild);
        createBiThrTree(T->rchild);
    }

}
void inOrder(BiTree T){
    if(T){
        inOrder(T->lchild);
        cout<<T->data<<" ";
        inOrder(T->rchild);
    }
}
void postOrder(BiTree T){
    if(T){
        postOrder(T->lchild);
        postOrder(T->rchild);
        cout<<T->data<<" ";
    }
}
void inOrder(BiThrTree T){
    while (T){
        while (T->lTag==0)
            T = T->lchild;
        cout<<T->data<<" ";   //找到中序遍历的第一个结点输出
        while (T->rTag==1&&T->rchild!= nullptr){
            T = T->rchild;
            cout<<T->data<<" ";
        }    //若结点有右线索，循环输出
        T = T->rchild; //结点无右线索，开始转向右子树，循环未退出，找到右子树中中序遍历的第一个结点输出
    }
    cout<<endl;
}
//中序遍历非递归
void inOrderTraverse1(BiTree T){
    LinkStack s;
    initStack(s);
    BiTNode *p = T,*q;
    while (p || !StackEmpty(s)){ //右子树为空时循环不终止，直到栈空为止
        if(p){
            push(s,p); //第一次访问到根结点并不访问，而是入栈
            p = p->lchild; //转向左子树
        } else{ //左子树为空
            pop(s,q);  //左子树遍历结束后，第二次遇到根结点，就将根结点（指针）退栈，并且访问根结点
            cout<<q->data<<" ";
            p = q->rchild; //转向右子树
        }
    }
}
void inOrderTraverse2(BiTree T){
    stack<BiTree> s;
    BiTNode *p = T,*q;
    while (p || !s.empty()){
        if(p){
            s.push(p);
            p = p->lchild;
        } else{
           q = s.top();
           s.pop();
           cout<<q->data<<" ";
           p = q->rchild;
        }
    }
}
//先序非递归
void preOrderTraverse(BiTree T){
    stack<BiTree> s;
    BiTNode *p = T,*q;
    while (p || !s.empty()){
        if(p){
            cout<<p->data<<" ";
            s.push(p);
            p = p->lchild;
        } else{
            q = s.top();
            s.pop();
            p = q->rchild;
        }
    }
}

/*
对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，
 直到搜索到没有左孩子的结点，此时该结点出现在栈顶，
 但是此时不能将其出栈并访问， 因此其右孩子还为被访问。
 所以接下来按照相同的规则对其右子树进行相同的处理，
 当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问
*/

//后序非递归
void postOrderTraverse(BiTree T){
    stack<BiTree> s;
    BiTNode *p = T,*q,*r; //r标记右子树是否访问过
    while (p||!s.empty()){
        if(p){
            s.push(p);
            p = p->lchild;
        } else{
            q = s.top();
            if(q->rchild != nullptr && q->rchild!=r) //右子树不为空且右子树没有访问过，转向右子树
                p = q->rchild;
            else{
                s.pop();  //右子树为空或是访问过出栈访问
                cout<<q->data<<" ";
                r = q; //标记当前结点访问过了
                p = nullptr; //访问完一个结点之后需要置空，不置空的话又会把这个结点压进去
            }
        }
    }
}
int Depth(BiTree T){
    if(T == nullptr)
        return 0;
    else{
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        return m>n ? m+1 : n+1;
    }
}
void Copy(BiTree T, BiTree &newT){
    if(T == nullptr){
        newT = nullptr;
    } else{
        newT = new BiTNode; //复制根结点
        newT->data = T->data;
        Copy(T->lchild, newT->lchild);
        Copy(T->rchild, newT->rchild);
    }

}
int NodeCount(BiTree T){
    if(T== nullptr){
        return 0;
    } else{
        int m = NodeCount(T->lchild);
        int n = NodeCount(T->rchild);
        return m+n+1;
    }
}
void InThreading(BiThrTree &T){
    if(T){
        InThreading(T->lchild);
        if(!T->lchild){
            T->lchild = pre; //初始pre为空 中序遍历第一个结点前驱为空
            T->lTag = 1;
        }
        if(pre&&!pre->rchild){ //判pre不为空时执行 初始pre为空不执行 仅执行建立前驱
            pre->rchild = T;
            pre->rTag = 1;
        }  //初始pre为空指针 无rTag rTag=0 默认设置
        pre = T;
        InThreading(T->rchild);
    }
}
void PreThreading(BiThrTree &T){
    if(T){
        if(!T->lchild){
            T->lchild = pre;
            T->lTag = 1;
        }
        if(pre&&!pre->rchild){
            pre->rchild = T;
            pre->rTag = 1;
        }
        pre = T;
        if(T->lTag == 0)
            PreThreading(T->lchild); //先序线索化会出现转圈问题
        // 当前结点的左指针为空时会进行线索化，此时左孩子指针会指向pre
        // 接下来要对当前结点的左孩子进行线索化也就是pre进行线索化 出现循环
        PreThreading(T->rchild);
    }
}
void InOrderThreading(BiThrTree &T){
    pre = nullptr;
    if(T){
        InThreading(T);
        pre->rTag = 1; //pre指向中序遍历最后一个结点 最后一个结点一定没有右孩子
    }
}
//查找二叉排序树
BSTNode *BST_Search1(BSTree T,int key){
    if(T == nullptr){
        return nullptr;
    }else if (T->key == key)
        return T;
    else if(T->key < key)
        return BST_Search1(T->rchild,key);
    else
        return BST_Search1(T->lchild,key);
}
BSTNode *BST_Search2(BSTree T, int key){
    while (T&&T->key!=key){
        if(T->key < key)
            T = T->rchild;
        if(T->key > key)
            T = T->lchild;
    }
    return T;
}
//二叉排序树的插入
int BST_insert(BSTree &T, int key){
    if(T == nullptr){
        T = new BSTNode;
        T->key = key;
        T->lchild = nullptr;
        T->rchild = nullptr;
        return 1;
    } else if(T->key == key) //树中存在关键字相同的结点，插入失败
        return 0;
    else if(T->key < key)
        BST_insert(T->rchild,key);
    else
        BST_insert(T->lchild,key);
}
void create_BST(BSTree &T, const int key[], int n){
    for(int i=0;i<n;i++)
        BST_insert(T,key[i]);
}
void Select1(HuffmanTree HT,int n, int &s1, int &s2){ //不能用交换排序，此方法错误
    int flag;
    int index[n+1];//记录HT的下标，防止交换时丢失下标
    for(int i=1;i<=n;i++)
        index[i] = i;
    for(int i=1;i<n;i++){
        flag = 0;
        for(int j=1;j<n-i+1;j++){
            if(HT[j].weight>HT[j+1].weight){
                swap(HT[j],HT[j+1]);
                swap(index[j],index[j+1]);
                flag = 1;
            }
        }
        if(flag == 0)
            break;
    }

    int k=0,a[2];
    for(int i=1;i<=n;i++){
        if(k==2) //k = 2时跳出循环
            break;
        if(HT[i].parent==0){
            a[k++] = index[i];
        }
    }
    s1 = a[0];
    s2 = a[1];
}
void Select2(const HuffmanTree HT,int n, int &s1, int &s2) {
    int min=0;
    //记录下最小元素的位置
    for(int i=1;i<=n;i++)
        if(HT[i].parent==0){
            min = i;
            break;
        }
    for(int i=min+1;i<=n;i++){
        if(HT[i].weight<HT[min].weight&&HT[i].parent==0)
            min = i; //更新最小元素位置
    }
    s1 = min;
    for(int i=1;i<=n;i++)
        if(HT[i].parent==0&&i!=min){
            min = i;
            break;
        }
    for(int i=min+1;i<=n;i++){
        if(HT[i].weight<HT[min].weight&&HT[i].parent==0&&i!=s1)
            min = i;
    }
    s2 = min;
}

void CreateHuffmanTree(HuffmanTree &HT,int n){
    HT = new HTNode[2*n];//0号单元未用，n个叶子结点的哈夫曼树共有2n-1个结点
    for(int i=1;i<=2*n-1;i++)
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    for(int i=1;i<=n;i++)
        cin>>HT[i].weight;
    int s1,s2;
    for(int i=n+1;i<=2*n-1;i++){
        Select2(HT,i-1,s1,s2); //在HT[0~i-1]选择双亲域为0且权值最小的两个结点
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}
int WPL(HuffmanTree HT,int n){
    int wpl = 0,j;
    int l;//路径长度，不是深度
    for(int i=1;i<=n;i++){
        l = 0;
        j = i;
        while (HT[j].parent!=0){
            l++;
            j = HT[j].parent;
        }
        wpl+=HT[i].weight*l;
    }
    return wpl;
}
void copy1(char str1[],const char str2[],int start){
    int i = start+1;
    int j = 0;
    while (str2[i]!='\0')
        str1[j++] = str2[i++];
    str1[j] = '\0';
}
void HuffmanCoding(HuffmanTree &HT,int n, char ** &HC){
    HC = new char*[n+1];
    char *cd = new char[n];
    cd[n-1] = '\0';
    int f,pre1,end;
    for(int i=1;i<=n;i++){
        f = HT[i].parent; //初值
        pre1 = i;
        end = n-2; //注意在循环内
        while (f!=0){ //从叶子节点向上回溯，直到根结点
            if(pre1==HT[f].lchild)
                cd[end--] = '0';
            else
                cd[end--] = '1';
            pre1 = f;
            f = HT[f].parent;
        }
        HC[i] = new char[n-2-end+1];
        copy1(HC[i],cd,end);
    }

}
//int main(){
//    BiTree T;
//    initBiTree(T);
////    ABC##DE#G##F###
//    cout<<"建立二叉树 请输入："<<endl;
//    createBiTree(T);
//    cout<<"已建立二叉树的中序遍历序列(递归)为："<<endl;
//    inOrder(T);
//    cout<<endl;
//    cout<<"已建立二叉树的中序遍历序列(非递归)为："<<endl;
//    inOrderTraverse(T);
//    cout<<endl;
//    cout<<"已建立二叉树的树高为："<<endl;
//    cout<<Depth(T)<<endl;
//    cout<<"已建立二叉树的结点数为："<<endl;
//    cout<<NodeCount(T)<<endl;
//    BiTree newT;
//    initBiTree(newT);
//    Copy(T,newT);
//    cout<<"拷贝二叉树的中序遍历序列为："<<endl;
//    inOrder(newT);
//    cout<<endl;
//    BiThrTree Thr;
//    Thr = nullptr;
//    cout<<"建立线索二叉树 请输入："<<endl;
//    createBiThrTree(Thr);
//    InOrderThreading(Thr);
//    cout<<"线索二叉树的中序遍历序列为："<<endl;
//    inOrder(Thr);
//
//    BSTree BST;
//    BST = nullptr;
//    int key[] = {50,66,60,26,21,30,70,68};
//    int n = sizeof(key)/sizeof(key[0]);
//    cout<<"建立二叉排序树{50,66,60,26,21,30,70,68}"<<endl;
//    create_BST(BST,key,n);
//    cout<<"在二叉排序树中查找66的结点: "<<BST_Search1(BST,66)->key<<endl<<"排序树中66结点的左孩子结点为："<<BST_Search2(BST,66)->lchild->key<<endl;
//
//    HuffmanTree HT;
////    5 29 7 8 14 23 3 11
//    cout<<"输入哈夫曼树叶子结点的权值："<<endl;
//    CreateHuffmanTree(HT,8);
//    cout<<"树的带权路径长度为："<<WPL(HT,8)<<endl;
//    char **HC;
//    cout<<"对应的哈夫曼编码为："<<endl;
//    HuffmanCoding(HT,8,HC);
//    int j;
//    for(int i=1;i<=8;i++){
//        j = 0;
//        while (HC[i][j]!='\0'){
//            cout<<HC[i][j];
//            j++;
//        }
//        cout<<endl;
//    }
//}
int main(){
    BiTree T;
    initBiTree(T);
    createBiTree(T);
    preOrderTraverse(T);
    cout<<endl;
    postOrderTraverse(T);
    cout<<endl;
    postOrder(T);
}
