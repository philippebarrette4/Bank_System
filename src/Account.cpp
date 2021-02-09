//
// Created by Phil Barrette on 2021-01-27.
//
#include "Account.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

Account::Account()
    :Id_acc{0}, first_name{"NA"}, last_name{"NA"}, Id_pay{0}, total{0.0}, p{}{
}

Account::Account(int Id_val)
    :Id_pay{0}, first_name{"NA"}, last_name{"NA"}, total{0.0}, p{}{
    setId_acc(Id_val);
}

Account::Account(int Id_val ,std::string fn, std::string ln)
    :Id_pay{0}, first_name{fn}, last_name{ln}, total{0.0}, p{}{
    setId_acc(Id_val);
}

void Account::setId_acc(int Id_val){
    this->Id_acc = Id_val;
}

void Account::setTotal(double Total){
    this->total = Total;
}

void Account::printPaychecks() {
    std::cout << "Account ID: " << getId_acc() << std::endl;
    std::cout << "User name: " << getName() << std::endl;
    std::cout << "======================" << std::endl;
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

void Account::printTotal(){
    std::cout << "Account ID: " << getId_acc() << std::endl;
    std::cout << "User name: " << getName() << std::endl;
    std::cout << "======================" << std::endl;
    cout << "Cumulative total: "
         << getTotal() << " $" << endl;
}



//Add a pay
void Account::addPay(){

    double amount;
    cout << "\nEnter the pay amount: ";
    cin >> amount;

    //Check if the value is a float
    while(!cin.good() | (amount < 0.0)){
        cout << "Error, please enter a valid pay amount: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> amount;
    }

    this->total += amount;



    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::string date = std::to_string(1900 + ltm->tm_year) + "/" +
                  std::to_string(1 + ltm->tm_mon) + "/" +
                  std::to_string(ltm->tm_mday);

    Pay pay(amount, ++(this->Id_pay), date);
    std::vector<Pay> v = this->p[date];
    v.push_back(pay);

    this->p[date] = v;
}

//Delete a pay
void Account::deletePay(){

    int Id_val;
    cout << "Enter the pay ID: ";
    cin >> Id_val;

    //Check if the value is a float
    while(!cin.good() | (Id_val < 0)){
        cout << "Error, please enter a valid pay amount: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> Id_val;
    }

    //Loop through all keys "date"
    for (auto &x: p) {
        //Loop through all the paycheck in the same "date" key
        vector<Pay> t;
        t = x.second;
        //t.erase(t.begin()+6);
        for(int i=0; i < t.size(); i++){
            if(Id_val == t[i].getID()){
                this->total -= t[i].getAmount();
                t.erase(t.begin() + i);
            }
        }
        x.second = t;
    }



}