<h1 align="center"> Análise Assintótica e Relações Recorrência <br>
  <a href="../"><img src="https://img.shields.io/badge/Anterior-Home-215a36" alt="Anterior"></a>
  <a href="../[ 2] Métodos de Ordenação O(N^2)/"><img src="https://img.shields.io/badge/Próximo-Struct%20e%20Ponteiro-215a36" alt="Próximo"></a>
</h1>


# Diferença entre um Algoritmo e um Programa:
- Um `ALGORITMO` é um conjunto de instruções sequenciais que, quando seguidas corretamente, resolvem um problema ou executam uma tarefa.
  - **Exemplo:** Receita de bolo.
- Já um `PROGRAMA` é uma implementação concreta de um algoritmo em uma linguagem de programação específica.
  - Assim, quando um algoritmo é traduzido para uma linguagem de programação, ele se torna um programa.
- Ambas operam sobre `ESTRUTURAS DE DADOS`.

# Estruturas de Dados e Tipos Abstratos de Dados:
- `ESTRUTURAS DE DADOS` são abstrações da realidade que permitem representar uma situação de forma organizada.
- O mesmo conjunto de dados pode ser representado/estruturado de diversas formas. Podemos representar números inteiros como:
  - **Palitos:** (| + || = |||), o que funciona bem para números pequenos.
  - **Números Decimais:** (1 + 2 = 3), o que funciona melhor para números maiores (facilitando a leitura e escrita por humanos). 
  - **Números Binários:** (01 + 10 = 11), o que é mais eficiente para computadores.
- `ALGORITMOS` e `ESTRUTURAS DE DADOS` são a base da Ciência da Computação e são essenciais para a resolução de problemas computacionais.
- Um `Tipo Abstrato de Dados (TAD)` é a combinação de uma estrutura de dados com as operações que podem ser realizadas sobre ela.
  - Por exemplo, poderíamos usar a mesma struct (informações + 2 ponteiros) em C para implementar tanto uma Lista Duplamente Encadeada quanto uma Árvore Binária.
  - No entanto, as operações que podem ser realizadas sobre essas estruturas são completamente diferentes.
