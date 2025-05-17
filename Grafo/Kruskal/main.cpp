/*
  Data di creazione: 17/05/2025 orario: 10:25
  Traccia:
  Implementare kruskal su di un grafo G passato in input (in.txt). Scrivere il risultato (out.txt)
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define TEMPLATE template<typename T>

TEMPLATE
class Node
{
  T data;
  int key;
  Node* predecessor;
  vector<Node*> children;
  
  //Per insiemi disgiunti
  Node* root;
  int rank;
  
  
  public:
  Node(int key) : key(key){rank = 0;}
  
  //Getters
  int getKey(){return key;}
  vector<Node*> getChildren(){return children;}
  Node * getRoot(){return root;}
  int getRank(){return rank;}
  
  //Setters
  void setKey(int key){this->key = key;}
  void addChild(Node*& ch){children.push_back(ch);}
  void setRoot(Node*& r){root = r;}
  void setRank(int rank){this->rank = rank;}
  
};

#define node Node<T>

TEMPLATE
class Edge
{
  pair<node*,node*> edge;
  int w;
  
  public:
  Edge(node *& x,node *& y,int w){edge.first = x; edge.second = y; this->w = w; x->addChild(y);}
  node* getX(){return edge.first;}
  node* getY(){return edge.second;}
  int   getW(){return w;}
  

};


TEMPLATE
class compare
{
  public:
  bool operator() (Edge<T>* one, Edge<T>* two)
  {
    if(one->getW() > two->getW())
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
  vector<Edge<T>*> E;
  
  public:
  Graph(){}
  
  node* searchNode(int key)
  {
    for(auto v : V)
    {
      if(v->getKey() == key)
      {
        return v;
      }
    }
    
    node* newNode = new node(key);
    V.push_back(newNode);
    return newNode;
  }
  
  void addEdge(int key1,int key2,int w)
  {
    node* x = searchNode(key1);
    node* y = searchNode(key2);
    
    Edge<T>* edge = new Edge<T>(x,y,w);
    E.push_back(edge);
  }
  
  
  void popola()
  {
    ifstream in("in.txt");
    char appoggio;
    int key1,key2,w;
    
    while(in>>appoggio>>key1>>appoggio>>key2>>appoggio>>w)
    {
      cout<<"key1: "<<key1<<" key2: "<<key2<<" w "<<w<<endl;
      addEdge(key1,key2,w);
    }
  }
  
  
  //Crea un insieme disgiunto
  void makeSet(node*& v)
  {
    v->setRoot(v);
  }
  
  
  //Restituisce il rappresentante
  node* findSet(node*& v)
  {
    node* app = v;
    while(app->getRoot()->getKey() != app->getKey())
    {
      
      app = app->getRoot();
    }
    
    return app;
  }
  
  
  void link(node*& x,node*& y)
  {
    if(x->getRank() > y->getRank())
    {
      x->setRoot(y);
    }else
    {
      y->setRoot(x);
      if(x->getRank() == y->getRank())
      {
        int r = x->getRank() + 1;
        x->setRank(r);
      }
    }
  }
  
  
  void Union(node*& x, node*& y)
  {
    node* u = findSet(x);
    node* v = findSet(y);
    
    link(u,v);
  }
  
  bool SameComponent(node*& x,node*& y)
  {
    if(findSet(x) == findSet(y))
    {
      return true;
    }else
    {
      return false;
    }
  }
  
  void kruscal()
  {
    priority_queue<Edge<T>*,vector<Edge<T>*>,compare<T>> Q;
    cout<<"Kruskal"<<endl;
    for(auto& v : V)
    {
      makeSet(v);
    }
    for(auto& e : E)
    {
      Q.push(e);
    }
    
    ofstream out("out.txt");
    out<<"Kruskal"<<endl;
    while(!Q.empty())
    {
      Edge<T>* e = Q.top();
      cout<<"edge peso: "<<e->getW()<<endl;
      node* x = e->getX();
      node* y = e->getY();
      
      if(findSet(x) != findSet(y))
      {
         out<<"L arcco "<<x->getKey()<<" "<<y->getKey()<<" è stato preso"<<endl;
        Union(x,y);
      }else
      {
        out<<"L arcco "<<x->getKey()<<" "<<y->getKey()<<" Non è stato preso"<<endl;
      }
      Q.pop();
    }
    
    out.close();
  }
  
};

int main()
{
  Graph<int> G;
  G.popola();
  G.kruscal();
}
