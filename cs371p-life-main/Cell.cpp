#include "Cell.hpp"

//calls AbstactCell's evolve();
void Cell::evolve() {
    _p->evolve();
}


//calls AbstactCell's is_Conway();
bool Cell::is_Conway() {
    return _p->is_Conway();
}


//calls AbstactCell's is_alive();
bool Cell::is_alive() {
    return _p->is_alive();
}

//calls AbstactCell's getAge(0);
//useful for FredkinCells
int Cell::getFredkinAge() {
    return _p->getAge();
}