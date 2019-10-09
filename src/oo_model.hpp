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

class Obstacle {
private:
  // Position atributes
  float old_x;
  float old_y;
  float x;
  float y;
  float vx;
  float vy;
  
public:
  Obstacle(float x, float y, float vx, float vy);
  float get_x();
  float get_y();
  float get_old_x();
  float get_old_y();
  float get_vx();
  float get_vy();
  void update(float new_x, float new_y, float new_vx, float new_vy);
};

class ObstacleList {
private:
  std::vector<Obstacle *> *obstacles;

public:
  ObstacleList();
  void add_obstacle(Obstacle *o);
  bool hit(int x, int y);
  std::vector<Obstacle*> *get_obstacles();
};

class Map {
private:
  // Map Dimension
  int height;
  int width;
  int victory_line;
  bool playing;
  bool victory;
  bool defeat;

public:
  Map(int width, int height, int victory_line);
  int get_height();
  int get_width();
  int get_victory_line();
  bool is_valid(int x, int y);
  bool is_victory();
  bool is_defeat();
  bool is_playing();
  void terminate(bool is_victory);
};

class Physics {
private:
  Player *p1;
  Map *m1;
  ObstacleList *obs;

public:
  Physics(Player *p1, Map *m1, ObstacleList *obs);
  void walk(char direction);
  void update(float deltaT);
};

class Screen {
private:
  Map *m1;
  Player *p1;
  ObstacleList *obs;
  int maxI, maxJ;
  float maxX, maxY;
  
public:
  Screen(Map *m1, Player *p1, ObstacleList *obs, float maxX, float maxY, int maxI, int maxJ);
  ~Screen(); 
  void stop();
  void init();
  void update();
  void win();
  void lose();
  void begin();
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
