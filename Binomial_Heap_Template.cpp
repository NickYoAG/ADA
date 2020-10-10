#include<iostream>
#include<fstream>
#include<list>

using namespace std;

template<class T>
class NodoB
{
     typedef NodoB<T> *    pNodo;
     public:
       T                   m_Value;
       list< pNodo  >      m_Sons;
       int          	     m_Grade;   
       pNodo               m_Father;
     public:
       NodoB(T value)
       {
            m_Value=value;
            m_Grade=0;
            m_Father =0;
       }
          
};

template<class T>
class BinomialHeap{
  typedef NodoB<T> *    pNodo;
   public:
      list<pNodo>    m_Heap;
      int            m_Size;
      pNodo		       m_Min;	
    public:
      BinomialHeap(){
        m_Size=0;
	      m_Min = 0;
      }
      void size(){
        return m_Heap.size();
      }

      // T(n) = O(logn)
      void Merge(){ // Tarea  //     Colocar el mínimo en la posición correcta
        int op=0;
        while(op==0){
          int cont=0,flag=0; pNodo a, temp;
          if(m_Heap.size()==1) break;
          for(auto nodo : m_Heap){ //log(n)
            for(auto nodo2 : m_Heap){
              if(nodo->m_Value!=nodo2->m_Value){
                if(nodo->m_Grade==nodo2->m_Grade){
                  temp=Unir(nodo, nodo2);
                  m_Heap.remove(temp);
                  cont=0;
                  flag=0;
                  break;
                }
                else{
                  flag=1;
                }
              }  
            }
            if(flag==1){
              flag=0;
              cont++;
            }
            else{
              cont=0;
              break;
            }
          }
          if(cont==m_Heap.size()) op=1;    
        }
      }
      // T(n) = O(logn)
      void Insert(T value)
      {
           pNodo pNew = new NodoB<T>(value);  // O(1)
           m_Heap.push_back(pNew);                // O(1)
           //Merge();                                // O(logn) 
      }

      // T(n) = O(1)
      T GetMin(){ return m_Min->m_Value;}

      void Extract_Min()
      {
            // Subir los hijos a la raiz O)(logm), donde m = número de hijos del nodo (m<=n)
            for(auto nodo : m_Min->m_Sons)
	          m_Heap.push_back(nodo);

            // O(1)
	          m_Heap.remove(m_Min);
            // O(logn)
            Merge();
      }

      //T(n) = O(logn) 
      void Decrease_Key(pNodo p, T value){
           if (p->m_Value > value) return;  // O(1)
           p->m_Value = value;             // O(1)
           // O(logn)
           while(p->m_Father)
           {
                if(p->m_Value < p->m_Father->m_Value)
		            swap(p->m_Value,p->m_Father->m_Value);
                else return;
           }
      }

      // T(n) = O(logn)
      void Delete(pNodo p)
      {
           Decrease_Key(p,-1000000);  // O(logn)
           Extract_Min();             // O(logn)
      }

      // T(n) = O(1)
      pNodo Unir(pNodo p1, pNodo p2)
      {
            // Nota: Retornamos al nodo que será eliminado de la lista de raices del heap
            if(p1->m_Value < p2->m_Value)
            {
                  p1->m_Sons.push_back(p2);
                  p2->m_Father = p1;
                  p1->m_Grade++;
                  return p2;
            }  
            p2->m_Sons.push_back(p1);
            p1->m_Father = p2;
            p2->m_Grade++;
            m_Heap.remove(p1);
            return p1;
            
      };
        
      void printBinomialHeapSons(list<pNodo>a){
        for(auto nodo : a){
          cout<<nodo->m_Value<<" ";
            printBinomialHeapSons(nodo->m_Sons);
        }
      }  
      void printBinomialHeap(BinomialHeap<T> n) 
      { 
          for(pNodo nodo : m_Heap){
            cout<<"Raiz: "<<nodo->m_Value<<" Hijos: ";
            printBinomialHeapSons(nodo->m_Sons);
            cout<<endl;
          }
      } 

};
//LEER IMPORTANTE
//IMPORTANTE-----------------------------------------------------------
//--Profesor, use el Merge al final de los insert, no lo inclui en la misma funcion Insert ya que se demoraba bastante como maximo 3 minutos en mi caso asi sean solo 6 numeros. Lo puse al final en el main porque lo hacia mas rapido. Quizas se deba a mi misma funcion Merge. Usted mismo lo puede comprobar. Disculpe profesor y Gracias.

int main() {
  BinomialHeap<int> A;
  /*A.Insert(10);
  A.Insert(20);
  A.Insert(30);
  A.Insert(40);
  A.Insert(50);
  A.Insert(60);*/
  for(int i=0;i<1000;i++){
     A.Insert(i);}
  A.Merge();
  cout<<endl<<"Raices del Arbol Final"<<endl;
  A.printBinomialHeap(A);
}
