#include <iostream>
#include <mem.h>
#include <queue>
#define MaxVertexNum 100

using namespace std;

typedef struct {
    char vexs[MaxVertexNum];
    int arcs[MaxVertexNum][MaxVertexNum];
    int vexnum,arcnum;
}MGraph;

typedef struct {
    char vexs[MaxVertexNum];
    int arcs[MaxVertexNum][MaxVertexNum];
    int vexnum,arcnum,weight;
}AMGraph;
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode{
    char data;
    ArcNode *firstarc;
}VNode,AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

typedef struct {
    char adjvex; //找到每次加入的最小边
    int lowcost;
}closedge[MaxVertexNum];

int LocateVex(MGraph G, char v){
    for(int i=0;i<G.vexnum;i++)
        if(G.vexs[i] == v)
            return i;
    return -1;
}
int LocateVex(AMGraph G, char v){
    for(int i=0;i<G.vexnum;i++)
        if(G.vexs[i] == v)
            return i;
    return -1;
}
int LocateVex(ALGraph G, char v){
    for(int i=0;i<G.vexnum;i++)
        if(G.vertices[i].data == v)
            return i;
    return -1;
}
int createGraph(MGraph &G){
    char v1,v2;
    int row,col;
    cin>>G.vexnum>>G.arcnum;
    for(int i=0;i<G.vexnum;i++)
        cin>>G.vexs[i];
    memset(G.arcs,0,sizeof(G.arcs));
    for(int i=0;i<G.arcnum;i++){
        cin>>v1>>v2;
        row = LocateVex(G,v1);
        col = LocateVex(G,v2);
        G.arcs[row][col] = 1;
        G.arcs[col][row] = 1;
    }
    return 1;
}
int createGraph(AMGraph &G){
    char v1,v2;
    int row,col;
    cin>>G.vexnum>>G.arcnum;
    for(int i=0;i<G.vexnum;i++)
        cin>>G.vexs[i];
    memset(G.arcs,0x3f,sizeof(G.arcs));
    int weight;
    for(int i=0;i<G.arcnum;i++){
        cin>>v1>>v2>>weight;
        row = LocateVex(G,v1);
        col = LocateVex(G,v2);
        G.arcs[row][col] = weight;
        G.arcs[col][row] = weight;
    }
    for(int i=0;i<G.arcnum;i++)
        G.arcs[i][i] = 0;
    return 1;
}
void createGraph(ALGraph &G){
    cin>>G.vexnum>>G.arcnum;
    for(int i=0;i<G.vexnum;i++){
        cin>>G.vertices[i].data;
        G.vertices[i].firstarc = nullptr;
    }
    char v1,v2;
    int m,n;
    ArcNode *p,*p2;
    for(int i=0;i<G.arcnum;i++){
        cin>>v1>>v2;
        m = LocateVex(G,v1);
        n = LocateVex(G,v2);
        p = new ArcNode;
        p->adjvex = n;
        p->nextarc = G.vertices[m].firstarc;
        G.vertices[m].firstarc = p;
        p2 = new ArcNode; //生成另一个对称的新的边结点
        p2->adjvex = m;
        p2->nextarc = G.vertices[n].firstarc;
        G.vertices[n].firstarc = p2;
    }
}
//连通图 如果是非连通图对每一个连通分量调用一次BFS
//树的层序遍历
void BFS(MGraph G, char v){
    bool visited[G.vexnum];
    for(int i=0;i<G.vexnum;i++)
        visited[i] = false;
    cout<<v<<" ";
    int u = LocateVex(G,v);
    visited[u] = true;
    queue<int> Q;
    Q.push(u);
    int w;
    while (!Q.empty()){
        w = Q.front(); Q.pop();
        for(int i=0;i<G.vexnum;i++)
            if(G.arcs[w][i]!=0&&!visited[i]){
                cout<<G.vexs[i]<<" ";
                visited[i] = true;
                Q.push(i);
            }
    }
}
void BFS(ALGraph G, char v){
    bool visited[G.vexnum];
    for(int i=0;i<G.vexnum;i++)
        visited[i] = false;
    cout<<v<<" ";
    int u = LocateVex(G,v);
    visited[u] = true;
    queue<int> Q;
    Q.push(u);
    int w; ArcNode *p;
    while (!Q.empty()){
        w = Q.front();
        Q.pop();
        p = G.vertices[w].firstarc;
        while (p){
            if(!visited[p->adjvex]){
                cout<<G.vertices[p->adjvex].data<<" ";
                visited[p->adjvex] = true;
                Q.push(p->adjvex);
            }
            p = p->nextarc;
        }
    }
}
bool visited[MaxVertexNum];
void DFS(MGraph G,char v){
    int w = LocateVex(G,v);
    cout<<G.vexs[w]<<" ";
    visited[w] = true;
    for(int i=0;i<G.vexnum;i++)
        if(G.arcs[w][i]!=0&&!visited[i])
            DFS(G,G.vexs[i]);
}
void DFSTraverse(MGraph G, char v){
    for(int i=0;i<G.vexnum;i++)
        visited[i] = false;
    for(int i=0;i<G.vexnum;i++)
        if(!visited[i])
            DFS(G,v);
}
void Prim(AMGraph G,char v){
    closedge closedge;
    int k = LocateVex(G,v);
    for(int i=0;i<G.vexnum;i++)
        if(i!=k)
            closedge[i] = {v,G.arcs[k][i]};
    closedge[k].lowcost = 0;
    int min;
    for(int i=0;i<G.vexnum-1;i++){
        for(int j=0;j<G.vexnum;j++){
            if(closedge[j].lowcost!=0)
                min = j;
        }
        for(int j=0;j<G.vexnum;j++){
            if(closedge[j].lowcost!=0&&closedge[j].lowcost<closedge[min].lowcost)
                min = j;
        }
        cout<<'('<<G.vexs[min]<<','<<closedge[min].adjvex<<')'<<" ";
        closedge[min].lowcost = 0;
        for(int j=0;j<G.vexnum;j++)
            if(closedge[j].lowcost!=0&&G.arcs[min][j]<closedge[j].lowcost){
                closedge[j].lowcost = G.arcs[min][j];
                closedge[j].adjvex = G.vexs[min];
            }
    }
}
//并查集
int Find(const int parent[], int x){
    while (parent[x]!=-1)
        x = parent[x];
    return x;
}
int Union(int parent[], int rank[], int x, int y){
    int x_root = Find(parent,x);
    int y_root = Find(parent,y);
    if(x_root == y_root)
        return 0;
    if(rank[x_root]<rank[y_root])
        parent[x_root] = y_root;
    else if(rank[x_root]>rank[y_root])
        parent[y_root] = x_root;
    else{
        parent[x_root] = y_root;
        rank[y_root]++;
    }
    return 1;
}
int main(){
//    MGraph G;
//    createGraph(G);
//    1 2 5 6 3 7 4 8
//    1 2 5 6 7 3 8 4 因为邻接表法的表示法不唯一，这就造成了遍历序列可能也不唯一
//    BFS(G,'1');
//    cout<<endl;
//    2 1 5 6 3 4 7 8
//    DFSTraverse(G,'2');
//    AMGraph G;
//    createGraph(G);
//    cout<<"最小生成树的各边："<<endl;
//    Prim(G,'1');
//    int parent[10];
//    memset(parent,-1,sizeof(parent));
//    int rank[10];
//    memset(rank,0,sizeof(rank));
//    int Edge[6][2] = {
//            {0,1},{1,2},{1,3},
//            {3,4},{2,5},{5,4}
//    };
//    int x,y;
//    for(auto & i : Edge){
//        x =i[0];
//        y =i[1];
//        if(Union(parent,rank,x,y)==0){
//            cout<<"Cycle detected!"<<endl;
//            exit(0);
//        }
//    }
//    cout<<"No Cycles found!"<<endl;
}

//测试用例
/*
8 10
1 2 3 4 5 6 7 8
1 5
1 2
2 6
3 6
3 7
6 7
3 4
4 7
4 8
7 8

最小生成树
6 10
1 2 3 4 5 6
1 2 6
1 3 1
1 4 5
2 3 5
3 4 5
2 5 3
3 5 6
3 6 4
4 6 2
5 6 6
*/
