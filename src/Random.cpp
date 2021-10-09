#include "Random.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

Sex Random::rand_sex()
{
    return static_cast<Sex>(rand()%2);
}

Color Random::rand_color()
{
    return static_cast<Color>(rand() % static_cast<int>(Color::_SIZE));
}

std::string Random::rand_name(Sex sex)
{
    static const std::vector<std::string> male_names = {
        "Sasha", "Mike", "Sindri", "Richie", "Atwan", "Michael",
    };
    static const std::vector<std::string> female_names = {
        "Lilly", "Becky", "Anne", "Mia", "Lucy",
    };

    if (sex == Sex::MALE)
        return male_names[rand()%male_names.size()];
    else
        return female_names[rand()%female_names.size()];
}

bool Random::rand_bool(int truth_probability_percent)
{
    return rand()%100 < truth_probability_percent;
}

std::vector<size_t> Random::rand_sequence(size_t min, size_t max, size_t len)
{
    std::vector<size_t> res(max-min);
    std::iota(res.begin(), res.end(), min);
    std::random_shuffle(res.begin(), res.end());
    res.resize(len);
    return res;
}

std::vector<size_t> Random::rand_sequence(size_t min, size_t max, size_t len, const std::function<bool(size_t)>& exclusions)
{
    auto res = rand_sequence(min, max, max-min);
    res.erase(std::remove_if(res.begin(), res.end(), exclusions), res.end());
    res.resize(len);
    return res;
}
