#include "main.h"

class imp_res : public Restaurant
{
public:
  class Queue {
  // public:
  //     class customer {
  //     public:
  //         string name;
  //         int energy;
  //         customer* prev;
  //         customer* next;
  //     public:
  //         customer() {}
  //         customer(string na, int e, customer* p, customer* ne) : name(na), energy(e), prev(p), next(ne) {}
  //         ~customer() {
  //             delete prev;
  //             delete next;
  //         }
  //         void print() {
  //             cout << name << " "<< energy << endl;
  //         }
  //     };
  
  private:
      customer* front;  // Node đầu hàng đợi
      customer* rear;   // Node cuối hàng đợi
      int maxQueue;      // Kích thước tối đa của hàng đợi
      int currentSize;  // Kích thước hiện tại của hàng đợi
      int pCount;
      int nCount;
      int n;
  public:
      Queue(int size) : front(nullptr), rear(nullptr), maxQueue(size), currentSize(0) , pCount(0), nCount(0), n(0){}
  
      ~Queue() {
          while (!empty()) {
              pop();
          }
      }
  
      bool empty() {
          return (front == nullptr);
      }
  
      bool isFull() {
          return (currentSize == maxQueue);
      }
  
      void push(string name, int energy) {
          // Kiểm tra xem hàng đợi đã đầy chưa
          if (isFull()) {
              return;
          }
  
          // Kiểm tra xem có phần tử có cùng name trong hàng đợi hay không
          customer* temp = front;
          while (temp != nullptr) {
              if (temp->name == name) {
                  return;
              }
              temp = temp->next;
          }
  
          // Thêm phần tử vào hàng đợi
          customer* newCustomer = new customer(name, energy, nullptr, nullptr);
          if (rear == nullptr) {
              front = rear = newCustomer;
          }
          else {
              rear->next = newCustomer;
              newCustomer->prev = rear;
              rear = newCustomer;
          }
          if(energy>0){
            pCount++;
          }else{
            nCount++;
          }
          currentSize++;
      }
  
      void pop() {
          if (empty()) {
              return;
          }
  
          customer* temp = front;
        int energy=temp->energy;
          if(energy>0){
            pCount--;
          }else{
            nCount--;
          }
          if (front == rear) {
              front = rear = nullptr;
          }
          else {
              front = front->next;
              front->prev = nullptr;
          }
  
          delete temp;
          currentSize--;
        
      }
  
      void printQueue() {
          if (empty()) {
              return;
          }
  
          customer* temp = front;
          while (temp != nullptr) {
              temp->print();
              temp = temp->next;
          }
      }
    customer* top() {
      if (empty()) {
          return nullptr;
      }
      return front;
    }
    void shellSort(customer* start, customer* end) {
          if (empty() || start == nullptr || end == nullptr || start == end) {
              return;
          }
  
          // Tìm khoảng cách ban đầu giữa các phần tử
          int gap = 0;
          customer* temp = start;
          while (temp != nullptr && temp != end) {
              gap++;
              temp = temp->next;
          }
  
          // Áp dụng thuật toán shellsort
          while (gap > 0) {
              for (customer* i = start; i != nullptr && i != end; i = i->next) {
                  customer* j = i;
                  while (j != nullptr && j != end && j->energy < j->prev->energy) {
                      swap(j->energy, j->prev->energy);
                      swap(j->name, j->prev->name);
                      j = j->prev;
                    n++;
                  }
              }
              gap /= 2;
          }
      }
  int getTimeSort(){
    return n;
  }
  void removeNeg() {
        customer* current = front;
        customer* prev = nullptr;

        while (current != nullptr) {
            if (current->energy < 0) {
                if (prev == nullptr) {
                    front = current->next;
                } else {
                    prev->next = current->next;
                }

                if (current == rear) {
                    rear = prev;
                }

                customer* temp = current;
                current = current->next;
                delete temp;

                currentSize--;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
  void removePos() {
        customer* current = front;
        customer* prev = nullptr;

        while (current != nullptr) {
            if (current->energy > 0) {
                if (prev == nullptr) {
                    front = current->next;
                } else {
                    prev->next = current->next;
                }

                if (current == rear) {
                    rear = prev;
                }

                customer* temp = current;
                current = current->next;
                delete temp;

                currentSize--;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
    int getnumPos(){
      return pCount;
    }
    int getnumNeg(){
      return nCount;
    }
  };
private:
    int current;
    customer *s;
    customer *e;
    customer *x;//vi tri x nguoi cuoi cung thay doi
    Queue *q;
    int MAXSIZE;
	public:	
		imp_res() {
      current=0;
      s=nullptr;
      e=nullptr;
      x=nullptr;
      MAXSIZE=30;
      q=new Queue(MAXSIZE);
    }
    ~imp_res() {
      delete s;
      delete e;
      delete x;
      delete q;
    }

//bien tam toi khi code chua sua
    // void setMaxSize(int maxsize){
    //   MAXSIZE=maxsize;
    // }
//



		void RED(string name, int energy)
		{
      if(energy==0)return;
      if(current==0){
        customer *cus = new customer(name, energy, nullptr, nullptr);
        x = cus;
        s = cus;
        e = cus;
      }else{
        if(current>=MAXSIZE){
          if(!q->empty()){
            q->push(name,energy);
          }
          return;
        }else if(current>=MAXSIZE/2){
          customer*temp=s, *changeCus=s;//changeCus: vi tri doi
          int change=0;
          do{
            if(change<abs(energy-temp->energy)){
              change=abs(energy-temp->energy);
              changeCus=temp;
            }
            temp=temp->next;
          }while(temp!=s);
          if(energy-changeCus->energy<0){
            temp=changeCus->prev;
            customer*a=new customer (name, energy, temp, changeCus);
            //cap nhat gia tri truoc va sau
            changeCus->prev=a;
            if(temp!=nullptr){
              temp->next=a;
            }else{
              s=a;
            }
            x=a;
          }else{
            temp=changeCus->next;
            customer*a=new customer (name, energy, changeCus, temp);
            //cap nhat gia tri truoc va sau
            changeCus->next=a;
            if(temp!=nullptr){
              temp->prev=a;
            }else{
              e=a;
            }
            x=a;
          }
        }
        else{
          int pow_val = x->energy;
          if (energy >= pow_val) {
            // customer *temp = x->next;
            // customer *a = new customer(name, energy, x, temp);
            // // Cập nhật giá trị trước và sau
            // x->next=a;
            // if (temp != nullptr) {
            //   temp->prev = a;
            // } else {
            //   e = a;
            //   a->next = s;
            // }
            // if (current == 1) {
            //   x->prev=a;
            // }
            // x=a;
          } else {
            customer *temp = x->prev;
            customer *a = new customer(name, energy, temp, x);
            // Cập nhật giá trị trước và sau
            x->prev = a;
            if (temp != nullptr) {
              temp->next = a;
            } else {
              s = a;
              a->prev = e;
            }
            if (current == 1) {
              x->next = a;
            }
            x = a;
          }
        }

        
      }
			current++;
		}
    
void BLUE(int num) {
    if (current <= 0) return;
    if (num >= current || num >= MAXSIZE) {
        customer* currentPtr = s;
        do {
            customer* k = currentPtr;
            currentPtr = currentPtr->next;
            delete k;
        }while (currentPtr != s);
        s = nullptr;
        current = 0;
        delete e;
        e = nullptr;
        return;
    }
    while (num--) {
        customer* nextPtr = s->next;
        delete s;
        s = nextPtr;
        current--;
    }
}
		void PURPLE()
		{
			customer*temp=s, *changeCus=s;//changeCus: vi tri doi
          int change=0;
      do{
          if(change<abs(temp->energy)){
              change=abs(temp->energy);
              changeCus=temp;
          }
        temp=temp->next;
		  }while(temp!=s);
      q->shellSort(s, changeCus);
      BLUE(MAXSIZE%q->getTimeSort());
    }

    /* ham phu reversal*/

    //nho check lai
	void REVERSAL() {
    if (s == nullptr || e == nullptr) return;
    int ip = 1, jp = MAXSIZE, in = 1, jn = MAXSIZE;
    customer* ps = s, * pe = e, * ns = s, * ne = e;

    // Đổi chỗ các giá trị năng lượng giữa các cặp năng lượng dương/dương và âm/âm
    do {
        if (ps->energy > 0 && pe->energy > 0) {
            swap(ps->energy, pe->energy);
            ps = ps->next;
            pe = pe->prev;  // Sử dụng con trỏ prev thay vì next để di chuyển từ cuối đến đầu
            ip++;
            jp--;
        }
        else if (ps->energy > 0 && pe->energy < 0) {
            pe = pe->prev;
            jp--;
        }
        else if (ps->energy < 0 && pe->energy > 0) {
            ps = ps->next;
            ip++;
        }
        else {
            ps = ps->next;
            pe = pe->prev;
            ip++;
            jp--;
        }
    } while (ps != s && pe != e && ip < jp && ip <= MAXSIZE && jp >= 1);

    // Di chuyển con trỏ ns và ne để tránh các giá trị dương
    do {
        if (ns->energy < 0 && ne->energy < 0) {
            swap(ns->energy, ne->energy);
            ns = ns->next;
            ne = ne->prev;  // Sử dụng con trỏ prev thay vì next để di chuyển từ cuối đến đầu
            in++;
            jn--;
        }
        else if (ns->energy < 0 && ne->energy > 0) {
            ne = ne->prev;
            jn--;
        }
        else if (ns->energy > 0 && ne->energy < 0) {
            ns = ns->next;
            in++;
        }
        else {
            ns = ns->next;
            ne = ne->prev;
            in++;
            jn--;
        }
    } while (ns != nullptr && ne != nullptr && in < jn && in <= MAXSIZE && jn >= 1);
}
		void UNLIMITED_VOID()
		{
    		if(s==nullptr||e!=nullptr)return;
        customer* start=s;
        long long minSum = 1e17;
        int maxLength = 0;
        customer* bestStart = nullptr;
    
        customer* currentStart = start;
        customer* currentEnd = start;
        int currentSum = 0;
        int currentLength = 0;
    
        do{
            if (currentSum <= minSum && currentLength >= 4 && currentLength > maxLength) {
                minSum = currentSum;
                maxLength = currentLength;
                bestStart = currentStart;
        }while (currentStart != start && currentEnd != start) 
    
            currentSum += currentEnd->energy;
            currentLength++;
            currentEnd = currentEnd->next;
    
            if (currentLength > maxLength) {
                minSum = currentSum;
                maxLength = currentLength;
                bestStart = currentStart;
            }
    
            if (currentLength >= 4) {
                currentSum -= currentStart->energy;
                currentLength--;
                currentStart = currentStart->next;
            }
        } while (currentStart != start && currentEnd != start);
    
        if (bestStart != nullptr) {
            for (int i = 0; i < maxLength; i++) {
                cout << bestStart->name << "-" << bestStart->energy << endl;
                bestStart = bestStart->next;
            }
        }

		}
		void DOMAIN_EXPANSION()
		{
			customer*start=s;
      long long sp=q->getnumPos(),sn=q->getnumNeg();
      do{
        if(start->energy>0){
          sp+=start->energy;
        }else{
          sn+=start->energy;
        }
        start=start->next;
      }while(start!=s);
      if(sp>=sn){
        start=s;
        q->removeNeg();
        do{
          if(start->energy<0){
            cout<<start->name<<"-"<<start->energy;
            if(!q->empty()){
              customer*tp=q->top();
              q->pop();
              swap(start->energy,tp->energy);
            }else{
              current--;
              customer*b=start->prev;
              customer*i=start->next;
              customer*temp=start;
              delete temp;
              if(b!=nullptr){
                b->next=i;
              }
              if(i!=nullptr){
                i->prev=b;
              }
            }
          }
          start=start->next;
        }while(start!=s);
      }else{
        current--;
        start=s;
        q->removePos();
        do{
          if(start->energy>0){
            cout<<start->name<<"-"<<start->energy;
            if(!q->empty()){
              customer*tp=q->top();
              q->pop();
              swap(start->energy,tp->energy);
            }else{
              customer*b=start->prev;
              customer*i=start->next;
              customer*temp=start;
              delete temp;
              if(b!=nullptr){
                b->next=i;
              }
              if(i!=nullptr){
                i->prev=b;
              }
            }
          }
          start=start->next;
        }while(start!=s);
      }
		}
    void printRight(customer* start) {
      customer* current = start;
      do{
          current->print();
          current = current->next; 
      } while (current != start);
      cout<<3;
    }
    void printReserve(customer* end) {
      customer* current = end;
      do{
          current->print();
          current = current->prev;
      }while(current!=end);
    }
		void LIGHT(int num)
		{
			if(num==0){
        q->printQueue();
        return;
      }
      if(num<0){
        printReserve(x);
      }else{  
        printRight(x);
      }
		}
};