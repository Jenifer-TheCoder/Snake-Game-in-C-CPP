// Snake Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

int g_snakeX, g_snakeY, g_fruitX, g_fruitY, g_score;
int iTailX[100], iTailY[100];
int g_Width = 20;
int g_Height = 17;
bool g_GameOver = false;
int nTail;
enum eDirection {STOP =0, RIGHT, LEFT, UP, DOWN } eDir;

void Setup() {
    eDir = STOP;
    g_score = 0;
    g_snakeX = g_Width / 2;
    g_snakeY = g_Height / 2;
    g_fruitX = rand() % g_Width;
    g_fruitY = rand() % g_Height;
}

void Draw()
{
    system("cls");
    for (int index = 0; index < g_Width + 2; index++) {
        std::cout << "#";
    }
    std::cout << std::endl;
    for (int row = 0; row < g_Height; row++) {
        for (int column = 0; column < g_Width; column++) {
            if (column == 0)
                std::cout << "#";
            if (column == g_snakeX && row == g_snakeY)
                std::cout << "*";
            else if (column == g_fruitX && row == g_fruitY)
                std::cout << "%";
            else
            {
                bool bPrintTail = false;
                for (int index = 0; index < nTail; index++) {
                    if (iTailX[index] == column && iTailY[index] == row) {
                        std::cout << "*";
                        bPrintTail = true;
                    }
                }
                if (!bPrintTail)
                    std::cout << " ";
            }
            if (column == g_Width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }
    for (int bIndex = 0; bIndex < g_Width + 2; bIndex++) {
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << "Score :" << g_score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            eDir = LEFT;
            break;
        case 'w':
            eDir = UP;
            break;
        case 's':
            eDir = DOWN;
            break;
        case 'd':
            eDir = RIGHT;
            break;
        case 'x':
            g_GameOver = true;
            break;
        default:
            break;
        }
    }
}

void algorithm() {
    Sleep(150);
    int prevX, prevY, prev2X, prev2Y;
    prevX = iTailX[0];
    prevY = iTailY[0];
    iTailX[0] = g_snakeX;
    iTailY[0] = g_snakeY;
    for (int index = 1; index < nTail; index++) {
        prev2X = iTailX[index];
        prev2Y = iTailY[index];
        iTailX[index] = prevX;
        iTailY[index] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (eDir) {
    case LEFT:
        g_snakeX--;
        break;
    case RIGHT:
        g_snakeX++;
        break;
    case UP: 
        g_snakeY--;
        break;
    case DOWN:
        g_snakeY++;
        break;
    }
    //Handle out of boundary cases
    if (g_snakeX > g_Width)
        g_snakeX = 0;
    else if (g_snakeX < 0)
        g_snakeX = g_Width - 1;
    if (g_snakeY > g_Height)
        g_snakeY = 0;
    else if (g_snakeY < 0)
        g_snakeY = g_Height - 1;

    for (int index = 0; index < nTail; index++) {
        if (iTailX[index] == g_snakeX && iTailY[index] == g_snakeY)
            g_GameOver = true;
    }

    if (g_snakeX == g_fruitX && g_snakeY == g_fruitY) {
        g_score += 10;
        g_fruitX = rand() % g_Width;
        g_fruitY = rand() % g_Height;
        nTail++;
    }


}


int main()
{
    std::cout << "Welcome to Snake Game\n";
    Setup();
    while (!g_GameOver) {
        Draw();
        Input();
        algorithm();
    }
    return 0;
}





