#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream> // cin, cout
#include <algorithm>
#include <sstream>
#include "Life.hpp"


using namespace std;


int main() {

    string readLine;
    uint num_test;

    //get number of tests to run
    getline(cin, readLine);
    num_test = stoi(readLine);

    uint curTest = 0;

    //loops through num test in given input file
    while(curTest != num_test) {

        //read in coordinates for Life
        string rowTemp;
        string rowCol;

        cin >> rowTemp;
        cin >> rowCol;

        uint lifeRow = stoi(rowTemp);
        uint lifeCol = stoi(rowCol);
        getline(cin, readLine);

        //read in how many FREDKIN cells to make
        getline(cin, readLine);

        uint num_cells = stoi(readLine);

        //loop to create cells and add to a vector list, mentioned in lecture
        uint curCell = 0;

        //Creating new FREDKIN cells
        vector<AbstractCell*> fredkin_cells;
        vector<CoordPairs> coordinates;

        while(curCell != num_cells) {

            //read in cell coordinates and save into vector
            string tempRow;
            string tempCol;

            cin >> tempRow;
            cin >> tempCol;

            //moves parser to next line in file
            getline(cin,readLine);

            uint curRow = stoi(tempRow);
            uint curCol = stoi(tempCol);

            CoordPairs current_coordinates;
            current_coordinates.x_coord = curRow;
            current_coordinates.y_coord = curCol;

            //push back coords and *FredkinCell in order
            coordinates.push_back(current_coordinates);
            fredkin_cells.push_back(new FredkinCell(true, false));
            curCell++;
        }

        //create Life object to run tests on
        Life life =  Life(lifeRow, lifeCol, coordinates, fredkin_cells, false);

        //read in number of generations to make and how many times we print out Life
        string genTemp;
        string freqTemp;

        cin >> genTemp;
        cin >> freqTemp;

        //moves parser to next line in file
        getline(cin, readLine);

        uint num_gen = stoi(genTemp);
        uint freq_print = stoi(freqTemp);

        cout << "*** Life<FredkinCell> " << lifeRow << "x" << lifeCol << " ***" << endl;

        life.eval(num_gen, freq_print, false);

        //update the cur_test
        curTest++;

        //avoid printing new line at last test
        if(curTest != num_test) {
            cout << endl;
        }

        //deallocate new Cells and new AbstractCells
        life.clear();
    }

    return 0;
}
