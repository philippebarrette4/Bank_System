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
    std::string name;
    int Id_pay;
    double total;
    std::map<std::string, std::vector<Pay>> p;
public:
    //Constructor - Destructor
    Account();
    Account(int);
    Account(int,std::string);
    ~Account(){}
    //Get
    double getTotal(){return total;}
    int getId_acc(){return Id_acc;}
    std::string getName(){return name;}
    //Display checks and cumulative total
    void printPaychecks();
    void printTotal();
    //Set
    void setId_acc(int);
    //Add a pay
    void addPay();
};


#endif //BANK_SYSTEM_ACCOUNT_H
