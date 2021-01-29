//
// Created by Phil Barrette on 2021-01-27.
//

#include "Account.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;


Account::Account()
    :Id_acc{0}, Id_pay{0}, total{0.0}, p{}{
}

Account::Account(int Id_val)
    :Id_pay{0}, total{0.0}, p{}{
    setId_acc(Id_val);
}

void Account::setId_acc(int Id_val){
    this->Id_acc = Id_val;
}

int Account::printPaychecks() {
    std::cout << "List of the paychecks:" << std::endl;
    //Loop through all keys "date"
    for (auto const &x: p) {
        std::cout << "Date: " << x.first << std::endl;
        //Loop through all the paycheck in the same "date" key
        for(auto num: x.second){
            std::cout << " => ID: " << num.getID() << ", Amount: "
                 << std::fixed << std::setprecision(2) << num.getAmount() << " $" << std::endl;
        }
    }
}

//Add a pay
void Account::addPay(){

    double amount;
    cout << "Enter the pay amount: ";
    cin >> amount;

    //Check if the value is a float
    while(!cin.good() | (amount < 0.0)){
        cout << "Error, please enter a valid pay amount: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> amount;
    }

    this->total += amount;

    Pay pay(amount, ++(this->Id_pay));

    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::string date = std::to_string(1900 + ltm->tm_year) + "/" +
                  std::to_string(1 + ltm->tm_mon) + "/" +
                  std::to_string(ltm->tm_mday);

    std::vector<Pay> v = this->p[date];
    v.push_back(pay);

    this->p[date] = v;
}