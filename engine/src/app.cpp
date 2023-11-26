#include "app.h"

using namespace std;

namespace securus {
  using namespace graphics;

  App::App() {
    _init_sdl();
  }

  App::~App() {
    _quit_sdl();

    delete m_scene;
    delete m_window;
  }

  auto App::update() -> void {
    // Update current scene
    m_scene->update();

    // Update window
    m_window->update();
  }

  auto App::_init_sdl() -> void {
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0 or not IMG_Init(IMG_INIT_PNG))
      throw runtime_error( SDL_GetError() );
  }

  auto App::_quit_sdl() -> void {
    IMG_Quit();
    SDL_Quit();
  }
}
