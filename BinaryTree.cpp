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
//���������˳������������
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
//���������˳��������������
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
        cout<<T->data<<" ";   //�ҵ���������ĵ�һ��������
        while (T->rTag==1&&T->rchild!= nullptr){
            T = T->rchild;
            cout<<T->data<<" ";
        }    //���������������ѭ�����
        T = T->rchild; //���������������ʼת����������ѭ��δ�˳����ҵ�����������������ĵ�һ��������
    }
    cout<<endl;
}
//��������ǵݹ�
void inOrderTraverse1(BiTree T){
    LinkStack s;
    initStack(s);
    BiTNode *p = T,*q;
    while (p || !StackEmpty(s)){ //������Ϊ��ʱѭ������ֹ��ֱ��ջ��Ϊֹ
        if(p){
            push(s,p); //��һ�η��ʵ�����㲢�����ʣ�������ջ
            p = p->lchild; //ת��������
        } else{ //������Ϊ��
            pop(s,q);  //���������������󣬵ڶ�����������㣬�ͽ�����㣨ָ�룩��ջ�����ҷ��ʸ����
            cout<<q->data<<" ";
            p = q->rchild; //ת��������
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
//����ǵݹ�
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
������һ���P��������ջ��Ȼ������������һֱ����������
 ֱ��������û�����ӵĽ�㣬��ʱ�ý�������ջ����
 ���Ǵ�ʱ���ܽ����ջ�����ʣ� ������Һ��ӻ�Ϊ�����ʡ�
 ���Խ�����������ͬ�Ĺ������������������ͬ�Ĵ���
 �����������Һ���ʱ���ý���ֳ�����ջ������ʱ���Խ����ջ������
*/

//����ǵݹ�
void postOrderTraverse(BiTree T){
    stack<BiTree> s;
    BiTNode *p = T,*q,*r; //r����������Ƿ���ʹ�
    while (p||!s.empty()){
        if(p){
            s.push(p);
            p = p->lchild;
        } else{
            q = s.top();
            if(q->rchild != nullptr && q->rchild!=r) //��������Ϊ����������û�з��ʹ���ת��������
                p = q->rchild;
            else{
                s.pop();  //������Ϊ�ջ��Ƿ��ʹ���ջ����
                cout<<q->data<<" ";
                r = q; //��ǵ�ǰ�����ʹ���
                p = nullptr; //������һ�����֮����Ҫ�ÿգ����ÿյĻ��ֻ��������ѹ��ȥ
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
        newT = new BiTNode; //���Ƹ����
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
            T->lchild = pre; //��ʼpreΪ�� ���������һ�����ǰ��Ϊ��
            T->lTag = 1;
        }
        if(pre&&!pre->rchild){ //��pre��Ϊ��ʱִ�� ��ʼpreΪ�ղ�ִ�� ��ִ�н���ǰ��
            pre->rchild = T;
            pre->rTag = 1;
        }  //��ʼpreΪ��ָ�� ��rTag rTag=0 Ĭ������
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
            PreThreading(T->lchild); //���������������תȦ����
        // ��ǰ������ָ��Ϊ��ʱ���������������ʱ����ָ���ָ��pre
        // ������Ҫ�Ե�ǰ�������ӽ���������Ҳ����pre���������� ����ѭ��
        PreThreading(T->rchild);
    }
}
void InOrderThreading(BiThrTree &T){
    pre = nullptr;
    if(T){
        InThreading(T);
        pre->rTag = 1; //preָ������������һ����� ���һ�����һ��û���Һ���
    }
}
//���Ҷ���������
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
//�����������Ĳ���
int BST_insert(BSTree &T, int key){
    if(T == nullptr){
        T = new BSTNode;
        T->key = key;
        T->lchild = nullptr;
        T->rchild = nullptr;
        return 1;
    } else if(T->key == key) //���д��ڹؼ�����ͬ�Ľ�㣬����ʧ��
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
void Select1(HuffmanTree HT,int n, int &s1, int &s2){ //�����ý������򣬴˷�������
    int flag;
    int index[n+1];//��¼HT���±꣬��ֹ����ʱ��ʧ�±�
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
        if(k==2) //k = 2ʱ����ѭ��
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
    //��¼����СԪ�ص�λ��
    for(int i=1;i<=n;i++)
        if(HT[i].parent==0){
            min = i;
            break;
        }
    for(int i=min+1;i<=n;i++){
        if(HT[i].weight<HT[min].weight&&HT[i].parent==0)
            min = i; //������СԪ��λ��
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
    HT = new HTNode[2*n];//0�ŵ�Ԫδ�ã�n��Ҷ�ӽ��Ĺ�����������2n-1�����
    for(int i=1;i<=2*n-1;i++)
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    for(int i=1;i<=n;i++)
        cin>>HT[i].weight;
    int s1,s2;
    for(int i=n+1;i<=2*n-1;i++){
        Select2(HT,i-1,s1,s2); //��HT[0~i-1]ѡ��˫����Ϊ0��Ȩֵ��С���������
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}
int WPL(HuffmanTree HT,int n){
    int wpl = 0,j;
    int l;//·�����ȣ��������
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
        f = HT[i].parent; //��ֵ
        pre1 = i;
        end = n-2; //ע����ѭ����
        while (f!=0){ //��Ҷ�ӽڵ����ϻ��ݣ�ֱ�������
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
//    cout<<"���������� �����룺"<<endl;
//    createBiTree(T);
//    cout<<"�ѽ����������������������(�ݹ�)Ϊ��"<<endl;
//    inOrder(T);
//    cout<<endl;
//    cout<<"�ѽ����������������������(�ǵݹ�)Ϊ��"<<endl;
//    inOrderTraverse(T);
//    cout<<endl;
//    cout<<"�ѽ���������������Ϊ��"<<endl;
//    cout<<Depth(T)<<endl;
//    cout<<"�ѽ����������Ľ����Ϊ��"<<endl;
//    cout<<NodeCount(T)<<endl;
//    BiTree newT;
//    initBiTree(newT);
//    Copy(T,newT);
//    cout<<"�����������������������Ϊ��"<<endl;
//    inOrder(newT);
//    cout<<endl;
//    BiThrTree Thr;
//    Thr = nullptr;
//    cout<<"�������������� �����룺"<<endl;
//    createBiThrTree(Thr);
//    InOrderThreading(Thr);
//    cout<<"�����������������������Ϊ��"<<endl;
//    inOrder(Thr);
//
//    BSTree BST;
//    BST = nullptr;
//    int key[] = {50,66,60,26,21,30,70,68};
//    int n = sizeof(key)/sizeof(key[0]);
//    cout<<"��������������{50,66,60,26,21,30,70,68}"<<endl;
//    create_BST(BST,key,n);
//    cout<<"�ڶ����������в���66�Ľ��: "<<BST_Search1(BST,66)->key<<endl<<"��������66�������ӽ��Ϊ��"<<BST_Search2(BST,66)->lchild->key<<endl;
//
//    HuffmanTree HT;
////    5 29 7 8 14 23 3 11
//    cout<<"�����������Ҷ�ӽ���Ȩֵ��"<<endl;
//    CreateHuffmanTree(HT,8);
//    cout<<"���Ĵ�Ȩ·������Ϊ��"<<WPL(HT,8)<<endl;
//    char **HC;
//    cout<<"��Ӧ�Ĺ���������Ϊ��"<<endl;
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
