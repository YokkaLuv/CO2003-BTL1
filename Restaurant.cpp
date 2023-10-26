#include "main.h"

class imp_res : public Restaurant {
private:
  int count = 0;                // check number customers
  int queued = 0;               // check number queued
  customer *res = nullptr;      // restaurant customer
  customer *queueing = nullptr; // queueing
  customer *datalog = nullptr;  // data of people going in restaurant
  customer *prevcus = nullptr;  // current customer
public:
  imp_res(){};
  static bool prior(int a, int b) { return abs(a) > abs(b); }
  bool namecheck(customer *cus) {
    if (res == nullptr)
      return true;
    customer *restmp = res;
    do {
      if (restmp->name == cus->name)
        return false;
      restmp = restmp->next;
    } while (restmp != res);
    customer *quetmp = queueing;
    while (quetmp) {
      if (quetmp->name == cus->name)
        return false;
      quetmp = quetmp->next;
    }
    return true;
  }
  bool cnspec(string s) {
    for (customer *tmp = datalog; tmp; tmp = tmp->next) {
      if (s == tmp->name)
        return 1;
    }
    return 0;
  }
  bool checkenergy(customer *head, customer *&x, customer *&y, int t, int gap,
                   int val) {
    x = head;
    y = head;
    for (int i = 0; i < t; i++)
      x = x->next;
    for (int i = 0; i < t - gap; i++)
      y = y->next;
    return abs(y->energy) < abs(val);
  }
  void RED(string name, int energy) {
    customer *cus = new customer(name, energy, nullptr, nullptr);
    customer *cussub = new customer(cus->name, cus->energy, nullptr, nullptr);
    customer *cussublog =
        new customer(cus->name, cus->energy, nullptr, nullptr);
    if (queued == MAXSIZE)
      return;
    if (cus->energy == 0)
      return;
    if (!namecheck(cus))
      return;
    if (!res) {
      res = cus;
      cus->next = cus;
      cus->prev = cus;
      prevcus = cus;
      count++;
    } else if (count < MAXSIZE / 2) {
      if (prevcus->energy <= cus->energy) {
        cus->next = prevcus->next;
        cus->prev = prevcus;
        prevcus->next = cus;
        cus->next->prev = cus;
        count++;
      } else if (prevcus->energy > cus->energy) {
        cus->next = prevcus;
        cus->prev = prevcus->prev;
        prevcus->prev = cus;
        cus->prev->next = cus;
        count++;
      }
      prevcus = cus;
    } else if (count >= MAXSIZE / 2 && count < MAXSIZE) {
      customer *restmp = prevcus;
      int dif = 0;
      customer *max_dif = nullptr;
      while (restmp->next != prevcus) {
        if (abs(restmp->energy - cus->energy) > abs(dif)) {
          dif = restmp->energy - cus->energy;
          max_dif = restmp;
        }
        restmp = restmp->next;
      }
      dif = cus->energy - max_dif->energy;
      if (dif < 0) {
        max_dif->prev->next = cus;
        cus->prev = max_dif->prev;
        cus->next = max_dif;
        max_dif->prev = cus;
        count++;
      } else if (dif >= 0) {
        cus->next = max_dif->next;
        cus->prev = max_dif;
        max_dif->next = cus;
        cus->next->prev = cus;
        res = cus;
        count++;
      }
      prevcus = cus;
    } else if (count == MAXSIZE) {
      if (queued == 0) {
        queueing = cussub;
        // queueing->prev = queueing;
        queued++;
      } else if (queued > 0 && queued < MAXSIZE) {
        customer *quetmp = queueing;
        while (quetmp->next != nullptr) {
          quetmp = quetmp->next;
        }
        quetmp->next = cussub;
        queued++;
      }
    }
    if (datalog == nullptr) { // put people in datalog case no one
      datalog = cussublog;
    } else { // case already have pp
      if (!cnspec(cus->name)) {
        customer *subdata = datalog;
        while (subdata->next) {
          subdata = subdata->next;
        }
        subdata->next = cussublog;
      }
    }
  }
  void BLUE(int num) {
    // cout << "blue " << num << endl;
    if (res) {
      while (num > 0 && res && count > 0) {
        customer *sub = res;
        customer *tmp =
            new customer(datalog->name, datalog->energy, nullptr, nullptr);
        do {
          if (sub->name == tmp->name && sub->energy == tmp->energy) {
            if (sub->prev == sub && sub->next == sub) {
              res = nullptr;
              prevcus = res;
            } else {
              sub->energy >= 0 ? prevcus = sub->next : prevcus = sub->prev;
              sub->prev->next = sub->next;
              sub->next->prev = sub->prev;
              if (sub == res)
                res = sub->next;
            }
            break;
          }
          sub = sub->next;
        } while (sub != res);
        datalog = datalog->next;
        num--;
        if (res)
          count--;
        else
          count = 0;
      }
      while (queued > 0 && count < MAXSIZE) // push pp from queue to restaurant
      {
        customer *ys = queueing;
        queueing = queueing->next;
        queued--;
        RED(ys->name, ys->energy);
      }
    }
  }
  void PURPLE() {
    // cout << "purple" << endl;
    int change = 0;
    customer *current;
    customer *i;
    customer *j;
    for (i = queueing; i != nullptr; i = i->next) {
      for (j = i->next; j != nullptr; j = j->next) {
        if (prior(j->energy, i->energy)) {
          swap(i, j);
          change++;
        }
      }
    }
    // cout << change << endl;
    BLUE(change % MAXSIZE);
  }

  void REVERSAL() {
    // cout << "reversal" << endl;
    if (count <= 1)
      return;
    customer *tmp = prevcus;
    do {
      if (tmp->energy * tmp->prev->energy > 0) {
        swap(tmp->energy, tmp->prev->energy);
        swap(tmp->name, tmp->prev->name);
      }
      tmp = tmp->prev;
    } while (tmp != prevcus);
  }

  void UNLIMITED_VOID() {
    // cout << "unlimited_void" << endl;
    if (count < 4)
      return;
    customer *bestStart = nullptr;
    customer *bestEnd = nullptr;
    int curenergy = 0;
    int minenergy = 999999;
    int sl = 0;
    customer *start = prevcus;
    customer *end;
    for (int i = 0; i < count * 2; i++) {
      sl = 0;
      curenergy = 0;
      for (end = start; end->next != start; end = end->next) {
        curenergy += end->energy;
        sl++;
        if (sl >= 4 && curenergy <= minenergy) {
          bestStart = start;
          bestEnd = end;
          minenergy = curenergy;
        }
        if (end->next->next == start) {
          curenergy += end->next->energy;
          sl++;
          if (sl >= 4 && curenergy <= minenergy) {
            bestStart = start;
            bestEnd = end->next;
            minenergy = curenergy;
          }
        }
      }
      start = start->next;
    }
    customer *min = bestStart;
    customer *x = bestStart;
    while (x != bestEnd) {
      if (x->energy < min->energy)
        min = x;
      x = x->next;
    }
    if (x->energy < min->energy)
      min = x;
    x = min;
    while (x != bestEnd) {
      x->print();
      x = x->next;
    }
    x->print();
    x = bestStart;
    while (x != min) {
      x->print();
      x = x->next;
    }
  }
  void search(string namex) {
    customer *sub1 = res;
    customer *sub2 = queueing;

    do {
      if (sub1->name == namex) {
        if (sub1->prev == sub1 && sub1->next == sub1) {
          res = nullptr;
          prevcus = res;
        } else {
          sub1->energy >= 0 ? prevcus = sub1->next : prevcus = sub1->prev;
          sub1->prev->next = sub1->next;
          sub1->next->prev = sub1->prev;
          if (sub1 == res)
            res = sub1->next;
        }
        return;
      }
      sub1 = sub1->next;
    } while (sub1 != res);
    while (sub2) {
      if (sub2->name == namex) {

        if (sub2 == queueing) {
          queueing = queueing->next;
          return;
        }

        customer *tmp = queueing;
        while (tmp->next != sub2) {
          tmp = tmp->next;
        }
        tmp->next = sub2->next;

        return;
      }
      sub2 = sub2->next;
    }
  }
  void DOMAIN_EXPANSION() {
    // cout << "domain_expansion" << endl;
    int sumpos = 0, sumneg = 0;
    customer *rescount = res;
    customer *quecount = queueing;
    customer *sub = nullptr;
    int subcount = 0;
    if (res) {
      do { // add energy to both sum up
        if (rescount->energy > 0)
          sumpos += rescount->energy;
        else
          sumneg += rescount->energy;
        rescount = rescount->next;
      } while (rescount != res);
    }
    while (quecount) {
      if (quecount->energy > 0)
        sumpos += quecount->energy;
      else
        sumneg += quecount->energy;
      quecount = quecount->next;
    }
    // cout<<sumpos<<" "<<sumneg<<endl;
    if (sumpos + sumneg >= 0) {
      customer *datasub = datalog;
      // customer* tmp = datasub;
      while (datasub != nullptr) {
        if (datasub->energy < 0) {

          customer *subsub =
              new customer(datasub->name, datasub->energy, nullptr,
                           nullptr);
          if (subcount == 0) {
            sub = subsub;

          } else {
            subsub->next = sub;
            sub = subsub;
          }
          subcount++;
          search(datasub->name);

          if (datalog->name == datasub->name) {
            datalog = datalog->next;
          } else {
            customer *tmp = datalog;
            while (tmp->next != datasub)
              tmp = tmp->next;
            tmp->next = datasub->next;
          }
        }
        // tmp=datasub;
        datasub = datasub->next;
        // cout<<888<<endl;//testerror
      }
    } else {
      customer *datasub = datalog;
      // customer* tmp = datasub;
      while (datasub != nullptr) {
        if (datasub->energy > 0) {
          customer *subsub =
              new customer(datasub->name, datasub->energy, nullptr,
                           nullptr);
          if (subcount == 0) {
            sub = subsub;
          } else {
            subsub->next = sub;
            sub = subsub;
          }
          subcount++;
          search(datasub->name);
          if (datalog->name == datasub->name) {
            datalog = datalog->next;
          } else {
            customer *tmp = datalog;
            while (tmp->next != datasub) {
              tmp = tmp->next;
            }
            tmp->next = datasub->next;
          }
          delete datasub;
        }
        datasub = datasub->next;
        //  cout<<888<<endl;//testerror
      }
    }
    while (sub) {
      sub->print();
      sub = sub->next;
    }
    while (queued > 0 && count < MAXSIZE) // push pp from queue to restaurant
    {
      customer *ys = queueing;
      queueing = queueing->next;
      queued--;
      RED(ys->name, ys->energy);
    }
  }

  void LIGHT(int num) {
    // cout << "light " << num << endl;
    customer *restmp = prevcus;
    customer *quetmp = queueing;
    if (res == nullptr)
      return;
    if (num > 0) {
      // print information of customers at table in clockwise order
      do {
        restmp->print();
        restmp = restmp->next;
      } while (restmp != prevcus);
    } else if (num < 0) {
      do {
        restmp->print();
        restmp = restmp->prev;
      } while (restmp != prevcus);
    } else if (num == 0) {
      // print information of customers in queue in order
      while (quetmp) {
        quetmp->print();
        quetmp = quetmp->next;
      }
    }
  }
};