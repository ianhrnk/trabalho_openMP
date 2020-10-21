/******************************************
 * 
 * 
 ******************************************/

#include <omp.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;

const int infinito = numeric_limits<int>::max();

struct celula { int i; int j; };

void ImprimeMatriz(vector<vector<int>> grid, int n_linhas, int n_colunas)
{
  for (int k = 0; k < n_linhas; ++k)
  {
    for (int l = 0; l < n_colunas; ++l)
      cout << grid[k][l] << " ";
    cout << "\n";
  }
}

void InsereCelula(queue<celula> &fila, int i, int j)
{
  celula cel = {.i = i, .j = j};
  fila.push(cel);
}

void Expansao(vector<vector<int>> &grid, int n_linhas, int n_colunas, 
              celula origem, celula destino)
{
  queue<celula> fila;
  celula cel = origem;
  grid[origem.i][origem.j] = 0;
  bool achou = false;

  fila.push(cel);
  while (!fila.empty() && !achou)
  {
    cel = fila.front();
    fila.pop();
    
    if (cel.i == destino.i && cel.j == destino.j)
      achou = true;
    else
    {
      if (cel.i+1 < n_linhas && grid[cel.i+1][cel.j] == infinito)
      {
        grid[cel.i+1][cel.j] = grid[cel.i][cel.j] + 1;
        InsereCelula(fila, cel.i+1, cel.j);
      }

      if (cel.i-1 >= 0 && grid[cel.i-1][cel.j] == infinito)
      {
        grid[cel.i-1][cel.j] = grid[cel.i][cel.j] + 1;
        InsereCelula(fila, cel.i-1, cel.j);
      }

      if (cel.j+1 < n_colunas && grid[cel.i][cel.j+1] == infinito)
      {
        grid[cel.i][cel.j+1] = grid[cel.i][cel.j] + 1;
        InsereCelula(fila, cel.i, cel.j+1);
      }
      
      if (cel.j-1 >= 0 && grid[cel.i][cel.j-1] == infinito)
      {
        grid[cel.i][cel.j-1] = grid[cel.i][cel.j] + 1;
        InsereCelula(fila, cel.i, cel.j-1);
      }
    }
  }
}

int main(int argc, char **argv)
{
  ifstream entrada (argv[1]);
  //ofstream saida (argv[2]);
  int n_linhas, n_colunas;
  int n_obstaculos;
  celula origem, destino, aux;

  if (entrada.is_open())
  {
    entrada >> n_linhas >> n_colunas;
    entrada >> origem.i >> origem.j;
    entrada >> destino.i >> destino.j;
    entrada >> n_obstaculos;

    vector<vector<int>> grid(n_linhas, vector<int>(n_colunas, infinito));

    // Marcando os obstaculos
    for (int temp = 0, k, l; temp < n_obstaculos; ++temp)
    {
      entrada >> aux.i >> aux.j >> k >> l;
      for (int i = aux.i, count1 = 0; count1 < k; ++i, ++count1)
        for (int j = aux.j, count2 = 0; count2 < l; ++j, ++count2)
          grid[i][j] = -1;
    }

    Expansao(grid, n_linhas, n_colunas, origem, destino);
    //ImprimeMatriz(grid, n_linhas, n_colunas);

    entrada.close();
  }
  else
  {
    std::cout << "Arquivo não encontrado!\n";
  }

  //saida.close();  
  return 0;
}
