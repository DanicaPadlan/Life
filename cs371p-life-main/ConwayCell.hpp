#ifndef ConwayCell_hpp
#define ConwayCell_hpp
#include "AbstractCell.hpp"

class ConwayCell : public AbstractCell {

private:

public:

    ConwayCell(bool state, bool conway) : AbstractCell(state, conway) {}

    ConwayCell* clone() {
        return new ConwayCell(*this);
    }

    void evolve();

    int getAge();

    void updateAge();
};

#endif