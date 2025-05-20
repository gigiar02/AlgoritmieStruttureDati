/*
  Data di creazione: 19/05/2025 orario: 11:23
  Implementare le hashTable con concatenazione e le relative operazioni. Scrivere il risultato in un file out.txt    
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define TEMPLATE template<typename T,typename S>
using namespace std;


TEMPLATE
class Node
{
  T key;
  S value;
  Node* next;
  Node* precedent;
  
  public:
  Node(T key,S value) : key(key), value(value){next = precedent = nullptr;}
  T getKey(){return key;}
  S getValue(){return value;}
  Node* getNext(){return next;}
  Node* getPrecedent(){return precedent;}
  
  void setNext(Node* n){next = n;}
  void setPrecedent(Node * p){precedent = p;}
};

TEMPLATE
class HashTable
{
  vector<Node<T,S>*> table;
  int m;
  
  public:
  HashTable(int m){this->m = m; table.resize(m,nullptr);}
  T hash(T key)
  {
    return key % m;
  }
  
  void insert(Node<T,S>* element)
  {
    T key = element->getKey();
    T h = hash(key);
    if(!table[h])
    {
      table[h] = element;
      }else
      {
        element->setNext(table[h]);
        table[h]->setPrecedent(element);
        table[h] = element;
        return;
      }
   }
   
   Node<T,S>* find(T key)
   {
      T h = hash(key);
      Node<T,S>* el = table[h];
      while(el)
      {
        if(el->getKey() == key)
        {
          return el;
        }
        el = el->getNext();
      }
      return nullptr;
   }
   
   void deleteEl(T key)
   {
    T h = hash(key);
    Node<T,S>* el = find(key);
    Node<T,S>* precedent = el->getPrecedent();
    Node<T,S>* next = el->getNext();
    
    if(precedent)
    {
      precedent->setNext(next);
    }else
    {
      table[h] = next;
    }
    if(next) next->setPrecedent(precedent);
    free(el);
   }
   
   void print()
   {
      int i = 0;
      while(i < m)
      {
        int h = i;
        i+=1;
        if(table[h])
        {
          cout<<"Analizzo cella: "<<h<<endl;
          Node<T,S>* el = table[h];
          while(el)
          {
            Node<T,S>* n = el->getNext();
            Node<T,S>* p = el->getPrecedent();
            if(n && p)
            {
              cout<<el->getKey()<<" "<<el->getValue()<<" next "<<n->getKey()<<"predecessor "<<p->getKey()<<endl;
            }else if(!n && p)
            {
              cout<<el->getKey()<<" "<<el->getValue()<<" next "<<"null "<<"predecessor "<<p->getKey()<<endl;
            }else if(!p && n)
            {
              cout<<el->getKey()<<" "<<el->getValue()<<" next "<<n->getKey()<<"predecessor "<<"null"<<endl;
            }else
            {
              cout<<el->getKey()<<" "<<el->getValue()<<" next "<<" null "<<"predecessor "<<"null"<<endl;
            }
            el = el->getNext();
          }
        }
      }
   }
    
   
  
};

int main()
{
    HashTable<int,char> h(10);
    
    ifstream in("in.txt");
    int key;
    char c;
    while(in>>key>>c)
    {
      Node<int,char>* el = new Node<int,char>(key,c);
      h.insert(el);
    }
    
    h.print();
    cout<<"Procedo all'eliminazione del nodo con chiave 150 "<<endl;
    h.deleteEl(100);
    
    cout<<"Aggiornamento"<<endl;
    h.print();
}
