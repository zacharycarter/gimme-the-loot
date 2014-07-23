#ifndef MAP_HPP
#define MAP_HPP

#include "libtcod.hpp"
#include "gmtl.pb.h"

struct Tile {
    bool explored; // been seen by player?
    Tile() : explored(false) {}
};
 
class Map {
public :
  int width,height;
 
  Map(int width, int height);
  ~Map();
  void init(bool withActors);
  bool isWall(int x, int y) const;
  bool isInFov(int x, int y) const;
  bool isExplored(int x, int y) const;
  bool canWalk(int x, int y) const;
  void computeFov();
  void render() const;
  void save(gmtl::Game_Map *gameMap);
  void load(const gmtl::Game_Map gameMap);
protected :
  Tile *tiles;
  TCODMap *map;
  long seed;
  TCODRandom *rng;
  friend class BspListener;
  void dig(int x1, int y1, int x2, int y2);
  void addItem(int x, int y);  
  void addMonster(int x, int y);
  void createRoom(bool first, int x1, int y1, int x2, int y2, bool withActors);
};

#endif
