

#ifndef Life_hpp
#define Life_hpp
#include <vector>
#include <cassert>
#include <iostream> // cin, cout
#include "CoordPairs.hpp"
#include "Cell.hpp"
#include "ConwayCell.hpp"
#include "FredkinCell.hpp"


using namespace std;

//directions to check for certain cells
int CONWAY_DIR[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
int FREDKIN_DIR[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Life {

    private:
        vector<vector<Cell*>> grid;
        vector<Cell> cellsInGrid;

    public:

        //constructor builds the Life grid filled with AbstractCells
        Life(int x, int y, vector<CoordPairs> coords, vector<AbstractCell*> starting_cells, bool init_conway){

            assert(x > 0);
            assert(y > 0);
            //create and null the grid out with dead cells
            for(int i = 0; i < x; i++){

                vector<Cell*> curRow;
                for(int j = 0; j < y; j++){

                    //initialize with dead cells
                    if(init_conway){

                        //setting this to dead default Conway cell
                        //THIS WORKS
                        curRow.push_back(new Cell( new ConwayCell(false, true)));
                
                    } else {
                        curRow.push_back(new Cell( new FredkinCell(false, false)));
                    }

                }
                grid.push_back(curRow);
            }

            //fill grid with actual conway cells we made and passed in earlier
            for(int x = 0; x < coords.size(); x++){

                int coordX = coords.at(x).x_coord;
                int coordY = coords.at(x).y_coord;

                grid[coordX][coordY]->changeCell(starting_cells.at(x));
            }
        }

        //checks if coordinates are in bounds of the grid size
        bool inbounds(int curR, int curC){
            return (curR >= 0) && (curR < grid.size()) && (curC >= 0) && (curC < grid[0].size());
        }


        //counts and returns number of alive neighbors an AbstractCell has
        int checkAliveNeighbors(int curR, int curC, bool conway){
            assert(curR >= 0);
            assert(curC >= 0);
            //array of directions
            int num_alive = 0;

            if(conway){
                for(int x = 0; x < 8; x++){

                    int tempR = curR + CONWAY_DIR[x][0];
                    int tempC = curC + CONWAY_DIR[x][1];

                    if(inbounds(tempR, tempC) && grid[tempR][tempC]->is_alive()){
                        num_alive++;
                    }
                }
            } else{
                for(int x = 0; x < 4; x++){

                    int tempR = curR + FREDKIN_DIR[x][0];
                    int tempC = curC + FREDKIN_DIR[x][1];

                    if(inbounds(tempR, tempC) && grid[tempR][tempC]->is_alive()){
                        num_alive++;
                    }
                }
            }
            return num_alive;
        }


        void runLife(bool testingCell){

            //keep a vector of Cells to switch the states if satisfied
            vector<Cell*> change_cells;

            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid.at(0).size(); j++){
                    Cell* current = grid[i][j];
                    if(current->is_Conway()){

                        //based on certain num of alive neighbors, change state
                        //check for cells neighbors
                        if(current->is_alive()){
                            int alive_total = checkAliveNeighbors(i, j, true);

                            //become dead?
                            if(alive_total < 2 || alive_total > 3){
                                //add to vector list
                                change_cells.push_back(current);
                            }

                        } else {

                            int alive_total = checkAliveNeighbors(i, j, true);

                            //become alive?
                            if(alive_total == 3){
                                //add to vector list
                                change_cells.push_back(current);
                            }
                        }

                    //Fredkin Case
                    } else{
                        if(current->is_alive()){
                            int alive_total = checkAliveNeighbors(i, j, false);

                            //become dead?
                            if(alive_total == 0 || alive_total == 2 || alive_total == 4){
                                //add to vector list
                                change_cells.push_back(current);
                            
                            //stays alive, update the age
                            } else{
                                current->updateAge();

                                //only do this if we are testing Cell!
                                //check if we age == 2, turn to ConwayCell
                                if(testingCell && current->getFredkinAge() == 2){
                                    Cell* old = current;
                                    grid[i][j] = new Cell(new ConwayCell(true, true));
                                    
                                    //swap whatever the grid is pointing to with that
                                    //delete the old cell
                                    delete old;
                                }

                            }

                        } else {
                            int alive_total = checkAliveNeighbors(i, j, false);

                            //become alive?
                            if(alive_total == 1 || alive_total == 3){
                                //add to vector list
                                change_cells.push_back(current);
                            }
                        }
                    }
                    

                }
            }

            //loop through cells to switch their states
            for(int x = 0; x < change_cells.size(); x++){
                change_cells.at(x)->evolve();
            }

        }

        //counts and returns the total number of alive cells in the whole Grid
        int countLife(){
            int alive = 0;
            for(int x = 0; x < grid.size(); x++){
                for(int y = 0; y < grid[0].size(); y++){
                    if(grid[x][y]->is_alive()){
                        alive++;
                    }
                }
            }
            return alive;
        }

        //runs Life simulation on grid
        void eval(int totalGen, int printFreq, bool testingCell){
            assert(totalGen > 0);
            assert(printFreq > 0);
            //loop to simulate and print generations
            //print out initial map
            cout << endl;
            cout << "Generation = " << 0 << ", Population = " << countLife() << "." << endl;

            print();

            int curGen = 1;
            while(curGen <= totalGen){
                runLife(testingCell);

                //print based on print frequency
                if(curGen % printFreq == 0){
                    cout << endl;
                    cout << "Generation = " << curGen << ", Population = " << countLife() << "." << endl;
                    print();
                }
                
                curGen++;
            }
        } 
        
        //prints out whole grid
        void print(){

            for(int i = 0; i < grid.size(); i++){

                for(int j = 0; j < grid.at(0).size(); j++){

                    Cell* current = grid[i][j];

                    if(current->is_Conway()){
                        if(current->is_alive()){
                            cout << '*';
                        } else {
                            cout << '.';
                        }
                    } else {
                        
                        if(current->is_alive()){
                            if(current->getFredkinAge() < 10){
                                cout << current->getFredkinAge();
                            } else {
                                cout << '+';
                            }
                        } else {
                            cout << '-';
                        }

                    }
                }
                cout << endl;
            }
        } 

        //deletes all new Cells and new AbstractCells* that were made in the constructor
        void clear(){

            //loop through everything in the grid
            for(int i = 0; i < grid.size(); i++){
                vector<Cell*> temp = grid.at(i);

                while(!temp.empty()){
                    
                    //call delete on the current Cell
                    delete grid[i][temp.size() - 1];

                    //pop off the address to that cell because its now invalid memory
                    temp.pop_back();
                }

            }
        }

};
#endif
