/*
  Data di creazione: 18/05/2025
  Dato in input un file contenente un albero binario di ricerca, inserire gli elementi in modo preorder. Successivamente considerare che l'albero dato sia un albero 
  di huffman e data una stringa in input effettuare la codifica e decodifica.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;
#define TEMPLATE template<typename T, typename S>

TEMPLATE
class Node
{
  T key;
  S value;
  Node* left;
  Node* right;
  Node* father;
  
  public:
  Node(T key, S value) : key(key), value(value){left = nullptr; right = nullptr; father = nullptr;}
  T getKey(){return key;}
  S getValue(){return value;}
  Node* getLeft(){return left;}
  Node* getRight(){return right;}
  Node* getFather(){return father;}
  
  
  void setLeft(Node*& l){left = l;}
  void setRight(Node*& r){right = r;}
  void setFather(Node*& f){father = f;}
};
#define node Node<T,S>

TEMPLATE
class Abr
{
  node* root;
  map<char,string> characterMap;
  
  public:
  Abr(){root = nullptr;}
  node* insert(T key, S value)
  {
    node* newNode = new node(key,value);
    cout<<"Inserimento di "<<newNode->getKey()<<" "<<newNode->getValue()<<endl;
    //App = currentNode
    node* app = root;
    //y = padre del nuovo
    node* y = nullptr;
    
    while(app != nullptr)
    {
      y = app;
      if(y->getKey() <= key)
      {
        cout<<"Vado a destra"<<endl;
        app = app->getRight();
      }else
      {
        cout<<"Vado a sinistra"<<endl;
        app = app->getLeft();
      }
    }
    
    if(!y)
    {
      cout<<"Va nella radice"<<endl;
      root = newNode;
      return newNode;
    }else if(y->getKey() > key)
    {
      y->setLeft(newNode);
    }else
    {
      y->setRight(newNode);
    }
    newNode->setFather(y);
    return newNode;
  }
  
  void preorder(vector<node*>& V,node*& x)
  {
    if(x)
    {
      V.push_back(x);
      node* l = x->getLeft();
      node* r = x->getRight();
      preorder(V,l);
      preorder(V,r);
    }
    
  }
  
  //Stampa in preorder
  void print()
  {
    ifstream in("in.txt");
    ofstream out("out.txt");
    vector<node*> V;
    T key; S value;
    while(in>>key>>value)
    {
      cout<<"Procendo con "<<key<<" "<<value<<endl;
      insert(key,value);
    }
    
    //Stampa
    preorder(V,root);
    for(auto& v : V)
    {
      out<<v->getKey()<<" "<<v->getValue()<<endl;
    }
    out.close();
  }
  
  void inizializzaMappa(map<S,string> &characterMap,node*& x,string codifica)
  {
    if(x)
    {
      if(x->getValue() != '*')
      {
        S character = x->getValue();
        characterMap[character] = codifica;
        cout<<"Codifica ottenuta per "<<x->getValue()<<" = "<<codifica<<endl;
        return;
      }
      node* l = x->getLeft();
      node* r = x->getRight();
      if(l) inizializzaMappa(characterMap,l,codifica + "0");
      if(r) inizializzaMappa(characterMap,r,codifica + "1");
    }
  }
  
  
  string codifica(string text)
  {
    map<S,string> chMap;
    string cod = "";
    inizializzaMappa(chMap,root,cod);
    ofstream out("outCodifica.txt");
    out<<"Codifica di "<<text<<" = "<<endl;
    string outCod = "";
    for(auto c : text)
    {
      if(c == ' ') continue;
      out<<c<<" -> "<<chMap[c]<<endl;
      outCod += chMap[c];
    }
    
    out.close();
    return outCod;
  }
  
  void find(node*& x,char &key,char c)
  {
    if(x->getValue() != '*')
    {
      key = x->getValue();
      //cout<<x->getValue()<<endl;
      x = root;
    }else
    {
      key = '*';
    }
    
    if(c == '0')
    {
      x = x->getLeft();
    }else
    {
      x = x->getRight();
    }
 }

  string decodifica(string codText)
  {
    string dec = "";
    node* x = root;
    S key;
    for(auto c : codText)
    {
      find(x,key,c);
      if(key != '*')dec += key;
      //cout<<"key = "<<key<<endl;
    }
    
    return dec;
  }

};


int main()
{
  Abr<int,char> a;
  a.print();
  string text = a.codifica("cicihic cicihi cicicihi");
  string dec = a.decodifica(text);
  cout<<"dec = "<<dec<<endl;
  ofstream out("CodDec.txt");
  out<<"codifica di cicihic cicihi cicicihi = "<<text<<" decodifica = "<<dec<<endl;
  out.close();
}
