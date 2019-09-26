# Planejamento Jogo 1

## Fase I: Jogador estático (25/09/2019)

### Descrição
Um jogador em uma área delimitada que termina quando o jogador atinge a posição final.

### Classe Mapa

1. Dimensão
   * int altura
   * int largura
      
2. Área objetivo
   * int altura
   * int largura
   * int pos_x
   * int pos_y

3. Posição de início
   * int pos_x
   * int pos_y

### Classe Jogador

1. Posição
   * int pos_x
   * int pos_y

### Classe Tela
  (Editar métodos)

### Classe Física
  (Editar métodos)
  
### Classe Teclado
  (Já implementado)

## Fase II: Jogador com obstáculo estático

  ### Descrição
  Um jogador em uma área delimitada que termina quando o jogador atinge a posição final, sem
  encostar em um obstáculo (estático).

  6. Classe Obstáculo

## Fase III: Obstáculo dinâmico

  ### Descrição
  Adicionar movimento ao obstáculo

  7. Dinâmica Obstáculo

## Apêndice

O visual do jogo é definido da seguinte forma:

```
  +-------+---------+--+
  |       x         .  |
  |  █    x         .  |
  |       x         .  |
  |                 .  |
  +-----------------+--+
```

` | - + ` = Limites do mapa

` x `     = Obstáculo

` . `     = Limite da área objetivo

' █ '     = Jogador (ASCII=219)


### Som
    Libaudiofile
