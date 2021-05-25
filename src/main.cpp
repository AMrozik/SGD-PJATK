/**
 * This is the simple hello world for SDL2.
 *
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "Pallete.hpp"
#include "Ball.hpp"

#define WIDTH 1280
#define HEIGHT 720

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

  errcheck(SDL_Init(SDL_INIT_EVERYTHING) != 0);

  shared_ptr<SDL_Window> window(SDL_CreateWindow("Pong SDL2 LEEEETS GOOOOO",
                                                 SDL_WINDOWPOS_UNDEFINED,
                                                 SDL_WINDOWPOS_UNDEFINED, WIDTH,
                                                 HEIGHT, SDL_WINDOW_SHOWN),
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
  for (bool game_active = true; game_active;) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // check if there are some events
      switch (event.type) {
      case SDL_QUIT:
        game_active = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
          game_active = false;
      }
    }

    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
    SDL_RenderClear(renderer.get());

    Pallete player1 = Pallete(renderer.get(), {20, HEIGHT / 2, 20, 100});
    Pallete player2 = Pallete(renderer.get(), {WIDTH - 40, HEIGHT / 2, 20, 100});
    Ball ball = Ball(renderer.get());
    player1.Render();
    player2.Render();
    ball.Render();

    SDL_RenderPresent(renderer.get()); // draw frame to screen

    this_thread::sleep_until(current_time = current_time + dt);
  }
  SDL_DestroyRenderer(renderer.get());
  SDL_DestroyWindow(window.get());
  SDL_Quit();
  return 0;
}
