/******************************************
 * 
 * 
 ******************************************/

#include <omp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const int infinito = numeric_limits<int>::max();

void Expansao() {
  queue<int> fila;
  
}

int main(int argc, char **argv)
{
  string line;
  ifstream entrada (argv[1]);
  //ofstream saida (argv[2]);
  int n_linhas, n_colunas;
  int i_origem, j_origem, i_destino, j_destino;
  int n_obstaculos;
  int i_inicio, j_inicio;
  int i, j;

  if (entrada.is_open())
  {
    entrada >> n_linhas >> n_colunas;
    int grid[n_linhas][n_colunas];
    entrada >> i_origem >> j_origem;
    entrada >> i_destino >> j_destino;
    entrada >> n_obstaculos;

    // Inicializando o grid
    for (int k = 0; k < n_linhas; ++k)
      for (int l = 0; l < n_colunas; ++l)
        grid[k][l] = infinito; 

    // Marcando os obstaculos
    for (int aux = 0; aux < n_obstaculos; ++aux)
    {
      entrada >> i_inicio >> j_inicio >> i >> j;
      for (int k = i_inicio, count1 = 0; count1 < i; ++k, ++count1)
        for (int l = j_inicio, count2 = 0; count2 < j; ++l, ++count2)
          grid[k][l] = -1;
    }

    entrada.close();
  }
  else
  {
    std::cout << "Arquivo não encontrado!\n";
  }

  cout << n_linhas << endl;

  //saida.close();  
  return 0;
}

/* Impressão do grid
    for (int k = 0; k < n_linhas; ++k)
    {
      for (int l = 0; l < n_colunas; ++l)
        cout << grid[k][l] << " ";
      cout << "\n";
    }
*/