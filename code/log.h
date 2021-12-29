//
// Created by 韦捷 on 2021/12/18.
//

#ifndef UNTITLED2_LOG_H
#define UNTITLED2_LOG_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "accounts.h"

enum Behavior {AddUser, Delete, Show, Buy, Select, Modify, Import};
struct Log {
    User user;
    Behavior behavior;
    char description[150];
    bool if_earn = false; // 表示是否是收入
    double Amount;
};
struct Finance{
    double income=0;
    double outcome=0;
    friend std::ostream& operator<<(std::ostream& os,const Finance &x){
        os << "+ ";
        os << std::setiosflags(std::ios::fixed) << std::setprecision(2) << std::fixed << x.income << " ";
        os << "- ";
        os << std::setiosflags(std::ios::fixed) << std::setprecision(2) << std::fixed << x.outcome << " ";
        os << '\n';
        return os;
    }
};

class LogManagement {
private:
    std::fstream log_data_;
    std::fstream finance_data_;
    int count_ = 0; // 交易笔数

public:
    std::string file_name_log_all;
    std::string file_name_finance_all;
    LogManagement(std::string name1,std::string name2);

    void Report(TokenScanner& line, AccountManagement& accounts);

    void AddLog(Log& log); // 把 log 放进文件的同时还需要检查是否有交易

    void ShowFinance(int Limit = -1); // 若为 -1，则显示全部

    void Log(TokenScanner& line); // log command，检查有无额外的 token

    void Addfinance(bool earn,double x);
};

#endif //UNTITLED2_LOG_H
