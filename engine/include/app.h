#pragma once

#include <map>
#include "sdl.h"
#include <stdexcept>
#include "graphics.h"
#include "gameplay.h"

namespace securus {
  class App {
  public:
    App();

    ~App();

    // - Methods -------------------------
    auto update() -> void;


    // ~ internal
    auto _init_sdl()  -> void;

    auto _quit_sdl()  -> void;

    
    // - Variables -----------------------
    gameplay::Scene* m_scene;
    graphics::Window* m_window;
    
  };
}
