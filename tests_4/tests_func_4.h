#pragma once

struct MyWeight {
    int cost;
    MyWeight(int c=0): cost(c) {}

    MyWeight operator+(const MyWeight& b) const {
        return MyWeight(this->cost + b.cost);
    }

    bool operator<(const MyWeight& b) const{
        return this->cost < b.cost;
    }

    bool operator>(const MyWeight& b) const{
        return this->cost > b.cost;
    }

    bool operator==(const MyWeight& b) const{
        return this->cost == b.cost;
    }
};

void TestGraphMethods();

void TestDijkstra();

void TestKruskal();

void RunAllFunctionalTests();
