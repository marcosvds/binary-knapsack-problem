### Algoritmo Genético para o Problema da Mochila

### Descrição

Este projeto implementa um algoritmo genético para resolver o problema da mochila binária, um problema de otimização combinatória. O programa cria um conjunto de itens, cada um com um valor e peso, e tenta maximizar o valor total dos itens na mochila sem exceder sua capacidade de peso.

### Funcionalidades

- Geração aleatória de itens com valores e pesos configuráveis.
- Implementação de algoritmo genético incluindo seleção, crossover, mutação e avaliação de aptidão.
- Simulação de múltiplas gerações para evoluir soluções ótimas ou quase ótimas.
- Saída detalhada do desempenho do algoritmo genético e resultados ao longo das gerações.

### Como Funciona

1. **Geração de Itens**: Os itens são gerados aleatoriamente com limites especificados para peso e valor.
2. **População Inicial**: Uma população de soluções potenciais (indivíduos) é inicializada, onde cada solução é um vetor binário representando se um item está incluído ou não na mochila.
3. **Cálculo de Aptidão**: A aptidão de cada indivíduo é calculada com base no valor total dos itens incluídos, penalizando aqueles que excedem a capacidade de peso.
4. **Seleção de Pais**: Um conjunto dos indivíduos mais aptos é selecionado para gerar a próxima geração.
5. **Crossover**: Novos indivíduos são produzidos combinando o material genético de dois pais.
6. **Mutação**: Os novos indivíduos sofrem mutações aleatórias para introduzir diversidade genética.
7. **Atualização da População**: A nova geração substitui a antiga, e o processo se repete.

### Requisitos

- Compilador C++ (por exemplo, GCC, Clang)
- Biblioteca padrão do C++

### Compilação e Execução

Para compilar e executar o projeto, use os seguintes comandos:

```sh
g++ -o knapsack knapsack.cpp
./knapsack inputs/In1.txt outputs/Out1.txt
```

### Configuração

Modifique os arquivos de entrada para alterar o número de itens, seus valores máximos e pesos, e a capacidade da mochila:

### Exemplo de Arquivo de Entrada (`inputs/In1.txt`):

```plaintext
5 15
2 3
3 4
4 5
5 8
9 10
```

### Saída

O programa gera arquivos de saída detalhando a progressão do algoritmo genético ao longo das gerações e a solução final, incluindo o valor total e o peso dos itens na mochila. 

### Exemplo de Uso

Suponha que você tenha cinco arquivos de entrada (`In1.txt` a `In5.txt`) na pasta `inputs` e deseja gerar os arquivos de saída correspondentes na pasta `outputs`:

```sh
./knapsack inputs/In1.txt outputs/Out1.txt
./knapsack inputs/In2.txt outputs/Out2.txt
./knapsack inputs/In3.txt outputs/Out3.txt
./knapsack inputs/In4.txt outputs/Out4.txt
./knapsack inputs/In5.txt outputs/Out5.txt
```

Seguindo essas instruções, você poderá executar o algoritmo genético para resolver o problema da mochila binária de forma eficiente.