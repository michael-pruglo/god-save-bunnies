#include "ColonySimulator.hpp"
#include <ctime>

int main()
{
    srand(time(nullptr));
    ColonySimulator().run();
}
