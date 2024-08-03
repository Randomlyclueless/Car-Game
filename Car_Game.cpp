#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPosition;

int enemyX[3];
int enemyY[3];
int enemyFlag[3];

char car[4][4] = {
    {' ', '|', '|', ' '},
    {'|', '|', '|', '|'},
    {' ', '|', '|', ' '},
    {'|', '|', '|', '|'}};

int carPos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y)
{
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(console, cursorPosition);
}

void drawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            gotoxy(0 + j, i);
            cout << "|";
            gotoxy(WIN_WIDTH - j, i);
            cout << "|";
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH, i);
        cout << "|";
    }
}

void updateScore()
{
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
}

void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand() % 33;
}

void drawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << car[i][j];
        }
    }
}

void drawEnemy(int ind)
{
    if (enemyFlag[ind] == 1)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "**";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "**";
    }
}

int collision()
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
        {
            return 1;
        }
    }
    return 0;
}

void gameOver()
{
    system("cls");
    cout << endl;
    cout << "\t\t--------------------------------------------------------" << endl;

    cout << "\t\t-----------------------GAME OVER-----------------------" << endl;

    cout << "\t\t--------------------------------------------------------" << endl;

    cout << "\t\tPress any key to go back to main menu. ";
    getch();
}

void eraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << " ";
        }
    }
}

void eraseEnemy(int ind)
{
    if (enemyFlag[ind] == 1)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "    ";
    }
}

void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void setCursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void play()
{
    carPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;
    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2);
    cout << "Car Game";

    gotoxy(WIN_WIDTH + 6, 4);
    cout << "--------------------:)";

    gotoxy(WIN_WIDTH + 6, 6);
    cout << "--------------------:)";

    gotoxy(WIN_WIDTH + 7, 12);
    cout << "Control";

    gotoxy(WIN_WIDTH + 7, 13);
    cout << "--------------------:)";

    gotoxy(WIN_WIDTH + 7, 14);
    cout << "A Key -->>>> Left";
    gotoxy(WIN_WIDTH + 7, 15);
    cout << "D Key -->>>> right";

    gotoxy(18, 5);
    cout << "Press any key to start";
    getch();
    gotoxy(18, 5);
    cout << "                      ";

    while (true)
    {
        if (kbhit())
        {
            char ch = getch();
            if (ch == 'a' || ch == 'A')
            {
                if (carPos > 18)
                {
                    carPos -= 4;
                }
            }
            if (ch == 'd' || ch == 'D')
            {
                if (carPos < 50)
                {
                    carPos += 4;
                }
            }
            if (ch == 27)
            {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);

        if (collision() == 1)
        {
            gameOver();
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
        {
            if (enemyFlag[1] == 0)
            {
                enemyFlag[1] = 1;
            }
        }
        if (enemyFlag[0] == 1)
        {
            enemyY[0] += 1;
        }
        if (enemyFlag[1] == 1)
        {
            enemyY[1] += 1;
        }
        if (enemyY[0] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(0);
            score++;
            updateScore();
        }
    }
}

int main()
{
    setCursor(false, 0);
    srand((unsigned)time(NULL));

    do
    {
        system("cls");
        gotoxy(10, 5);
        cout << "--------------------------------------------------------" << endl;
        gotoxy(10, 6);
        cout << "|-----------------------CAR GAME-----------------------|" << endl;
        gotoxy(10, 7);
        cout << "--------------------------------------------------------" << endl;

        gotoxy(10, 9);
        cout << "1.Start game " << endl;
        gotoxy(10, 10);
        cout << "2.Instructions " << endl;
        gotoxy(10, 11);
        cout << "3.Quit " << endl;

        gotoxy(10, 13);
        cout << "Select Options";
        char op = getche();

        if (op == '1')
        {
            play();
        }
        else if (op == '2')
        {
            // instructions();
        }
        else if (op == '3')
        {
            exit(0);
        }

    } while (true);
    return 0;
}