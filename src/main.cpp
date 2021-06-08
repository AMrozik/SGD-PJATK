/**
 * This is the simple hello world for SDL2.
 *
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Pallete.hpp"
#include "Ball.hpp"

#define WIDTH 1280
#define HEIGHT 720
#define FONT_SIZE 32

using namespace std;

int frameCount, timerFPS, lastFrame, fps;
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
SDL_Color color;

bool running;

SDL_Rect score_board;
SDL_Rect test1;

string score;
int score_1=0, score_2=0;
bool turn;


void write(string text, int x, int y){
  SDL_Surface *surface;
  SDL_Texture *texture;
  if(font==NULL) {
    cout << "failed to load font exiting..." << endl;
    exit(1);
  }
  const char* t = text.c_str();
  surface = TTF_RenderText_Solid(font, t, color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  score_board.w=surface->w;
  score_board.h=surface->h;
  score_board.x=x-score_board.w;
  score_board.y=y-score_board.h;

  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, texture, NULL, &score_board);
}


void render(Pallete player1, Pallete player2, Ball ball){
  SDL_SetRenderDrawColor(renderer, 0,0,0,255);
  SDL_RenderClear(renderer);

  frameCount++;
  timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(1000/60)){
    SDL_Delay((1000/60)-timerFPS);
  }

  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  player1.Render();
  player2.Render();
  ball.Render();

  write(score, WIDTH/2+FONT_SIZE, FONT_SIZE*2);

  SDL_RenderPresent(renderer);
}

void update(){
  score = to_string(score_1) + "  " + to_string(score_2);
}

void input(){
  SDL_Event e;
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running=false;
  if(keystates[SDL_SCANCODE_ESCAPE]) running=false;
  if(keystates[SDL_SCANCODE_UP]);
  if(keystates[SDL_SCANCODE_DOWN]);
}


int main(int, char **) {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) cout << "SDL init failed" << endl;
  if (SDL_Init(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0,  &window, &renderer)) < 0) cout << "failed to create window and renderer" << endl;
  if (TTF_Init() < 0) cout << "failed to initialize sdl_ttf" << endl;
  font = TTF_OpenFont("Peepo.ttf", FONT_SIZE);

  color.r = color.g = color.b = 255;

  Pallete player1 = Pallete(renderer, {20, HEIGHT / 2, 20, 100});
  Pallete player2 = Pallete(renderer, {WIDTH - 40, HEIGHT / 2, 20, 100});
  Ball ball = Ball(renderer);


  running = true;

  static int lastTime=0;
    while(running){
      lastFrame=SDL_GetTicks();
      if(lastFrame>=(lastTime+1000)){
        lastTime=lastFrame;
        fps=frameCount;
        frameCount = 0;
      }

      update();
      input();
      render(player1, player2, ball);
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;


  //
  // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  // SDL_RenderClear(renderer);
  //
  // Pallete player1 = Pallete(renderer, {20, HEIGHT / 2, 20, 100});
  // Pallete player2 = Pallete(renderer, {WIDTH - 40, HEIGHT / 2, 20, 100});
  // Ball ball = Ball(renderer);
  // player1.Render();
  // player2.Render();
  // ball.Render();
  //
  // SDL_RenderPresent(renderer); // draw frame to screen

    // this_thread::sleep_until(current_time = current_time + dt);
  //}

}
