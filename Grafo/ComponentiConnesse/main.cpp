/*
  Data Creazione 13/05/2025 09:18 
  Dato un grafo G scrivere un algoritmo che trovi le componenti connesse del grafo e le stampi a video
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
using namespace std;
#define TEMPLATE template<typename T>


//Colore del nodo
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
  vector<Node*> adj;
  int key;
  Color color;
  
  public:
    Node(int k){key = k;}
    
    //Getter
    vector<Node*> getAdj(){return adj;}
    int getKey(){return key;}
    Color getColor(){return color;}
    
    //Setters
    void addChild(Node*& ch){adj.push_back(ch);}
    void setColor(Color col){color = col;}
    
};
#define node  Node<T>*

TEMPLATE 
class Edge
{
  pair<node,node> edge;
  int W;
  
  public:
    Edge(node &x,node &y ){edge.first = x; edge.second = y;}
    node getX(){return edge.first;}
    node getY(){return edge.second;}
};


TEMPLATE
class Graph
{
  vector<node> V;
  vector<Edge<T>*> E;
  
  public:
  Graph(){}
  node searchNode(int key)
  {
    //Cerco il nodo
    for(auto v : V)
    {
      if(v->getKey() == key)
      {
        return v;
      }
    }
    
    //Il nodo non è stato trovato
    node newNode = new Node<T>(key);
    V.push_back(newNode);
    return newNode;
  }
  
  void addEdge(int key,int key2)
  {
    node x = searchNode(key);
    node y = searchNode(key2);
    
    x->addChild(y);
    Edge<T> *edge = new Edge<T>(x,y);
    E.push_back(edge);
  }
  
  void popola()
  {
    ifstream in("in.txt");
    
    int key1,key2;
    while(in>>key1>>key2)
    {
      cout<<"Sto aggiungendo: "<<key1<<" e "<<key2<<endl;
      addEdge(key1,key2);
    }
  }

  Graph Trasposta()
  {
    Graph G;
    
    for(auto e : E)
    {
       G.addEdge(e->getY()->getKey(),e->getX()->getKey());
    }
    
    return G;
  }
  
  void dfs_visit(node &v,stack<node> &S)
  {
    v->setColor(GRAY);
    
    for(auto& c : v->getAdj())
    {
      if(c->getColor() == WHITE)
      {
        dfs_visit(c,S);
      }
    }
    
    v->setColor(BLACK);
    S.push(v);
  }
  void dfs(stack<node>& S)
  {
    for(auto& v : V)
    {
      v->setColor(WHITE);
    }
    
    for(auto& v : V)
    {
      if(v->getColor() == WHITE)
      {
        dfs_visit(v,S);
      }
    }
  }
  
  void dfs2(Graph &G,node &u,ofstream &out)
  {
   //node uConverted = G.searchNode(u->getKey());
    u->setColor(GRAY);
    
    for(auto& v : u->getAdj())
    {
      if(v->getColor() == WHITE)
      {
         out<<"key: "<<v->getKey()<<endl;
         dfs2(G,v,out);
      }
    }
    
    u->setColor(BLACK);
    
  }
  
  
  void componentiConnesse()
  {
    ofstream out("out.txt");
    //DFS con salvataggio nodi nello stack
    stack<node> S;
    dfs(S);
    
    //Trasposta del grafo G
    Graph G = Trasposta();
    
    //Estrazione componenti connesse
    int i = 0;
    while(!S.empty())
    {
      node u = G.searchNode(S.top()->getKey());
      
      if(u->getColor() == WHITE)
      {
        i++;
        out<<"Ho trovato la componente connessa: "<<i<<endl<<"key: "<<u->getKey()<<endl;
        dfs2(G,u,out);
      }
      
      S.pop();
    }
    out.close();
  }

};

int main()
{
  Graph<int> G;
  G.popola();
  G.componentiConnesse();
  
}


