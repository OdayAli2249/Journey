#include<iostream>

using namespace std;

class Queue{       // Building a queue class

private:

int Q[50];        // queue
int Front;        // Variable to point at the top of the queue

public:

Queue(){          // Constructor

Front = 0;

}

bool Enq(int Val){    // Adding at the end of queue

    if(Front >= 50)
        return false;

    Q[Front] = Val;
    Front++;
    return true;


}

int Deq(){          // Deleting from the top of queue

    if(IsEmp())
        return -1;

        int deq = Q[0];
     for(int i = 1 ; i<Front ; i++)
           Q[i-1] = Q[i];
     Front--;
    return deq;

}

bool IsEmp(){          // Check if the queue is EMPTY

     return Front == 0;

}

};

struct Hyperlink{    // structure of the branch node

int Address;
int Weight;

struct Hyperlink *NextH;

};

struct Node{

int Address;

struct Node *NextN;
struct Hyperlink *NextH;

};


struct Node *Head = NULL;


void Build(int NodeNumbers,int EdgeNumbers){

    struct Node *Curr = NULL ;
    struct Node *NewN = NULL;
    struct Hyperlink *NewH = NULL;

    int NodeNumber,EdgeNumber;
    int ConnectionNode,Weight;

    for(int i = 0 ; i<NodeNumbers ; i++){

            NewN = new struct Node;
            NewN->Address = NodeNumbers-i;
            NewN->NextH = NULL;
            NewN->NextN = Head;
            Head = NewN;

    }

    for(int i = 0 ; i<EdgeNumbers ; i++){

        Curr = Head;
        cin >> NodeNumber;
        while(Curr->Address != NodeNumber && Curr != NULL)
           Curr = Curr->NextN;
           cin >> ConnectionNode;
           cin >> Weight;
           NewH = new struct Hyperlink;
           NewH->Address = ConnectionNode;
           NewH->Weight = Weight;
           NewH->NextH = Curr->NextH;
           Curr->NextH = NewH;

    }

}


struct Node *Search(int Adr);
int Dijkstraa(int Res[],int Size);


int main(void){

int nodenumbers,edgenumbers;

cin >> nodenumbers;
cin >> edgenumbers;

int Result[nodenumbers],result;

Build(nodenumbers,edgenumbers);
result = Dijkstraa(Result,nodenumbers);

if(result == 100000){
    cout << endl << -1 << endl;
}else cout << endl << result << endl;


return 0;
}


struct Node *Search(int Adr){

    struct Node *Curr = Head;

    while(Curr->Address != Adr && Curr != NULL)
        Curr = Curr->NextN;

    return Curr;

}


int Dijkstraa(int Res[],int Size){

int Visited[Size];
int StartingPoint,Distnation;
int CurrAddress;
int Time;
int Counter = 0;

struct Node *CurrNode = NULL;
struct Hyperlink *CurrHyperlink = NULL;

Queue Qu;

cin >> StartingPoint;
cin >> Distnation;

    for(int i = 0 ; i<Size ; i++){

          Visited[i] = false;
          if(i == StartingPoint-1)
            Res[i] = 0;
          else
          Res[i] = 100000;

    }


    Qu.Enq(StartingPoint);

    while(!Qu.IsEmp() && Counter < 100){

       CurrAddress = Qu.Deq();
       //cout << CurrAddress;

       if(!Visited[CurrAddress-1]){

            Visited[CurrAddress-1] == true;
            CurrNode = Search(CurrAddress);
            CurrHyperlink = CurrNode->NextH;

            while(CurrHyperlink != NULL){
            if(!Visited[(CurrHyperlink->Address)-1])
               Qu.Enq(CurrHyperlink->Address);

               Time =(Res[CurrAddress-1]%2 == 0 )?(Res[CurrAddress-1]):(Res[CurrAddress-1]+1);

               if(Res[(CurrHyperlink->Address)-1] > Time +(CurrHyperlink->Weight)){

                   Res[(CurrHyperlink->Address)-1] = Time +(CurrHyperlink->Weight);
                   if(Visited[(CurrHyperlink->Address)-1] == true){
                    Visited[(CurrHyperlink->Address)-1] = false;
                    Qu.Enq(CurrHyperlink->Address);
                   }

               }

               CurrHyperlink = CurrHyperlink->NextH;

          }

       }

       Counter++;

    }

    return Res[Distnation-1];

}
