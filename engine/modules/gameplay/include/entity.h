#pragma once

#include <string>
#include <stdexcept>
#include "graphics.h"
#include "gameplay_types.h"

namespace securus::gameplay {
  class Entity {
  friend class Scene;
  public:
    Entity();


    // - Variables -----------------------
    float x = 0, y = 0;
    float xscale = 1, yscale = 1;

    // ~ readonly
    graphics::Sprite* const & sprite;

  protected:
    // - Methods -------------------------
    auto get_delta_time() -> float;
    

    // ~ camera
    auto get_camera() -> Camera*;


    // ~ entities
    auto get_entity(std::string, int) -> Entity*;


    // ~ collisions
    auto place_collision(float, float, std::string type="any") -> Entity*;

    auto point_collision(float, float, std::string type="any") -> Entity*;


    // ~ draw
    auto set_sprite(std::string) -> void;

    auto draw_sprite(std::string, int, int, float, float) -> void;
    
    auto draw_self() -> void;


  private:
    // - Events --------------------------
    virtual auto on_create()  -> void {}

    virtual auto on_update()  -> void {}

    virtual auto on_destroy() -> void {}

    virtual auto on_draw()    -> void { draw_self(); }
    

    // - Variables -----------------------
    Scene *m_scene;

    std::string m_type;

    graphics::Sprite* m_sprite = nullptr;
    std::string m_spriteName = "";
  };
}
