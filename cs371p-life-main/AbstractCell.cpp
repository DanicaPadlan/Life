#include "AbstractCell.hpp"

//returns bool to check if cell is a ConwayCell
bool AbstractCell::is_Conway() {
    return is_conway;
}

//returns bool to check if cell is alive
bool AbstractCell::is_alive() {
    return alive;
}