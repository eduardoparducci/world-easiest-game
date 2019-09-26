// Desenvolvido por: Eduardo Parducci (170272)

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
  // Corpo(float massa, float aceleracao, float velocidade, float posicao, float comprimento, float k, float atrito);
  Corpo *c0 = new Corpo(10, 0, 0, 3, 15, 80, 0.6);

  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(c0);

  Fisica *f = new Fisica(l);

  Tela *tela = new Tela(l, 50, 50);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();


  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  int i = 0;

  T = get_now_ms();

  t1 = T;
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    // Atualiza modelo
    f->update(deltaT);

    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    if (c=='w') {
      f->choque();
    }
    if (c=='q') {
      break;
    }
    
    // Condicao de parada (10s)
    if ( (t1-T) > 100000 ) break;

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  teclado->stop();
  tela->stop();
  return 0;
}
