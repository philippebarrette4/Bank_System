//
// Created by Phil Barrette on 2021-01-27.
//

#include "Pay.h"

Pay::Pay()
    :amount{0.0}, ID{0}{
}

Pay::Pay(double amount, int ID){
    setAmount(amount);
    setID(ID);
}

Pay::Pay(double amount, int ID, std::string date){
    setAmount(amount);
    setID(ID);
    setDate(date);
}

void Pay::setAmount(double amount) {
    this->amount = amount;
}

void Pay::setID(int ID){
    this->ID = ID;
}

void Pay::setDate(std::string date){
    this->date = date;
}