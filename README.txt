Comando para compilação:
    gcc *.c -o t1

Utilização:
./t1 <nome_do_arquivo>
ou
./t1

O símbolo BRANCO é representado por ‘[‘
Exemplo de entrada no formato 5-tupla:
BEGIN_MACHINE
Q0 Q1 a b R
Q0 Q0 b b R
Q1 Q2 a [ L
END_MACHINE
BEGIN_INPUT
aaaabb
babbaa
END_INPUT
RUN

Exemplo de entrada no formato binário:
BEGIN_MACHINE
01001001010110100010101011010000100010101100100100100101100100100010001011
END_MACHINE
BEGIN_INPUT
aaaabb
baaaab
END_INPUT
STEP

Movimentos do cabeçote:
R -> Direita(Right)
L -> Esquerda(Left)
S -> Sem Movimento(Stay)

Execução imediata ou passo a passo:
RUN/STEP