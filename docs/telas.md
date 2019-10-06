# Telas do Jogo
    Fluxo de telas do jogo. 
    Obs: Os quadros com texto devem estar posicionados no meio da tela. Olhar telas implementadas para ver como isso é feito.

## 1- Tela inicial
    Tela contendo o objetivo do jogo e as instruções de movimentação.

```
+---------------------------------+
|                                 |
|       WORLD EASIEST GAME!       |
|                                 |
| YOUR GOAL IS TO MOVE TO THE     |
| AREA DELIMITED WITH '*' WITHOUT |
| BYPASSING THE OBSTACLES '#'     |
|                                 |
| MOVE THE PLAYER 'P' USING THE   | 
| FOLLOWING KEYS:                 |
| 'W' - MOVE UP                   |
| 'S' - MOVE DOWN                 |
| 'A' - MOVE LEFT                 |
| 'D' - MOVE RIGHT                |
|                                 |
| GOOD LUCK, HAVE FUN!            |
|                                 |
| Press 's' key to start...       |
|                                 |
+---------------------------------+
```

## 2- Tela de jogo
    Tela contendo o mapa do jogo e a informação de vidas restantes.

```
  +-------+---------+--+
  |       #         *  |
  |  P    #         *  |
  |       #         *  |
  |                 *  |
  +-----------------+--+
   LIVES: 3
```

## 3- Tela de vitória (parcialmente implementado)
    Tela contendo a informação de fim de jogo vitorioso.

```
+---------------------------+
| CONGRATULATIONS, YOU WON! |
|                           |
| Press 'q' to quit...      |
+---------------------------+
```

## 3- Tela de derrota (com vidas restantes)
    Tela contendo a informação de vidas restantes.

```
+---------------------------+
| NOT THIS TIME, TRY AGAIN! |
|                           |
| LIVES REMAINING: 2        |
|                           |
| Press 's' to try again... |
+---------------------------+
```


## 4- Tela de derrota (sem vidas restantes)
    Tela contendo a informação de fim de jogo com derrota.

```
+----------------------+
|      GAME OVER       |
|                      |
| Press 'q' to quit... |
+----------------------+
```
