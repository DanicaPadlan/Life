#ifndef Cell_hpp
#define Cell_hpp
#include "AbstractCell.hpp"
#include <algorithm>

using namespace std;

class Cell {

private:
    AbstractCell* _p;

public:
    Cell(AbstractCell* p) : _p (p) {}

    Cell(const Cell& rhs) : _p (rhs._p->clone()) {}

    //move constructor
    Cell(Cell&& rhs) {

        std::swap(_p, rhs._p);
    }

    //copy assignment
    Cell& operator = (const Cell& rhs) {
        _p = rhs._p;
        return *this;
    }

    //move operator
    Cell& operator = (Cell&& rhs) {
        //swap
        if(this == &rhs) {
            return *this;
        }

        swap(_p, rhs._p);
        return *this;

    }

    ~Cell() {
        delete _p;
    }

    void evolve();

    bool is_Conway();

    bool is_alive();

    //changes what Cell is pointing to
    //VALID setter to handle switching FredkinCells to ConwayCells
    //change this
    void changeCell(AbstractCell* newCell) {

        AbstractCell* temp = _p;
        _p = newCell;
        delete(temp);
    }

    int getFredkinAge();

    void updateAge() {
        _p->updateAge();
    }

};

#endif