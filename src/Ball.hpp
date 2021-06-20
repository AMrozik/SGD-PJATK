#pragma once

#include "Vector2f.hpp"
#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 720


// Ball Object
class Ball{

private:
  Vector2f velocity = Vector2f(10,5);
  SDL_Color color = {255, 255, 255, 255}; //RGBA
  SDL_Point center = {WIDTH / 2, HEIGHT / 2};
  int radius = 10;
  SDL_Renderer *renderer;


public:
////// constructors
  Ball(SDL_Renderer *renderer);
  Ball(SDL_Renderer *renderer, SDL_Point center, int radius, Vector2f velocity);
  Ball(SDL_Renderer *renderer, SDL_Point c, int r, Vector2f v, SDL_Color cr);
  ~Ball();



////// getters
  double get_Velocity_x();
  double get_Velocity_y();
  SDL_Color get_Color();
  SDL_Point get_Center();
  int get_X();
  int get_Y();
  int get_Radius();


/////// setters
  void set_Velocity(double x, double y);
  void set_Color(SDL_Color color);
  void set_Center(SDL_Point p);
  void set_Radius(int r);


  void Bounce_X();
  void Bounce_Y();
  void Move();


////// rendering
  void Render();

};
