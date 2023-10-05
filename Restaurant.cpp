#include "main.h"

class imp_res : public Restaurant
{
	private:
		int count = 0; // check number customers
		int queued = 0; // check number queued
		customer *res = nullptr; //restaurant customer
		customer *queueing = nullptr; //queueing
		customer *datalog = nullptr; //data of people going in restaurant 
	public:	
		imp_res() {};
		bool namecheck(string name,customer *res,customer *queueing){
			customer *subcheck1 = res;
			customer *subcheck2 = queueing;
			for(int i = 0;i<count;i++){
				if(name == subcheck1->name) return 0;
				subcheck1 = subcheck1->next;
			}
			for(int i = 0;i<queued;i++){
				if(name == subcheck2->name) return 0;
				subcheck2 = subcheck2->next;
			}
			return 1;
		}
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if(energy!=0){ // check people energy
				if(namecheck(name,res,queueing)){ // check the name
					if(count == MAXSIZE){ // check if restaurant full
						if(queued<MAXSIZE){ // check if queue full
							if(queueing = nullptr){
								queueing = cus;
								queued++;
							} else {
								customer *quesub = queueing;
								for(int i = 0;i<queued-1;i++){
									quesub = quesub->next;
								}
								quesub->next = cus;
								queued++;
							}
						}
					} else {
						if (count>=MAXSIZE/2){// case restaurant over half
							customer *tmp1 = res; 
							customer *subspot = tmp1; // spot highest diff
							int maxdiff = 0;
							for(int i = 0;i<count;i++){
								if(abs(energy+tmp1->energy)>maxdiff){
									maxdiff = abs(energy+tmp1->energy);
									subspot = tmp1;
								}
								tmp1 = tmp1->next;
							}
							if(energy+tmp1->energy>=0){ // checking positive or negative
									cus->next = tmp1->next;
									cus->prev = tmp1;
									tmp1->next = cus;
									cus->next->prev = cus;
									res = cus;
							} else {
									cus->prev = tmp1->prev;
									cus->next = tmp1;
									tmp1->prev = cus;
									cus->prev->next = cus;
									res = cus;
							}
						} else {
							if(res == nullptr){ // case that restaurant have no one
								res = cus;
								res->next = res;
								res->prev = res;
								count++;
							} else { // restaurant have people
								if(energy>=res->energy){ // energy >= X
									cus->next = res->next;
									cus->prev = res;
									res->next = cus;
									cus->next->prev = cus;
									res = res->next;
								} else { // energy < X
									cus->prev = res->prev;
									cus->next = res;
									res->prev = cus;
									cus->prev->next = cus;
									res = res->prev;
								}
								count++;
							}
						}
						if(datalog == nullptr){ // put people in datalog case no one
							datalog = cus;
						} else { // case already have pp
							customer *subdata = datalog;
							for(int i = 0;i<count-2;i++){
								subdata = subdata->next;
							}
							subdata->next = cus;
						}
					}
				}
			}
		}
		void BLUE(int num)
		{
			customer *resubb = res;
			cout << "blue "<< num << endl;
			for(int i = 0;i<min(num,count);i++){ // delete people in data & res
				for(int j = 0;j<count;j++){
					if(datalog->name==resubb->name){
						resubb->next->prev = resubb->prev;
						resubb->prev->next = resubb->next;
						count--;
						// delete [] resubb;
						datalog = datalog->next;
					}
				}
			}
			while(queued!=0&&count<MAXSIZE){ // push pp from queue to restaurant
				RED(queueing->name,queueing->energy);
				count++;
				queued--;
				queueing = queueing->next;
			}
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
			if(num==0){
				customer *quesub1 = queueing;
				for(int i = 0;i<queued;i++){
					quesub1->print();
					quesub1 = quesub1->next;
				}
			} else {
				if(num>0){
					customer *resub = res;
					for(int i = 0;i<count;i++){
						resub->print();
						resub = resub->next;
					}
				} else {
					customer *resub = res;
					for(int i = 0;i<count;i++){
						resub->print();
						resub = resub->prev;
					}
				}
			}
		}
};