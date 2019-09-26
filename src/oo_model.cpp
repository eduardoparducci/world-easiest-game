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


Corpo::  Corpo(float massa, float aceleracao, float velocidade, float posicao, float comprimento, float k, float atrito) {
  this->massa = massa;
  this->velocidade = velocidade;
  this->aceleracao = aceleracao;
  this->posicao = posicao;
  this->comprimento = comprimento;
  this->k = k;
  this->atrito = atrito;
}

void Corpo::update(float nova_aceleracao, float nova_velocidade, float nova_posicao) {
  this->aceleracao = nova_aceleracao;
  this->velocidade = nova_velocidade;
  this->posicao = nova_posicao;
}

float Corpo::get_massa() {
  return this->massa;
}

float Corpo::get_velocidade() {
  return this->velocidade;
}

float Corpo::get_aceleracao() {
  return this->aceleracao;
}

float Corpo::get_posicao() {
  return this->posicao;
}

float Corpo::get_k() {
  return this->k;
}

float Corpo::get_comprimento() {
  return this->comprimento;
}

float Corpo::get_atrito() {
  return this->atrito;
}

ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
  std::cout << "Agora tenho: " << this->corpos->size() << " elementos" << std::endl;
}

std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}

void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<(int)corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_massa(),\
                          (*corpos)[k]->get_aceleracao(),\
                          (*corpos)[k]->get_velocidade(),\
                          (*corpos)[k]->get_posicao(),\
                          (*corpos)[k]->get_comprimento(),\
                          (*corpos)[k]->get_k(),\
                          (*corpos)[k]->get_atrito()
                        );
    this->add_corpo(c);
  }

}

Fisica::Fisica(ListaDeCorpos *ldc) {
  this->lista = ldc;
}

void Fisica::update(float deltaT) {

  std::vector<Corpo *> *c = this->lista->get_corpos();

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

void Fisica::choque() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (int)(*c).size(); i++) {
    (*c)[i]->update((*c)[i]->get_aceleracao(), (*c)[i]->get_velocidade()+(float)15, (*c)[i]->get_posicao());
  }
}

Tela::Tela(ListaDeCorpos *ldc, float maxX, float maxY) {
  this->lista = ldc;
  this->lista_anterior = new ListaDeCorpos();
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


  std::vector<Corpo *> *corpos_old = this->lista_anterior->get_corpos();
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
  std::vector<Corpo *> *corpos = this->lista->get_corpos();

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
