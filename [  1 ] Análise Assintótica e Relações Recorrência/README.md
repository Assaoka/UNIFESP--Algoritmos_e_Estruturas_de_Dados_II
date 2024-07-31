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

 





# Como escolher o algoritmo mais adequado para um problema?
Primeiramente, é necessário saber o que é mais importante para o problema:
- Tempo de Execução.
- Espaço de Memória.
- Facilidade de Implementação.

## Medindo o Tempo de Execução:
- Calcular o tempo de execução em si é considerado uma má prática, pois depende de diversos fatores externos (impedindo a generalização).
  - Os resultados podem variar de acordo com o hardware, sistema operacional, linguagem de programação, compilador.
  - Quando grandes quantidades de memória são alocadas as medidas de tempo podem ser afetadas por esse aspecto também.
- Apesar disso, existem argumentos a favor da prática.
  - Comparar algoritmos com a mesma complexidade. 

## Complexidade de Algoritmos:
- No lugar de medir o tempo de execução, é mais comum medir a complexidade do algoritmo.
- Podemos estudar a complexidade de um algoritmo de duas formas:
  - Complexidade de Tempo: Podemos fazer isso contando o número de operações elementares que o algoritmo realiza.
    - Operações elementares são operações que são executadas em tempo constante (ou seja, não dependem do tamanho da entrada).
  - Complexidade de Espaço: Estudamos a quantidade de memória que o algoritmo utiliza em função do tamanho da entrada.
- A complexidade de um algoritmo é uma função que associa o tamanho da entrada com o custo computacional do algoritmo.
  - O tamanho da entrada é geralmente representado por n.
  - O custo computacional é geralmente representado por f(n).	
- Alguns algoritmos dependem da forma como os dados estão organizados, e não apenas do tamanho da entrada. Isso é comum em algoritmos de ordenação. Nesses casos podemos dividir a complexidade em casos:
  - Melhor Caso: Complexidade do algoritmo quando a entrada está organizada de forma que o algoritmo execute o mínimo de operações possível.
  - Pior Caso: Complexidade do algoritmo quando a entrada está organizada de forma que o algoritmo execute o máximo de operações possível.
  - Caso Médio: Complexidade do algoritmo quando a entrada está organizada de forma aleatória. Geralmente é mais difícil de calcular (média ponderada dos casos possíveis e suas probabilidades).


# Análise Assintótica:
- A escolha do algoritmo não é um problema critico para entradas pequenas.
- Porém, para entradas grandes, a escolha do algoritmo pode ser crucial (onde um algoritmo menos eficiente não consegue terminar a execução em tempo hábil).
  - Dessa forma, é comum analisar o comportamento assintótico (para valores suficientemente grandes de n) dos algoritmos.
- `Definição:` $f(n)$ domina assintoticamente $g(n)$ se existem constantes $c$ e $m$ tais que para $n >= m$, $g(n) <= c * f(n)$.
  - Ou seja, quando a entrada é maior que $m$, $c * f(n)$ é sempre maior que $g(n)$.
  - Quando $f(n)$ domina $g(n)$ e $g(n)$ domina $f(n)$, as funções são da mesma classe de algoritmos.

## Notação O (Big O):
- Escrevemos $f(n) = O(g(n))$ se $f(n)$ domina assintoticamente $g(n)$.
  - Ou seja, se a complexidade de um problema é $O(g(n^2))$, isso significa que existem constantes $c$ e $m$ tais que para $n >= m$, o custo computacional do algoritmo é menor ou igual a $c * g(n^2)$.
  - Observe algo interessante: Se o algoritmo é $O(g(n^2))$, ele também é $O(g(n^3))$, porém essa afirmação é mais fraca que a anterior.
- Particularidade do Logaritmo:
  - $\log_a n$ difere de $\log_b n$ por uma constante $c$. Onde $c = \log_a b$. Tomando $n = b^{\log_b n}$, temos que $\log_a n = \log_a b * \log_b n$.
  - Logo, existe uma constante $c$ tal que $\log_a n = c * \log_b n$. Portanto, $\log_a n = O(\log_b n)$. Ou seja, o logaritmo é independente da base.
- Tabela de Operações com Notação O

TA HORRIVEL ISSO AQUI, MELHORA GPT

| Operação | Resultado | Explicação |
|:--------:|:---------:| :----------: |
| $f(n)$ | $O(f(n))$ | A função $f(n)$ domina ela mesma. |
| $c * f(n)$ | $O(f(n))$ | Basta escolher $c$ como constante. |
| $O(f(n)) + O(f(n))$ | $O(f(n))$ | Seria o mesmo que $2 * O(f(n))$. O que caia na regra da constante. |
| $O(O(f(n)))$ | $O(f(n))$ | |
| $O(f(n)) + O(g(n))$ | $O(max(f(n), g(n)))$ | Suponha que $f(n) = O(n^2)$ e $g(n) = O(n)$. Como $O(n^2)$ domina $h(n) = n^2 + n$, temos que $O(n^2) + O(n) = O(n^2)$. |
| $O(f(n)) * O(g(n))$ | $O(f(n) * g(n))$ | Podemos pensar que serão executadas $f(n)$ operações e para cada uma delas $g(n)$ operações. |
| $f(n) * O(g(n))$ | $O(f(n) * g(n))$ | Pode ser pensado como $O(f(n)) * O(g(n))$. |

- No caso de ambas as funções dominarem a outra, o comportamento assintótico não serve para comparar as funções.
- Um algoritmo $O(n)$ é mais eficiente que um algoritmo $O(n^2)$, porém as constantes podem alterar essa relação até um certo ponto.
  - Por exemplo, um algoritmo $O(n^2)$ com constante 1 pode ser mais eficiente que um algoritmo $O(n)$ com constante 1000. 
  
## Classes de Algoritmos:
- Classes de algoritmos são uma família de algoritmos que possuem aproximadamente a mesma complexidade.
  - Por exemplo: Algoritmos de Complexidade Quadrática (O(N^2)), Algoritmos de Complexidade Logarítmica (O(log N)), etc.
- O menor custo possível para resolver um problema é a dificuldade intrínseca do problema.
- Quando um algoritmo possui o mesmo custo que a dificuldade intrínseca do problema, dizemos que ele é ótimo.
- Damos nomes especiais para algumas classes de algoritmos:

| Complexidade | Explicação |
|:------:|:----:|
| $O(1)$ | Algoritmos de Complexidade Constante. O algoritmo não depende do tamanho da entrada. |
| $O(\log n)$ | Algoritmos de Complexidade Logarítmica. Tipico de algoritmos de divisão e conquista. |
| $O(n)$ | Algoritmos de Complexidade Linear. O algoritmo executa uma quantidade constante de operações para cada elemento da entrada. |
| $O(n \log n)$ | Tipico de algoritmos que dividem o problema em partes menores e depois combinam as soluções (como algoritmos de ordenação). |
| $O(n^2)$ | Algoritmos de Complexidade Quadrática. Comuns em casos que os itens da entrada são comparados entre si. |
| $O(n^3)$ | Algoritmos de Complexidade Cúbica. A partir desse ponto, esses algoritmos são uteis apenas para entradas pequenas. |
| $O(2^n)$ | Algoritmos de Complexidade Exponencial. |

- Considerando que um computador x execute $10^6$ operações por segundo:
| Complexidade | n = 10 | n = 20 | n = 30 | n = 40 |
|:------:|:----:|:----:|:----:|:----:|
| $O(n)$ | 0,00001 s | 0,00002 s | 0,00003 s | 0,00004 s |
| $O(n^2)$ | 0,0001 s | 0,0004 s | 0,0009 s | 0,0016 s |
| $O(n^5)$ | 0,1 s | 3,2 s | 24,3 s | 1,7 min |
| $O(2^n)$ | 0,001 s | 1 s | 17,9 min | 12,7 dias |
| $O(3^n)$ | 0,059 s | 58 min | 6,5 anos | 385 milênios |



# Técnicas de Análise de Algoritmos:
- Determinar a complexidade pode ser uma tarefa difícil. A ordem de complexidade pode simplificar essa tarefa.
- Para problemas não recursivos, podemos encontrar a complexidade analisando o número de operações elementares.
  - Comandos de atribuição, comparação, aritmética, etc contam como O(1).
  - Para estruturas de repetição, multiplicamos o número de operações pelo número de repetições.
  - Para sequências de comandos, consideramos o maior custo.




- Existem diversas técnicas para analisar algoritmos:
  - Método de Substituição.
  - Método de Árvore de Recorrência.
  - Método Mestre.


























# Complexidade de Algoritmos:
## Notação Assintótica:
## Tipos de Notação:
## Classes de Algoritmos:

# Relações de Recorrência:
## Método de Substituição:
## Método de Árvore de Recorrência:
## Método Mestre:

