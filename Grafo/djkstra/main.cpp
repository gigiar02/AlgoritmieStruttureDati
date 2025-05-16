/*
  Data: 16/05/2025 orario: 11:05
  Traccia:
  Dato un grafo G popolato da file di testo ed un vertice sorgente, implementare djkstra. Scrivere il risultato in file out
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
#define TEMPLATE template<typename T>


TEMPLATE
class Node
{
  T data;
  int key;
  int distance;
  vector<Node*> children;
  Node* predecessor;
  
  public:
  Node(int key) : key(key){}
  
  //Getters
  int getKey(){return key;}
  int getDistance(){return distance;}
  vector<Node*> getChildren(){return children;}
  
  //Setter
  void setDistance(int d){distance = d;}
  void addChild(Node*& x){children.push_back(x);}
  void setPredecessor(Node*& x){predecessor = x;}

};
#define node Node<T>*


TEMPLATE
class Edge
{
  pair<node,node> edge;
  int W;
  
  public:
  Edge(node& x,node &y,int W){edge.first = x; edge.second = y; this->W = W;}
  node getX(){return edge.first;}
  node getY(){return edge.second;}
  int getW(){return W;}

};

TEMPLATE
class Comparatore
{
  public:
  bool operator() (node x,node y)
  {
    if(x->getDistance() > y->getDistance())
    {
      cout<<"Stampo key: "<<x->getKey()<<" "<<x->getDistance()<<" key2 "<<y->getKey()<<" "<<y->getDistance()<<endl;
      return true;
    }else
    {
      return false;
    }
  }
};

TEMPLATE
class Graph
{
    vector<node> V;
    vector<Edge<T>*> E;
    
    public:
    
    node searchNode(int key)
    {
      for(auto& x : V)
      {
        if(x->getKey() == key)
        {
          return x;
        }
      }
      
      node newNode = new Node<T>(key);
      V.push_back(newNode);
      return newNode;
    }
    
    Edge<T>* searchEdge(int key1,int key2)
    {
      for(auto& x : E)
      {
        if(x->getX()->getKey() == key1 && x->getY()->getKey() == key2)
        {
          return x;
        }
      }
      return nullptr;
    }
    
    void addEdge(int key1,int key2,int W)
    {
      node x = searchNode(key1);
      node y = searchNode(key2);
      Edge<T> *edge = new Edge<T>(x,y,W);
      x->addChild(y);
      E.push_back(edge);
    }
    
    void popola()
    {
      ifstream in("in.txt");
      int key1,key2,W;
      
      while(in>>key1>>key2>>W)
      {
        addEdge(key1,key2,W);
        cout<<"Nodi aggiunti key1: "<<key1<<" key2: "<<key2<<endl;
      }
      
    }
    
    void relax(node &u,node &v,int W)
    {
      if(v->getDistance() > u->getDistance() + W)
      {
        cout<<"Modifica ai valori"<<endl;
        v->setDistance(u->getDistance() + W);
      }
    }
    //Prende in input la sorgente da cui calcolare le distanze
    void djkstra(int sKey)
    {
      ofstream out("out.txt");
      
      //Coda di minima priorità Q
      priority_queue<node,vector<node>,Comparatore<T>> Q;
      node s = searchNode(sKey);
      s->setDistance(0);
      Q.push(s);
      
      for(auto& v : V)
      {
        if(v == s) continue;
        v->setDistance(INFINITY);
        Q.push(v);
      }
      
      out<<"DJKSTRA"<<endl;
      while(!Q.empty())
      {
        node u = Q.top();
        cout<<"Operazione di pop eseguita: x: "<<u->getKey()<<endl;
        Q.pop();
        
        for(auto v : u->getChildren())
        {
          relax(u,v,searchEdge(u->getKey(),v->getKey())->getW());
        }
      }

      for(auto v : V)
      {
        out<<"d["<<v->getKey()<<"] = "<<v->getDistance()<<endl;
      }
      out.close();
    }
};


int main()
{
  Graph<int> G;
  G.popola();
  G.djkstra(1);
}

