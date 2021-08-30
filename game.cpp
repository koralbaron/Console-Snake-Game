#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width /2;   // for centering 
    y = height /2; // the head psition on start of game
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            else if (j == width - 1)
                cout << "#";
            else if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (i == tailY[k] && j == tailX[k]) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if(printTail == false)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0]; //last head pos
    int prevY = tailY[0];//
    int prevTmpX, prevTmpY;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prevTmpX = tailX[i];
        prevTmpY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevTmpX;
        prevY = prevTmpY;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x < 0 || y > height || y < 0)
    //    gameOver = true;
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    else if (y >= height)
        y = 0;
    else if(y < 0)
        y = height - 1;
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(30);
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
