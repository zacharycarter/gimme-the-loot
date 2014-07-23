#ifndef GUI_H
#define GUI_H

#include "libtcod.hpp"
#include "gmtl.pb.h"

class Gui {
public:
  Gui();
  ~Gui();
  void render();
  void logEntry(const TCODColor &col, const char *text, ...);
  void save(gmtl::Game_Logs *gameLogs);
  void load(const gmtl::Game_Logs gameLogs);
protected:
  TCODConsole *con;
  struct LogEntry {
    char *text;
    TCODColor col;
    LogEntry(const char *text, const TCODColor &col);
    ~LogEntry();
  };
  TCODList<LogEntry *> log;
  void renderBar(int x, int y, int width, const char *name,
		 float value, float maxValue, const TCODColor &barColor,
		 const TCODColor &backColor);
  void renderMouseLook();
};
#endif
