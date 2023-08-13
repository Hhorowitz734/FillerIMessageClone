#include <stdio.h>
#include <iostream>
#include "/opt/homebrew/Cellar/raylib/4.5.0/include/raylib.h"
#include <vector>
#include <random>
#include <cmath>

//cd "/Users/bhorowitz/Documents/CPLUSPLUS/Filler/" && g++ filler.cpp -o filler -I/opt/homebrew/Cellar/raylib/4.5.0/include -L/opt/homebrew/lib -lraylib -std=c++11 && "/Users/bhorowitz/Documents/CPLUSPLUS/Filler/filler"

class Manager{
    // Manages the state of the game, holds crucial variables, etc
    public:
        // Dims of the screen
        static int GameWidth; // GameHeight and GameWidth should always have the same value
        static int GameHeight;
        static int AuxHeight;

        // Number of squares
        static int squares; // Value MUST be a perfect square

        // Square dim information (squareWidth = squareHeight)
        int squareWidth = GameWidth / sqrt(static_cast<double>(squares));

        // Represents number of lines for the game board
        double numLines = sqrt(static_cast<double>(squares));

        Manager() {
            // Confirms that squares was indeed a perfect square
            if (numLines != static_cast<int>(numLines)){
                std::cout << "Please pick a perfect square for squares in manager.\n\n\n\n\n";
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

        Square(int posX, int posY, Color blockcolor) : positionX(posX), positionY(posY), squarecolor(blockcolor) {};
    
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

int Manager::squares = 100;

int main()
{
    // Initialize the window and set the frame rate
    InitWindow(Manager::GameWidth, Manager::GameHeight + Manager::AuxHeight, "Filler");
    SetTargetFPS(60);
    ClearBackground(BLACK);


    //DO ANY TESTING HERE
    Square squaretest(0, 0, {255, 0, 0, 255});
    Square squaretest2(manager.squareWidth, manager.squareWidth, {0, 255, 0, 255});

    // Main game loop
    while (!WindowShouldClose())
    {

        // Clear the screen
        BeginDrawing();
        ClearBackground(BLACK);

        manager.drawBoard();

        squaretest.display();
        squaretest2.display();

        



        EndDrawing();
        
    }

    // Clean up and exit
    CloseWindow();
    return 0;
}