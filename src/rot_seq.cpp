/*********************************************************
 * Aluno: Ian Haranaka | RGA: 2018.1904.009-7
 * Comando de compilação: g++ rot_seq.cpp -o rot_seq -Wall
 *********************************************************/

#include <omp.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;

const int INFINITO = numeric_limits<int>::max();

struct Celula { int i; int j; };

bool Expansao(vector<vector<int>> &grid, int n_linhas, int n_colunas, 
              Celula origem, Celula destino)
{
  queue<Celula> fila;
  Celula cel = origem, viz;
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
      if (cel.i+1 < n_linhas && grid[cel.i+1][cel.j] == INFINITO)
      {
        viz = (Celula){cel.i+1, cel.j};
        grid[viz.i][viz.j] = grid[cel.i][cel.j] + 1;
        fila.push(viz);
      }

      if (cel.i-1 >= 0 && grid[cel.i-1][cel.j] == INFINITO)
      {
        viz = (Celula){cel.i-1, cel.j};
        grid[viz.i][viz.j] = grid[cel.i][cel.j] + 1;
        fila.push(viz);
      }

      if (cel.j+1 < n_colunas && grid[cel.i][cel.j+1] == INFINITO)
      {
        viz = (Celula){cel.i, cel.j+1};
        grid[viz.i][viz.j] = grid[cel.i][cel.j] + 1;
        fila.push(viz);
      }
      
      if (cel.j-1 >= 0 && grid[cel.i][cel.j-1] == INFINITO)
      {
        viz = (Celula){cel.i, cel.j-1};
        grid[viz.i][viz.j] = grid[cel.i][cel.j] + 1;
        fila.push(viz);
      }
    }
  }

  return achou;
}

void Backtracking(vector<vector<int>> grid, vector<Celula> &caminho,
                  Celula origem, Celula destino)
{
  Celula cel = destino;
  caminho.insert(caminho.begin(), cel);

  while (cel.i != origem.i || cel.j != origem.j)
  {
    if (grid[cel.i+1][cel.j] == grid[cel.i][cel.j] - 1)
      cel.i++;
    else if (grid[cel.i-1][cel.j] == grid[cel.i][cel.j] - 1)
      cel.i--;
    else if (grid[cel.i][cel.j+1] == grid[cel.i][cel.j] - 1)
      cel.j++;
    else
      cel.j--;

    caminho.insert(caminho.begin(), cel);
  }
}

bool AlgoritmoLee(vector<vector<int>> &grid, vector<Celula> &caminho, 
                  int n_linhas, int n_colunas, 
                  Celula origem, Celula destino)
{
  if (Expansao(grid, n_linhas, n_colunas, origem, destino))
  {
    Backtracking(grid, caminho, origem, destino);
    return true;
  }

  return false;
}

int main(int argc, char **argv)
{
  ifstream entrada (argv[1]);
  ofstream saida (argv[2]);
  int n_linhas, n_colunas;
  int n_obstaculos;
  Celula origem, destino, aux;

  if (entrada.is_open())
  {
    entrada >> n_linhas >> n_colunas;
    entrada >> origem.i >> origem.j;
    entrada >> destino.i >> destino.j;
    entrada >> n_obstaculos;

    vector<vector<int>> grid(n_linhas, vector<int>(n_colunas, INFINITO));
    vector<Celula> caminho;

    // Marcando os obstaculos
    for (int temp = 0, k, l; temp < n_obstaculos; ++temp)
    {
      entrada >> aux.i >> aux.j >> k >> l;
      for (int i = aux.i, count1 = 0; count1 < k; ++i, ++count1)
        for (int j = aux.j, count2 = 0; count2 < l; ++j, ++count2)
          grid[i][j] = -1;
    }

    if (AlgoritmoLee(grid, caminho, n_linhas, n_colunas, origem, destino))
    {
      saida << grid[destino.i][destino.j] << '\n';
      for (const auto it : caminho)
        saida << it.i << ' ' << it.j << '\n';
    }
         
    entrada.close();
  }
  else
  {
    std::cout << "Arquivo não encontrado!\n";
  }

  saida.close();  
  return 0;
}
