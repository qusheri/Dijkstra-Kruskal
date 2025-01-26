#pragma once
#include "../DataStructures/IArc.h"
#include <string>

class BusArcData : public IArc<int> {
private:
    int cost; 
    std::string routeName;
public:
    BusArcData(int c, std::string& route)
        : cost(c), routeName(route) {}

    int GetCost() const override {
        return cost;
    }

    std::string Describe() const override {
        return "Bus route=" + routeName + ", cost=" + std::to_string(cost);
    }
};

class TrainArcData : public IArc<int> {
private:
    int ticketPrice;
    int travelTime;
public:
    TrainArcData(int p, int t)
        : ticketPrice(p), travelTime(t) {}

    int GetCost() const override {
        return ticketPrice;
    }

    std::string Describe() const override {
        return "Train price=" + std::to_string(ticketPrice) + 
               ", time=" + std::to_string(travelTime);
    }
};

class TaxiArcData : public IArc<int> {
private:
    int baseFare;
    int distance;
public:
    TaxiArcData(int baseF, int dist)
        : baseFare(baseF), distance(dist) {}

    int GetCost() const override {
        return baseFare + distance;
    }

    std::string Describe() const override {
        return "Taxi baseFare=" + std::to_string(baseFare) +
               ", distance=" + std::to_string(distance) + " => cost=" + std::to_string(GetCost());
    }
};
