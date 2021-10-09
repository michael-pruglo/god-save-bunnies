#include "ColonySimulator.hpp"
#include "Random.hpp"
#include <ctime>
#include <vector>
#include <algorithm>

namespace
{
    template<typename Container, typename Item>
    bool contains(const Container& container, const Item& item)
    {
        return std::find(container.begin(), container.end(), item) != container.end();
    }
}

void ColonySimulator::run()
{
    init();
//    while (blist.size() > 0)
    for (int i = 0; i < 3; ++i)
    {
        std::cout<<"Turn #"<<i+1<<"\n"<<std::flush;
        take_turn();
        std::cout<<"---------------------"<<"\n"<<std::flush;
        std::cout<<blist.size()<<"  ";
        int r = 0;
        for (const auto& bunny: blist) std::cout<<bunny.name<<(bunny.is_radioactive?++r,"[r] ":" ");
        std::cout<<"\n rads: "<<r<<"\n";
        std::cout<<"\n=======================\n\n\n"<<std::flush;
    }
}

void ColonySimulator::init()
{
    srand(time(nullptr));
    constexpr size_t INITIAL_POPULATION = 5;
    for (size_t i = 0; i < INITIAL_POPULATION; ++i)
        blist.push_back(BunnyBuilder::build_bunny());
}

bool ColonySimulator::take_turn()
{
    size_t fertile_males = 0;
    size_t radioactives = 0;

    std::cout<<"a"<<std::flush;
    for (auto& bunny: blist)
    {
        ++bunny.age;
        if (bunny.sex==Sex::MALE && bunny_is_fertile(bunny))
            ++fertile_males;
        if (bunny.is_radioactive)
            ++radioactives;
    }
    std::cout<<"b"<<std::flush;


    std::vector<size_t> food_shortage_victims;
    if (blist.size() > 30)
        food_shortage_victims = Random::rand_sequence(0, blist.size(), blist.size()/2);
    const auto& radioactive_victims = Random::rand_sequence(0, blist.size()-radioactives, radioactives);

    std::cout<<"\nfood victims:  "; for (const auto& x: food_shortage_victims) std::cout<<x<<"  "; std::cout<<"\n";
    std::cout<<"\nradio victims:  "; for (const auto& x: radioactive_victims) std::cout<<x<<"  "; std::cout<<"\n";

    std::cout<<"c"<<std::flush;
    size_t i = 0, non_rad_i = 0;
    for (auto bunny = blist.begin(); bunny != blist.end(); ++bunny)
    {
        const bool is_rad = bunny->is_radioactive;

        if (bunny->sex==Sex::FEMALE && bunny_is_fertile(*bunny))
            produce_children(*bunny, fertile_males);

        if (bunny_is_old(*bunny))
            kill_bunny(bunny, "old age");
        else if (contains(food_shortage_victims, i))
            kill_bunny(bunny, "food shortage");
        else if (!bunny->is_radioactive && contains(radioactive_victims, non_rad_i))
            bunny->is_radioactive = true;

        non_rad_i += !is_rad;
        ++i;
    }
    std::cout<<"d\n"<<std::flush;
}

void ColonySimulator::produce_children(const Bunny& mother, size_t count)
{
    for (int i = 0; i < count; ++i)
    {
        const auto& child = BunnyBuilder::build_bunny(mother);
        blist.push_back(child);
        //Logger::message(mother.name+" gave birth! Behold, "+child.name+" is here!");
    }
}

#include<sstream>
void ColonySimulator::kill_bunny(DoublyLinkedList<Bunny>::iterator bunny, std::string reason)
{
    blist.erase(bunny);

    std::stringstream ss;
    ss << bunny->name << " died at the age of "<<bunny->age<<". Reason: "<<reason;
    //Logger::message(ss.str());
}

bool ColonySimulator::bunny_is_fertile(const Bunny& bunny)
{
    return !bunny.is_radioactive && bunny.age >= 2;
}

bool ColonySimulator::bunny_is_old(const Bunny& bunny)
{
    return bunny.age >= (bunny.is_radioactive ? 50 : 10);
}

Bunny BunnyBuilder::build_bunny()
{
    Bunny bunny;
    bunny.sex = Random::rand_sex();
    bunny.color = Random::rand_color();
    bunny.age = 0;
    bunny.name = Random::rand_name(bunny.sex);
    bunny.is_radioactive = Random::rand_bool(3);
    return bunny;
}

Bunny BunnyBuilder::build_bunny(const Bunny& mother)
{
    auto bunny = build_bunny();
    bunny.color = mother.color;
    return bunny;
}
