#include "window.h"
#include <cstring>
#include <stdexcept>

using namespace std;

namespace securus::graphics {
  Window::Window(const char* p_title, int p_surf_w, int p_surf_h, int p_win_w, int p_win_h) {
    m_window = SDL_CreateWindow(
      p_title,
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      p_win_w, p_win_h,
      SDL_WINDOW_SHOWN
    );

    if (not m_window)
      throw runtime_error( SDL_GetError() ); 

    m_renderer = SDL_CreateRenderer(
      m_window,
      -1,
      SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC
    );

    if (not m_renderer)
      throw runtime_error( SDL_GetError() ); 

    SDL_RenderSetLogicalSize(m_renderer,p_surf_w, p_surf_h);
  }


  Window::~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
  }


  // - Methods -------------------------
  // ~ update
  auto Window::update() -> void {
    SDL_RenderPresent(m_renderer);

    SDL_Color &clr = backgroundColor;

    SDL_SetRenderDrawColor(m_renderer, clr.r, clr.g, clr.b, clr.a);
    SDL_RenderClear(m_renderer);
  }


  // ~ sprites
  auto Window::load_sprite(string filename) -> void { 
    // Check if sprite was already opened
    if (m_sprites.contains(filename))
      throw runtime_error("Sprite with name \"" + filename + "\" already opened");

    SDL_Texture* texture = IMG_LoadTexture(m_renderer, ("assets/sprites/" + filename).c_str());

    // Check if texture was successfuly loaded
    if (not texture)
      throw runtime_error( SDL_GetError() );

    m_sprites[filename] = new Sprite(texture);
  }

  auto Window::get_sprite(string filename) -> Sprite* {
    // Check if sprite was loaded
    if(not m_sprites.contains(filename))
      throw runtime_error("Sprite with name \"" + filename + "\" wasn't loaded");

    return m_sprites[filename];
  }


  // ~ draw
  auto Window::draw_sprite(string name, int x, int y, float xscale, float yscale) -> void {
    Sprite *sprite = m_sprites[name];
    SDL_Rect draw_rect;

    draw_rect.x = x;
    draw_rect.y = y;
    draw_rect.w = sprite->w * xscale;
    draw_rect.h = sprite->h * yscale;

    if (SDL_RenderCopy(m_renderer, sprite->texture, &sprite->rect, &draw_rect) < 0)
      throw runtime_error( SDL_GetError() );
  } 
}
