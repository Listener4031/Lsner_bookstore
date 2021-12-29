//
// Created by 韦捷 on 2021/12/18.
//

#ifndef UNTITLED2_ACCOUNTS_H
#define UNTITLED2_ACCOUNTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "token_scanner.h"
#include "unrolled_linked_list.h"
//#include "log.h"


struct UserID {
    char value[31];
    UserID(std::string userID){
        if(userID.size()>30) throw 1;
        for(int i=0;i<userID.size();i++){
            value[i]=userID[i];
        }
        value[userID.size()]='\0';
    }
    UserID(){memset(value,'\0',31);}
    std::string GetUserID() const{return std::string(value);}
    bool operator==(const UserID& rhs) const{return (strcmp(value,rhs.value)==0);}
    bool operator!=(const UserID& rhs) const{return (strcmp(value,rhs.value)!=0);}
    bool operator<(const UserID& rhs) const{return (strcmp(value,rhs.value)<0);}
    bool operator>(const UserID& rhs) const{return (strcmp(value,rhs.value)>0);}
    friend bool operator<=(const UserID &x,const UserID &y){return (x<y||x==y);}
    friend bool operator>=(const UserID &x,const UserID &y){return (x>y||x==y);}
    UserID& operator=(const UserID &x){
        strcpy(this->value,x.value);
        return (*this);
    }
};

class User {
private:
    UserID user_id;
    char user_name[31];
    int priority;
public:
    char password[31];
    User()=default;
    User(const std::string& ID, const std::string& name, const std::string& passworD, int prioritY): user_id(ID){
        if(name.empty()||name.size()>30) throw 1;
        for(int i=0;i<name.size();++i){
            user_name[i]=name[i];
        }
        user_name[name.size()]='\0';
        if(passworD.empty()||passworD.size()>30) throw 1;
        for(int i=0;i<passworD.size();i++){
            password[i]=passworD[i];
        }
        password[passworD.size()]='\0';
        if(prioritY!=0&&prioritY!=1&&prioritY!=3&&prioritY!=7) throw 1;
        this->priority=prioritY;
    }
    [[nodiscard]] int GetPriority() const{return this->priority;}
    friend bool operator==(const User &a,const User &b){return (a.user_id==b.user_id&&a.priority==b.priority&&strcmp(a.user_name,b.user_name)==0);}
    User& operator=(const User &x){
        this->user_id=x.user_id;
        strcpy(this->user_name,x.user_name);
        this->priority=x.priority;
        strcpy(this->password,x.password);
        return (*this);
    }
};

struct LogInAccount {
    User user;
    int selected_book_id=-1;
    friend bool operator==(const LogInAccount &x,const LogInAccount &y){return (x.user==y.user);}
    friend bool operator!=(const LogInAccount &x,const LogInAccount &y){return !(x.user==y.user);}
};

class AccountManagement {
private:
    std::fstream account_data_; // 用于储存所有数据的文件

    UnrolledLinkedList<UserID, int, int> user_id_map_; // 第一个 int 忽略即可，填入时用 0 就行

    // Other private variables ...

public:
    std::vector<LogInAccount> login_; // 用于储存登录的账户及其选定的书本 id，不可使用 ISBN 作为指定对象，因为 ISBN 可能会被之后其他用户改变
    std::string file_name_account_data_;

    AccountManagement(std::string name1,std::string name2,std::string name3); // 注意检查是否有用户名为 root，密码为 sjtu，权限为 {7} 的超级管理员账户，如没有，则添加该用户

    void SwitchUser(TokenScanner& line); // su command

    void LogOut(TokenScanner& line); // logout command

    void RegisterUser(TokenScanner& line); // register command

    void ChangePassword(TokenScanner& line); // passwd command

    void AddUser(TokenScanner& line); // useradd command

    void RemoveUser(TokenScanner& line); // delete command

    void UserSelect(int book_id); // 对于当前用户选中对象

    [[nodiscard]] int GetCurrentPriority() const;
};


#endif //UNTITLED2_ACCOUNTS_H
