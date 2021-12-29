//
// Created by 韦捷 on 2021/12/18.
//

#ifndef UNTITLED2_TOKENER_SCANNER_H
#define UNTITLED2_TOKENER_SCANNER_H

#include <iostream>
#include <string>
#include <cstring>

class TokenScanner{
private:
    std::string buffer_; //储存的字符串缓冲区
    int current_ = 0; //所在的位置
    char delimiter_ = ' '; //分隔符
public:
    TokenScanner()=default; //Default Constructor

    TokenScanner(char delimiter);

    TokenScanner(const std::string& String, char delimiter = ' ');

    ~TokenScanner()=default; //Default destructor

    std::string NextToken();
    //先跳过此前遗留的一个或多个分隔符
    //记录第一位不是分隔符的位置（如没有则返回空串）
    //找到下一个分隔符前一个字符
    //返回字串
    void Clear(); //还原到初始空字符串状态

    friend std::istream& operator>>(std::istream& is, TokenScanner& obj); //输入新 buffer

    void SetDelimiter(char newdelimiter); //设定新分隔符

    bool if_left();

};


#endif //UNTITLED2_TOKENER_SCANNER_H
