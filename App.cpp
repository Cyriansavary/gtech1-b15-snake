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
#include "sentence.hpp"
#include "App.hpp"


SDL_Window * window;
SDL_Renderer * renderer; //Déclaration du renderer

int score = 0;
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int verif = 0;
int indexmenu = 0;
int arrowpos = 0;
int init(void);
bool check_collision(SDL_Rect & A, SDL_Rect & B);
void render(void);
int makefruitrand(void);
void game(void);
void maketext(int alltext[][35], std::vector < Text > sentence, int row, int size, int height, int width);
void menu(void);
void endgame(void);
void optionmenu(void);
void scoreboard(int digit1, int digit2, int digit3, int row, int size, int height, int width);


int posarrow[3] = {
  HeightText1,
  HeightText2,
  HeightText3
};


  App::App(){
      this->fruit = new Fruit(0, 0);
      this->head =new Head(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, score);
  }

  App::~App(){
      if(this->fruit != NULL) delete this->fruit;
      if(this->head != NULL) delete this->head;
  }

int App::run(){
              const Uint8 * keystates = SDL_GetKeyboardState(0);
  int initCode = init();
  bool closeRequest = false;
  SDL_Event e;
  pos.push_back(Pos(500, 500, score));
  Uint32 frameStart, frameTime, frameDelay = 7;
         if (initCode)
    return initCode;

  while (!closeRequest) {
    frameStart = SDL_GetTicks();
    // Poll window events.
    while (SDL_PollEvent( & e) != 0) {
      if (e.type == SDL_QUIT) {
        closeRequest = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          closeRequest = true;
          break;
        }
      }
    }
    switch (indexmenu) {

    case 0:
      menu();
      break;
    case 1:
      game();
      scoreboard(digit1, digit2, digit3, sizeof(numbers) / sizeof(numbers[0]), SizeNumber , HeightNumber , WidthNumber );
      break;
    case 2:
      endgame();
      break;
	case 3:
		optionmenu();
		break;
    }
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }

  }
  // Destruction du renderer et de la fenêtre :
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  return 0;
    }

    int App::init(void) {
  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL init failed.\n");
    return 1;
  }
  // Create the SDL window.
  window = SDL_CreateWindow("Snake.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("SDL window creation failed.\n");
    return 2;
  }
  // Create renderer for window.
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  return 0;
}

void App::render() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Couleur blanche
  fruit->makerectfruit();
  pos[0].makerect(pos[0].posX, pos[0].posY, 0);
  SDL_RenderFillRect(renderer, & pos[0].rect);
  for (int i = 1; i < score; i++) {
    pos.push_back(Pos(pos[i].posX, pos[i].posY, i));
  }
  for (int j = score; j != 0; j--) {
    pos[j].posX = pos[j - 1].posX;
    pos[j].posY = pos[j - 1].posY;
  }
  for (int k = 1; k < score; k++) {
    pos[k].makerect(pos[k].posX, pos[k].posY, k);
    SDL_RenderFillRect(renderer, & pos[k].rect);
  }
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //Couleur blanche
  SDL_RenderFillRect(renderer, & fruit->fruit);
  //SDL_Delay(1);
  SDL_RenderPresent(renderer);
  //SDL_Delay(5);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

bool App::check_collision(SDL_Rect & A, SDL_Rect & B) {
  //Les cotes des rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calcul les cotes du rectangle A
  leftA = A.x;
  rightA = A.x + A.w;
  topA = A.y;
  bottomA = A.y + A.h;

  //Calcul les cotes du rectangle B
  leftB = B.x;
  rightB = B.x + B.w;
  topB = B.y;
  bottomB = B.y + B.h;
  //Tests de collision
  if (bottomA <= topB) {
    return false;
  }

  if (topA >= bottomB) {
    return false;
  }

  if (rightA <= leftB) {
    return false;
  }

  if (leftA >= rightB) {
    return false;
  }

  //Si conditions collision detectee
  return true;
}

int App::makefruitrand(void) {

  if ((fruit->fruitX == 0 && fruit->fruitY == 0)) {
    srand(time(NULL));
    fruit->fruitX = rand() % (SCREEN_WIDTH - SNAKE);
    fruit->fruitY = rand() % (SCREEN_HEIGHT - SNAKE);
  }

  if (check_collision(pos[0].rect, fruit->fruit)) {
    score += 25;
    digit1 ++;
    if (digit1 == 10){
      digit1 = 0;
      digit2++;
    }
    if (digit2 == 10){
      digit2 = 0;
      digit3++;
    }
    
  }
  for (int j = 0; j < score; j++) {
    if (check_collision(pos[j].rect, fruit->fruit) == 1) {
      fruit->fruitX = rand() % (SCREEN_WIDTH - SNAKE);
      fruit->fruitY = rand() % (SCREEN_HEIGHT - SNAKE);
      return 0;
    }
  }
  return 0;
}

void App::game(void) {
  head->update(pos[0]);
  head->moving(pos[0]);
  render();
  makefruitrand();
  for (int i = (SNAKE * 3); i < score; i++) {
    if (check_collision(pos[0].rect, pos[i].rect)) {
      indexmenu = 2;
    }
  }
}

void App::maketext(int alltext[][35], std::vector < Text > sentence, int row, int size, int height, int width) {
  int column;
  column = sizeof(alltext[0]) / row;
  for (int i = 0; i < row; i++) {
    sentence.push_back(Text(alltext[i]));
  }
  for (int j = 0; j < row; j++) {
    for (int k = 0; k < column; k++) {
      if (sentence[j].row[k] == 1) {
        SDL_Rect rect = {
          width + (k * size),
          height + (j * size),
          size,
          size
        };
        SDL_RenderDrawRect(renderer, & rect);
        SDL_RenderFillRect(renderer, & rect);
      }
    }
  }
}

void App::menu() {
  SDL_SetRenderDrawColor(renderer, 50, 200, 50, 0);
  maketext(Title, snaketext, sizeof(Title) / sizeof(Title[0]), SizeTextTitle, HeightTextTitle, WidthTextTitle);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  maketext(start, starttext, sizeof(start) / sizeof(start[0]), SizeText, HeightText1, WidthText);
  maketext(option, optiontext, sizeof(option) / sizeof(option[0]), SizeText, HeightText2, WidthText);
  maketext(leave, leavetext, sizeof(leave) / sizeof(leave[0]), SizeText, HeightText3, WidthText);
  maketext(arrow, arrowtext, sizeof(arrow) / sizeof(arrow[0]), SizeText, posarrow[head->movearrow], WidthArrow);
  indexmenu = head->update(pos[0]);
  SDL_RenderPresent(renderer);
  //SDL_Delay(5);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void App::endgame(void) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  maketext(gamels, gamelstext, sizeof(gamels) / sizeof(gamels[0]), SizeTextTitle, HeightTextTitle * 2, WidthTextTitle);
  maketext(over, overtext, sizeof(over) / sizeof(over[0]), SizeTextTitle, HeightTextTitle * 4, WidthTextTitle);
  SDL_RenderPresent(renderer);
  //SDL_Delay(5);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}
void App::optionmenu(void) {
	  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  maketext(option, optiontext, sizeof(option) / sizeof(option[0]), SizeTextTitle, HeightTextTitle, WidthTextTitle);
  maketext(start, starttext, sizeof(start) / sizeof(start[0]), SizeText, HeightText1, WidthText);
  maketext(option, optiontext, sizeof(option) / sizeof(option[0]), SizeText, HeightText2, WidthText);
  maketext(leave, leavetext, sizeof(leave) / sizeof(leave[0]), SizeText, HeightText3, WidthText);
  maketext(arrow, arrowtext, sizeof(arrow) / sizeof(arrow[0]), SizeText, posarrow[head->movearrow], WidthArrow);
 // indexmenu = head->update(pos[0]);
  SDL_RenderPresent(renderer);
  //SDL_Delay(5);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void App::scoreboard(int digit1, int digit2, int digit3, int row, int size, int height, int width){


  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
for (int i = 0; i < 5; i++)
{
  for (int j = 0; j < 4; j++)
  {
        if (numbers[digit3][i][j] == 1) {
        SDL_Rect rect = {
          width + (j * size),
          height + (i * size),
          size,
          size
        };
          SDL_RenderDrawRect(renderer, & rect);
        SDL_RenderFillRect(renderer, & rect);
        } 
  }
}
for (int i = 0; i < 5; i++)
{
  for (int j = 0; j < 4; j++)
  {
        if (numbers[digit2][i][j] == 1) {
        SDL_Rect rect = {
          width + (j * size)+size*5,
          height + (i * size),
          size,
          size
        };
          SDL_RenderDrawRect(renderer, & rect);
        SDL_RenderFillRect(renderer, & rect);
        } 
  }
}
  for (int i = 0; i < 5; i++)
{
  for (int j = 0; j < 4; j++)
  {
        if (numbers[digit1][i][j] == 1) {
        SDL_Rect rect = {
          width + (j * size)+size*10,
          height + (i * size),
          size,
          size
        };
          SDL_RenderDrawRect(renderer, & rect);
        SDL_RenderFillRect(renderer, & rect);
        } 
  }
}
}