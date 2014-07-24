#include "libtcod.hpp"
#include "Engine.hpp"
 
Engine engine(80,50);
 
int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  engine.load();
  while ( !TCODConsole::isWindowClosed() ) {
    engine.update();
    engine.render();
    TCODConsole::flush();
  }
  engine.save();
  return 0;
}
