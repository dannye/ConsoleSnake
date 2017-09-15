#include <iostream>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include "constants.h"
#include "SetConsoleAttributes.h"

using namespace std;

vector<COORD>* snake = new vector<COORD>;
COORD goal;
char dir;
char dirOld;
bool setup;

void initSnake();
void initGoal();
void printBorder();
void printSnake();
void printHead();
bool contains();
bool containsHead();
bool outOfBounds();
void getDirection();
void ai();
void advance();
void clearScreen();

int main() {
    SetWindowTitle("SNAKE++");
    SetWindowSize(LEVEL_HEIGHT, LEVEL_WIDTH);
    SetCursorVisibility(false);
    srand((int)time(0));
    SetTextColor(WHITE);
    printBorder();
    SetTextColor(BLUE);
    while (true) {
        initSnake();
        initGoal();
        printSnake();
        while (true) {
            Sleep(50);
            getDirection();
            //ai();
            advance();
            if (containsHead() || outOfBounds()) {
                break;
            }
            printHead();
        }
        clearScreen();
    }
    delete snake;
    return 0;
}

void initSnake() {
    snake->clear();
    for (int i = 4; i > 1; i--) {
        snake->push_back({ (SHORT)i, (SHORT)4 });
    }
    dirOld = 'd';
    setup = false;
}

void initGoal() {
    do {
        goal = { rand() % (LEVEL_WIDTH - 2) + 1, rand() % (LEVEL_HEIGHT - 2) + 1 };
    } while (contains());
    SetCursorPosition(goal);
    SetTextColor(RED);
    cout << char(219);
    SetTextColor(BLUE);
}

void printBorder() {
    SetCursorPosition(0, 0);
    for (int i = 0; i < LEVEL_WIDTH; i++) {
        cout << char(178);
    }
    for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
        SetCursorPosition(i, 0);
        cout << char(178);
        SetCursorPosition(i, LEVEL_WIDTH - 1);
        cout << char(178);
    }
    SetCursorPosition(LEVEL_HEIGHT - 1, 0);
    for (int i = 0; i < LEVEL_WIDTH - 1; i++) {
        cout << char(178);
    }
}

void printSnake() {
    for (COORD c : *snake) {
        SetCursorPosition(c);
        cout << char(219);
    }
}

void printHead() {
    if (!(snake->front().X == 0 || snake->front().X == LEVEL_WIDTH - 1 ||
        snake->front().Y == 0 || snake->front().Y == LEVEL_HEIGHT - 1)) {
        SetCursorPosition(snake->front());
        SetTextColor(GREEN);
        cout << char(219);
        SetTextColor(BLUE);
        SetCursorPosition(snake->at(1));
        cout << char(219);
    }
}

bool contains() {
    for (COORD c : *snake) {
        if (goal.X == c.X && goal.Y == c.Y) {
            return true;
        }
    }
    return false;
}

bool containsHead() {
    for (int i = snake->size() - 1; i > 0; i--) {
        if (snake->at(i).X == snake->front().X && snake->at(i).Y == snake->front().Y) {
            return true;
        }
    }
    return false;
}

bool outOfBounds() {
    if (snake->front().X <= 0 || snake->front().X >= LEVEL_WIDTH - 1 ||
        snake->front().Y <= 0 || snake->front().Y >= LEVEL_HEIGHT - 1) {
        return true;
    }
    return false;
}

void getDirection() {
    dir = 'x';
    // check if the user has entered 'w', 'a', 's' or 'd'
    if (_kbhit()) {
        dir = tolower(_getch());
        if ((dir == 'a' && dirOld == 'd') ||
            (dir == 'd' && dirOld == 'a') ||
            (dir == 'w' && dirOld == 's') ||
            (dir == 's' && dirOld == 'w')) {
            dir = 'x';
        }
    }
    // if not, try moving in the same direction as before
    if (!strchr(ALL_DIRS, dir)) {
        dir = dirOld;
    }
    dirOld = dir;
}

void ai() {
    int x = snake->front().X;
    int y = snake->front().Y;
    if (!setup) {
        if (y != 1) {
            dir = 'w';
            return;
        }
        else if (x != 1) {
            dir = 'a';
            return;
        }
        else {
            setup = true;
        }
    }
    if (y == 1) {
        if (x != 1) {
            dir = 'a';
            return;
        }
        dir = 's';
        return;
    }
    if (y == 2) {
        if (x == LEVEL_WIDTH - 2) {
            dir = 'w';
            return;
        }
        if (dir == 'w') {
            dir = 'd';
            return;
        }
        dir = 's';
        return;
    }
    if (y == LEVEL_HEIGHT - 2) {
        if (dir == 's') {
            dir = 'd';
            return;
        }
        dir = 'w';
        return;
    }
}

void advance() {
    if (!(snake->back().X == snake->at(snake->size() - 2).X && snake->back().Y == snake->at(snake->size() - 2).Y)) {
        SetCursorPosition(snake->back());
        cout << " ";
    }
    for (int i = snake->size() - 1; i > 0; i--) {
        snake->at(i) = snake->at(i - 1);
    }
    if (dir == 'a') {
        snake->front().X--;
    }
    else if (dir == 'd') {
        snake->front().X++;
    }
    else if (dir == 'w') {
        snake->front().Y--;
    }
    else { // 's'
        snake->front().Y++;
    }
    if (snake->front().X == goal.X && snake->front().Y == goal.Y) {
        snake->push_back(snake->back());
        initGoal();
    }
}

void clearScreen() {
    if (!(snake->front().X == 0 || snake->front().X == LEVEL_WIDTH - 1 ||
        snake->front().Y == 0 || snake->front().Y == LEVEL_HEIGHT - 1)) {
        SetCursorPosition(snake->front());
        cout << " ";
    }
    for (unsigned int i = 1; i < snake->size(); i++) {
        SetCursorPosition(snake->at(i));
        cout << " ";
    }
    SetCursorPosition(goal);
    cout << " ";
}
