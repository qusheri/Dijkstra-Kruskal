cmake_minimum_required(VERSION 3.29)
project(Graph_Dijkstra_BF_Kruskal)

set(CMAKE_CXX_STANDARD 20)

add_executable(Graph_Dijkstra_BF_Kruskal main.cpp
        DataStructures/SequenceIterator.h
        DataStructures/IGraph.h
        DataStructures/UndirectedGraph.h
        DataStructures/Dijkstra.h
        DataStructures/Kruskal.h
        tests_4/tests_func_4.h
        tests_4/tests_load_4.h
        DataStructures/IArc.h
        tests_4/Arcs.h
        DataStructures/MainArc.h
        tests_4/tests_load_4.cpp
        tests_4/tests_func_4.cpp
)
