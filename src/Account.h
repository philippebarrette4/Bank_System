//
// Created by Phil Barrette on 2021-01-27.
//

#ifndef BANK_SYSTEM_ACCOUNT_H
#define BANK_SYSTEM_ACCOUNT_H
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include "Pay.h"
#include <string>
#include <vector>
#include <map>


class Account {
private:
    int Id_acc;
    int Id_pay;
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
    void setTotal(double);

    //Display checks and cumulative total
    void printPaychecks(soci::session&);
    void printTotal(soci::session&);

    //Add a pay
    void addPay(soci::session&);

    //Delete a pay
    void deletePay(soci::session&);
};


#endif //BANK_SYSTEM_ACCOUNT_H
