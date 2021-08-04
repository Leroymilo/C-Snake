#include <iostream>
#include <conio.h>
#include <unistd.h>

using namespace std;

bool isAlive;
const int w = 10;
const int h = 10;
int Sx, Sy, Fx, Fy;
enum eDirection { STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailx[w*h], taily[w*h];
int lenTail;

void newF()
{
    bool isOnSnake = true;
    while (isOnSnake)
    {
        Fx = rand()%w;
        Fy = rand()%h;
        isOnSnake = false;
        for (int k = 0; k < lenTail; k++)
        {
            if (Fx == tailx[k] && Fy == taily[k])
                isOnSnake = true;
        }
        if (Sx == Fx && Sy == Fy)
            isOnSnake = true;
    }
    
}

void setup()
{
    isAlive = true;
    dir = STOP;
    Sx = w/2;
    Sy = h/2;
    newF();
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            isAlive = false;
            break;
        }
    }
}

void logic()
{
    int Tx = tailx[lenTail];
    int Ty = taily[lenTail];
    for (int i = lenTail; i > 0; i--)
    {
        tailx[i] = tailx[i-1];
        taily[i] = taily[i-1];
    }
    tailx[0] = Sx;
    taily[0] = Sy;

    switch(dir)
    {
    case LEFT:
        Sx--;
        break;
    case RIGHT:
        Sx++;
        break;
    case UP:
        Sy--;
        break;
    case DOWN:
        Sy++;
        break;
    }

    if (Sx < 0 || Sx >= w || Sy < 0 || Sy >= h)
        isAlive = false;

    for (int k = 0; k < lenTail; k++)
    {
        if (tailx[k] == Sx && taily[k] == Sy)
            isAlive = false;
    }

    if (Sx == Fx && Sy == Fy)
    {
        newF();
        lenTail++;
        tailx[lenTail] = Tx;
        taily[lenTail] = Ty;
    }
}

void draw()
{
    system("cls");
    cout << endl;
    for (int col = 0; col < w+2; col++)
        cout << "#";
    cout << endl;
    
    for (int line = 0; line < h; line++)
    {
        cout << "#";
        for (int col = 0; col < w; col++)
        {
            if (col == Sx && line == Sy)
                cout << "X";

            else if (col == Fx && line == Fy)
                cout << "O";

            else
            {
                bool tailDrawn = false;
                
                for (int k = 0; k < lenTail; k++)
                {
                    if (col == tailx[k] && line == taily[k])
                    {
                        cout << "x";
                        tailDrawn = true;
                    }
                }
                if (!tailDrawn)
                    cout << " ";
            }
        }
        cout << "#";
        cout << endl;
    }

    for (int col = 0; col < w+2; col++)
        cout<< "#";
    cout << endl;
}

int main()
{
    setup();
    while (isAlive)
    {
        input();
        logic();
        draw();
        usleep(200000);
    }
    return 0;
}