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


Player::  Player(int x, int y) {
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

Map::Map(int x, int y) {
  this->x = x;
  this->y = y;
}

int Map::get_x() {
  return this->x;
}

int Map::get_y() {
  return this->y;
}

int Map::get_old_x() {
  return this->old_x;
}

int Map::get_old_y() {
  return this->old_y;
}


// ListaDePlayers::ListaDePlayers() {
//   this->corpos = new std::vector<Player *>(0);
// }

// void ListaDePlayers::add_corpo(Player *c) {
//   (this->corpos)->push_back(c);
//   std::cout << "Agora tenho: " << this->corpos->size() << " elementos" << std::endl;
// }

// std::vector<Player*> *ListaDePlayers::get_corpos() {
//   return (this->corpos);
// }

// void ListaDePlayers::hard_copy(ListaDePlayers *ldc) {
//   std::vector<Player *> *corpos = ldc->get_corpos();

//   for (int k=0; k<(int)corpos->size(); k++) {
//     Player *c = new Player( (*corpos)[k]->get_massa(),\
//                           (*corpos)[k]->get_aceleracao(),\
//                           (*corpos)[k]->get_velocidade(),\
//                           (*corpos)[k]->get_posicao(),\
//                           (*corpos)[k]->get_comprimento(),\
//                           (*corpos)[k]->get_k(),\
//                           (*corpos)[k]->get_atrito()
//                         );
//     this->add_corpo(c);
//   }

// }
  
Physics::Physics(Player *p1, Map *m1) {
  this->p1 = p1;
  this->m1 = m1;
}

void Physics::walk(char direction) {

  int old_x = this->p1->get_x();
  int old_y = this->p1->get_y();
  
  switch(direction) {
  case 's':
    this->p1->update(old_x, old_y+1);
    break;
  case 'w':
    this->p1->update(old_x, old_y-1);
    break;
  case 'd':
    this->p1->update(old_x+1, old_y);
    break;
  case 'a':
    this->p1->update(old_x-1, old_y);
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
}

void Screen::update() {

  // Erase Player from screen
  move(this->p1->get_old_y(), this->p1->get_old_x());
  echochar(' ');

  // Draw Player on the screen
  move(this->p1->get_y(), this->p1->get_x());
  echochar('p');

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
