/* Desenvolvido por: Eduardo  (170272)
 *                   Henrique (174638)
 */

#include <vector>
#include "oo_model.hpp"
#include <iostream>
#include <cmath>
#include <ncurses.h>
#include <chrono>
#include <thread>

Player::Player(int x, int y) {
  this->x = x;
  this->y = y;
  this->old_x = x;
  this->old_y = y;
}

void Player::update(int new_x, int new_y) {
  this->old_x = this->x;
  this->old_y = this->y;
  this->x = new_x;
  this->y = new_y;
}

int Player::get_x() {
  return this->x;
}

int Player::get_y() {
  return this->y;
}

int Player::get_old_x() {
  return this->old_x;
}

int Player::get_old_y() {
  return this->old_y;
}

Obstacle::Obstacle(int x, int y) {
  this->x = x;
  this->y = y;
}

int Obstacle::get_x() {
  return this->x;
}

int Obstacle::get_y() {
  return this->y;
}

ObstacleList::ObstacleList() {
  this->obstacles = new std::vector<Obstacle *>(0);
}

void ObstacleList::add_obstacle(Obstacle *o) {
  (this->obstacles)->push_back(o);
}

bool ObstacleList::hit(int x, int y) {
  std::vector<Obstacle *> *o = this->obstacles;
  for (int i = 0 ; i < (int)(*o).size() ; i++)
    if( x == (*o)[i]->get_x() && y == (*o)[i]->get_y())
      return true;
  return false;
}

std::vector<Obstacle*> *ObstacleList::get_obstacles(){
  return this->obstacles;
}

Map::Map(int width, int height, int victory_line) {
  this->width = width;
  this->height = height;
  this->victory_line = victory_line;
  this->playing = true;
  this->victory = false;
  this->defeat = false;
}

int Map::get_width() {
  return this->width;
}

int Map::get_height() {
  return this->height;
}
int Map::get_victory_line() {
  return this->victory_line;
}
  
bool Map::is_valid(int x, int y) {
  // Checck boundaries of the map
  if(x>=this->width  || x<=0) return false;
  if(y>=this->height || y<=0) return false;
  return true;
}

bool Map::is_victory() {
  return this->victory;
}

bool Map::is_defeat() {
  return this->defeat;
}

bool Map::is_playing() {
  return this->playing;
}

void Map::terminate(bool is_victory) {
  this->playing = false;
  if(is_victory) this->victory = true;
  else this->defeat = true;
}


Physics::Physics(Player *p1, Map *m1, ObstacleList *obs) {
  this->p1 = p1;
  this->m1 = m1;
  this->obs = obs;
}

void Physics::walk(char direction) {
  int x = this->p1->get_x();
  int y = this->p1->get_y();
  if(m1->is_playing()) {
    switch(direction) {
    case 's':
      if(m1->is_valid(x, y+1)) this->p1->update(x, ++y);
      break;
    case 'w':
      if(m1->is_valid(x, y-1)) this->p1->update(x, --y);
      break;
    case 'd':
      if(m1->is_valid(x+1, y)) this->p1->update(++x, y);
      break;
    case 'a':
      if(m1->is_valid(x-1, y)) this->p1->update(--x, y);
      break;
    }
  }

  // Verify victory
  if(y > this->m1->get_victory_line())
    this->m1->terminate(true);

  // Verify defeat
  if(this->obs->hit(x,y))
    this->m1->terminate(false);


}

Screen::Screen(Map *m1, Player *p1, ObstacleList *obs, float maxX, float maxY, int maxI, int maxJ) {
  this->m1 = m1;
  this->p1 = p1;
  this->obs = obs;
  this->maxX = maxX;
  this->maxY = maxY;
  this->maxJ = maxJ;
  this->maxI = maxI;
}

void Screen::init() {
  initscr();			 /* Start curses mode 		*/
  raw();				 /* Line buffering disabled	*/
  curs_set(0);           /* Do not display cursor   */
  getmaxyx(stdscr, this->maxI, this->maxJ);

  int i;
  std::vector<Obstacle *> *o = this->obs->get_obstacles();

  // Draw Map on the screen  
  // Corners
  move(0,0);
  echochar('+');
  move(m1->get_height(), 0);
  echochar('+');
  move(m1->get_height(), m1->get_width());
  echochar('+');
  move(0,m1->get_width());
  echochar('+');
  
  // Vertical Border
  for(i=1;i<m1->get_height();i++) {
    move(i,0);
    echochar('|');
    move(i,m1->get_width());
    echochar('|');

  }

  // Horizontal Border
  for(i=1;i<m1->get_width();i++) {
    move(0,i);
    echochar('-');
    move(m1->get_height(),i);
    echochar('-');
  }
	
  // Victory Area
  for(i=1;i<m1->get_width();i++) {
    move(this->m1->get_victory_line(),i);
    echochar('*');
  }
	
  // Victory Area
  for(i=0;i<(int)(*o).size();i++) {
    move((*o)[i]->get_y(),(*o)[i]->get_x());
    echochar('#');
  }
  
  refresh();
}

void Screen::update() {

  if(this->m1->is_playing()) {
    // Erase Player from screen
    char c;
    move(this->p1->get_old_y(), this->p1->get_old_x());
    if(this->p1->get_old_y()==this->m1->get_victory_line())
      echochar('*');
    else 
      echochar(' ');

    // Draw Player on the screen
    move(this->p1->get_y(), this->p1->get_x());
    echochar('P');

    // Atualiza tela
    refresh();
  } else {
    if(this->m1->is_victory()) this->win();
    if(this->m1->is_defeat()) this->lose();
  }
}

void Screen::win() {

  int i;
  // Erase Screen
  for(i=0 ; i<this->maxI ; i++) {
    move(i, 0);
    if(i==this->maxI/2-1) {
      // Write victory message in the middle height
      move(i, this->maxJ/2-15);
      printw("+---------------------------+");
      move(++i, this->maxJ/2-15);
      printw("| CONGRATULATIONS, YOU WON! |");
      move(++i, this->maxJ/2-15);
      printw("+---------------------------+");
      move(++i, this->maxJ/2-15);
      printw("press \'q\' to quit");
    } else
      echochar('\n');
  }
  // Atualiza tela
  refresh();
}

void Screen::lose() {

  int i;
  // Erase Screen
  for(i=0 ; i<this->maxI ; i++) {
    move(i, 0);
    if(i==this->maxI/2-1) {
      // Write victory message in the middle height
      move(i, this->maxJ/2-15);
      printw("+---------------------------+");
      move(++i, this->maxJ/2-15);
      printw("| NOT THIS TIME, TRY AGAIN! |");
      move(++i, this->maxJ/2-15);
      printw("+---------------------------+");
      move(++i, this->maxJ/2-15);
      printw("press \'q\' to quit");
    } else
      echochar('\n');
  }
  // Atualiza tela
  refresh();
}

void Screen::stop() {
  endwin();
}

Screen::~Screen() {
  this->stop();;
}

void threadfun (char *keybuffer, int *control)
{
  char c;
  while ((*control) == 1) {
    c = getch();
    if (c!=ERR) (*keybuffer) = c;
    else (*keybuffer) = 0;
    std::this_thread::sleep_for (std::chrono::milliseconds(10));
  }
  return;
}

Keyboard::Keyboard() {
}

Keyboard::~Keyboard() {
}

void Keyboard::init() {
  // Inicializa ncurses
  raw();				 /* Line buffering disabled	*/
  keypad(stdscr, TRUE);	 /* We get F1, F2 etc..		*/
  noecho();			     /* Don't echo() while we do getch */
  curs_set(0);           /* Do not display cursor */

  this->running = 1;
  std::thread newthread(threadfun, &(this->last_char), &(this->running));
  (this->kb_thread).swap(newthread);
}

void Keyboard::stop() {
  this->running = 0;
  (this->kb_thread).join();
}

char Keyboard::getchar() {
  char c = this->last_char;
  this->last_char = 0;
  return c;
}
