#include "openglwindow.hpp"

#include <fmt/core.h>
#include <imgui.h>

void OpenGLWindow::initializeGL() {
  auto windowSettings{getWindowSettings()};
  fmt::print("Initial window size: {}x{}\n", windowSettings.width,
             windowSettings.height);
}

void OpenGLWindow::paintGL() {
  // Set the clear color
  glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2],
               m_clearColor[3]);
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
}

void mudaEstado(int i, char botoes[], char *turn, bool temGanhador, bool temEmpate, std::string *texto) {

   if(!temGanhador && !temEmpate){
    if (botoes[i] == ' ') {
      if (*turn == 'O'){
        botoes[i] = 'O';
        *turn = 'X';
        *texto = "X turn";
      }
      else{
        botoes[i] = 'X';
        *turn = 'O';
        *texto = "O turn";
      }
    }
  }
}

bool verificaSeIguais(char botoes[], int i, int j, int k){
  if(botoes[i] == botoes[j] && botoes[i] == botoes[k] && botoes[j] == botoes[k]) return true;
  return false;

}

bool verificaSePreenchido(char botoes[], int i, int j, int k){
  if(botoes[i] != ' ' && botoes[j] != ' ' && botoes[k] != ' ') return true;
  return false;
}

void houveGanhador(char botoes[], bool *temGanhador, std::string *texto, int i){

  if(!*temGanhador){
    if((verificaSeIguais(botoes, 0,3,6) && verificaSePreenchido(botoes, 0,3,6)) ||
      (verificaSeIguais(botoes, 1,4,7) && verificaSePreenchido(botoes, 1,4,7)) ||
      (verificaSeIguais(botoes, 2,5,8) && verificaSePreenchido(botoes, 2,5,8)) ||
      (verificaSeIguais(botoes, 0,1,2) && verificaSePreenchido(botoes, 0,1,2)) ||
      (verificaSeIguais(botoes, 3,4,5) && verificaSePreenchido(botoes, 3,4,5)) ||
      (verificaSeIguais(botoes, 6,7,8) && verificaSePreenchido(botoes, 6,7,8)) ||
      (verificaSeIguais(botoes, 0,4,8) && verificaSePreenchido(botoes, 0,4,8)) ||
      (verificaSeIguais(botoes, 2,4,6) && verificaSePreenchido(botoes, 2,4,6)))
      {
        *temGanhador = true;
        std::string s(1, botoes[i]);
        *texto = s + " is the winner!";
      }
      else *temGanhador = false;

  }
}

void houveEmpate(char botoes[], bool *temEmpate, bool *temGanhador, std::string *texto){

  bool aux = true;

  for(int i = 0; i < 9; i++){
    if(botoes[i] == ' ') aux = false;
  }

  if(aux && !(*temGanhador)) {
    *temEmpate = true;
    *texto = "Draw!";
  }
  else *temEmpate = false;
}

void OpenGLWindow::paintUI() {
  // Parent class will show fullscreen button and FPS meter
  // abcg::OpenGLWindow::paintUI();

  // Our own ImGui widgets go below
  {
    ImGui::SetNextWindowSize(ImVec2(580, 650));
    auto flags{ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize};
    ImGui::Begin("Tic-Tac-Toe", nullptr, flags);
    {
      bool restart{};                       // variavel que aciona o restart do jogo
      static bool temGanhador = false;      // indica se houve ganhador
      static bool temEmpate = false;        // indica se houve empate
      static char botoes[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // estado de cada botão
      static char turn = 'O';               // armazena que quem é a vez de jogar;
      static std::string texto = "O turn";  // label
      char *char_arr = &texto[0];
      

      // Menu Bar
      if (ImGui::BeginMenuBar()) {
        // Game menu
        if (ImGui::BeginMenu("Game")) {
          ImGui::MenuItem("Restart", nullptr, &restart);
          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }

      // Texto
      ImGui::Text(char_arr);

      ImGui::Columns(3, "mycolumns");
      for (int i = 0; i < 9; i++) {
        
        if (i % 3 == 0 && i != 0) {
          ImGui::Separator();
        }
        
        char aux = botoes[i];
        //ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        
        ImGui::Button(&aux, ImVec2(180, 150));
        if(ImGui::IsItemClicked()){
          mudaEstado(i, botoes, &turn, temGanhador, temEmpate, &texto);
          houveGanhador(botoes, &temGanhador, &texto, i);
          houveEmpate(botoes, &temEmpate, &temGanhador, &texto);
        }

        ImGui::NextColumn();
      }

      // Botão Restart Game
      ImGui::Columns(1);
      ImGui::NewLine();
      if (ImGui::Button("Restart Game", ImVec2(580, 50))) {
        restart = true;
      }
      ImGui::Spacing();

      // Resetar o jogo
      if (restart) {
        for (int i = 0; i < 9; i++) botoes[i] = ' ';
        temGanhador = false;
        temEmpate = false;
        texto = "O turn";
      }
    }
    // Window end
    ImGui::End();
  }
}