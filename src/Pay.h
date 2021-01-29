//
// Created by Phil Barrette on 2021-01-27.
//

#ifndef BANK_SYSTEM_PAY_H
#define BANK_SYSTEM_PAY_H


class Pay {
private:
    int ID;
    double amount;
public:
    //Constructor - Destructor
    Pay();
    Pay(double, int);
    ~Pay(){};

    //Get
    int getID(){return ID;}
    double getAmount(){return amount;}

    //Set
    void setID(int);
    void setAmount(double);
};


#endif //BANK_SYSTEM_PAY_H
