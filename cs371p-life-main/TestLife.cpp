#include "gtest/gtest.h"
#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream> // cin, cout
#include "Life.hpp"
#include "AbstractCell.hpp"
#include "ConwayCell.hpp"
#include "FredkinCell.hpp"

using namespace std;

TEST(LifeTest, conwayConstructor) {
    ConwayCell test_cell = ConwayCell(false, true);
    ASSERT_EQ(test_cell.is_alive(), false);
    ASSERT_EQ(test_cell.is_Conway(), true);
}

TEST(LifeTest, conwayGetAge) {
    ConwayCell test_cell = ConwayCell(true, true);
    ASSERT_EQ(test_cell.getAge(), 0);
}

TEST(LifeTest, conwayEvolve) {
    ConwayCell test_cell = ConwayCell(true, true);
    test_cell.evolve();
    ASSERT_EQ(test_cell.is_alive(), false);
}

TEST(LifeTest, conwayClone) {
    ConwayCell test_cell = ConwayCell(true, true);
    ConwayCell* a = test_cell.clone();
    ASSERT_NE(&test_cell, a);
    delete a;
}

TEST(LifeTest, fredkinConstructor) {
    FredkinCell test_cell = FredkinCell(true, false);
    ASSERT_EQ(test_cell.is_alive(), true);
    ASSERT_EQ(test_cell.is_Conway(), false);
}

TEST(LifeTest, fredkinEvolve) {
    FredkinCell test_cell = FredkinCell(true, false);
    test_cell.evolve();
    ASSERT_EQ(test_cell.is_alive(), false);
}

TEST(LifeTest, fredkinUpdateAge) {
    FredkinCell test_cell = FredkinCell(true, false);
    test_cell.updateAge();
    ASSERT_EQ(test_cell.getAge(), 1);
}

TEST(LifeTest, fredkinGetAge) {
    FredkinCell test_cell = FredkinCell(true, false);
    ASSERT_EQ(test_cell.getAge(), 0);
    test_cell.updateAge();
    ASSERT_EQ(test_cell.getAge(), 1);
}

TEST(LifeTest, fredkinTurnToConway) {
    FredkinCell test_cell = FredkinCell(true, false);
    test_cell.updateAge();
    test_cell.updateAge();
    ASSERT_EQ(test_cell.turnToConway(), true);
}

TEST(LifeTest, fredkinClone) {
    FredkinCell test_cell = FredkinCell(true, false);
    FredkinCell* a = test_cell.clone();
    ASSERT_NE(&test_cell, a);
    delete a;
}


TEST(LifeTest, lifeConstructor) {
    vector<CoordPairs> coord;
    vector<AbstractCell*> cells;
    Life life_test = Life(4, 4, coord, cells, false);
    ASSERT_NE(&life_test, nullptr);
    life_test.clear();
}

TEST(LifeTest, lifeInBounds) {
    vector<CoordPairs> coord;
    vector<AbstractCell*> cells;
    Life life_test = Life(4, 4, coord, cells, false);
    ASSERT_EQ(life_test.inbounds(1, 1), true);
    life_test.clear();
}

TEST(LifeTest, lifecheckAliveNeighbors) {
    vector<CoordPairs> coord;
    CoordPairs first = {1, 1};
    CoordPairs second = {1, 0};
    coord.push_back(first);
    coord.push_back(second);
    vector<AbstractCell*> cells;
    FredkinCell* first_cell = new FredkinCell(true, false);
    FredkinCell* second_cell = new FredkinCell(true, false);
    cells.push_back(first_cell);
    cells.push_back(second_cell);
    Life life_test = Life(4, 4, coord, cells, false);
    ASSERT_EQ(life_test.checkAliveNeighbors(1, 1, false), 1);
    ASSERT_EQ(life_test.checkAliveNeighbors(1, 0, false), 1);
    ASSERT_EQ(life_test.checkAliveNeighbors(4, 4, false), 0);
    life_test.clear();
}

TEST(LifeTest, lifeCheckAliveNeighbors2) {
    vector<CoordPairs> coord;
    CoordPairs first = {1, 1};
    CoordPairs second = {1, 0};
    CoordPairs third = {2, 1};
    coord.push_back(first);
    coord.push_back(second);
    coord.push_back(third);
    vector<AbstractCell*> cells;
    FredkinCell* first_cell = new FredkinCell(true, false);
    FredkinCell* second_cell = new FredkinCell(true, false);
    FredkinCell* third_cell = new FredkinCell(true, false);
    cells.push_back(first_cell);
    cells.push_back(second_cell);
    cells.push_back(third_cell);
    Life life_test = Life(4, 4, coord, cells, false);
    ASSERT_EQ(life_test.checkAliveNeighbors(1, 1, false), 2);
    life_test.clear();
}

TEST(LifeTest, lifeCountLife) {
    vector<CoordPairs> coord;
    CoordPairs first = {1, 1};
    CoordPairs second = {1, 0};
    coord.push_back(first);
    coord.push_back(second);
    vector<AbstractCell*> cells;
    FredkinCell* first_cell = new FredkinCell(true, false);
    FredkinCell* second_cell = new FredkinCell(true, false);
    cells.push_back(first_cell);
    cells.push_back(second_cell);
    Life life_test = Life(4, 4, coord, cells, false);
    ASSERT_EQ(life_test.countLife(), 2);
    life_test.clear();
}

TEST(LifeTest, lifeCountLife2) {
    vector<CoordPairs> coord;
    CoordPairs first = {1, 1};
    CoordPairs second = {1, 0};
    CoordPairs third = {2, 1};
    coord.push_back(first);
    coord.push_back(second);
    coord.push_back(third);
    vector<AbstractCell*> cells;
    FredkinCell* first_cell = new FredkinCell(true, false);
    FredkinCell* second_cell = new FredkinCell(true, false);
    FredkinCell* third_cell = new FredkinCell(true, false);
    cells.push_back(first_cell);
    cells.push_back(second_cell);
    cells.push_back(third_cell);
    Life life_test = Life(4, 4, coord, cells, false);
    ASSERT_EQ(life_test.countLife(), 3);
    life_test.clear();
}

TEST(LifeTest, cellEvolve) {
    ConwayCell* temp = new ConwayCell(true, true);
    Cell* test_cell = new Cell(temp);
    test_cell->evolve();
    ASSERT_EQ(test_cell->is_alive(), false);
    delete test_cell;
}

TEST(LifeTest, cellIsConway) {
    ConwayCell* temp = new ConwayCell(true, true);
    Cell* test_cell = new Cell(temp);
    ASSERT_EQ(test_cell->is_Conway(), true);
    delete test_cell;
}

TEST(LifeTest, cellIsAlive) {
    ConwayCell* temp = new ConwayCell(true, true);
    Cell* test_cell = new Cell(temp);
    ASSERT_EQ(test_cell->is_alive(), true);
    delete test_cell;
}

TEST(LifeTest, cellUpdateAge) {
    FredkinCell* a = new FredkinCell(true, false);
    Cell* test_cell = new Cell(a);
    test_cell->updateAge();
    ASSERT_EQ(test_cell->getFredkinAge(), 1);
    delete test_cell;
}