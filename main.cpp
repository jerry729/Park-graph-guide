#include <iostream>
#include "Graph.h"
#include "Tourism.h"
using namespace std;

void showMenu();

Graph* G = new Graph();

int main() {
    cout<<"===== Welcome to Disneyland in L.A. ====="<<endl;
    CreateMGraph(G);
    showMenu();
    return 0;
}

//入口菜单
void showMenu(){

    menu();
    while(true){
        char choice;
        cin>>choice;
        switch (choice) {
            case '1':
                showGraph(G);
                break;
            case '2':
                cout<<"输入景点编号: ";
                int v;
                cin>>v;
                FindEdge(v);
                break;
            case '3':
                navigator();
                break;
            case '4':
                shortNavi();
                break;
            case '5':
                showPipe();
                break;
            case '0':
                exit(0);
            default:
                cout<<"请正确输入 :";
                break;
        }
    }
}
