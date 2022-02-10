//
// Created by Zhaorui Yang on 2021/5/17.
//
#include "Tourism.h"

using namespace std;

void FindEdge(int v){
    cout<<"相邻景点\t介绍\t距离"<<endl;
    for(int i = 0; i < G->numVertexes; i++){
        if(G->AdjMatrix[v][i] != 0 && G->AdjMatrix[v][i] != MAX_WEIGHT){
            int w = G->AdjMatrix[v][i];
            cout<<&G->vex[i].name[0]<<"\t"<<&G->vex[i].describe[0]<<"\t"<<w<<endl;
        }
    }
    cout<<endl;
    menu();
}




vector<vector<int>> path;
//i出发顶点编号，visited数组保存访问状态，visit_vex保存一条路径，idx保存访问深度
void DFS(Graph* graph, int i, int visited[], int visit_vex[], int& idx){
    visited[i] = 1; //i顶点已访问
    visit_vex[idx++] = i; //将i加入当前路径

    int vexnum = 0;
    for(int i = 0; i < G->numVertexes; i++){
        if(visited[i])
            vexnum++;
    } //最后保存的一定是一遍能走完的路线而没有回头路
    //如果访问过了所有顶点，则将一条完整的遍历路径推入路径栈
    if(vexnum == G->numVertexes) {
        vector<int> tmp;
        for (int i = 0; i < graph->numVertexes; i++) {
            tmp.push_back(visit_vex[i]);
        }
        path.push_back(tmp);
    } else{
        for(int j = 0; j < graph->numVertexes; j++){
            //检查所有邻接顶点
            if (graph->AdjMatrix[i][j] < MAX_WEIGHT && visited[j] == 0){
                //如果两顶点间有路径且仍未访问
                DFS(graph, j, visited, visit_vex, idx);
                visited[j] = 0; //回溯时
                idx--;
            }
        }
    }
}

void DFSTraverse(Graph* graph, int visited[], int visit_vex[], int& idx){
    for(int i = 0; i < graph->numVertexes; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < graph->numVertexes; i++){
        if(visited[i] == 0){
            DFS(graph ,i, visited, visit_vex, idx);
        }
    }
}

void navigator(){
    cout<<"输入出发点编号: ";
    int start;
    cin>>start;
    int idx = 0;
    int visited[VERTEXES_NUM] = {0};
    int visit_vex[VERTEXES_NUM] = {0};

    DFS(G, start, visited, visit_vex, idx);
    for (auto& e: path) {
        for(int i = 0; i < G->numVertexes; i++){
            if(i == G->numVertexes - 1){
                cout<<&G->vex[e[i]].name[0]<<endl;
            } else{
                cout<<&G->vex[e[i]].name[0]<<" -> ";
            }
        }
    }
    path.clear(); //每次调用后都清空路径栈
    menu();
}

//Dijkstra最短路径  v0为起点，path保存v0至下标点最短路径所经过的顶点，weight为v0到各点最短路径的权值
void shortestPath(int v0, int* path, int* weight){
    int isFound[VERTEXES_NUM] = {0}; //是否已经求得v0至此下标顶点的最短路径

    //初始化
    for(int v = 0; v < G->numVertexes; v++){
        isFound[v] = 0;
        weight[v] = G->AdjMatrix[v0][v];
        path[v] = v0;
    }
    path[v0] = v0; //v0至v0 需经过v0
    isFound[v0] = 1; //v0至v0最短路径已经找到

    //主循环 每次求得v0至某点的最短路径
    for(int i = 1; i < G->numVertexes; i++){
        int min = MAX_WEIGHT;
        int tmp;
        int w;
        //寻找当前离v0最近的点
        for(w = 0; w < G->numVertexes; w++){
            if(isFound[w] == 0 && weight[w] < min){
                min = weight[w];
                tmp = w;
            }
        }
        isFound[tmp] = 1; //求得v0至当前最近点的最短路径

        //根据找到的当前最近点的最短路径，修正v0 至 与当前最近点有关联 的点的最短路径
        for(w = 0; w < G->numVertexes; w++){
            if(isFound[w] == 0 && (min+G->AdjMatrix[tmp][w] < weight[w])){
                //说明找到了更短的路径，修正权值数组和最短路径
                weight[w] = min + G->AdjMatrix[tmp][w];
                path[w] = tmp;
            }
        }
    }
}

void shortNavi(){
    int s, e;
    cout<<"输入起点 :";
    cin>>s;
    cout<<"输入终点 :";
    cin>>e;
    int p[VERTEXES_NUM] = {0};
    int w[VERTEXES_NUM] = {0};
    shortestPath(s, p, w); //从s点到各点的最短路径都在p数组中
    int i = e;
    int re[VERTEXES_NUM] = {0};
    int len = 0;
    re[len++] = e;//终点
    while(i != s){
        re[len++] = p[i];
        i = p[i]; //将vi的前驱顶点赋值vi
    }
    cout<<"路线 :";
    for(int j = len - 1; j >=0; j--){
        if(j != 0){
            cout<<&G->vex[re[j]].name[0]<<" -> ";
        }else{
            cout<<&G->vex[re[j]].name[0]<<endl;
        }
    }
    cout<<"路径总长度 :"<<w[e]<<endl;
    menu();
}

//prim最小生成树
void miniSpanTree(int* path, int* weight){
    int cost[VERTEXES_NUM] = {0};

    //初始化 cost[i]保存了v0到vi的距离
    for(int i = 0; i < G->numVertexes; i++){
        cost[i] = G->AdjMatrix[0][i];
        path[i] = 0;
        weight[i] = 0;
    }
    for(int i = 1; i < G->numVertexes; i++){
        int min = MAX_WEIGHT;
        int k = 0;

        //找到当前cost中的最小值
        for(int j = 1; j < G->numVertexes; j++){
            if(cost[j] != 0 && cost[j] < min){
                min = cost[j];
                k = j; //k保存当前最小值下标
            }
        }
        weight[k] = cost[k]; //将此边长度存入weight
        cost[k] = 0; //表示下标k的顶点已经完成任务 置0

        for(int j = 1; j < G->numVertexes; j++){
            if(G->AdjMatrix[k][j] < cost[j]){
                cost[j] = G->AdjMatrix[k][j];//将与k邻接的较小权值存入cost
                path[j] = k; //cost中所存权值为从k到j的
            }
        }
    }
}

void showPipe(){
    int w[VERTEXES_NUM] = {0};
    int p[VERTEXES_NUM] = {0};
    miniSpanTree(p, w);
    cout<<"需要架设管道: "<<endl;
    for(int i = 1; i < G->numVertexes; i++){
        cout<<"("<<&G->vex[p[i]].name[0]<<" -> "<<&G->vex[i].name[0]<<") 长度 :"<<w[i]<<endl;
    }
    menu();
}