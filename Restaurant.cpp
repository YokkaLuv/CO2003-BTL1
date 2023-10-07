#include "main.h"

class imp_res : public Restaurant
{
	private:
		int count = 0; // check number customers
		int queued = 0; // check number queued
		customer *res = nullptr; //restaurant customer
		customer *queueing = nullptr; //queueing
		customer *datalog = nullptr; //data of people going in restaurant 
		customer *prevcus = nullptr; //current customer
	public:
		imp_res() {};
		
		bool namecheck(customer* cus, customer* res, customer* queueing)
		{
            customer* restmp = res;
            while(restmp)
            {
                if(restmp->name == cus->name) return false;
                restmp = restmp->next;
            }
            customer* quetmp = queueing;
            while(quetmp)
            {
                if(quetmp->name == cus->name) return false;
                quetmp = quetmp->next;
            }
            return true;
		}

        bool is_valid_name(const std::string& name) {
            for (char c : name) {
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                    return false;
                }
            }
            return true;
        }   

        int number_in_queue(customer* cus)
        {
            int cnt = 0;
			customer* tmp = cus;
			while(tmp->next != cus)
			{
				cnt++;
				tmp = tmp->next;
			}
			cnt++;
            return cnt;
        }
		
		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			customer* cus = new customer (name, energy, nullptr, nullptr);
            if(energy == 0) return;
            if(is_valid_name(name) == false) return;
			if(namecheck(cus, res, queueing) == false) return;
            if(number_in_queue(queueing) == MAXSIZE) return;
            if(number_in_queue(res) == 0)
            {
                res = cus;
                res->next = res;
                res->prev = res;
				count++;
            }
			else if(number_in_queue(res) > 0 && number_in_queue(res) < MAXSIZE/2)
			{
				if(prevcus->energy <= cus->energy)
				{
					cus->next = prevcus->next;
					cus->prev = prevcus;
					prevcus->next = cus;
					cus->next->prev = cus;
					count++;
				}
				else if(prevcus->energy > cus->energy)
				{
					cus->next = prevcus;
					cus->prev = prevcus->prev;
					prevcus->prev = cus;
					cus->prev->next = cus;
					count++;
				}
			}
            else if(number_in_queue(res) >= MAXSIZE/2 && number_in_queue(res) < MAXSIZE)
            {
                customer* restmp = prevcus;
                int dif = 0;
                customer* max_dif = nullptr;
                while(restmp->next != prevcus) 
                {
                    if(abs(restmp->energy - cus->energy) > abs(dif))
                    {
                        dif = restmp->energy - cus->energy;
                        max_dif = restmp;
                    }
					restmp = restmp->next;
                }
                if(dif < 0) 
                {
                    max_dif->prev->next = cus;
                    cus->prev = max_dif->prev;
                    cus->next = max_dif;
                    max_dif->prev = cus;
                    count++;
                }
                else if(dif >= 0)
                {
                    cus->next = max_dif->next;
                    cus->prev = max_dif;
                    max_dif->next = cus;
                    cus->next->prev = cus;
                    res = cus;
                    count++;
                }
            }
            else if(number_in_queue(res) == MAXSIZE)
            {
				if(number_in_queue(queueing) == 0)
				{
					queueing = cus;
					queueing->next = queueing;
					queueing->prev = queueing;
					queued++;
				}
				else if(number_in_queue(queueing) > 0 && number_in_queue(queueing) < MAXSIZE) 
				{
                	customer* quetmp = queueing;
                	while(quetmp->next)
                	{
                    	quetmp = quetmp->next;
                	}
                	quetmp->next = cus;
                	cus->prev = quetmp;
                	queued++;
				}
			}
			prevcus = cus;
		}

		void BLUE(int num)
		{
			customer *resubb = res;
			cout << "blue "<< num << endl;
			for(int i = 0; i < min(num,count); ++i)	// delete people in data & res
			{
				for(int j = 0; j < count; ++j)
				{
					if(datalog->name == resubb->name)
					{
						if(count == 1)
						{
							res = nullptr;
							count--;
						} 
						else 
						{
							resubb->next->prev = resubb->prev;
							resubb->prev->next = resubb->next;
							count--;
							delete[] resubb;
							datalog = datalog->next;
						}
					}
				}
			}
			while(queued != 0 && count < MAXSIZE)	// push pp from queue to restaurant
			{
				RED(queueing->name, queueing->energy);
				count++;
				queued--;
				queueing = queueing->next;
			}
		}

		void PURPLE()
		{
			/*
			void shellsort(Node*& pHead)
			{
			    int n = 0;
			    Node* cur = pHead;
			    while (cur) {
			        n++;
			        cur = cur->pNext;
			    }
			    int gap = n / 2;
			    while (gap > 0) {
			        for (int i = gap; i < n; i++) {
			            Node* temp = pHead;
			            for (int j = 0; j < i - gap; j++) {
			                temp = temp->pNext;
			            }
			            Node* temp2 = temp->pNext;
			            while (temp2 && temp2->data < temp->data) {
			                swap(temp->data, temp2->data);
			                temp = pHead;
			                for (int j = 0; j < i - gap; j++) {
			                    temp = temp->pNext;
			                }
			                temp2 = temp->pNext;
			            }
			        }
			        gap /= 2;
			    }
			}
			*/
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
			if (num > 0) {
				// print information of customers at table in clockwise order
				for (int i = count - 1; i >= 0; i--) {
					cout << res[i].name << "-" << res[i].energy << "/n";
				}
			}
			else if (num < 0) {
				// print information of customers at table in counterclockwise order
				for (int i = 0; i < count; i++) {
					cout << res[i].name << "-" << res[i].energy << "/n";
				}
			}
			else {
				// print information of customers in queue in order
				for (int i = 0; i < queued; i++) {
					cout << queueing[i].name << "-" << queueing[i].energy << "/n";
				}
			}
		}
};