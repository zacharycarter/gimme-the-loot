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
  ~Menu();
  void clear();
  void addItem(MenuItemCode code, const char *label);
  MenuItemCode pick();
protected:
  struct MenuItem {
    MenuItemCode code;
    const char *label;
  };
  TCODList<MenuItem *> items;
};
#endif
