#pragma once
#include "string"

template<typename WeightType>
class IArc {
public:
    virtual ~IArc() = default;

    virtual WeightType GetCost() const = 0;

    virtual std::string Describe() const = 0;
};
