#ifndef AbstractCell_hpp
#define AbstractCell_hpp

class AbstractCell {

protected:
    bool alive;
    bool is_conway;

public:
    AbstractCell(bool state, bool cell_type) {
        alive = state;
        is_conway = cell_type;
    }
    virtual ~AbstractCell() {};
    virtual AbstractCell* clone() = 0;
    virtual void evolve() = 0;
    bool is_Conway();
    bool is_alive();
    virtual int getAge() = 0; //only FredkinCell but Conway's method should never be called
    virtual void updateAge() = 0;

};

#endif