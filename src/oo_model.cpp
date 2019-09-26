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

Map::Map(int width, int height) {
  this->width = width;
  this->height = height;
}

int Map::get_width() {
  return this->width;
}

int Map::get_height() {
  return this->height;
}
  
bool Map::is_valid(int x, int y) {
  if(x>=this->width  || x<=0) return false;
  if(y>=this->height || y<=0) return false;
  return true;
}

Physics::Physics(Player *p1, Map *m1) {
  this->p1 = p1;
  this->m1 = m1;
}

void Physics::walk(char direction) {

  int old_x = this->p1->get_x();
  int old_y = this->p1->get_y();
  
  switch(direction) {
  case 's':
    if(m1->is_valid(old_x, old_y+1)) this->p1->update(old_x, old_y+1);
    break;
  case 'w':
    if(m1->is_valid(old_x, old_y-1)) this->p1->update(old_x, old_y-1);
    break;
  case 'd':
    if(m1->is_valid(old_x+1, old_y)) this->p1->update(old_x+1, old_y);
    break;
  case 'a':
    if(m1->is_valid(old_x-1, old_y)) this->p1->update(old_x-1, old_y);
    break;
  }
}

Screen::Screen(Map *m1, Player *p1, float maxX, float maxY, int maxI, int maxJ) {
  this->m1 = m1;
  this->p1 = p1;
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

  // Draw Map on the screen
  int i;
  
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

  refresh();
}

void Screen::update() {

  // Erase Player from screen
  move(this->p1->get_old_y(), this->p1->get_old_x());
  echochar(' ');

  // Draw Player on the screen
  move(this->p1->get_y(), this->p1->get_x());
  echochar('P');

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
