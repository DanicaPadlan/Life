#ifndef FredkinCell_hpp
#define FredkinCell_hpp
#include "AbstractCell.hpp"

class FredkinCell : public AbstractCell {

private:
    int age;
public:
    FredkinCell(bool state, bool conway) : AbstractCell(state, conway), age(0) {}

    FredkinCell* clone() {
        return new FredkinCell(*this);
    }

    void evolve();

    void updateAge();

    int getAge();

    bool turnToConway();

};

#endif