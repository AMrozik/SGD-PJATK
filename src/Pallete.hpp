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
  Pallete(SDL_Renderer *renderer, SDL_Rect rect){
    this->renderer = renderer;
    this->rect = rect;
  }


  Pallete(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color){
    this->renderer = renderer;
    this->rect = rect;
    this->color = color;
  }


  ~Pallete(){
    SDL_DestroyRenderer(this->renderer);
  }



////// getters
  double get_Velocity(){
    return this->velocity;
  }

  SDL_Color get_Color(){
    return this->color;
  }

  SDL_Rect get_Rect(){
    return this->rect;
  }


/////// setters
  void set_Velocity(double v){
    this->velocity = v;
  }

  void set_Color(SDL_Color color){
    this->color = color;
  }

  void set_Rect(SDL_Rect dims){
    this->rect = dims;
  }

  void set_position(int y){
    this->rect.y = y;
  }



  void move_Down(){
    
    this->rect.y+=this->velocity;
    if(this->rect.y + this->rect.h > HEIGHT) this->rect.y = HEIGHT - this->rect.h;
  }

  void move_Up(){
    this->rect.y -= this->velocity;
    if(this->rect.y<0) this->rect.y = 0;
  }



////// rendering
  void Render(){
    SDL_SetRenderDrawColor(this->renderer, this->color.r,this->color.g,this->color.b,this->color.a);
    SDL_RenderFillRect(this->renderer, &this->rect);
  }

};
