#include "scene.h"

using namespace std;

namespace securus::gameplay {
  using namespace graphics;

  Scene::Scene(Window *p_window, const float& p_deltaTime)
    : m_window(p_window), deltaTime(p_deltaTime) {}


  Scene::~Scene() {
    for(auto entity : m_entities["any"]) { delete entity; }
    m_entities.clear();
  }


  // - Methods -------------------------
  auto Scene::update() -> void {
    // Update all entities states
    for (auto entity : m_entities["any"]) { entity->on_update(); }

    // Draw all entities
    for (auto entity : m_entities["any"]) { entity->on_draw(); }
  }


  // ~ camera
  auto Scene::get_camera() -> Camera* {
    return &m_camera;
  }

  
  // ~ entities
  auto Scene::get_entity(string type, int n) -> Entity* {
    // Check if any entities of this type exist
    if (not m_entities.contains(type))
      throw runtime_error("Entities of type \"" + string(type) + "\" weren't instantiated");

    // Check if index is valid
    if (m_entities[type].size() <= n or n < 0)
      throw runtime_error("Wrong index");

    return m_entities[type][n];
  }


  // ~ collisions
  auto Scene::check_collision(float x1, float y1, float x2, float y2, string type, Entity *from) -> Entity* {
    for (auto entity : m_entities[type]) {
      if (entity == from) { continue; }
      // Check collision by AABB
      if (
          x1 <= entity->x + entity->m_sprite->rect.w  and
          x2 >= entity->x                             and
          y1 <= entity->y + entity->m_sprite->rect.y  and
          y2 >= entity->y
        ) 
        return entity;
    }
    return nullptr;
  }

    
  // ~ draw
  auto Scene::draw_spirte(string spriteName, int x, int y, float xscale, float yscale) -> void {
    m_window->draw_sprite(spriteName, x - m_camera.x, y - m_camera.y, xscale, yscale);
  }

  
  // - Internal methods ----------------
  auto Scene::_initialize_entity(Entity *entity, string spriteName, float x, float y, string type) -> void {
    entity->m_scene = this;
    entity->m_type = type.substr(2);
    entity->m_sprite = m_window->get_sprite(spriteName);
    entity->m_spriteName = spriteName;
    entity->x = x;
    entity->y = y;
    m_entities["any"].push_back(entity);
    m_entities[entity->m_type].push_back(entity);
    entity->on_create();
  }
}
