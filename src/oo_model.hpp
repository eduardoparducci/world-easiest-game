/* Desenvolvido por: Eduardo  (170272)
 *                   Henrique (174638)
 */

#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>
#include <vector>

class Player {
private:
  // Position atributes
  int x;
  int y;
  int old_x;
  int old_y;
public:
  Player(int x, int y);
  void update(int new_x, int new_y);
  int get_x();
  int get_y();
  int get_old_x();
  int get_old_y();

};

class Map {
private:
  // Position atributes
  int x;
  int y;
  int old_x;
  int old_y;
public:
  Map(int x, int y);
  int get_x();
  int get_y();
  int get_old_x();
  int get_old_y();

};

// class ListaDeCorpos {
// private:
//   std::vector<Corpo*> *corpos;

// public:
//   ListaDeCorpos();
//   void add_corpo(Corpo *c);
//   void hard_copy(ListaDeCorpos *ldc);
//   std::vector<Corpo*> *get_corpos();
// };

class Physics {
private:
  Player *p1;
  Map *m1;
  
public:
  Physics(Player *p1, Map *m1);
  // u=Up, d=Down, l=Left, r=Right
  void walk(char direction);
};

class Screen {
  private:
    Map *m1;
    Player *p1;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Screen(Map *m1, Player *p1, float maxX, float maxY, int maxI, int maxJ);
    ~Screen(); 
    void stop();
    void init();
    void update();
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
