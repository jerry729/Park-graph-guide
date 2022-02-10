//
// Created by Zhaorui Yang on 2021/5/17.
//

#ifndef GRAPHCPRO_TOURISM_H
#define GRAPHCPRO_TOURISM_H
#include "Graph.h"
#include <iostream>
#include <vector>
extern Graph* G;

void FindEdge(int v);
void DFS(Graph* graph, int i, int visited[], int visit_vex[], int& idx);
void DFSTraverse(Graph* graph, int visited[], int visit_vex, int& idx);
void shortestPath(int v0, int* path, int* weight);
void miniSpanTree(int* path, int* weight);

void showPipe();
void navigator();
void shortNavi();


#endif //GRAPHCPRO_TOURISM_H
