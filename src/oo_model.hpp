/* Desenvolvido por: Eduardo  (170272)
 *                   Henrique (174638)
 */

#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>
#include <vector>

class Player {
public:
  // Position atributes
  static int x;
  static int y;
  Player(int x, int y);
  static int get_x();
  static int get_y();
  void update(int new_x, int new_y);
};

class Screen {
private:
  Player *p1;
  
public:
  Screen(Player *p1);
  ~Screen();
  void init(int argc, char** argv);
};

void threadfun (char *keybuffer, int *control);

class Keyboard {
private:
  char last_char;
  int running;

  std::thread kb_thread;

public:
  Keyboard();
  ~Keyboard();
  void stop();
  void init();
  char getchar();
};
#endif
