#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

void printGrid(string gridCode) {
	if (gridCode.length() == 9) {
		int gridIndex = 0;
		for (int i = 0; i < 5; i++) {
			if (i % 2 == 0) {
				cout << gridCode[gridIndex * 3] << " | " << gridCode[gridIndex * 3 + 1] << " | " << gridCode[gridIndex * 3 + 2] << "\n";
				gridIndex++;
			} else {
				cout << "---------\n";
			}
		}
	} else {
		perror("ERROR: 'gridCode' argument is invalid");
		exit(0);
	}
}

bool findLetters(string input) {
    string nono = "abcdefghijklmnopqrstuvwxyzABXDEFGHIJKLMNOPQRSTUVWXYZ";
    
    bool isValid = true;
    for (int i = 0; i < input.length(); i++) {
        if (input.find(nono[i]) != std::string::npos) {
			isValid = false;
		}
    }
    
    return isValid;
}

bool checkBounds(int cellNum) {
    if (cellNum <= 0 || cellNum >= 10) {
        return false;
    }
    
    return true;
}

bool checkCell(int cellNum, string grid) {
	bool isValidCell = false;
	if (grid[cellNum - 1] == ' ') {
		isValidCell = true;
	}

	return isValidCell;
}

string getInput(int player, string grid) {
	string sign = "O";
	if (player == 1) {
		sign = "X";
	}

    string input;
    
    bool inIsValid = false;
    while (!inIsValid) {
        bool isNoChars = false;
        bool isInBounds = false;
        bool isValidCell = false;
        
        cout << "Enter a place to place your " << sign << " (Player " << player + 1 << ")\n";
        cin >> input;
        
        isNoChars = findLetters(input);
        if (isNoChars == true) {
            isInBounds = checkBounds(stoi(input));
        }

        if (isNoChars && isInBounds) {
        	isValidCell = checkCell(stoi(input), grid);
        }
        
        if (isValidCell) {
            inIsValid = true;
        }
    }
    
    return input;
}

string alterGrid(string gridCode, string cellNum, int player) {
	string sign = "O";
	if (player == 1) {
		sign = "X";
	}

	gridCode.replace(stoi(cellNum) - 1, 1, sign);

	return gridCode;
}

int findWin(string gridCode) {
	char sign;
	int cornerPos[4] = {1, 3, 7, 9};
	int retVal = -1;

	// Check centre and its permutations
	if (gridCode[5] != ' ') {
		sign = gridCode[5];

		// Check cells 1 to 4 for the same sign
		for (int i = 0; i < 4; i++) {
			if (gridCode[i + 1] == sign && gridCode[gridCode.length() - i] == sign) {
				if (sign == 'X') {
					retVal = 1;
					break;
				} else {
					retVal = 0;
					break;
				}
			}
		}
	}

	// Check corners and their permutations
	if (retVal == -1) {
		int positions[2] = {0, 9};
		int offsets[2] = {1, 3};
		for (int i = 1; i < 3; i++) {
			if (gridCode[positions[i]] != ' ') {
				char sign = gridCode[positions[i]];

				for (int x = 0; x < 2; x++) {         // TODO: rewrite corner win checking algorithm
					if (gridCode[0] == sign && gridCode[offsets[x]] == sign && gridCode[offsets[x] * 2] == sign) {
						if (sign == 'X') {
							retVal = 1;
						} else {
							retVal = 0;
						}
					}
				}
			}
		}
	}

	return retVal;
}

int main() {
	bool gameOver = false;
	string grid = "         ";

	int turnCounter = 0;

	while (!gameOver) {
		string cell = getInput(turnCounter % 2, grid);
		grid = alterGrid(grid, cell, turnCounter % 2);
		printGrid(grid);

		turnCounter++;

		// Check for any 3 in a rows.
		int win = findWin(grid);
		if (win == 0 || win == 1) {
			gameOver = true;
			cout << "Player " << win + 1 << " wins! Congratualations!\n";
		}

		// Check for a draw
		if (turnCounter >= 9) {
			gameOver = true;
			cout << "\n\n----- Draw -----\n";
		}
	}

	return 0;
}