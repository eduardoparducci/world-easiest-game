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
  Map *m0 = new Map(15,12,10);


  // Static Obstacles
  Obstacle *o0 = new Obstacle(1, 2, 0, 0);
  Obstacle *o1 = new Obstacle(2, 2, 0, 0);
  Obstacle *o2 = new Obstacle(3, 2, 0, 0);
  Obstacle *o3 = new Obstacle(4, 2, 0, 0);
  Obstacle *o4 = new Obstacle(5, 2, 0, 0);
  Obstacle *o5 = new Obstacle(6, 2, 0, 0);
  Obstacle *o6 = new Obstacle(7, 2, 0, 0);
  Obstacle *o7 = new Obstacle(8, 2, 0, 0);
  Obstacle *o8 = new Obstacle(9, 2, 0, 0);
  Obstacle *o9 = new Obstacle(10, 2, 0, 0);
  Obstacle *o10 = new Obstacle(11, 2, 0, 0);
  Obstacle *o11 = new Obstacle(12, 2, 0, 0);
  Obstacle *o12 = new Obstacle(13, 2, 0, 0);
  Obstacle *o13 = new Obstacle(10, 3, 0, 0);
  Obstacle *o14 = new Obstacle(10, 4, 0, 0);
  Obstacle *o15 = new Obstacle(10, 5, 0, 0);
  Obstacle *o16 = new Obstacle(9, 6, 0, 0);
  Obstacle *o17 = new Obstacle(8, 7, 0, 0);
  Obstacle *o18 = new Obstacle(7, 8, 0, 0);

  // Dynamic Obstacles
  Obstacle *d0 = new Obstacle(1, 3, 10, 0);
  Obstacle *d1 = new Obstacle(1, 5, 10, 0);
  Obstacle *d2 = new Obstacle(1, 7, 10, 0);
  Obstacle *d3 = new Obstacle(14, 9, 0, 10);

  ObstacleList *obs = new ObstacleList();


  obs->add_obstacle(o0);
  obs->add_obstacle(o1);
  obs->add_obstacle(o2);
  obs->add_obstacle(o3);
  obs->add_obstacle(o4);
  obs->add_obstacle(o5);
  obs->add_obstacle(o6);
  obs->add_obstacle(o7);
  obs->add_obstacle(o8);
  obs->add_obstacle(o9);
  obs->add_obstacle(o10);
  obs->add_obstacle(o11);
  obs->add_obstacle(o12);
  obs->add_obstacle(o13);
  obs->add_obstacle(o14);
  obs->add_obstacle(o15);
  obs->add_obstacle(o16);
  obs->add_obstacle(o17);
  obs->add_obstacle(o18);

  obs->add_obstacle(d0);
  obs->add_obstacle(d1);
  obs->add_obstacle(d2);
  obs->add_obstacle(d3);

  Physics *f = new Physics(p0, m0, obs);

  Screen *screen = new Screen(m0, p0, obs, 50, 50, 50, 50);
  Keyboard *keyboard = new Keyboard();

  uint64_t t0;
  uint64_t t1=0;
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
