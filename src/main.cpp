/**
 * This is the simple hello world for SDL2.
 *
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#define HEIGHT 640
#define WIDTH 480

// check for errors
#define errcheck(e)                                                            \
  {                                                                            \
    if (e) {                                                                   \
      cout << SDL_GetError() << endl;                                          \
      SDL_Quit();                                                              \
      return -1;                                                               \
    }                                                                          \
  }

int main(int, char **) {
  using namespace std;
  using namespace std::chrono;

  errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);

  shared_ptr<SDL_Window> window(SDL_CreateWindow("Pong SDL2 LEEEETS GOOOOO",
                                                 SDL_WINDOWPOS_UNDEFINED,
                                                 SDL_WINDOWPOS_UNDEFINED,
                                                 HEIGHT,
                                                 WIDTH,
                                                 SDL_WINDOW_SHOWN),
                                [](SDL_Window *p) { SDL_DestroyWindow(p); });
  errcheck(window == nullptr);

  shared_ptr<SDL_Renderer> renderer(
      SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
      [](SDL_Renderer *r) {
        SDL_DestroyRenderer(r);
      }); // SDL_RENDERER_PRESENTVSYNC
  errcheck(renderer == nullptr);

  // auto dt = 15ms;
  milliseconds dt(15);

  steady_clock::time_point current_time =
      steady_clock::now(); // remember current time
      int x=0,y=0;
      bool point_active = false;
  for (bool game_active = true; game_active;) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // check if there are some events
      switch (event.type) {
      case SDL_QUIT:
        game_active = false;
        break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) game_active = false;
          if(event.key.keysym.sym == SDLK_RIGHT && point_active){
            x+=1;
            SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
            SDL_RenderClear(renderer.get());
            SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer.get(), x, y);
          }
          if(event.key.keysym.sym == SDLK_LEFT && point_active){
            x-=1;
            SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
            SDL_RenderClear(renderer.get());
            SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer.get(), x, y);
          }
          if(event.key.keysym.sym == SDLK_UP && point_active){
            y-=1;
            SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
            SDL_RenderClear(renderer.get());
            SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer.get(), x, y);
          }
          if(event.key.keysym.sym == SDLK_DOWN && point_active){
            y+=1;
            SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
            SDL_RenderClear(renderer.get());
            SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer.get(), x, y);
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          SDL_GetMouseState(&x, &y);
          SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
          SDL_RenderDrawPoint(renderer.get(), x, y);
          point_active = true;
          break;
      }
    }

    // double x = 0, y = 240;
    // double px = x, py = y;
    //
    // x += 0.6;
    // y = sin(0.1 * x / M_PI) * 200 + 240;
    //
    // SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    // SDL_RenderDrawLineF(renderer.get(), x, y, px, py);

    SDL_RenderPresent(renderer.get()); // draw frame to screen

    this_thread::sleep_until(current_time = current_time + dt);
  }
  SDL_DestroyRenderer(renderer.get());
  SDL_DestroyWindow(window.get());
  SDL_Quit();
  return 0;
}
