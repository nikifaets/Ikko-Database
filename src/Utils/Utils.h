#pragma once

#include <vector>

namespace Utils{

    template<typename T>
    std::vector<T> concatenate(std::vector<T> v1, std::vector<T> v2);
}

#include "Utils.cpp"