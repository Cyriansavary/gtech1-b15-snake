#ifndef POS_POS_H
#define POS_POS_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

#define SNAKE 25

class Pos {
  public:
  int posY;
  int posX;
  SDL_Rect rect;

  Pos(int posY, int posX, int score) {
    this -> rect = {
      posX,
      posY,
      SNAKE,
      SNAKE
    };
    if (score == 0) {
      this -> posX = SCREEN_WIDTH / 2;
      this -> posY = SCREEN_HEIGHT / 2;
    }

  }
  void makerect(int posX, int posY, int score) {

    this -> rect = {
      posX,
      posY,
      SNAKE,
      SNAKE
    };
  }
};

#endif