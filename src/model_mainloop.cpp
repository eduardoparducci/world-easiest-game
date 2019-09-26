/* Desenvolvido por: Eduardo  (170272)
 *                   Henrique (174638)
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "oo_model.hpp"

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{
  Player *p0 = new Player(1,1);
  Map *m0 = new Map(1,1);
  Physics *f = new Physics(p0, m0);

  Screen *screen = new Screen(m0, p0, 50, 50, 50, 50);
  screen->init();

  Keyboard *keyboard = new Keyboard();
  keyboard->init();

  while (1) {

    // Lê o teclado
    char c = keyboard->getchar();
    f->walk(c);

    screen->update();

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
  }
  keyboard->stop();
  screen->stop();
  return 0;
}
