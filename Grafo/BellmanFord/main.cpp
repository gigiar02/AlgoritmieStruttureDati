/*
  Data di creazione: 20/05/2025 orario 14:03 
  Implementare un grafo ed eseguire BellmanFord
*/
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define TEMPLATE template<typename T>
#define inf INFINITY


TEMPLATE
class Node
{
  T data;
  int key;
  int distance;
  Node* predecessor;
  vector<Node*> adj; 
  public:
  Node(int key) : key(key){}
  int getKey(){return key;}
  int getDistance(){return distance;}
  Node* getPredecessor(){return predecessor;}
  vector<Node*> getChildren(){return adj;}
  
  void setDistance(int dist){distance = dist;}
  void setPredecessor(Node* p){predecessor = p;}
  void addChild(Node* ch){adj.push_back(ch);}
};
#define node Node<T>

TEMPLATE
class Edge
{
  pair<node*,node*> edge;
  int w;
  public:
  Edge(node* x,node* y,int w){x->addChild(y); edge.first = x; edge.second = y; this->w = w;}
  node* getX(){return edge.first;}
  node* getY(){return edge.second;}
  int getW(){return w;}
};
#define edge Edge<T>

TEMPLATE
class Compare
{
  public:
  bool operator() (node* x,node* y)
  {
    if(x->getDistance() > y->getDistance())
    {
      return true;
    }
    return false;
  }
};


TEMPLATE
class Graph
{
  vector<node*> V;
  vector<edge*> E;
  
  public:
  Graph(){}
  node* searchNode(int key)
  {
    for(auto& v : V)
    {
      if(v->getKey() == key) return v;
    }
    
    node* newNode = new node(key);
    V.push_back(newNode);
    return newNode;
  }
  
  void addEdge(int key,int key2,int w)
  {
    node* x = searchNode(key);
    node* y = searchNode(key2);
    edge* ed = new edge(x,y,w);
    E.push_back(ed);
  }
  
  void popola()
  {
    ifstream in("in.txt");
    int key,key1,w;
    
    while(in>>key>>key1>>w)
    {
      addEdge(key,key1,w);
    }
  }
  
  void relax(node* x,node* y,int w)
  {
    if(y->getDistance() > x->getDistance() + w) y->setDistance(x->getDistance() + w);
  }
  
  void print()
  {
    for(auto v: V)
    {
      cout<<"d["<<v->getKey()<<"]"<<" = "<<v->getDistance()<<endl;
    }
  }
  
  bool BellmanFord(int key)
  {
    node* s = searchNode(key);

    for(auto& v : V)
    {
      if(v == s) continue;
      v->setDistance((int) inf);
      v->setPredecessor(nullptr);
    }
    s->setDistance(0);
    s->setPredecessor(nullptr);
    
    for(int i = 0; i < V.size(); i++)
    {
      for(auto& e : E)
      {
        relax(e->getX(),e->getY(),e->getW());
      }
    }
    
    for(auto& e : E)
    {
      node* x = e->getX();
      node* y = e->getY();
      int w = e->getW();
      if(y->getDistance() > x->getDistance() + w) return false;
    }
    return true;
   }
  
};

int main()
{
  Graph<int> G;
  G.popola();
  if(G.BellmanFord(1))
  {
    cout<<"Non ci sono cicli negativi"<<endl;
    G.print();
  }else
  {
    cout<<"C'è un ciclo negativo"<<endl;
  }
  
}
