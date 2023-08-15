#include <stdio.h>
#include <iostream>
#include "/opt/homebrew/Cellar/raylib/4.5.0/include/raylib.h"
#include <vector>
#include <random>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

//cd "/Users/bhorowitz/Documents/CPLUSPLUS/Filler/" && g++ filler.cpp -o filler -I/opt/homebrew/Cellar/raylib/4.5.0/include -L/opt/homebrew/lib -lraylib -std=c++11 && "/Users/bhorowitz/Documents/CPLUSPLUS/Filler/filler"

class Square;

class Manager{
    // Manages the state of the game, holds crucial variables, etc
    public:
        // Dims of the screen
        static int GameWidth; // GameHeight and GameWidth should always have the same value
        static int GameHeight;
        static int AuxHeight;

        // Number of numSquares
        static int numSquares; // Value MUST be a perfect square

        //Stores all squares
        static std::vector<Square*> squares;

        //Colors of the base game
        static std::vector<Color> gamecolors;

        // Square dim information (squareWidth = squareHeight)
        int squareWidth = GameWidth / sqrt(static_cast<double>(numSquares));

        // Represents number of lines for the game board
        double numLines = sqrt(static_cast<double>(numSquares));

        Manager() {
            // Confirms that numSquares was indeed a perfect square
            if (numLines != static_cast<int>(numLines)){
                std::cout << "Please pick a perfect square for numSquares in manager.\n\n\n\n\n";
                exit(1); // Exit the program
            }
        }
    
    void drawBoard() {
        // Draws the lines of the gameboard
        for (int i = 0; i < static_cast<int>(numLines); i++){
            DrawLine(0, i * squareWidth, GameWidth, i * squareWidth, WHITE);
            DrawLine(i * squareWidth, 0, i * squareWidth, GameHeight, WHITE);
        }
        DrawLine(0, GameHeight, GameWidth, GameHeight, WHITE);
    }

    void setupSquares();

        
};

//Defines manager that controls the game
Manager manager;


class Square{
    public:

        //Color of the square
        Color squarecolor;

        //Represents the squares surrounding the given square
        Square* top = nullptr;
        Square* bottom = nullptr;
        Square* left = nullptr;
        Square* right = nullptr;

        //Represents the coordinates of the top left of the square
        int positionX;
        int positionY;

        //Hitbox for raylib
        Rectangle squarebox = {static_cast<float>(positionX), static_cast<float>(positionY), static_cast<float>(manager.squareWidth), static_cast<float>(manager.squareWidth)};

        Square(int posX, int posY, Color blockcolor) : positionX(posX), positionY(posY), squarecolor(blockcolor) {
            Manager::squares.push_back(this);
        };
    
    void display(){

        int offset = 5; //sets a small ofset so blocks arent all together
        DrawRectangle(positionX + offset, positionY + offset, manager.squareWidth - (2 * offset), manager.squareWidth - (2 * offset), squarecolor);
    
    }
};


//Static member variables of Manager
//DEFINES GAME SETTINGS
int Manager::GameWidth = 600;
int Manager::GameHeight = 600;
int Manager::AuxHeight = 150;

int Manager::numSquares = 25;
std::vector<Square*> Manager::squares;

std::vector<Color> Manager::gamecolors = {
    {255, 0, 0, 255},     // 0 - red
    {0, 255, 0, 255},     // 1 - green
    {255, 255, 0, 255},   // 2 - yellow
    {0, 0, 255, 255},     // 3 - blue
    {128, 0, 128, 255},   // 4 - purple
    {0, 0, 0, 0}          // 5 - black
};

//SetupSquares

bool areColorsEqual(const Color& c1, const Color& c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}


bool isSafeColor(int row, int col, Color color) {
    // Check top neighbor
    if (row > 0 && areColorsEqual(Manager::squares[(row-1) * static_cast<int>(manager.numLines) + col]->squarecolor, color))
        return false;

    // Check left neighbor
    if (col > 0 && areColorsEqual(Manager::squares[row * static_cast<int>(manager.numLines) + (col-1)]->squarecolor, color))
        return false;

    // Check right neighbor
    if (col < static_cast<int>(manager.numLines) - 1 && areColorsEqual(Manager::squares[row * static_cast<int>(manager.numLines) + (col+1)]->squarecolor, color))
        return false;

    // Check bottom neighbor
    if (row < static_cast<int>(manager.numLines) - 1 && areColorsEqual(Manager::squares[(row+1) * static_cast<int>(manager.numLines) + col]->squarecolor, color))
        return false;

    return true;
}

void Manager::setupSquares() {
    //Write this method here
}

int main()
{
    // Initialize the window and set the frame rate
    InitWindow(Manager::GameWidth, Manager::GameHeight + Manager::AuxHeight, "Filler");
    SetTargetFPS(60);
    ClearBackground(BLACK);

    manager.setupSquares();

    // Main game loop
    while (!WindowShouldClose())
    {

        // Clear the screen
        BeginDrawing();
        ClearBackground(BLACK);

        manager.drawBoard();

        for (Square* square : Manager::squares){
            square->display();
        }

        
        for (Square* square : Manager::squares){

            //Executes if a button is pressed
            if (CheckCollisionPointRec(GetMousePosition(), square->squarebox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                std::cout << "Square " << (square->positionX / manager.squareWidth) * manager.numLines + (square->positionY / manager.squareWidth) << " has been pressed.\n";
            }
        }


        EndDrawing();
        
    }

    // Clean up and exit
    CloseWindow();
    return 0;
}