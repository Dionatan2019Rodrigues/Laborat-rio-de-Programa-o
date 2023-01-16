
#define CATCH_CONFIG_MAIN // O Catch fornece uma main()
#include "catch.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <functional>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

struct Aresta {
  int v;         // vertice destino
  float peso;    // peso da aresta
};

struct Vertice {
  int info;                   // valor do vertice
  float chave;                // chave usada no heap
  int anterior;               // quem é o anterior (Dijkstra)
  std::list<Aresta> arestas;
};

/** 
 * A struct abaixo define um HEAP Mínimo
 */
template<typename T, typename C>
struct Heap {
  std::vector<T> dado; // vetor do heap
  C compara; // funcao para comprar elementos

  // inicia o Heap com funcao de comparação
  Heap(C cmp): compara(cmp) {}

  // insere sem atualizar o heap
  void insere(T v){
    dado.push_back(v);
  }

  // remove o elemento no topo do heap
  void remove(void){
    std::pop_heap(dado.begin(), dado.end(), compara);
    dado.pop_back();
  }

  // retorna o menor elemento
  T topo(void){
    return dado.front();
  }

  // testa se heap é vazio
  bool vazio(void){
    return dado.empty();
  }

  // atualiza o heap
  void atualiza(void){
    std::make_heap(dado.begin(), dado.end(), compara);
  }
};

/**
 * struct inicial de um Grafo com pesos
 */
struct Grafo {
  int nvertices;
  int narestas;
  std::map<int, Vertice> grafo;

  // inicia o grafo vazio
  void inicia(void){
      nvertices = 0;
      narestas = 0;
  }

  void inicia(const char* arquivo){
    std::ifstream entrada {arquivo};    

    if(!entrada.is_open())
      throw std::runtime_error{"ERRO nao foi possivel abrir arquivo!"};
  
    entrada >> nvertices;
    entrada >> narestas;

    // cria os vertices
    std::string chave, nome;
    for(auto v= 0; v < nvertices; v++){
      grafo[v] = Vertice();
      grafo[v].info = v;
      grafo[v].anterior = -1;
    }

    int v1, v2;
    float peso;
    for(auto i= 0; i < narestas; i++){
      entrada >> v1;
      entrada >> v2;
      entrada >> peso;
      grafo[v1].arestas.push_back( Aresta{v2, peso} );
      grafo[v2].arestas.push_back( Aresta{v1, peso} );
    }
    entrada.close();    
  }

  void vertice(const int v){
    grafo[v] = Vertice();
    grafo[v].info = v;
    grafo[v].anterior = -1;
    nvertices++;
  }

  void aresta(const int u, const int v, const float peso){
    grafo[u].arestas.push_back( Aresta{v, peso} );
    grafo[v].arestas.push_back( Aresta{u, peso} );
  }

  void dijkstra(const int fonte) {
    // inicializa todos vertices do grafo G com chave infinita
    for(auto & i : grafo){
      i.second.chave = std::numeric_limits<float>::max();
    }
    //cria heap mínimo H
    auto compara = [](Vertice* v1, Vertice* v2) {return v1->chave > v2->chave;};
    Heap<Vertice*, decltype(compara)> heap(compara);
    //inicia chave da fonte com valor 0
    grafo[fonte].chave = 0;
    //insere todos os vértices de G no heap 
    for(auto &i:grafo){
      //std::cout << i.second.info << "Inserindo " << std::endl;
      heap.insere(&(i.second));
    }

    heap.atualiza();

    while(!heap.vazio()){
      auto u = heap.topo();
      heap.remove();
      for(auto i : u->arestas){  
        
        if((u->chave + i.peso) < (grafo[i.v].chave)){
          grafo[i.v].anterior = u->info;
        
          grafo[i.v].chave = u->chave + i.peso;
          heap.atualiza();
        }
      }
    }
  }
  
  void imprime(void){
    for(const auto& v: grafo){
      std::cout << v.first << " -> ";
      for(const auto& a: v.second.arestas){
	      std::cout << a.v << "(" << a.peso << ") ";
      }
      std::cout << std::endl;
    }    
  }

  // essa versao imprime o caminho mínimo
  bool caminhoMinimo(int u, int v){
    //std::cout << "ola" << std::endl;

    if(grafo.count(u) == 0 || grafo.count(v) == 0){
      return false;
    }


    if(u == v){
      std::cout << grafo[u].info << " ";
      return true;
    }
    
    if(grafo.empty() == true){
      //std::cout << "ola02" << std::endl;    
        return false;
      }

    if(grafo[v].anterior == -1){
      std::cout << "ERRO: caminho nao existe!" << std::endl;
      return false;
    } 
    //std::cout << "ol04s" << std::endl;
    caminhoMinimo( u, grafo[v].anterior );
    std::cout << grafo[v].info << " ";
    return true;
  }

  bool caminhoMinimo(int u, int v, std::list<int>& lista){
    if(u == v){
      //std::cout << grafo[u].info << " ";
      lista.push_back(u);
      return true;
    }

    if(grafo.empty() == true)
        return false;

    if(grafo[v].anterior == -1){
      // caminho nao existe!
      return false;
    } 
    
    caminhoMinimo( u, grafo[v].anterior, lista );
    //std::cout << grafo[v].info << " ";
    lista.push_back(v);

    return true;
  }
  
};

TEST_CASE("Teste vazio") {
    Grafo g;
    g.inicia();
    g.dijkstra(1);
    REQUIRE(g.caminhoMinimo(1,2) == false);
}

TEST_CASE("1-2,2-3") {
    Grafo g;
    g.inicia();
    g.vertice(1);
    g.vertice(2);
    g.vertice(3);
    g.aresta(1, 2, 1.0);
    g.aresta(2, 3, 1.0);
    g.dijkstra(1);
    std::list<int> res;
    std::list<int> resp {1, 2, 3};
    g.caminhoMinimo(1, 3, res);
    REQUIRE(res.size() == 3);
    REQUIRE(res == resp);
}

TEST_CASE("1-2,1-3") {
    Grafo g;
    g.inicia();
    g.vertice(1);
    g.vertice(2);
    g.vertice(3);
    g.aresta(1, 2, 1.0);
    g.aresta(1, 3, 1.0);
    g.dijkstra(1);
    std::list<int> res;
    std::list<int> resp {1, 3};
    g.caminhoMinimo(1, 3, res);
    REQUIRE(res.size() == 2);
    REQUIRE(res == resp);
}

TEST_CASE("tinyEWD.txt 5 <-> 6") {
    Grafo g;
    g.inicia("tinyEWD.txt");
    g.dijkstra(5);
    std::list<int> res;
    std::list<int> resp {5, 7, 2, 6};
    g.caminhoMinimo(5, 6, res);
    REQUIRE(res == resp);
}

TEST_CASE("tinyEWD.txt 4 <-> 3") {
    Grafo g;
    g.inicia("tinyEWD.txt");
    g.dijkstra(4);
    std::list<int> res;
    std::list<int> resp { 4, 7, 3 };
    g.caminhoMinimo(4, 3, res);
    REQUIRE(res == resp);
}

TEST_CASE("mediumEWD.txt 10 <-> 247") {
    Grafo g;
    g.inicia("mediumEWD.txt");
    g.dijkstra(10);
    std::list<int> res;
    std::list<int> resp { 10, 106, 179, 79, 51, 18, 35, 12, 121, 158, 249, 189, 150, 190, 247 };
    g.caminhoMinimo(10, 247, res);
    REQUIRE(res == resp);
}


TEST_CASE("rome99.txt 2 <-> 3337") {
    Grafo g;
    g.inicia("rome99.txt");
    g.dijkstra(2);
    std::list<int> res;
    std::list<int> resp { 2, 1, 22, 165, 162, 167, 164, 171, 190, 191, 336, 338, 343, 344, 340, 347, 348, 335, 515, 407, 524, 582, 589, 596, 628, 630, 648, 1217, 1218, 1237, 1239, 1252, 1253, 1258, 1259, 1260, 1354, 1360, 1365, 1364, 1381, 1382, 1426, 1429, 1736, 1740, 1741, 1744, 1745, 1786, 1785, 1791, 1799, 1800, 1808, 1813, 1814, 1815, 2028, 1935, 1936, 2052, 2055, 1966, 2056, 2057, 2422, 2360, 2358, 2359, 2361, 2364, 2395, 2396, 2397, 2400, 2407, 2411, 2506, 2632, 2633, 2638, 2594, 2642, 2658, 2659, 2660, 2670, 2673, 2841, 2844, 2856, 2857, 2863, 2864, 3337 };
    g.caminhoMinimo(2, 3337, res);
  REQUIRE(res == resp);
}

