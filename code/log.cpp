//
// Created by 韦捷 on 2021/12/18.
//

#include <iostream>
#include <fstream>
#include "log.h"
#include "accounts.h"

LogManagement::LogManagement(std::string name1,std::string name2):file_name_log_all(name1),file_name_finance_all(name2){
    log_data_.open(file_name_log_all);
    if(!log_data_){
        log_data_.open(file_name_log_all,std::ofstream::out);
        log_data_.close();
        log_data_.open(file_name_log_all);
        int count_logs=0;
        log_data_.seekp(0);
        log_data_.write(reinterpret_cast<char*>(&count_logs),sizeof(int));
    }
    log_data_.close();
    finance_data_.open(file_name_finance_all);
    if(!finance_data_){
        finance_data_.open(file_name_finance_all,std::ofstream::out);
        finance_data_.close();
        finance_data_.open(file_name_finance_all);
        int count_finance=0;
        finance_data_.seekp(0);
        finance_data_.write(reinterpret_cast<char*>(&count_finance),sizeof(int));
    }
    finance_data_.close();
}

void LogManagement::Report(TokenScanner& line, AccountManagement& accounts){

}

//void LogManagement::AddLog(Log& log){

//} // 把 log 放进文件的同时还需要检查是否有交易

void LogManagement::ShowFinance(int Limit){
    if(Limit==-1){
        finance_data_.open(file_name_finance_all);
        int count=0;
        finance_data_.seekg(0);
        finance_data_.read(reinterpret_cast<char*>(&count),sizeof(int));
        if(count>=1){
            Finance targeted_f;
            finance_data_.seekg(sizeof(int)+(count-1)*sizeof(Finance));
            finance_data_.read(reinterpret_cast<char*>(&targeted_f),sizeof(Finance));
            std::cout << targeted_f;
        }
        finance_data_.close();
    }
    else if(Limit==0){
        std::cout << std::endl;
    }
    else{
        finance_data_.open(file_name_finance_all);
        int count=0;
        finance_data_.seekg(0);
        finance_data_.read(reinterpret_cast<char*>(&count),sizeof(int));
        finance_data_.close();
        if(Limit>count) throw 1;
        Finance targeted_f;
        if(Limit==count){
            finance_data_.open(file_name_finance_all);
            finance_data_.seekg(sizeof(int)+(count-1)*sizeof(Finance));
            finance_data_.read(reinterpret_cast<char*>(&targeted_f),sizeof(Finance));
            finance_data_.close();
            std::cout << targeted_f;
        }
        else{
            finance_data_.open(file_name_finance_all);
            finance_data_.seekg(sizeof(int)+(count-1)*sizeof(Finance));
            finance_data_.read(reinterpret_cast<char*>(&targeted_f),sizeof(Finance));
            Finance f2;
            finance_data_.seekg(sizeof(int)+(count-Limit-1)*sizeof(Finance));
            finance_data_.read(reinterpret_cast<char*>(&f2),sizeof(Finance));
            finance_data_.close();
            targeted_f.outcome-=f2.outcome;
            targeted_f.income-=f2.income;
            std::cout << targeted_f;
        }
    }
} // 若为 -1，则显示全部

void LogManagement::Log(TokenScanner& line){

}

void LogManagement::Addfinance(bool earn,double x){
    finance_data_.open(file_name_finance_all);
    int count=0;
    finance_data_.seekg(0);
    finance_data_.read(reinterpret_cast<char*>(&count),sizeof(int));
    if(!count) {
        Finance new_f;
        if (earn) {
            new_f.income = x;
        } else {
            new_f.outcome = x;
        }
        finance_data_.seekp(sizeof(int));
        finance_data_.write(reinterpret_cast<char *>(&new_f), sizeof(Finance));
        count=1;
        finance_data_.seekp(0);
        finance_data_.write(reinterpret_cast<char *>(&count), sizeof(int));
        finance_data_.close();
    }
    else {
        Finance new_f;
        finance_data_.seekg(sizeof(int) + (count - 1) * sizeof(Finance));
        finance_data_.read(reinterpret_cast<char *>(&new_f), sizeof(Finance));
        if (earn) {
            new_f.income += x;
        } else {
            new_f.outcome += x;
        }
        finance_data_.seekp(sizeof(int) + count * sizeof(Finance));
        finance_data_.write(reinterpret_cast<char *>(&new_f), sizeof(Finance));
        count++;
        finance_data_.seekp(0);
        finance_data_.write(reinterpret_cast<char *>(&count), sizeof(int));
        finance_data_.close();
    }
}
