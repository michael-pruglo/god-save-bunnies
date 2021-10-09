#pragma once

#include "types.hpp"
#include <vector>
#include <functional>

class Random
{
public:
    static Sex rand_sex();
    static Color rand_color();
    static std::string rand_name(Sex sex);
    static bool rand_bool(int truth_probability_percent);
    static std::vector<size_t> rand_sequence(size_t min, size_t max, size_t len);
    static std::vector<size_t> rand_sequence(size_t min, size_t max, size_t len, const std::function<bool(size_t)>& exclusions);
};
