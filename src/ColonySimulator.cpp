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
    for (size_t turn = 1; blist.size() > 0; ++turn)
    {
        std::cout<<"Turn #"<<turn<<"\n"<<std::flush;
        take_turn();
        std::cout<<"\n---------------------\n"<<std::flush;
        int r = 0;
        for (const auto& bunny: blist) std::cout<<bunny.name<<(bunny.is_radioactive?++r,"[r] ":" ");
        std::cout<<"\n total bunnies: "<<blist.size();
        std::cout<<"\n rads: "<<r;
        std::cout<<"\n=======================\n\n\n"<<std::flush;
    }
}

const ColonySimulator::BunnyList& ColonySimulator::get_bunnies() const
{
    return blist;
}

void ColonySimulator::init()
{
    constexpr size_t INITIAL_POPULATION = 5;
    for (size_t i = 0; i < INITIAL_POPULATION; ++i)
        blist.push_back(BunnyBuilder::build_bunny());
}

bool ColonySimulator::take_turn()
{
    std::cout<<"aging\n"<<std::flush;
    initiate_aging();
    std::cout<<"radio\n"<<std::flush;
    initiate_radioactive_massacre();
    if (blist.size() > 1000)
    {
        std::cout<<"food shortage\n"<<std::flush;
        initiate_food_shortage();
    }
    std::cout<<"procreation\n"<<std::flush;
    initiate_procreation();
    std::cout<<"turn done\n"<<std::flush;
}

void ColonySimulator::initiate_aging()
{
    for (auto bunny = blist.begin(); bunny != blist.end(); ++bunny)
    {
        ++bunny->age;
        if (bunny_is_old(*bunny))
            kill_bunny(bunny, "old age");
    }
}

void ColonySimulator::initiate_procreation()
{
    size_t fertile_males = 0;
    for (const auto& bunny: blist)
    {
        if (bunny.sex==Sex::MALE && bunny_is_fertile(bunny))
            ++fertile_males;
    }
    std::cout<<"\tcounted "<<fertile_males<<" fertile males\n"<<std::flush;
    const auto this_generation_end = blist.end();
    for (auto bunny = blist.begin(); bunny!=this_generation_end; ++bunny)
    {
        if (bunny->sex==Sex::FEMALE && bunny_is_fertile(*bunny))
        {
            std::cout<<"\t"<<bunny->name<<" produces children\n"<<std::flush;
            produce_children(*bunny, fertile_males);
        }
    }
    std::cout<<"\t procreation done.\n"<<std::flush;
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

void ColonySimulator::initiate_food_shortage()
{
    size_t init_size = blist.size();
    std::vector<size_t> food_shortage_victims;
    food_shortage_victims = Random::rand_sequence(0, blist.size(), blist.size()/2);
    std::cout<<"\nfood victims:  "; for (const auto& x: food_shortage_victims) std::cout<<x<<"  "; std::cout<<"\n";

    size_t i = 0;
    for (auto bunny = blist.begin(); bunny != blist.end(); ++bunny)
    {
        if (contains(food_shortage_victims, i))
            kill_bunny(bunny, "food shortage");
        ++i;
    }
    assert(blist.size() == init_size - init_size/2);
}

void ColonySimulator::initiate_radioactive_massacre()
{
    size_t radioactives = 0;

    for (auto& bunny: blist)
    {
        if (bunny.is_radioactive)
            ++radioactives;
    }

    size_t to_be_converted_count = std::min(radioactives, blist.size()-radioactives);
    const auto& radioactive_victims = Random::rand_sequence(0, to_be_converted_count, to_be_converted_count);
    std::cout<<"\tradio victims(tbcc="<<to_be_converted_count<<" s="<<blist.size()<<"r="<<radioactives<<"):  ";
    for (const auto& x: radioactive_victims) std::cout<<x<<"  "; std::cout<<"\n";

    size_t non_rad_i = 0, converts = 0;
    for (auto& bunny: blist)
    {
        if (!bunny.is_radioactive)
        {
            if (contains(radioactive_victims, non_rad_i))
            {
                bunny.is_radioactive = true;
                ++converts;
            }
            ++non_rad_i;
        }
    }
    assert(converts == to_be_converted_count);
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
