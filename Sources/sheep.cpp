#include "sheep.h"
#include "board.h"
#include <ctime>
#include <iostream>

using namespace std;

sheep::sheep() {}

// Function used to calculate and return number of sheep on game board
int sheep::numberOfSheep(char gameBoard[7][7])
{
    int numSheep = 0;
    for (int x = 0; x < 7; x++)
        for (int y = 0; y < 7; y++) {
            if (gameBoard[x][y] == 'S')
                numSheep++;
        }
    return numSheep;
}


/*/// This function prompts and reads the user's input, tests whether or not the new position they entered
//// is legal, and if it is, the new position in the "board.h" public board array gets changed to 'S'.
//// If the new position the user entered was illegal, then it will continually ask the user
//// to enter a legal position until the user does so. If the user is playing blitz (speed) Halatafl,
//// then their turn is timed (recorded in 'duration'). If they do not make a move in 20 seconds,
//// the function returns false. Otherwise, the function will return true.*/
bool sheep::userInput(char gameBoard[7][7], std::istream& in, bool speedHalatafl, double& duration)
{
    ///// Create 5 variables to read the input of the user, initial position - moving position.
    char oldPos = 'x', dash = '-', newPos = 'y';
    int oldPosition = 0, newPosition = 0;

    // Timer Variables for Blitz (Speed) Halatafl
    clock_t start;
    duration = 0;

    ///// Create an array to match the letters that represent the game board columns with
    ///// the two-dimensional gameBoard array.
    char letterArray[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    ///// Create an array to match the numbers that represent the game board rows with
    ///// the two-dimensional gameBoard array.
    int numberArray[7] = {7, 6, 5, 4, 3, 2, 1};

    ///// Prompt user for input and read data into variables.
    cout << "\nYour move? ";
    if (speedHalatafl) {
        start = clock();
    }
    in >> oldPos >> oldPosition >> dash >> newPos >> newPosition;
    if (speedHalatafl) {
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        if (duration > 20)
            return false;
    }

    int validLetters = 0;
    int validNumbers = 0;
    for (int x = 0; x < 7; x++) {
        if (oldPos == letterArray[x])
            validLetters++;
        if (newPos == letterArray[x])
            validLetters++;
        if (oldPosition == numberArray[x])
            validNumbers++;
        if (newPosition == numberArray[x])
            validNumbers++;
    }
    while (validLetters != 2 && validNumbers != 2) {
        if (speedHalatafl) {
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            if (duration > 20)
                return false;
        }
        validLetters = 0;
        validNumbers = 0;
        cout << "\nThat is not a legal move.\nYour move? ";
        in >> oldPos >> oldPosition >> dash >> newPos >> newPosition;
        for (int x = 0; x < 7; x++) {
            if (oldPos == letterArray[x])
                validLetters++;
            if (newPos == letterArray[x])
                validLetters++;
            if (oldPosition == numberArray[x])
                validNumbers++;
            if (newPosition == numberArray[x])
                validNumbers++;
        }
    }

    ///// Match oldPos, newPos, oldPosition, and newPosition with the letter and number arrays,
    ///// and store those values in new variables
    int columnOld = 0, rowOld = 0, columnNew = 0, rowNew = 0;
    for (int x = 0; x < 7; x++) {
        if (oldPos == letterArray[x])
            columnOld = x;
        if (oldPosition == numberArray[x])
            rowOld = x;
        if (newPos == letterArray[x])
            columnNew = x;
        if (newPosition == numberArray[x])
            rowNew = x;
    }
    ///// Check the new board array position to see if it's a legal move
    ////// Loop until user enters proper position
    while (gameBoard[rowOld][columnOld] != 'S') {
        if (speedHalatafl) {
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            if (duration > 20)
                return false;
        }
        cout << "\nThat is not a legal move.\nYour move? ";
        in >> oldPos >> oldPosition >> dash >> newPos >> newPosition;
        for (int x = 0; x < 7; x++) {
            if (oldPos == letterArray[x])
                columnOld = x;
            if (oldPosition == numberArray[x])
                rowOld = x;
            if (newPos == letterArray[x])
                columnNew = x;
            if (newPosition == numberArray[x])
                rowNew = x;
        }
    }
    while ((columnNew < 0 || columnNew > 6) || (rowNew < 0 || rowNew > 6)) {
        if (speedHalatafl) {
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            if (duration > 20)
                return false;
        }
        cout << "\nThat is not a legal move.\nYour move? ";
        in >> oldPos >> oldPosition >> dash >> newPos >> newPosition;
        for (int x = 0; x < 7; x++) {
            if (oldPos == letterArray[x])
                columnOld = x;
            if (oldPosition == numberArray[x])
                rowOld = x;
            if (newPos == letterArray[x])
                columnNew = x;
            if (newPosition == numberArray[x])
                rowNew = x;
        }
    }

    while ((gameBoard[rowNew][columnNew] != '.') ||
           (((rowNew == rowOld + 1) && (columnNew == columnOld)) || ((rowNew == rowOld + 1) && (columnNew == columnOld + 1)) || ((rowNew == rowOld + 1) && (columnNew == columnOld - 1)) || ((rowNew == rowOld - 1) && (columnNew == columnOld - 1)) || ((rowNew == rowOld - 1) && (columnNew == columnOld + 1))) || ((rowNew > rowOld + 1) || (rowNew < rowOld - 1) || (columnNew > columnOld + 1) || (columnNew < columnOld - 1))) {
        if (speedHalatafl) {
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            if (duration > 20)
                return false;
        }
        cout << "\nThat is not a legal move.\nYour move? ";
        in >> oldPos >> oldPosition >> dash >> newPos >> newPosition;
        for (int x = 0; x < 7; x++) {
            if (oldPos == letterArray[x])
                columnOld = x;
            if (oldPosition == numberArray[x])
                rowOld = x;
            if (newPos == letterArray[x])
                columnNew = x;
            if (newPosition == numberArray[x])
                rowNew = x;
        }
    }


    ////// Set the new board position to 'S' and change the old position to '.'
    gameBoard[rowNew][columnNew] = 'S';
    gameBoard[rowOld][columnOld] = '.';

    return true;
}
