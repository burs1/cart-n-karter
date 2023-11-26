#pragma once

#include <map>
#include "sdl.h"
#include <string>
#include "sprite.h"
#include <stdexcept>
#include "sdl_image.h"

namespace securus::graphics {
  class Window {
  public:
    Window(const char*, int, int, int, int);

    ~Window();

    
    // - Methods -------------------------
    // ~ update
    auto update()                 -> void;


    // ~ resources
    auto load_sprite(std::string) -> void;

    auto get_sprite(std::string)  -> Sprite*;


    // ~ draw
    auto draw_sprite(std::string, int, int, float xscale=1, float yscale=1) -> void;


    // - Variables -----------------------
    SDL_Color backgroundColor;

    
  private:
    // - Variables -----------------------
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    std::map< std::string, Sprite* > m_sprites;


  };
}
