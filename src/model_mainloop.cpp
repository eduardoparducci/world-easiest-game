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
  Map *m0 = new Map(8,15,12);

  Obstacle *o0 = new Obstacle(2,5);
  Obstacle *o1 = new Obstacle(3,3);
  ObstacleList *obs = new ObstacleList();

  obs->add_obstacle(o0);
  obs->add_obstacle(o1);

  Physics *f = new Physics(p0, m0, obs);

  Screen *screen = new Screen(m0, p0, obs, 50, 50, 50, 50);
  Keyboard *keyboard = new Keyboard();




  screen->init();
  keyboard->init();

  while (1) {

    // Read keyboard
    char c = keyboard->getchar();
    f->walk(c);
    
    // key 'q' stops the program
    if(c=='q') break;
    screen->update();

    std::this_thread::sleep_for (std::chrono::milliseconds(50));
  }
  keyboard->stop();
  screen->stop();
  return 0;
}
