#pragma once

#include "types.hpp"

class ColonySimulator
{
public:
    using BunnyList = DoublyLinkedList<Bunny>;
    void run();

private:
    void init();
    bool take_turn();

    void initiate_aging();
    void initiate_procreation();
    void produce_children(const Bunny& mother, size_t count);
    void initiate_food_shortage();
    void initiate_radioactive_massacre();
    void kill_bunny(BunnyList::iterator bunny, std::string reason);

    static bool bunny_is_fertile(const Bunny&);
    static bool bunny_is_old(const Bunny&);

private:
    BunnyList blist;
};


class BunnyBuilder
{
public:
    static Bunny build_bunny();
    static Bunny build_bunny(const Bunny& mother);
};

