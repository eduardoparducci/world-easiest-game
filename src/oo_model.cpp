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

// GTK includes
#include <GLFW/glfw3.h>
#include <GL/glut.h>

Player::Player(int x, int y) {
  Player::x = x;
  Player::y = y;
}

void Player::update(int new_x, int new_y) {
  Player::x = new_x;
  Player::y = new_y;
}

 int Player::get_x() {
  return Player::x;
}

int Player::get_y() {
  return Player::y;
}

void UpdateScreenFrame() {
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw grid on the screen
  glColor3f(0.8f,0.8f,0.8f);
  glLineWidth(1.0f);
  glBegin(GL_LINES);
  float x = -10;
  for(;x<=10; x++)
    {
      glVertex2f(-10,x);
      glVertex2f( 10,x);
      glVertex2f(x,-10);
      glVertex2f(x, 10);
    }
  glEnd();
  glColor3f(0.0f,0.0f,0.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  glVertex2f(-10,0);
  glVertex2f( 10,0);
  glVertex2f(0,-10);
  glVertex2f(0, 10);
  glEnd();
    
  // Cofigure dots appearence
  glColor3f(0.0f, 0.0f, 1.0f); // Define color of dot
  glPointSize(30.0f); // Size
  
  // Draw dots on the screen  
  glBegin(GL_POINTS);
  glVertex2f(Player::get_x(),Player::get_y());
  glEnd();

  // Update frame
  glutSwapBuffers();
}

Screen::Screen(Player *p1) {
  this->p1 = p1;
}

void Screen::init(int argc, char** argv) {
  // Configs of GTK 
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(320,240); //Size
  glutInitWindowPosition(100,100); // Position
  glutCreateWindow("World Easiest Game - GTK"); //Title
  glutDisplayFunc(UpdateScreenFrame); //Frame Handler
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Background color
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-10,10,-10,10);
  glMatrixMode(GL_MODELVIEW);
  glutMainLoop();
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
  raw();				         /* Line buffering disabled	*/
  keypad(stdscr, TRUE);	 /* We get F1, F2 etc..		*/
  noecho();			         /* Don't echo() while we do getch */
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
