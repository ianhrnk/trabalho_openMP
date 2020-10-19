/******************************************
 * 
 * 
 ******************************************/

#include <omp.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
  string line;
  ifstream entrada (argv[1]);
  ofstream saida (argv[2]);

  if (entrada.is_open())
  {
    while (getline(entrada, line))
      cout << line << '\n';
    entrada.close();
  }
  else
  {
    std::cout << "Arquivo não encontrado!\n";
  }

  saida.close();
  
  return 0;
}
