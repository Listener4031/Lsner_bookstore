//
// Created by 韦捷 on 2021/12/18.
//

#ifndef UNTITLED2_LOG_H
#define UNTITLED2_LOG_H

#include <iostream>
#include <fstream>

#include "accounts.h"

enum Behavior {AddUser, Delete, Show, Buy, Select, Modify, Import};
struct Log {
    User user;
    Behavior behavior;
    char[150] description;
    bool if_earn = false; // 表示是否是收入
    double Amount;
};

class LogManagement {
private:
    std::fstream log_data_;
    int count_ = 0; // 交易笔数

public:
    LogManagement();

    void Report(TokenScanner& line, AccountManagement& accounts);

    void AddLog(log& Log); // 把 log 放进文件的同时还需要检查是否有交易

    void ShowFinance(int Limit = -1); // 若为 -1，则显示全部

    void Log(TokenScanner& line); // log command，检查有无额外的 token
};

#endif //UNTITLED2_LOG_H
