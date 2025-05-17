/*
  Data di creazione: 17/05/2025 orario: 14:22
  Implementare prim
  
  Idea:
  Parto da un vertice sorgente s e a questo punto scopro i figli. Se un figlio v è ancora nella coda e il d[u] > w[u,v] -> d[u] = w[u,v]
*/
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <cmath>
#define inf INFINITY
using namespace std;
#define TEMPLATE template<typename T>


TEMPLATE
class Node
{
  int key;
  vector<Node*> children;
  int distance;
  bool visited = false;
  
  public:
  
  Node(int key) : key(key){}
  
  int getKey(){return key;}
  vector<Node*> getChildren(){return children;}
  int getDistance(){return distance;}
  bool isVisited(){return visited;}
  
  void setDistance(int d){distance = d;}
  void addChild(Node*& ch){children.push_back(ch);}
  void setVisited(){visited = true;}
};
#define node Node<T>

TEMPLATE
class Edge
{
  pair<node*,node*> edge;
  int W;
  
  public:
  Edge(node*& x,node*& y,int w){edge.first = x; edge.second = y; W = w; x->addChild(y);}
  node* getX(){return edge.first;}
  node* getY(){return edge.second;}
  int getW(){return W;}
  
};
#define e Edge<T>


TEMPLATE
class comp
{
  public:
  bool operator() (node* x, node* y)
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
  vector<e*>    E;
  
  public:
  Graph(){}
  
  node* searchNode(int key)
  {
    for(auto& v : V)
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
  
  int getW(int key1,int key2)
  {
    for(auto& ed : E)
    {
      if((ed->getX()->getKey() == key1 && ed->getY()->getKey() == key2) ||  (ed->getX()->getKey() == key2 && ed->getY()->getKey() == key1))
      {
        return ed->getW();
      }
    }
    return -1;
  }
  
  void addEdge(int key,int key2,int W)
  {
    node* x = searchNode(key);
    node* y = searchNode(key2);
    
    e* ed = new e(x,y,W);
    e* ed2 = new e(y,x,W);
    E.push_back(ed);
    E.push_back(ed2);
  }
 
  void popola()
  {
    ifstream in("in.txt");
    
    int key1,key2,w;
    
    while(in>>key1>>key2>>w)
    {
      addEdge(key1,key2,w);
    }
  }
  
  
  void printDistance()
  {
    for(auto& v : V)
    {
      cout<<"distanze altri nodi: "<<v->getKey()<<" dist = "<<v->getDistance()<<endl;
    }
  }
  
  
  void updateQ(priority_queue<node*,vector<node*>,comp<T>> &Q,node*& x)
  {
    //Effettuo pop finché la coda non diventa coerente
    vector<node*> extracted;
    while(!Q.empty())
    {
      node* v = Q.top();
      extracted.push_back(v);
      if(x->getDistance() > v->getDistance())
      {
        break;
      }
      Q.pop();
    }
    Q.push(x);
    for(auto& v : extracted)
    {
      Q.push(v);
    }
  }
  
  void prim(int sKey)
  {
    cout<<"Prim"<<endl;
    node* s = searchNode(sKey);
    priority_queue<node*,vector<node*>,comp<T>> Q;
    
    for(auto& v : V)
    {
      if(v == s) continue;
      v->setDistance((int) inf);
      Q.push(v);
    }
    s->setDistance(0);
    Q.push(s);
    
    while(!Q.empty())
    {
      node* u = Q.top();
      Q.pop();
      if(u->isVisited()) continue;
      u->setVisited();
      cout<<"pop: "<<u->getKey()<<" dist = "<<u->getDistance()<<endl;
      printDistance();
      
      for(auto& v : u->getChildren())
      {
        if(!v->isVisited() && v->getDistance() > getW(u->getKey(),v->getKey()))
        {
          cout<<"rilasso"<<endl;
          v->setDistance(getW(u->getKey(),v->getKey()));
          updateQ(Q,v);
        } 
      }
    
    }
  }
  
  void Stampa()
  {
    ofstream out("out.txt");
    out<<"PRIM"<<endl;
    for(auto& v : V)
    {
      out<<"v: "<<v->getKey()<<" d = "<<v->getDistance()<<endl;
    }
    
    out.close();
  
  }
  
};



int main()
{
  
  Graph<int> G;
  G.popola();
  G.prim(1);
  G.Stampa();
  return 0;
}
