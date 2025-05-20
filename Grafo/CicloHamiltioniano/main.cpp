/*
  Data di creazione: 20/05/2025 orario: 09:12
  Traccia: Implementare un grafo in cui andare a caricare i nodi presi dal file in.txt. Successivamente verificare se il grafo è un ciclo hamiltoniano e stampare in 
  out.txt il risultato.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
#define TEMPLATE template<typename T>

enum Color
{
  WHITE,
  GRAY
};


TEMPLATE
class Nodo
{
  T data;
  int key;
  Color color;
  vector<Nodo*> adj;
  
  public:
  Nodo(int key) : key(key){}
  int getKey(){return key;}
  Color getColor(){return color;}
  vector<Nodo*> getChildren(){return adj;}
  
  void addChild(Nodo* ch){adj.push_back(ch);}
  void setColor(Color c){color = c;}
};
#define nodo Nodo<T>


TEMPLATE
class Arco
{
  pair<nodo*,nodo*> edge;
  int w;
  
  public:
  Arco(nodo* x,nodo* y,int w){x->addChild(y); edge.first = x; edge.second = y; this->w = w;}
  nodo* getX(){return edge.first;}
  nodo* getY(){return edge.first;}
  int getW(){return w;}
};
#define arco Arco<T>


TEMPLATE
class Grafo
{
  vector<nodo*> V;
  vector<arco*> E;
  
  public:
  Grafo(){}
  nodo* ricercaNodo(int key)
  {
    //Ricerca del nodo
    for(auto& v : V)
    {
      if(v->getKey() == key) return v;
    }
    
    //Se il nodo non esiste lo creo e lo aggiungo alla lista di vertici del grafo
    nodo* nuovo = new nodo(key);
    V.push_back(nuovo);
    return nuovo;
  }
  
  
  arco* aggiungiArco(int key,int key1,int w)
  {
    nodo* x = ricercaNodo(key);
    nodo* y = ricercaNodo(key1);
    arco* ar = new arco(x,y,w);
    E.push_back(ar);
    return ar;
  }
  
  void popola()
  {
    ifstream in("in.txt");
    int key,key1,w;
    
    while(in>>key>>key1>>w)
    {
      aggiungiArco(key,key1,w);
    }
  }
  
  void stampa()
  {
    for(auto& u : V)
    {
      for(auto& v : u->getChildren())
      {
        cout<<u->getKey()<<" -> "<<v->getKey()<<endl;
      }
    }
  }
  bool verifica(nodo* start,nodo* corrente,int nodiTrovati,ofstream &out)
  {
    corrente->setColor(GRAY);
    if(nodiTrovati < 10) cout<<"nodi Trovati "<<nodiTrovati<<" v: "<<corrente->getKey()<<endl;
    
    for(auto& v : corrente->getChildren())
    {
      if(v->getColor() == GRAY && nodiTrovati == V.size() && v == start)
      {
        return true;
      }else if(v->getColor() == WHITE)
      {
        if(verifica(start,v,nodiTrovati + 1,out)){out<<"Sono "<<v->getKey()<<" Trovato "<<endl; return true;}
      }
    }
    
    corrente->setColor(WHITE);
    return false;
  
  }
  
  
  void CicloHamilton()
  {
    ofstream out("out.txt");
    out<<"Verifica dell' esistenza di un ciclo Hamiltoniano"<<endl;
    cout<<"Size = "<<V.size()<<endl;
    
    for(auto& v : V)
    {
      v->setColor(WHITE);
    }
    
    for(auto& v : V)
    {
      if(v->getColor() == WHITE)
      {
        if(verifica(v,v,1,out)){out<<"Il grafo ha ciclo hamiltoniano"<<endl; out.close(); return;}
      }
    }
    
    out<<"Non esiste nessun ciclo Hamiltoniano all'interno del grafo"<<endl;
    out.close();
  }
};



int main()
{
  Grafo<int> G;
  G.popola();
  G.stampa();
  G.CicloHamilton();
}
