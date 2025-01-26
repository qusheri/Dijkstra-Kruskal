#include <chrono>
#include <fstream>
#include <iostream>

#include "../DataStructures/UndirectedGraph.h"
#include "../DataStructures/DynamicArray.h"
#include "../DataStructures/Dijkstra.h"
#include "../DataStructures/Kruskal.h"
#include "../DataStructures/BubbleSort.h"
#include "../DataStructures/QuickSort.h"
#include "Arcs.h"

UndirectedGraph<int, int>* GenerateRandomGraph(int n, int m, int maxWeight=10) {
    auto* g = new UndirectedGraph<int, int>();
    for(int i=0; i<n; i++){
        g->AddVertex(i);
    }
    srand((unsigned)time(nullptr));
    int count=0;
    while(count<m){
        int u = rand()%n;
        int v = rand()%n;
        if(u==v) continue;
        if(!g->HasEdge(u,v)){
            int w = (rand()%maxWeight)+1;
            g->AddEdge(u,v,ShrdPtr<IArc<int>>(new TrainArcData(w,2)));
            count++;
        }
    }
    return g;
}

long long TimeDijkstra(UndirectedGraph<int, int>& g, int start) {
    auto begin = std::chrono::high_resolution_clock::now();
    Dijkstra(g, start, INT_MAX - 1);
    auto end = std::chrono::high_resolution_clock::now();
    long long t = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    return t;
}

long long TimeKruskal(UndirectedGraph<int, int>& g) {
    QuickSort<Arc<int, int>> sorter;
    auto begin = std::chrono::high_resolution_clock::now();
    auto mstEdges = KruskalMST(g, g.GetVertexCount(), &sorter);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

void RunLoadTestsAndSaveCSV() {
    std::vector<int> testSizes;
    for(int i = 1; i <= 10'001; i += 500) {
        testSizes.push_back(i);
    }

    std::ofstream csv("../tests_4/performance_data.csv");
    csv << "TestName";
    for(auto ts: testSizes){
        csv << "," << ts;
    }
    csv << "\n";

    {
        csv << "Dijkstra";
        std::cout << "Dijkstra" << std::endl;
        for(auto ts: testSizes){
            std::cout << ts << " elements: ";
            int n=ts;
            int m=ts -1;
            auto g = GenerateRandomGraph(n,m);
            long long t = TimeDijkstra(*g, 0);
            csv << "," << t;
            std::cout << t << " ms\n";
        }
        csv << "\n";
    }

    {
        csv << "Kruskal";
        std::cout << "Kruskal" << std::endl;
        for(auto ts: testSizes){
            std::cout << ts << " elements: ";
            int n=ts;
            int m=ts / 2;
            auto* g = GenerateRandomGraph(n,m);
            long long t = TimeKruskal(*g);
            csv << "," << t;
            std::cout << t << " ms\n";
            delete g;
        }
        csv << "\n";
    }
    csv.close();
    std::cout << "performance_data.csv generated.\n";
    std::system("python3 ../plot_graph.py");
}
