#pragma once

#include "../DataStructures/UndirectedGraph.h"

UndirectedGraph<int, int>* GenerateRandomGraph(int n, int m, int maxWeight=10);

long long TimeDijkstra(UndirectedGraph<int, int>& g, int start);

long long TimeKruskal(UndirectedGraph<int, int>& g);

void RunLoadTestsAndSaveCSV();
