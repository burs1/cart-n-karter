#include "entity.h"

#include <iostream>
#include <string>

using namespace std;

namespace securus::gameplay {
  Entity::Entity() 
    : sprite(m_sprite) {}

  // - Methods -------------------------
  auto Entity::get_delta_time() -> float {
    return m_scene->deltaTime;
  }


  // ~ camera
  auto Entity::get_camera() -> Camera* {
    return m_scene->get_camera();
  }


  // ~ entities
  auto Entity::get_entity(string type, int n) -> Entity* {
    return m_scene->get_entity(type, n);
  }


  // ~ collision
  auto Entity::place_collision(float x, float y, string type) -> Entity* {
    return m_scene->check_collision(x, y, x + m_sprite->rect.w * xscale, y + m_sprite->rect.h * yscale, type, this);
  }

  auto  Entity::point_collision(float x, float y, string type) -> Entity* {
    return m_scene->check_collision(x, y, x, y, type, this);
  }


  // ~ draw
  auto Entity::draw_sprite(string sprite, int x, int y, float xscale, float yscale) -> void {
    m_scene->draw_spirte(sprite, x, y, xscale, yscale);
  }


  auto Entity::draw_self() -> void {
    if (m_sprite)
      m_scene->draw_spirte(m_spriteName, x, y, xscale, yscale);
  }
}
