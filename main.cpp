#include <iostream>
#include <stdexcept>
#include "entity.h"
#include "app.h"
#include <cmath>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define clamp(a, l, r) (max((l), min((r), (a))))

using namespace std;
using namespace securus;
using namespace securus::gameplay;
using namespace securus::graphics;

class Player : public Entity {
public:
  Player() : yVel(m_yVel), Entity() {};

  const float &yVel;
private:
  void on_create() override {
    cam = get_camera();
  }

  void on_update() override {
    // Controlls
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
  
    int xAxis = keys[SDL_SCANCODE_D] - keys[SDL_SCANCODE_A];
    bool jumpKey = keys[SDL_SCANCODE_W];
    bool dropKey = keys[SDL_SCANCODE_S];

    float deltaTime = get_delta_time();

    // Walk
    m_xVel = lerp(m_xVel, xAxis * m_speed, 10 * deltaTime);

    // Jump
    if (jumpKey and m_grounded) { m_yVel = -m_jumpSpeed; }
    
    // Gravity
    if (not m_grounded)
      m_yVel += m_grav * deltaTime;

    // Clamp speed
    m_yVel = clamp(m_yVel, -m_maxYVel, m_maxYVel);
    
    float dx = m_xVel * deltaTime;
    float dy = m_yVel * deltaTime;

    // Collision
    Entity *platform = place_collision(x, y + dy, "Platform");
    if (platform and y+sprite->rect.h <= platform->y and dy > 0 and not dropKey) {
      y = platform->y - sprite->h;
      m_yVel = 4;
      m_grounded = true;
    }
    else {
      m_grounded = false;
      y += dy;
    }
   
    // Move
    x += dx;

    // Move camera
    if (cam->y < y - 64)
      cam->y = lerp(cam->y, y - 64, 20 * deltaTime);

    // Clamp x
    x = clamp(x, 16, 108);
  }

  float m_yVel = 0, m_xVel = 0;
  float m_maxYVel = 256;

  float m_speed = 64;
  float m_jumpHeight = 16;
  float m_grav = 500;
  
  float m_jumpSpeed = sqrt(2 * m_grav * m_jumpHeight);

  Camera *cam;
  
  bool m_grounded = false;
};

class Walls : public Entity {
private:
  void on_create() override {
    m_player = static_cast<Player*>( get_entity("Player", 0) );
  }

  void on_update() override {
    y = (int)m_player->y / 128 * 128;
  }

  void on_draw() override {
    draw_sprite("walls.png", 0, y - 128, 1, 1);
    draw_sprite("walls.png", 0, y, 1, 1);
    draw_sprite("walls.png", 0, y + 128, 1, 1);
  }

  Player *m_player;
};

class Platform : public Entity {
private:
  void on_create() override {
    cam = get_camera();
  }

  void on_update() override {
    if (y - cam->y < -16) { y += 144; }
  }

  Camera *cam;
};

int main (int argc, char *argv[]) {
  App *app = new App();

  float deltaTime = 0;
  
  // Open window
  Window *main_window = new Window("Cart&Karter", 128, 128, 512, 512);
  app->m_window = main_window;

  // Create scene
  app->m_scene = new Scene(main_window, deltaTime);
  auto scene = app->m_scene;

  // Load sprites
  main_window->load_sprite("walls.png");
  main_window->load_sprite("player.png");
  main_window->load_sprite("platform.png");

  // Instantiate entities 
  scene->instantiate_entity<Player>(64, 0, "player.png");
  scene->instantiate_entity<Walls>(0, 0, "walls.png");
  scene->instantiate_entity<Platform>(64, 0, "platform.png");
  scene->instantiate_entity<Platform>(16, 32, "platform.png");
  scene->instantiate_entity<Platform>(48, 64, "platform.png");
  scene->instantiate_entity<Platform>(32, 96, "platform.png");

  // Main cycle
  bool run = true;
  SDL_Event event;

  int currentTicks = SDL_GetTicks();
  int lastUpdateTicks = currentTicks;
  int nextUpdateTicks = currentTicks;
  int updateDelay = 16;

  while (run) {
    currentTicks = SDL_GetTicks();
    if (currentTicks < nextUpdateTicks)
      continue;

    nextUpdateTicks = currentTicks + (updateDelay - currentTicks % updateDelay);
    deltaTime = (currentTicks - lastUpdateTicks) * 0.001;
    if (deltaTime > 1) { deltaTime = 0; }
    lastUpdateTicks = currentTicks;

    // Poll events
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
          run = false;
    }
    
    // Update
    app->update();
  }

  delete app;
  return 0;
}
