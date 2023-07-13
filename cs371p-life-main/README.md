Name: Danica Padlan and Austin Nguyen


EID: dmp3357 and acn883


GitLab ID: DanicaPadlan and austincnguyen


HackerRank ID: danica_padlan1 and austincnguyen17 (submitted through Danica's HackerRank)


Git SHA: (most recent Git SHA, final change to your repo will change this, that's ok) 0422f1c651305e8e82189d32631b434f054d6563


GitLab Pipelines: (link to your GitLab CI Pipeline) https://gitlab.com/DanicaPadlan/cs371p-life/-/pipelines


Estimated completion time: 45 hours (3 hours everyday for 2 weeks at most)


Actual completion time: 25 hours


Comments: validating setter and getter methods

-void changeCell(AbstractCell* newCell){};
We created this setter method because in our RunLifeConway, RunLifeFredkin, and RunLifeCell we create the requested cells beforehand to align them with the test files coordinates. In our Life constructor, we create default dead Cells to fill the map and then change what Cell is pointing to at the requested coordinates (either pointing to the Conway or Fredkin cell we made in the main methods)

-int FredkinCell::getAge(){}
We created this getter for FredkinCells because we need to print out the ages of the cells on the map. The age variable is private to the FredkinCell class so we have to use a getter method to print its correct age.
