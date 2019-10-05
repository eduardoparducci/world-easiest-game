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
  Map *m0 = new Map(21,25,22);

  Obstacle *o0 = new Obstacle(1,10, -10, 0);
  Obstacle *o1 = new Obstacle(20,11, 10, 0);
  Obstacle *o2 = new Obstacle(1,12, -15, 0);
  Obstacle *o3 = new Obstacle(20,13, 15, 0);
  Obstacle *o4 = new Obstacle(1,14, -20, 0);
  Obstacle *o5 = new Obstacle(20,15, 20, 0);

  ObstacleList *obs = new ObstacleList();

  obs->add_obstacle(o0);
  obs->add_obstacle(o1);
  obs->add_obstacle(o2);
  obs->add_obstacle(o3);
  obs->add_obstacle(o4);
  obs->add_obstacle(o5);


  Physics *f = new Physics(p0, m0, obs);

  Screen *screen = new Screen(m0, p0, obs, 50, 50, 50, 50);
  Keyboard *keyboard = new Keyboard();

  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  screen->init();
  keyboard->init();


  T = get_now_ms();
  while (1) {

    // Update timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;


    // Read keyboard
    char c = keyboard->getchar();
    f->walk(c);
    
    // key 'q' stops the program
    if(c=='q') break;

    f->update(deltaT);
    screen->update();

    std::this_thread::sleep_for (std::chrono::milliseconds(50));
  }
  keyboard->stop();
  screen->stop();
  return 0;
}
