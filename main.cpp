#include <iostream>

#include "tests_4/tests_func_4.h"
#include "tests_4/tests_load_4.h"
#include "tests_4/Arcs.h"
#include "DataStructures/Dijkstra.h"
#include "DataStructures/Kruskal.h"
#include "DataStructures/QuickSort.h"

#include <climits>
#include <stdexcept>

void ConsoleLoop() {
    UndirectedGraph<int, int> G;

    while(true){
        std::cout<<"\n======== Menu =======\n";
        std::cout<<"1) Run functional tests\n";
        std::cout<<"2) Run load tests & CSV\n";
        std::cout<<"3) Manipulate graph\n";
        std::cout<<"4) Dijkstra\n";
        std::cout<<"5) Kruskal MST\n";
        std::cout<<"0) Exit\n";
        std::cout<<"Choice: ";
        int c; std::cin>>c;
        if(!std::cin) {std::cin.clear(); break;}
        if(c==0) break;

        switch(c) {
            case 1:
                RunAllFunctionalTests();
                break;
            case 2:
                RunLoadTestsAndSaveCSV();
                break;
            case 3: {
                std::cout<<"--- Graph commands:\n";
                std::cout<<" (1) Add vertex\n";
                std::cout<<" (2) Remove vertex\n";
                std::cout<<" (3) Add edge\n";
                std::cout<<" (4) Remove edge\n";
                std::cout<<"Choice: ";
                int gc; std::cin>>gc;
                if(gc==1) {
                    int v;
                    std::cout<<" Vertex: ";
                    std::cin>>v;
                    G.AddVertex(v);
                } else if(gc==2){
                    int v;
                    std::cout<<" Vertex: ";
                    std::cin>>v;
                    G.RemoveVertex(v);
                } else if(gc==3){
                    int u,v,w;
                    std::cout<<" (u,v,w): ";
                    std::cin>>u>>v>>w;
                    G.AddEdge(u,v,ShrdPtr<IArc<int>>(new TrainArcData(w, 321)));
                } else if(gc==4){
                    int u,v;
                    std::cout<<" (u,v): ";
                    std::cin>>u>>v;
                    G.RemoveEdge(u,v);
                }
                std::cout<<"[OK]\n";
            } break;
            case 4: {
                // Dijkstra
                std::cout<<"Enter start: ";
                int s; std::cin>>s;
                try {
                    auto dist = Dijkstra(G, s, INT_MAX - 1);
                    std::cout<<"Distances:\n";
                    auto vertices = G.GetAllVertices();
                    for(int i=0; i < G.GetVertexCount(); i++){
                        std::cout<<"dist["<<vertices[i]<<"]="<<dist->Get(vertices[i])<<"\n";
                    }
                } catch(const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            } break;
            case 5: {
                // Kruskal
                QuickSort<Arc<int, int>> sorter;
                auto mst = KruskalMST(G, G.GetVertexCount(), &sorter);
                std::cout<<"MST edges:\n";
                auto vertices = G.GetAllVertices();
                auto it = mst.GetIterator();
                while(!it->atEnd()){
                    auto e = **it;
                    std::cout<< e.from <<"--"<< e.to<<" weight="<<e.data->GetCost()<<"\n";
                    ++(*it);
                }
            } break;
            default:
                break;
        }
    }
    std::cout<<"Bye.\n";
}

int main(){
    ConsoleLoop();
}
