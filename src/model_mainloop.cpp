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

int main(int argc, char** argv) {
  
  Player *p0 = new Player(1,1);
  Screen *screen = new Screen(p0);
  Keyboard *keyboard = new Keyboard();

  // uint64_t t0;
  // uint64_t t1=0;
  // uint64_t deltaT;
  uint64_t T;

  screen->init(argc, argv);
  keyboard->init();

  T = get_now_ms();
  while (1) {

    // Read keyboard
    char c = keyboard->getchar();
    
    // key 'q' stops the program
    if(c=='q') break;

    std::this_thread::sleep_for (std::chrono::milliseconds(50));
  }
  keyboard->stop();
  return 0;
}
