#include "Pallete.hpp"
#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 720

////// constructors
  Pallete::Pallete(SDL_Renderer *renderer, SDL_Rect rect){
    this->renderer = renderer;
    this->rect = rect;
  }


  Pallete::Pallete(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color){
    this->renderer = renderer;
    this->rect = rect;
    this->color = color;
  }


  Pallete::~Pallete(){
    SDL_DestroyRenderer(this->renderer);
  }



////// getters
  double Pallete::get_Velocity(){
    return this->velocity;
  }

  SDL_Color Pallete::get_Color(){
    return this->color;
  }

  SDL_Rect Pallete::get_Rect(){
    return this->rect;
  }


/////// setters
  void Pallete::set_Velocity(double v){
    this->velocity = v;
  }

  void Pallete::set_Color(SDL_Color color){
    this->color = color;
  }

  void Pallete::set_Rect(SDL_Rect dims){
    this->rect = dims;
  }

  void Pallete::set_position(int y){
    this->rect.y = y;
  }



  void Pallete::move_Down(){

    this->rect.y+=this->velocity;
    if(this->rect.y + this->rect.h > HEIGHT) this->rect.y = HEIGHT - this->rect.h;
  }

  void Pallete::move_Up(){
    this->rect.y -= this->velocity;
    if(this->rect.y<0) this->rect.y = 0;
  }



////// rendering
  void Pallete::Render(){
    SDL_SetRenderDrawColor(this->renderer, this->color.r,this->color.g,this->color.b,this->color.a);
    SDL_RenderFillRect(this->renderer, &this->rect);
  }
