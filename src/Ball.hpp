#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 720


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

class Vector2f{
public:
  double x;
  double y;

  Vector2f(double x, double y){
    this->x = x;
    this->y = y;
  }

  void reverse_X(){
    this->x = -this->x;
  }
  void reverse_Y(){
    this->y = -this->y;
  }
};


// Ball Object
class Ball{

private:
  Vector2f velocity = Vector2f(0,0);
  SDL_Color color = {255, 255, 255, 255}; //RGBA
  SDL_Point center = {WIDTH / 2, HEIGHT / 2};
  int radius = 10;
  SDL_Renderer *renderer;


public:

////// constructors
  Ball(SDL_Renderer *renderer){
    this->renderer = renderer;
  }

  Ball(SDL_Renderer *renderer, SDL_Point center, int radius, Vector2f velocity){
    this->renderer = renderer;
    this->center = center;
    this->radius = radius;
    this->velocity = velocity;
  }


  Ball(SDL_Renderer *renderer, SDL_Point c, int r, Vector2f v, SDL_Color cr){
    this->renderer = renderer;
    this->center = c;
    this->radius = r;
    this->velocity = v;
    this->color = cr;
  }


  ~Ball(){
    SDL_DestroyRenderer(this->renderer);
  }



////// getters
  double get_Velocity_x(){
    return this->velocity.x;
  }

  double get_Velocity_y(){
    return this->velocity.y;
  }

  SDL_Color get_Color(){
    return this->color;
  }

  SDL_Point get_Center(){
    return this->center;
  }

  int get_X(){
    return this->center.x;
  }

  int get_Y(){
    return this->center.y;
  }

  int get_Radius(){
    return this->radius;
  }


/////// setters
  void set_Velocity(double x, double y){
    this->velocity.x = x;
    this->velocity.y = y;
  }

  void set_Color(SDL_Color color){
    this->color = color;
  }

  void set_Center(SDL_Point p){
    this->center = p;
  }

  void set_Radius(int r){
    this->radius = r;
  }




  void Bounce_X(){
    this->velocity.reverse_X();
  }

  void Bounce_Y(){
    this->velocity.reverse_Y();
  }


////// rendering
  void Render(){
    draw_circle(this->renderer, this->center, this->radius, this->color);
  }

};
