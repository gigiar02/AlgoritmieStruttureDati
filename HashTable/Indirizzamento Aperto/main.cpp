/*
  Data di creazione: 19/05/2025 orario: 09:09
  Realizzare un hash table ad indirizzamento aperto con funzione di hash h(k) = (k % m). Si prenda  da file "in.txt" le chiavi con i relativi valori e in out.txt andare 
  a scrivere il contenuto della hash e un esempio di find e delete
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
#define TEMPLATE template<typename T,typename S>

TEMPLATE
class Element
{
  T key;
  S value;
  
  public:
  Element(T key, S value) : key(key), value(value){}
  T getKey(){return key;}
  S getValue(){return value;}
};

TEMPLATE
class HashTable
{
  vector<Element<T,S>*> table;
  int m;
  
  public:
  HashTable(int m){this->m = m; table.resize(m,nullptr);}
  T hashFunction(T key)
  {
    return (key % m);
  }
  
  
  bool insertElement(Element<T,S> *el)
  {
    T key = el->getKey();
    int i = 0;
    while(i < m)
    {
      T h = hashFunction(key + i);
      if(table[h] == nullptr)
      {
        table[h] = el;
        cout<<"Inserimento el "<<table[h]->getKey()<<" "<<table[h]->getValue();
        cout<<" cella: "<<h<<endl;
        return true;
    }
      i++;
    }
    
    return false;
  }
  
  
  Element<T,S>* findElement(T key)
  {
    T h = hashFunction(key);
    int i = 0;
    while(i < m)
    {
      if(table[h])
      {
        //cout<<"Trovato "<<table[h]->getKey()<<" "<<table[h]->getValue()<<" cella: "<<h<<"key = "<<key<<endl;
        if(table[h]->getKey() == key){return table[h];}
      }
      i++;
      h = hashFunction(key + i);
      //cout<<"Non trovato cella: "<<h<<endl;
    }
    
    return nullptr;
    
  }
  
  
  bool deleteElement(int key)
  {
    T h = hashFunction(key);
    int i = 1;
    while(i < m)
    {
      if(table[h]->getKey() == key)
      {
        table[h] = nullptr;
        return true;
      }
      h = hashFunction(key + i);
      i++;
    }
    return false;
  }
  
  
  void print()
  {
    ofstream out("out.txt");
    for(auto t : table)
    {
      if(!t) continue;
      out<<t->getKey()<<" "<<t->getValue()<<endl;
    }
    
    //Ricerco una chiave
    Element<T,S> *el = findElement(2);
    out<<"Ricerca della chiave 2: "<<endl;
    if(el)
    {
      out<<"Ricerca andata a buon fine "<<el->getKey()<<el->getValue()<<endl;
    }else
    {
      out<<"Ricerca non andata a buon fine"<<endl;
    }
    
    cout<<"Elimino 2"<<endl;
    if(deleteElement(2))
    {
      out<<"Eliminato con successo"<<endl;
    }
  }
};


int main()
{
  ifstream in("in.txt");
  int key;
  char value;
  HashTable<int,char> t(10);
  
  while(in>>key>>value)
  {
    Element<int,char> *el = new Element<int,char>(key,value);
    if(!t.insertElement(el)){cout<<"Spazio finito"<<endl;}
  }
  
  t.print();
  
  


}
