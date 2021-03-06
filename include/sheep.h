#ifndef SHEEP_H_INCLUDED
#define SHEEP_H_INCLUDED

#include "board.h"
#include <iostream>

class sheep
{
public:
    sheep();

    // Function used to calculate and return number of sheep on game board
    int numberOfSheep(char gameBoard[7][7]);


    /*/// This function prompts and reads the user's input, tests whether or not the new position they entered
    //// is legal, and if it is, the new position in the "board.h" public board array gets changed to 'S'.
    //// If the new position the user entered was illegal, then it will continually ask the user
    //// to enter a legal position until the user does so. If the user is playing blitz (speed) Halatafl,
    //// then their turn is timed (recorded in 'duration'). If they do not make a move in 20 seconds,
    //// the function returns false. Otherwise, the function will return true.*/
    bool userInput(char gameBoard[7][7], std::istream& in, bool speedHalatafl, double& duration);
};


#endif // SHEEP_H_INCLUDED
