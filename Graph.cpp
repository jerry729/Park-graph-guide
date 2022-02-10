//
// Created by Zhaorui Yang on 2021/5/13.
//
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

void CreateMGraph(Graph* G){
    string infileName("Vertex.txt");
    string line;
    ifstream in;
    in.open(infileName, ifstream::in | ifstream::binary);
    vector<Vertex> vs;
    if(!in){
        cerr<<"failed to open Vertex.txt"<<endl;
        exit(EXIT_FAILURE);
    } else{
        getline(in, line);
        while(getline(in, line)) {
            Vertex tmp;
            istringstream iStr(line);
            iStr >> tmp.num;
            array<char, NAME_STR_LEN> s{'\0'};
            vector<std::array<char, NAME_STR_LEN>>words;
            char a;
            iStr.read(reinterpret_cast<char* >(&a), sizeof(a));
            while (iStr.getline(&s[0], NAME_STR_LEN, '\t')) {
                words.push_back(s);
            }
            char* b = (char*) malloc(sizeof(char) * s.size());
            for(int i = 0; i < s.size(); i++){
                tmp.name[i] = words[0][i];
                tmp.describe[i] = words[1][i];
            }
            vs.push_back(tmp);
        }
        in.close();
    }
    G->numVertexes = vs.size();
    for(int i = 0; i < G->numVertexes; i++){
        G->vex[i] = vs[i];
    }

    string edgeFile("Edge.txt");
    ifstream inEdge;
    inEdge.open(edgeFile, ifstream::in | ifstream::binary);
    vector<string> es;
    if(!inEdge){
        cerr<<"failed to open Edge.txt"<<endl;
        exit(EXIT_FAILURE);
    } else{
        getline(inEdge, line);
        G->numEdges = 0;
        while(getline(inEdge, line)){
            istringstream istringstream1(line);
            array<char, NAME_STR_LEN> c{'\0'};
            vector<std::array<char, NAME_STR_LEN>> eWords;
            while (istringstream1.getline(&c[0], NAME_STR_LEN, '\t')){
                eWords.push_back(c);
            }
            int v1 = findVex(eWords[0], G);
            int v2 = findVex(eWords[1], G);
            if(v1 != -1 && v2 != -1){
                stringstream ss(&eWords[2][0]);
                ss >> G->AdjMatrix[v1][v2];
                G->AdjMatrix[v2][v1] = G->AdjMatrix[v1][v2];
                G->numEdges++;
            }
        }
        inEdge.close();
    }
}

int findVex(array<char, NAME_STR_LEN> s, Graph* G){
    int flag = -1;
    for(int i = 0; i < G->numVertexes; i++){
        if(!strcmp(&G->vex[i].name[0], &s[0])){
            flag = G->vex[i].num;
        }
    }
    return flag;
}

//必须先在图中插入相应的顶点 才能插入边
bool Graph::insertEdge(Edge edge) {
    //越界
    if(edge.v1.num < 0 || edge.v1.num >= VERTEXES_NUM || edge.v2.num < 0 || edge.v2.num >= VERTEXES_NUM){
        return false;
    }
    //图中是否存在
    if((findVex(edge.v1.name, this) == -1) || (findVex(edge.v2.name, this) == -1)){
        return false;
    }
    AdjMatrix[edge.v1.num][edge.v2.num] = edge.weight;
    AdjMatrix[edge.v2.num][edge.v1.num] = edge.weight;
    numEdges++;
}

bool Graph::insertVex(Vertex v) {
    if(numVertexes == VERTEXES_NUM){
        cerr<<"已达最大景点数，请申请扩容"<<endl;
        return false;
    }
    vex[numVertexes++] = v;
    return true;
}

Graph::Graph(): numVertexes(0), numEdges(0){
    for(int i = 0; i < VERTEXES_NUM; i++){
        vex[i].num = i;
        for(int j = 0; j < NAME_STR_LEN; j++){
            vex[i].name[j] = '\0';
        }
        for(int j = 0; j < DESC_STR_LEN; j++){
            vex[i].name[j] = '\0';
        }
    }
    for(int i = 0; i < VERTEXES_NUM; i++){
        for(int j = 0; j < VERTEXES_NUM; j++){
            if(i == j){
                AdjMatrix[i][j] = 0;
            } else{
                AdjMatrix[i][j] = MAX_WEIGHT;
            }
        }
    }
}

Vertex::Vertex(): num(0), name{'\0'}, describe{'\0'}{}

void showGraph(Graph* G){
    cout<<"顶点数目 ：";
    cout<<G->numVertexes<<endl;
    cout<<"-----景点-----"<<endl;
    cout<<"编号\t景点名"<<endl;
    for(int i = 0; i < G->numVertexes; i++){
        cout<<G->vex[i].num<<"\t"<<&G->vex[i].name[0]<<endl;
    }
    cout<<"-----路径-----"<<endl;
    for(int i = 0; i < G->numVertexes; i++){
        for(int j = i + 1; j < G->numVertexes; j++){
            if(G->AdjMatrix[i][j] != MAX_WEIGHT && i != j){
                cout<<"(v"<<i<<",v"<<j<<") "<<G->AdjMatrix[i][j]<<endl;
            }
        }
    }
    cout<<endl;
    menu();
}

void menu(){
    cout<<"1.创建景区景点图"<<endl;
    cout<<"2.查询景点信息"<<endl;
    cout<<"3.旅游导览规划"<<endl;
    cout<<"4.两点最短路径"<<endl;
    cout<<"5.铺设电路规划"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入操作编号(0~5) :";
}

Vertex Graph::GetVertex(int v) {
    return vex[v];
}


