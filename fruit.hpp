#ifndef FRUIT_FRUIT_H
#define FRUIT_FRUIT_H

#include <SDL2/SDL.h>

class Fruit {
  private:

    public:
    SDL_Rect fruit;
  int fruitX;
  int fruitY;
  Fruit(int fruitX, int fruitY) {

    this -> fruitX = 0;
    this -> fruitY = 0;
    this -> fruit = {
      fruitX,
      fruitY,
      25,
      25
    };
  }
  void makerectfruit() {
    this -> fruit = {
      fruitX,
      fruitY,
      25,
      25
    };
  }

};

#endif