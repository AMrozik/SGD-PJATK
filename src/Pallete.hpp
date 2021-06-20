#pragma once

#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 720

// Player object
class Pallete{

private:
  double velocity = 8; // object moves only on y axis
  SDL_Color color = {0, 0, 255, 255}; //RGBA
  SDL_Rect rect; // {location.x, location.y, width, high}
  SDL_Renderer *renderer;
  


public:

////// constructors
  Pallete(SDL_Renderer *renderer, SDL_Rect rect);
  Pallete(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
  ~Pallete();



////// getters
  double get_Velocity();
  SDL_Color get_Color();
  SDL_Rect get_Rect();


/////// setters
  void set_Velocity(double v);
  void set_Color(SDL_Color color);
  void set_Rect(SDL_Rect dims);
  void set_position(int y);



  void move_Down();
  void move_Up();



////// rendering
  void Render();
};
