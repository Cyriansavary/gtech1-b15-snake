#ifndef APP_APP_H
#define APP_APP_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;
#include "snake.hpp"
#include "fruit.hpp"
#include "pos.hpp"
#include "text.hpp"

class App
{
private:
public:
    Fruit *fruit;
    vector<Pos> pos;
    vector<Text> snaketext;
    vector<Text> starttext;
    vector<Text> optiontext;
    vector<Text> leavetext;
    vector<Text> arrowtext;
    vector<Text> gamelstext;
    vector<Text> overtext;
    Head *head;

    App();
    ~App();
    int run();

    int init(void);
    void render();
    bool check_collision(SDL_Rect &A, SDL_Rect &B);
    int makefruitrand(void);
    void game(void);
    void maketext(int alltext[][35], std::vector<Text> sentence, int row, int size, int height, int width);
    void menu();
    void endgame(void);
    void optionmenu(void);
    void scoreboard(int digit1, int digit2, int digit3, int row, int size, int height, int width);
};

#endif