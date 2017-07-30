#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <windows.h>

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score, option, enemyX, enemyY, lives;
enum eDirection {Stop = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[100], tailY[100];
int nTail;

void redo();
void game();
void draw();
void logic();
void setup();
void options();
void input();
void gameover();
void scores();
int highscore;

using namespace std;

int main()
{
    nTail = 0;
    score = 0;
    cout<<".-. . . .-. . . .-."<<endl;
    cout<<"`-. |/| |-| |<  |- "<<endl;
    cout<<"`-' ' ` ` ' ' ` `-'"<<endl;
    cout<<"      1. Play      "<<endl;
    cout<<"      2. Options   "<<endl;
    cout<<"      3. Scores    "<<endl;
    cout<<"      4. End       "<<endl;
    cin>>option;
    if (option == 1)
    {
        game();
    }
    else if (option == 2)
    {
        options();
    }
    else if (option == 3)
    {
        scores();
    }
    else if (option == 4)
    {
        return 0;
    }
    else
    {
        cout<<"Invalid"<<endl;
        redo();
    }
}

void scores()
{
    string line;
    ifstream myfile ("score.dat");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
        cout << line << '\n';
        }
        myfile.close();
    }

    else cout << "Unable to open file";
    main();
}

void input()
{
    if (_kbhit())
    {


        switch(_getch())
        {
            case 'w':

                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void draw()
{
    system("cls");
    for (int i = 0; i < width + 1; i++)
        cout<<"#";
    cout<<endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout<<"#";
            if (i == y && j == x)
                cout<<"O";
            else if (i == fruitY && j == fruitX)
                cout<<"F";
            else if (i == enemyY && j == enemyX)
                cout<<"E";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                if (!print)
                    cout<<" ";
            }

            if (j == width - 1)
                cout<<"#";
        }
        cout<<endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout<<"#";
    cout<<endl;
    cout<<"Score: "<<score<<endl;
    cout<<"Lives: "<<lives<<endl;
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
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
    if (x > width || x < 0 || y > height || y < 0)
    {
        lives -= 1;
        x = width / 2;
        y = height / 2;
    }

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            lives -= 1;
            x = width / 2;
            y = height / 2;
        }
    if (fruitX == enemyX && fruitY == enemyY)
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        enemyX = rand() & width;
        enemyY = rand() & height;
    }
    if (x == enemyX && y == enemyY)
    {
        lives -= 1;
        enemyX = rand() & width;
        enemyY = rand() & height;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        enemyX = rand() & width;
        enemyY = rand() & height;
        nTail++;
    }
}

void redo()
{
    main();
}

void gameover()
{
    cout<<"GAME OVER!"<<endl;
    if (score > highscore)
    {
        highscore = score;
    }
    cout<<"Your score is: "<<score<<endl;
    ofstream myfile;
    myfile.open ("score.dat");
    myfile << "Previous Score: "<<score;
    myfile << "High Score: "<<highscore;
    myfile.close();
    main();
}

void options()
{
    cout<<"Coming Soon!"<<endl;
    system("pause");
    main();
}

void setup()
{
    gameOver = false;
    dir = Stop;
    x = width / 2;
    y = height / 2;
    enemyX = rand() % width;
    enemyY = rand() % height;
    fruitX = rand() % width;
    fruitY = rand() % height;
    lives = 3;
    score = 0;
}

void game()
{
    setup();
    while (!gameOver)
    {
        draw();
        logic();
        input();
        Sleep(25);
        if (lives <= -1)
        {
            gameOver = true;
        }
    }
    gameover();
}
