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
}

void Player::update(int new_x, int new_y) {
  this->x = new_x;
  this->y = new_y;
}

int Player::get_x() {
  return this->x;
}

int Player::get_y() {
  return this->y;
}

ListaDePlayers::ListaDePlayers() {
  this->corpos = new std::vector<Player *>(0);
}

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

void Physics::update(float deltaT) {

  std::vector<Player *> *c = this->lista->get_corpos();

  for (int i = 0; i < (int)(*c).size(); i++) {
    
    float v_ant = (*c)[i]->get_velocidade();
    float x_ant = (*c)[i]->get_posicao();
    float a_ant = (*c)[i]->get_aceleracao();
    float m = (*c)[i]->get_massa();
    float k = (*c)[i]->get_k();
    float b = (*c)[i]->get_atrito();

    float new_accel = (-1)*((k*x_ant/m) + (b*v_ant/m));
    float new_vel   = v_ant + (float)deltaT * new_accel/1000;
    float new_pos   = x_ant + (float)deltaT * new_vel/1000;

    (*c)[i]->update(new_accel, new_vel, new_pos);
   }
}

void Physics::choque() {
  // Atualiza parametros dos corpos!
  std::vector<Player *> *c = this->lista->get_corpos();
  for (int i = 0; i < (int)(*c).size(); i++) {
    (*c)[i]->update((*c)[i]->get_aceleracao(), (*c)[i]->get_velocidade()+(float)15, (*c)[i]->get_posicao());
  }
}

Tela::Tela(ListaDePlayers *ldc, float maxX, float maxY) {
  this->lista = ldc;
  this->lista_anterior = new ListaDePlayers();
  this->lista_anterior->hard_copy(this->lista);
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;
}

void Tela::init() {
  initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
  curs_set(0);           /* Do not display cursor */
  getmaxyx(stdscr, this->maxI, this->maxJ);
}

void Tela::update() {


  std::vector<Player *> *corpos_old = this->lista_anterior->get_corpos();
  int i;
  
  // Apaga corpos na tela
  for (int k=0; k<(int)corpos_old->size(); k++)
  {
    i = ((*corpos_old)[k]->get_comprimento() + (*corpos_old)[k]->get_posicao());

    move(k, 0);   /* Move cursor to the begining of the line */
    if(i < this->maxJ) {
      echochar('\n');
    }
  }

  // Desenha corpos na tela
  std::vector<Player *> *corpos = this->lista->get_corpos();

  for (int k=0; k<(int)corpos->size(); k++)
  {
    i = ((*corpos_old)[k]->get_comprimento() + (*corpos_old)[k]->get_posicao());

    move(k, 0);   /* Move cursor to the begining of the line */

    if(i < this->maxJ) {
      for(int j=0 ; j<i ; j++) {
        echochar('-');  /* Prints character, advances a position */
      }
      if(++i < this->maxJ)
        echochar('|');
      if(++i < this->maxJ)
        echochar('X');
      if(++i < this->maxJ)
        echochar('|');
    }

    // Atualiza corpos antigos
    (*corpos_old)[k]->update(  (*corpos)[k]->get_aceleracao(),\
                               (*corpos)[k]->get_velocidade(),\
                               (*corpos)[k]->get_posicao());
  }

  // Atualiza tela
  refresh();
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
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

Teclado::Teclado() {
}

Teclado::~Teclado() {
}

void Teclado::init() {
  // Inicializa ncurses
  raw();				         /* Line buffering disabled	*/
	keypad(stdscr, TRUE);	 /* We get F1, F2 etc..		*/
	noecho();			         /* Don't echo() while we do getch */
  curs_set(0);           /* Do not display cursor */

  this->rodando = 1;
  std::thread newthread(threadfun, &(this->ultima_captura), &(this->rodando));
  (this->kb_thread).swap(newthread);
}

void Teclado::stop() {
  this->rodando = 0;
  (this->kb_thread).join();
}

char Teclado::getchar() {
  char c = this->ultima_captura;
  this->ultima_captura = 0;
  return c;
}
