//
// Created by Phil Barrette on 2021-01-27.
//

#ifndef BANK_SYSTEM_PAY_H
#define BANK_SYSTEM_PAY_H
#include <string>


class Pay {
private:
    int ID;
    double amount;
    std::string date;
public:
    //Constructor - Destructor
    Pay();
    Pay(double, int);
    Pay(double, int, std::string);
    ~Pay(){};

    //Get
    int getID(){return ID;}
    double getAmount(){return amount;}
    std::string getDate(){return date;}

    //Set
    void setID(int);
    void setAmount(double);
    void setDate(std::string);
};


#endif //BANK_SYSTEM_PAY_H
