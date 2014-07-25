#ifndef MENU_HPP
#define MENU_HPP

#include "libtcod.hpp"

class Menu {
public:
  enum MenuItemCode {
    NONE,
    NEW_GAME,
    CONTINUE,
    EXIT
  };
  Menu();
  ~Menu();
  void clear();
  void addItem(MenuItemCode code, const char *label, int offset);
  MenuItemCode pick();
protected:
  TCODConsole *con;
  struct MenuItem {
    MenuItemCode code;
    const char *label;
    int offset;
  };
  TCODList<MenuItem *> items;
};
#endif
