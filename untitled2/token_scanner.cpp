//
// Created by 韦捷 on 2021/12/18.
//
#include "token_scanner.h"
#include <string>
#include <cstring>


TokenScanner::TokenScanner(char delimiter){
    delimiter_=delimiter;
    buffer_="";
}

TokenScanner::TokenScanner(const std::string& String, char delimiter){
    buffer_=String;
    delimiter_=delimiter;
}

std::string TokenScanner::NextToken(){
    while(buffer_[current_]==delimiter_&&current_<buffer_.size()) ++current_;
    if(current_==buffer_.size()) return "";
    int h=current_;
    while(buffer_[current_]!=delimiter_&&current_<buffer_.size()) ++current_;
    return buffer_.substr(h,current_-h);
}
//先跳过此前遗留的一个或多个分隔符
//记录第一位不是分隔符的位置（如没有则返回空串）
//找到下一个分隔符前一个字符
//返回字串
void TokenScanner::Clear(){
    buffer_="";
} //还原到初始空字符串状态

std::istream& operator>>(std::istream& is, TokenScanner& obj){
    is >> obj.buffer_;
    return is;
}//输入新 buffer

void TokenScanner::SetDelimiter(char newdelimiter){
    delimiter_=newdelimiter;
} //设定新分隔符