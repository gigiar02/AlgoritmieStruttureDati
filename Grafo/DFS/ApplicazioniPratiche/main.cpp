/*
  Data di creazione: 19/05/2025 orario: 17:11
  Implementare dfs topologica. Classificare gli archi.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;
#define TEMPLATE  template<typename T>
int indietro = 0;
int avanti = 0;
int trasversale = 0;
int albero = 0;

enum Color
{
  WHITE,
  GRAY,
  BLACK
};

TEMPLATE
class Node
{
  T data;
  int key;
  Color color;
  vector<Node*> children; 
  int start;
  int end;
  
  public:
  Node(int key) : key(key){}
  int getKey(){return key;}
  int getStart(){return start;}
  int getEnd(){return end;}
  vector<Node*> getChildren(){return children;}
  Color getColor(){return color;}
  
  void addChild(Node* ch){children.push_back(ch);}
  void setColor(Color col){color = col;}
  void setStart(int s){start = s;}
  void setEnd(int e){end = e;}
  
};
#define node Node<T>

TEMPLATE
class Edge
{
  pair<node*,node*> edge;
  int W;
  
  public:
  Edge(node* x, node* y,int w){x->addChild(y); edge.first = x; edge.second = y; W = w;}
  node* getX(){return edge.first;}
  node* getY(){return edge.second;}
  int getW(){return W;}
  
};
#define edge Edge<T>


TEMPLATE
class Graph
{
  vector<node*> V;
  vector<edge*> E;
  
  public:
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
  
  edge* addEdge(int key1,int key2,int W)
  {
    node* x = searchNode(key1);
    node* y = searchNode(key2);
    
    edge* ed  = new edge(x,y,W);
    E.push_back(ed);
    return ed;
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
  
  void dfsVisit(node* u,stack<node*> &s,int &time)
  {
    u->setColor(GRAY);
    time+=1;
    u->setStart(time);
    cout<<"Visito u: "<<u->getKey()<<endl;
    
    for(auto& v : u->getChildren())
    {
      if(v->getColor() == WHITE)
      {
        albero+=1;
        cout<<u->getKey()<<" -> "<<v->getKey()<<" albero"<<endl;
        dfsVisit(v,s,time);
      }else if(v->getColor() == GRAY)
      {
        indietro+=1;
        cout<<u->getKey()<<" -> "<<v->getKey()<<" indietro"<<endl;
      }else if(v->getColor() == BLACK)
      {
        if(u->getStart() >= v->getStart())
        {
          trasversale++;
          cout<<u->getKey()<<" -> "<<v->getKey()<<" trasversale"<<endl;
        }else
        {
          avanti++;
          cout<<u->getKey()<<" -> "<<v->getKey()<<" avanti"<<endl;
        }
      }
    }
    
    u->setColor(BLACK);
    time+=1;
    u->setEnd(time);
    s.push(u);
    cout<<"Fine visita u: "<<u->getKey()<<endl;
    
  }
  
  void dfs()
  {
    for(auto& v : V)
    {
      v->setColor(WHITE);
      v->setStart(0);
      v->setEnd(0);
    }
    int time = 0;
    int i = 0;
    stack<node*> s;
    for(auto& v : V)
    {
      if(v->getColor() == WHITE)
      {
        i++;
        cout<<"Albero: "<<i<<endl;
        dfsVisit(v,s,time);
      }
    }
    
    ofstream out("out.txt");
    out<<"Visita topologica"<<endl;
    
    while(!s.empty())
    {
      node* v = s.top();
      s.pop();
      out<<"key: "<<v->getKey()<<" start: "<<v->getStart()<<" end "<<v->getEnd()<<endl;
    }

   }

};

int main()
{
  Graph<int> G;
  G.popola();
  G.dfs();
}
