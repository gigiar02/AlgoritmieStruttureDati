/*  
  Data 04/11/2025
  Traccia:
  Implementare un grafo, popolarlo tramite il file traccia.txt e implementare la bfs.
  Nella prima riga trovi num vertici e num archi, nelle altre nodo sorgente,nodo destinazione,peso arco.
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <stack>
#include <cmath>
using namespace std;
#define t template<typename T>

enum class Color
{
  WHITE,
  GRAY,
  BLACK
};


t
class Node
{
  T data;
  vector<Node*> children;
  Node* predecessor;
  int key;
  int distance;
  Color color = Color::WHITE;
  
  
  public:
    //Constructor
    Node(int key) : key(key){}
    Node(int key,T data) : key(key), data(data) {}
    
    //Getter
    vector<Node*> getChildren(){return children;}
    Node*         getPredecessor(){return predecessor;}
    Node*         getChild(int key);
    int           getKey(){return key;}
    int           getDistance(){return distance;}
    Color         getColor(){return color;}
    T             getData(){return data;}
    
    //Setter
    bool          addChild(Node<T>*& child);
    bool          addChild(int key);
    void          setKey(int key) {this->key = key;}
    void          setDistance(int distance) {this->distance = distance;}
    void          setData(T data){this->data = data;}
    void          setColor(Color color) {this->color = color;}

};


t
class Edge
{
  pair<Node<T>*,Node<T>*> edge;
  int w;
  
  public:
    //Constructor
    Edge(Node<T>*& xKey,Node<T>*& yKey,int w) : w(w) {edge.first = xKey;  edge.second = yKey;}
    
    //Getter
    Node<T>* x()    {return edge.first;}
    Node<T>* y()    {return edge.second;}
    int      getW() {return w;}

};


t
class Graph
{
  vector<Node<T>*> V;
  vector<Edge<T>*> E;
  
  int vertex;
  int edges;
  
  public:
    //Constructor
    Graph(){vertex = 0; edges = 0;}
    
    bool     addVertex(int key);
    Node<T>* findVertex(int key);
    Node<T>* findVertexSecure(int key);
    int      getEdges() {return edges;}
    int      getVertex(){return vertex;}
    bool     addEdge(int key1,int key2,int w);
    void     population();
    void     bfs(int source);  
};



//METODI NODE


//Trova il figlio che ha chiave key e lo restituisce. Nel caso in cui fallisce restituisce nullptr;
t
Node<T>* Node<T>::getChild(int key)
{
      for(auto& v : children)
      {
        if(v->key == key) return v;
      }
      return nullptr;
}

//Aggiunge un figlio che avrà chiave key. Nel caso in cui fallisce restituisce false
t
bool Node<T>::addChild(Node<T>*& child)
{
  if(this->key == child->key) return false;
  
  for(auto& v : children)
  {
    if(v->key == child->key) return false;
  }
  
  //Aggiunge il figlio
  children.push_back(child);
  return true;
}


//METODI GRAFO


//Aggiunge un vertice
t
bool Graph<T>::addVertex(int key)
{
  //Verifica se esiste già un vertice nel grafo con la stessa chiave
  for(auto& v : V)
  {
    if(v->getKey() == key)
    {
      return false;
    }
  }
  
  //Aggiungi il vertice
  Node<T>* nodo = new Node<T>(key);
  V.push_back(nodo);
  vertex++;
  return true;
}


//Ricerca un vertice all'interno del grafo e se lo trova lo restituisce
t
Node<T>* Graph<T>::findVertex(int key)
{
  for(auto& v : V)
  {
    if(v->getKey() == key)
    {
      return v;
    }
  }
  
  return nullptr;
}

//Ricerca un vertice all'interno del grafo e se lo trova lo restituisce altrimenti lo aggiunge
t
Node<T>* Graph<T>::findVertexSecure(int key)
{
  for(auto& v : V)
  {
    if(v->getKey() == key)
    {
      return v;
    }
  }
  
  //Non ho trovate nessun vertice con la chiave e quindi lo aggiungo
  this->addVertex(key);
  return this->findVertex(key);
}


//Aggiungi un arco. Se uno dei due nodi non esiste viene creato
t
bool Graph<T>::addEdge(int key1,int key2,int w)
{
  //Ricerca sicura dei nodi
  Node<T>* x = findVertexSecure(key1);
  Node<T>* y = findVertexSecure(key2);
  
  //Aggiunta al grafo 
  x->addChild(y);
  Edge<T>* edge = new Edge<T>(x,y,w);
  E.push_back(edge);
  edges++;
  return true;
}


//Popola il grafo
t
void Graph<T>::population()
{
  ifstream in("traccia.txt");
  int key1,key2,w,edges,vertex;
  int countedEdge = 0;
  int countedVertex;
  
  //Prendo il numero di vertici e di archi
  in>>edges>>vertex;
  
  cout<<"vertex = "<<vertex<<" edges = "<<edges<<endl;
  
  for(int i = 0; i < edges; i++)
  {
    if(this->edges < edges) return;
    if(this->vertex < vertex) return;
    if(in>>key1>>key2>>w)
    {
        cout<<"key1: "<<key1<<" key2 "<<key2<<endl;
        this->addEdge(key1,key2,w);
        continue;
    }
  }

  in.close();
}


//Effettua una BFS a partire dalla sorgente presa in input
t
void Graph<T>::bfs(int source)
{
  Node<T>* s = findVertexSecure(source);
  s->setColor(Color::GRAY);
  s->setDistance(0);
  queue<Node<T>*> coda;
  coda.push(s);
  
  for(auto &v : V)
  {
    if(v != s)
    {
      v->setColor(Color::WHITE);
      v->setDistance(INFINITY);
    }
  }
  
  while(!coda.empty())
  {
    //Pop del nodo corrente
    Node<T>* u = coda.front();
    coda.pop();
    cout<<"Key corrente: "<<u->getKey()<<endl;
    
    //Inserisco i figli
    for(auto &v : u->getChildren())
    {
      if(v->getColor() == Color::WHITE)
      {
        v->setColor(Color::GRAY);
        v->setDistance(u->getDistance() + 1);
        coda.push(v);
      }
    }
    
    u->setColor(Color::BLACK);
  }
  
  //Stampa in un file del risultato
  ofstream out("out.txt");
  for(auto &v : V)
  {
    out<<"key = "<<v->getKey()<<" distance = "<<v->getDistance()<<endl;
  }
  
  out.close();
  
}
