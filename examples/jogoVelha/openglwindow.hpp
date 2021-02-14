#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <array>

#include "abcg.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;

 private:
  std::array<float, 4> m_clearColor{0.906f, 0.910f, 0.918f, 1.0f};
};

void mudaEstado(int i, char botoes[], char *turn, bool temGanhador, bool temEmpate, std::string *texto);
bool verificaSeIguais(char botoes[], int i, int j, int k);
bool verificaSePreenchido(char botoes[], int i, int j, int k);
void houveGanhador(char botoes[], bool *temGanhador, std::string *texto, int i);
void houveEmpate(char botoes[], bool *temEmpate, bool *temGanhador, std::string *texto);


#endif