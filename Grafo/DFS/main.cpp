/*
  Leggere dal file in.txt e scrivere nel file out.txt il risultato
  Implementare DFS
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
#define temp template<typename T>


enum class Color
{
  WHITE,
  GRAY,
  BLACK
};


temp
class Node
{
  T data;
  int key;
  vector<Node*> adj;
  Color color;
  int distance;
  int start;
  int end;
  
  public:
  Node(T data,int key){this->data = data; this->key = key; color = Color::WHITE;}
  
  int  getKey(){return key;}
  int  getDistance(){return distance;}
  Color  getColor(){return color;}
  vector<Node*> getAdj(){return adj;}
  
  void setDistance(int newDist){distance = newDist;}
  void setColor(Color color){this->color = color;}
  void setStart(int st){start = st;}
  void setEnd(int en){end = en;}
  void addChild(Node *& ch){adj.push_back(ch);}
};

temp
class Edge
{
  pair<Node<T>*,Node<T>*> edge;
  int W;
  
  public:
  Edge(Node<T>*& x,Node<T>*& y,int w){edge.first = x; edge.second = y; x->addChild(y); W = w;}
  Node<T>* getX(){return edge.first;}
  Node<T>* getY(){return edge.second;}
  int getW(){return W;}
  
};


temp
class Graph
{
  vector<Edge<T>*> E;
  vector<Node<T>*> V;
  
  public:
  Node<T>* exist(int key)
  {
    for(auto v : V)
    {
      if(v->getKey() == key)
      {
        return v;
      }
    }
    return nullptr;
  }
  
  Node<T>* addNode(T data,int key)
  {
    Node<T>* nodo;
    if(!(nodo = exist(key)))
    {
      nodo = new Node<T>(data,key);
      V.push_back(nodo);
      return nodo;
    }
    
    return nodo;
  }
  
  void addEdge(int key,T data,int key2,T data2,int W)
  {
    Node<T>* x = addNode(data,key);
    Node<T>* y = addNode(data2,key);
    
    Edge<T>* xy = new Edge<T>(x,y,W);
    E.push_back(xy);
    
  }
  
  void populate()
  {
    ifstream in("in.txt");
    int key,key1,w;
    T data1,data2;
    while(in>>key>>key1>>w)
    {
      this->addEdge(key,data1,key1,data2,w);
    }
  
  }
  
  //DFS
  void dfs_visit(Node<T>*& x,int &TIME,ofstream &out)
  {
    
    TIME++;
    x->setStart(TIME);
    x->setEnd(TIME);
    x->setColor(Color::GRAY);
    out<<x->getKey()<<" start"<<endl;
    
    for(auto &v : x->getAdj())
    {
      if(v->getColor() == Color::WHITE)
      {
        dfs_visit(v,TIME,out);
      }
    }
    out<<x->getKey()<<" end"<<endl;
    TIME++;
    x->setColor(Color::BLACK);
    x->setEnd(TIME);
  }
  
  void dfs()
  {
    for(auto &v: V)
    {
      v->setStart(0);
      v->setEnd(0);
      v->setColor(Color::WHITE);
    }
    int time = 0;
    ofstream out("out.txt");
    out<<"inizio"<<endl;
    for(auto &v: V)
    {
      if(v->getColor() == Color::WHITE)
      {
        dfs_visit(v,time,out);
      }
    }
  }
  
  
};

int main()
{
  Graph<int> g;
  g.populate();
  g.dfs();
  return 0;
}
