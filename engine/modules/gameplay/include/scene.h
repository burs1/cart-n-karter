#pragma once

#include <map>
#include <vector>
#include <string>
#include "graphics.h"
#include "gameplay_types.h"

namespace securus::gameplay {
  class Scene {
  public:
    Scene(graphics::Window*, const float&);

    ~Scene();


    // - Methods -------------------------
    // ~ main
    auto update() -> void;

    template<class T>
    auto instantiate_entity(float x=0, float y=0, std::string spriteName="") -> T* {
      static_assert(std::is_base_of<Entity, T>(), "This class doesn't derrives from the Entity class");

      T *entity = new T();
      _initialize_entity(entity, spriteName, x, y, typeid(entity).name());
      return entity;
    }

    // ~ camera
    auto get_camera() -> Camera*;


    // ~ entities
    auto get_entity(std::string, int) -> Entity*;


    // ~ collisions
    auto check_collision(float, float, float, float, std::string, Entity* from=nullptr) -> Entity*;


    // ~ draw
    auto draw_spirte(std::string, int, int, float, float) -> void;


    // - Variables -----------------------
    const float &deltaTime;

  private:
    // - Internal methods ----------------
    auto _initialize_entity(Entity*, std::string, float, float, std::string) -> void;


    // - Variables -----------------------
    Camera m_camera;

    graphics::Window *m_window;
    std::map< std::string, std::vector<Entity*> > m_entities;


  };
}
