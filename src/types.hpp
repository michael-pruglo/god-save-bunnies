#pragma once

#include "utility/Logger.hpp"
#include "utility/DoublyLinkedList.hpp"
#include <string>

enum class Sex { MALE, FEMALE };
enum class Color { WHITE, BROWN, BLACK, SPOTTED, _SIZE };

struct Bunny
{
    Sex sex;
    Color color;
    size_t age;
    std::string name;
    bool is_radioactive;
};
