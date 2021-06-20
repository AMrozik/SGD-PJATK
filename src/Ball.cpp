
#include "Ball.hpp"
#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 720

// https://stackoverflow.com/questions/28346989/drawing-and-filling-a-circle
void draw_circle(SDL_Renderer *renderer, SDL_Point center, int radius, SDL_Color color) {

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {

      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset

      if ((dx * dx + dy * dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}


////// constructors
  Ball::Ball(SDL_Renderer *renderer){
    this->renderer = renderer;

  }

  Ball::Ball(SDL_Renderer *renderer, SDL_Point center, int radius, Vector2f velocity){
    this->renderer = renderer;
    this->center = center;
    this->radius = radius;
    this->velocity = velocity;
  }


  Ball::Ball(SDL_Renderer *renderer, SDL_Point c, int r, Vector2f v, SDL_Color cr){
    this->renderer = renderer;
    this->center = c;
    this->radius = r;
    this->velocity = v;
    this->color = cr;
  }


  Ball::~Ball(){
    SDL_DestroyRenderer(this->renderer);
  }



////// getters
  double Ball::get_Velocity_x(){
    return this->velocity.x;
  }

  double Ball::get_Velocity_y(){
    return this->velocity.y;
  }

  SDL_Color Ball::get_Color(){
    return this->color;
  }

  SDL_Point Ball::get_Center(){
    return this->center;
  }

  int Ball::get_X(){
    return this->center.x;
  }

  int Ball::get_Y(){
    return this->center.y;
  }

  int Ball::get_Radius(){
    return this->radius;
  }


/////// setters
  void Ball::set_Velocity(double x, double y){
    this->velocity.x = x;
    this->velocity.y = y;
  }

  void Ball::set_Color(SDL_Color color){
    this->color = color;
  }

  void Ball::set_Center(SDL_Point p){
    this->center = p;
  }

  void Ball::set_Radius(int r){
    this->radius = r;
  }




  void Ball::Bounce_X(){
    this->velocity.reverse_X();
  }

  void Ball::Bounce_Y(){
    this->velocity.reverse_Y();
  }

  void Ball::Move(){
    this->center = {
      this->center.x + this->velocity.x,
      this->center.y + this->velocity.y
    };
  }


////// rendering
  void Ball::Render(){
    draw_circle(this->renderer, this->center, this->radius, this->color);
  }
