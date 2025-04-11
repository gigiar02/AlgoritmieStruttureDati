/*  
  Data 04/11/2025
  Traccia:
  Implementare un grafo, popolarlo tramite il file traccia.txt e implementare la bfs.
  Nella prima riga trovi num vertici e num archi, nelle altre nodo sorgente,nodo destinazione,peso arco.
*/
#include "lib.hpp"

int main()
{
  Graph<int> g;
  g.population();
  g.bfs(1);
  return 0;
}
