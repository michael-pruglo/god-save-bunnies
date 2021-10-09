#pragma once

#include "types.hpp"

class ColonySimulator
{
public:
    void run();

private:
    void init();
    bool take_turn();
    void produce_children(const Bunny& mother, size_t count);
    void kill_bunny(DoublyLinkedList<Bunny>::iterator bunny, std::string reason);

    static bool bunny_is_fertile(const Bunny&);
    static bool bunny_is_old(const Bunny&);

private:
    DoublyLinkedList<Bunny> blist;
};


class BunnyBuilder
{
public:
    static Bunny build_bunny();
    static Bunny build_bunny(const Bunny& mother);
};

