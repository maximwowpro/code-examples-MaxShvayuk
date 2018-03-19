#include <iostream>

#include <battlefield.hpp>

using namespace std;

int main()
{


    Battlefield test(5);

    test.drawBattlefield();

    test.updatePlayer();

    test.updateEnemies();

    std::cout<<"\n\n\n\n\n\n\n\n\n"<<std::endl;

    test.drawBattlefield();

    return 0;
}

