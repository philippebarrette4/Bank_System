//
// Created by Phil Barrette on 2021-01-27.
//

#ifndef BANK_SYSTEM_ACCOUNT_H
#define BANK_SYSTEM_ACCOUNT_H
#include "Pay.h"
#include <string>
#include <vector>
#include <map>


class Account {
private:
    int Id_acc;
    int Id_pay;
    double total;
    std::map<std::string, std::vector<Pay>> p;
public:
    //Constructor - Destructor
    Account();
    Account(int);
    ~Account(){}
    //Get
    double getTotal(){return total;}
    int getId_acc(){return Id_acc;}
    int printPaychecks();
    //Set
    void setId_acc(int);
    //Add a pay
    void addPay();
};


#endif //BANK_SYSTEM_ACCOUNT_H
