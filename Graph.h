//
// Created by Zhaorui Yang on 2021/5/13.
//

#ifndef GRAPHCPRO_GRAPH_H
#define GRAPHCPRO_GRAPH_H
#define VERTEXES_NUM 20
#define NAME_STR_LEN 1024
#define DESC_STR_LEN 1024
#define MAX_WEIGHT INT_MAX - 5000

#include <iostream>
#include <string>
#include <array>

//顶点从0开始编号 最多到VERTEXES_NUM-1
struct Vertex{
    int num;
    std::array<char, NAME_STR_LEN> name;
    std::array<char, DESC_STR_LEN> describe;

    Vertex();
};

typedef int EdgeType;

struct Edge{
    Vertex v1;
    Vertex v2;
    int weight;
};


struct Graph{
    EdgeType AdjMatrix[VERTEXES_NUM][VERTEXES_NUM]; //邻接矩阵
    Vertex vex[VERTEXES_NUM]; //顶点表
    int numVertexes, numEdges; //当前顶点数， 边数

    Graph();
    bool insertVex(Vertex v);
    bool insertEdge(Edge edge);
    Vertex GetVertex(int v);
};

int findVex(std::array<char, NAME_STR_LEN> s, Graph* G);
void CreateMGraph(Graph* G);
void showGraph(Graph* G);
void menu();
extern Graph* G;

#endif //GRAPHCPRO_GRAPH_H
