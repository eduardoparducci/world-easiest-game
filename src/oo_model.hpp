// Desenvolvido por: Eduardo Parducci (170272)

#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>
#include <vector>

class Corpo {
private:
  // Atributos da massa
  float massa;
  float velocidade;
  float posicao;
  float aceleracao;
  
  // Atributos da mola
  float k;
  float atrito;
  float comprimento;

public:
  Corpo(float massa, float aceleracao, float velocidade, float posicao, float comprimento, float k, float atrito);
  void update(float nova_aceleracao, float nova_velocidade, float nova_posicao);
  float get_massa();
  float get_velocidade();
  float get_aceleracao();
  float get_posicao();
  float get_k();
  float get_comprimento();
  float get_atrito();
};

class ListaDeCorpos {
private:
  std::vector<Corpo*> *corpos;

public:
  ListaDeCorpos();
  void add_corpo(Corpo *c);
  void hard_copy(ListaDeCorpos *ldc);
  std::vector<Corpo*> *get_corpos();
};

class Fisica {
private:
  ListaDeCorpos *lista;
  
public:
  Fisica(ListaDeCorpos *ldc);
  void add_corpo(Corpo *c);
  void choque();
  void update(float deltaT);
};

class Tela {
  private:
    ListaDeCorpos *lista, *lista_anterior;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(ListaDeCorpos *ldc, float maxX, float maxY);
    // Destrutor
    ~Tela(); 
    void stop();
    void init();
    void update();
};

void threadfun (char *keybuffer, int *control);

class Teclado {
  private:
    char ultima_captura;
    int rodando;

    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};
#endif
