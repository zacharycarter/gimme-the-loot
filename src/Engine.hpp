#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Gui.hpp"

class Engine {
public :
  enum GameStatus {
    STARTUP,
    IDLE,
    NEW_TURN,
    VICTORY,
    DEFEAT
  } gameStatus;
  TCOD_key_t lastKey;
  TCOD_mouse_t mouse;
  TCODList<Actor *> actors;
  Actor *player;
  Map *map;
  int fovRadius;
  int screenWidth;
  int screenHeight;
  Gui *gui;
 
  Engine(int screenWidth, int screenHeight);
  ~Engine();
  void update();
  void render();
  void sendToBack(Actor *actor);
  bool pickATile(int *x, int *y, float maxRange = 0.0f);
  Actor *getClosestMonster(int x, int y, float range) const;
  Actor *getActor(int x, int y) const;
  void init();
  void load();
  void save();
};
 
extern Engine engine;

#endif
