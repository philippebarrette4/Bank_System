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
    int Id_acc, Id_pay;
    std::string first_name, last_name;
    double total;
    std::map<std::string, std::vector<Pay>> p;
public:
    //Constructor - Destructor
    Account();
    Account(int);
    Account(int,std::string,std::string);
    ~Account(){}

    //Get
    double getTotal(){return total;}
    int getId_acc(){return Id_acc;}
    std::string getName(){return first_name + " " + last_name;}
    std::string getFn(){return first_name;}
    std::string getLn(){return last_name;}

    //Set
    void setId_acc(int);

    //Display checks and cumulative total
    void printPaychecks();
    void printTotal();

    //Add a pay
    void addPay();

    //Delete a pay
    void deletePay();
};


#endif //BANK_SYSTEM_ACCOUNT_H
