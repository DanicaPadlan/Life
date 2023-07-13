#include "ConwayCell.hpp"

//updates the alive variable in parent class,
//if alive, turns dead
//if dead turns alive
void ConwayCell::evolve() {
    AbstractCell::alive = !AbstractCell::alive;
}

//default method to fulfill AbstactCell's virtual getAge()
//age does not matter for ConwayCells
int ConwayCell::getAge() {
    return 0;
}

//empty method to fulfill AbstactCell's virtual updateAge()
//does not effect ConwayCells
void ConwayCell::updateAge() {}