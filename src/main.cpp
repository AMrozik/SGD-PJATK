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

#include <math.h>

#define WIDTH 1280
#define HEIGHT 720
#define FONT_SIZE 64

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
SDL_Color color;
int frameCount, timerFPS, lastFrame, fps;

bool has_winner = false;
bool running;
bool turn;

SDL_Rect score_board;
SDL_Rect test1;

string score;
int score_1=0, score_2=0;


void Intersections(SDL_Rect *ball_hitbox, SDL_Rect *player_hitbox, Ball &ball){
  if(SDL_HasIntersection(ball_hitbox, player_hitbox)){
    double bounce_angle = (ball_hitbox->y - (player_hitbox->y + player_hitbox->h/2))*0.05;
    cout << bounce_angle << endl;
    ball.set_Velocity(-ball.get_Velocity_x()*1.05, bounce_angle*1.05);
  }
}



void serve(Pallete &player1, Pallete &player2, Ball &ball, bool turn){
  if(turn){
    ball.set_Center({80, player1.get_Rect().y + player1.get_Rect().h/2});
    ball.set_Velocity(10, 0);
  }
  else{
    ball.set_Center({WIDTH - 60, player2.get_Rect().y+ player1.get_Rect().h/2});
    ball.set_Velocity(-10, 0);
  }
}


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

void check_winner(Pallete &player1, Pallete &player2, Ball &ball, bool turn){
  if (score_1==10){
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    score = to_string(score_1) + "  " + to_string(score_2);
    write(score, WIDTH/2+FONT_SIZE, FONT_SIZE);
    write("Player 1 Wins!", WIDTH/2+FONT_SIZE+130, FONT_SIZE+300);
    has_winner = true;
    return;
  }

  if (score_2==10){
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    score = to_string(score_1) + "  " + to_string(score_2);
    write(score, WIDTH/2+FONT_SIZE, FONT_SIZE);
    write("Player 2 Wins!", WIDTH/2+FONT_SIZE+130, FONT_SIZE+300);
    has_winner = true;
    return;
  }

  serve(player1, player2, ball, turn);

}


void render(Pallete &player1, Pallete &player2, Ball &ball){
  SDL_SetRenderDrawColor(renderer, 0,0,0,255);

  frameCount++;
  timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(1000/60)){
    SDL_Delay((1000/60)-timerFPS);
  }

  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  player1.Render();
  player2.Render();
  ball.Render();

  write(score, WIDTH/2+FONT_SIZE, FONT_SIZE);

  SDL_RenderPresent(renderer);
}


void update(Pallete &player1, Pallete &player2, Ball &ball, SDL_Renderer &renderer){

  SDL_Rect player1_hitbox = player1.get_Rect();
  SDL_Rect player2_hitbox = player2.get_Rect();
  SDL_Rect new_ball_hitbox = {ball.get_Center().x - ball.get_Radius() + ball.get_Velocity_x(), ball.get_Center().y - ball.get_Radius() + ball.get_Velocity_y(), ball.get_Radius()*2, ball.get_Radius()*2};

  SDL_SetRenderDrawColor(&renderer, 0,0,0,0);
  SDL_RenderClear(&renderer);
  SDL_SetRenderDrawColor(&renderer, 0,255,0,255);


  Intersections(&new_ball_hitbox, &player1_hitbox, ball);
  Intersections(&new_ball_hitbox, &player2_hitbox, ball);


  score = to_string(score_1) + "  " + to_string(score_2);
  if(ball.get_X() <= 0) {score_2++; check_winner(player1, player2, ball, false); }
  if(ball.get_X() + ball.get_Radius() >= WIDTH) {score_1++; check_winner(player1, player2, ball, true);}
  if(ball.get_Y() < 0) ball.Bounce_Y();
  if(ball.get_Y() + ball.get_Radius() >= HEIGHT) ball.Bounce_Y();

  ball.Move();
}

void input(Pallete &player1, Pallete &player2){
  SDL_Event e;
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running=false;
  if(keystates[SDL_SCANCODE_ESCAPE]) running=false;
  if(keystates[SDL_SCANCODE_UP]) player2.move_Up();
  if(keystates[SDL_SCANCODE_DOWN]) player2.move_Down();
  if(keystates[SDL_SCANCODE_W]) player1.move_Up();
  if(keystates[SDL_SCANCODE_S]) player1.move_Down();
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

      if (!has_winner){
        update(player1, player2, ball, *renderer);
      }
      input(player1, player2);
      render(player1, player2, ball);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
