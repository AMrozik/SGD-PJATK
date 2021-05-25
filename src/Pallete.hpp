#include <SDL2/SDL.h>

// Player object
class Pallete{

private:
  double velocity = 0; // object moves only on y axis
  SDL_Color color = {0, 0, 255, 255}; //RGBA
  SDL_Rect dimensions; // {location.x, location.y, width, high}
  SDL_Renderer *renderer;


public:

////// constructors
  Pallete(SDL_Renderer *renderer, SDL_Rect dimensions){
    this->renderer = renderer;
    this->dimensions = dimensions;
  }


  Pallete(SDL_Renderer *renderer, SDL_Rect dimensions, SDL_Color color){
    this->renderer = renderer;
    this->dimensions = dimensions;
    this->color = color;
  }


///// do i need to manually delete something?
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

  SDL_Rect get_Dimensions(){
    return this->dimensions;
  }


/////// setters
  void set_Velocity(double v){
    this->velocity = v;
  }

  void set_Color(SDL_Color color){
    this->color = color;
  }

  void set_Dimensions(SDL_Rect dims){
    this->dimensions = dims;
  }


////// rendering
  void Render(){
    SDL_SetRenderDrawColor(this->renderer, this->color.r,this->color.g,this->color.b,this->color.a);
    SDL_RenderFillRect(this->renderer, &this->dimensions);
  }

};
