#include "tests_func_4.h"

#include "../DataStructures/UndirectedGraph.h"
#include "../DataStructures/Dijkstra.h"
#include "../DataStructures/Kruskal.h"
#include "Arcs.h"
#include "../DataStructures/BubbleSort.h"
#include "../DataStructures/QuickSort.h"

#include <cassert>
#include <iostream>
#include <climits>


void TestGraphMethods() {
    UndirectedGraph<int, int> g;
    g.AddVertex(0);
    g.AddVertex(1);
    assert(g.GetVertexCount() == 2);
    std::string info = "route";
    g.AddEdge(0,1, ShrdPtr<IArc<int>>(new BusArcData(5, info)));
    assert(g.GetEdgeCount() == 1);
    assert(g.HasEdge(0,1));

    g.RemoveEdge(0,1);
    assert(!g.HasEdge(0,1));
    assert(g.GetEdgeCount()==0);

    g.RemoveVertex(1);
    assert(!g.HasVertex(1));
    assert(g.GetVertexCount()==1);

    std::cout << "[OK] TestGraphMethods passed\n";
}

void TestDijkstra() {
    UndirectedGraph<int, int> g;
    std::string info = "route";
    for(int i=0; i<3; i++) g.AddVertex(i);
    g.AddEdge(0,1,ShrdPtr<IArc<int>>(new BusArcData(1, info)));
    g.AddEdge(1,2,ShrdPtr<IArc<int>>(new TrainArcData(2, 52)));
    g.AddEdge(0,2,ShrdPtr<IArc<int>>(new TaxiArcData(3, 2)));

    auto dist = Dijkstra(g, 0, INT_MAX - 1);
    assert(dist->Get(0)==0);
    assert(dist->Get(1)==1);
    assert(dist->Get(2)==3);
    std::cout << "[OK] TestDijkstra passed\n";
}

void TestKruskal() {
    UndirectedGraph<int, int> g;
    std::string info = "route";
    for(int i=0; i<4; i++) g.AddVertex(i);
    g.AddEdge(0,1,ShrdPtr<IArc<int>>(new BusArcData(1, info)));
    g.AddEdge(0,2,ShrdPtr<IArc<int>>(new TrainArcData(2, 215)));
    g.AddEdge(0,3,ShrdPtr<IArc<int>>(new BusArcData(4, info)));
    g.AddEdge(1,2,ShrdPtr<IArc<int>>(new TaxiArcData(1, 2)));
    g.AddEdge(1,3,ShrdPtr<IArc<int>>(new TaxiArcData(1, 1)));
    g.AddEdge(2,3,ShrdPtr<IArc<int>>(new TrainArcData(1, 32)));

    QuickSort<Arc<int, int>> sorter;
    auto mstEdges = KruskalMST(g,4, &sorter);
    assert(mstEdges.GetLength()==3);

    std::cout << "[OK] TestKruskal passed\n";
}

void RunAllFunctionalTests(){
    TestGraphMethods();
    TestDijkstra();
    TestKruskal();
    std::cout<<"All functional tests done.\n";
}
