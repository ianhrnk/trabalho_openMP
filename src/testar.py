import os

for i in range(1,10):
  comando = 'time ./rotseq Entradas_Saidas/entrada{}.txt saida_seq{}'.format(i, i)
  print('Executando sequencial {}'.format(i))
  if (os.system(comando) != 0):
    print('Sequencial {} retornou valor diferente de zero!'.format(i))
    break

  comando = 'diff saida_seq{} Entradas_Saidas/saida{}.txt'.format(i, i)
  if (os.system(comando) != 0):
    print('Saída não bateu.')
    break

  comando = 'time ./rotpar Entradas_Saidas/entrada{}.txt saida_par{}'.format(i, i)
  print('Executando paralelo {}'.format(i))
  if (os.system(comando) != 0):
    print('Paralelo {} retornou valor diferente de zero!'.format(i))
    break

  comando = 'diff saida_par{} Entradas_Saidas/saida{}.txt'.format(i, i)
  if (os.system(comando) != 0):
    print('Saída não bateu.')
    break
