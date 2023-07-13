#include "FredkinCell.hpp"

//updates the alive variable in parent class,
//if alive, turns dead
//if dead turns alive
void FredkinCell::evolve() {
    AbstractCell::alive = !AbstractCell::alive;
}

//increase the age variable
void FredkinCell::updateAge() {
    age++;
}

//returns the age value
//VALID getter: need to print out age for Fredkin's in grid
int FredkinCell::getAge() {
    return age;
}

//checks if a FredkinCell can turninto a ConwayCell
bool FredkinCell::turnToConway() {
    return age == 2;
}