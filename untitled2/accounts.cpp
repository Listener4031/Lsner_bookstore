//
// Created by 韦捷 on 2021/12/18.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "token_scanner.h"
#include "unrolled_linked_list.h"
#include "log.h"
#include "accounts.h"

/*
std::vector<LogInAccount> login_; // 用于储存登录的账户及其选定的书本 id，不可使用 ISBN 作为指定对象，因为 ISBN 可能会被之后其他用户改变

    std::fstream account_data_; // 用于储存所有数据的文件

    UnrolledLinkedList<UserID, int, int> user_id_map_; // 第一个 int 忽略即可，填入时用 0 就行

    // Other private variables ...
 */
AccountManagement::AccountManagement(std::string name1,std::string name2,std::string name3): user_id_map_(name2,name3),file_name_account_data_(name1){
    login_.clear();
    account_data_.open(file_name_account_data_);
    if(!account_data_){
        account_data_.open(file_name_account_data_,std::ofstream::out);
        account_data_.close();
        account_data_.open(file_name_account_data_);
    }
    int count_all=0;
    account_data_.seekg(0);
    account_data_.read(reinterpret_cast<char*>(&count_all),sizeof(int));
    if(!count_all){
        count_all=1;
        account_data_.seekp(0);
        account_data_.write(reinterpret_cast<char*>(&count_all),sizeof(int));
        account_data_.seekp(sizeof(int));
        account_data_.write(reinterpret_cast<char*>(&count_all),sizeof(int));
        UserID sup_id("root");
        User sup_ad("root","root","sjtu",7);
        LogInAccount sup_ac;
        sup_ac.user=sup_ad;
        sup_ac.selected_book_id=-1;
        account_data_.seekp(4*sizeof(int));
        account_data_.write(reinterpret_cast<char*>(&sup_ac),sizeof(LogInAccount));
        account_data_.close();
        user_id_map_.Insert(sup_id,0,4*sizeof(int));
    }
} // 注意检查是否有用户名为 root，密码为 sjtu，权限为 {7} 的超级管理员账户，如没有，则添加该用户

void AccountManagement::SwitchUser(TokenScanner& line){
    line.SetDelimiter(' ');
    std::string user_id=line.NextToken();

} // su command

void AccountManagement::LogOut(TokenScanner& line){
    if(login_.empty()||login_.back().user.GetPriority()<1) throw 1;
    login_.pop_back();
} // logout command

void AccountManagement::RegisterUser(TokenScanner& line){
    line.SetDelimiter(' ');
    std::string user_id=line.NextToken();
} // register command

void AccountManagement::ChangePassword(TokenScanner& line){
    if(login_.empty()||login_.back().user.GetPriority()<1) throw 1;
    line.SetDelimiter(' ');
    UserID user_id(line.NextToken());
    std::string old_password=line.NextToken();
    std::string new_password=line.NextToken();
    int location=user_id_map_.Get(user_id,0);
    account_data_.open(file_name_account_data_);
    LogInAccount target_user;
    account_data_.seekg(location);
    account_data_.read(reinterpret_cast<char*>(&target_user),sizeof(LogInAccount));
    account_data_.close();
    if(login_.back().user.GetPriority()==7){
        if(new_password==""){
            if(old_password.size()>30) throw 1;
            for(int i=0;i<old_password.size();i++) target_user.user.password[i]=old_password[i];
            target_user.user.password[old_password.size()]='\0';
            account_data_.open(file_name_account_data_);
            account_data_.seekp(location);
            account_data_.write(reinterpret_cast<char*>(&target_user),sizeof(LogInAccount));
            account_data_.close();
            for(unsigned long long int i=0;i<login_.size();i++){
                if(login_[i]==target_user) {
                    for(int j=0;j<old_password.size();j++) login_[i].user.password[j]=old_password[j];
                    login_[i].user.password[old_password.size()]='\0';
                }
            }
        }
        else{
            if(std::string(target_user.user.password)!=old_password) throw 1;
            if(new_password.size()>30) throw 1;
            for(int i=0;i<new_password.size();i++) target_user.user.password[i]=new_password[i];
            target_user.user.password[new_password.size()]='\0';
            account_data_.open(file_name_account_data_);
            account_data_.seekp(location);
            account_data_.write(reinterpret_cast<char*>(&target_user),sizeof(LogInAccount));
            account_data_.close();
            for(unsigned long long int i=0;i<login_.size();i++){
                if(login_[i]==target_user) {
                    for(int j=0;j<new_password.size();j++) login_[i].user.password[j]=new_password[j];
                    login_[i].user.password[new_password.size()]='\0';
                }
            }
        }
    }
    else{

    }
} // passwd command

void AccountManagement::AddUser(TokenScanner& line, LogManagement& logs){
    if(login_.empty()||login_.back().user.GetPriority()<3) throw 1;
    UserID user_id(line.NextToken());
    std::string password=line.NextToken();
    if(password.size()>30) throw 1;
    std::string priority=line.NextToken();
    if(priority.size()!=1||(priority[0]!='0'&&priority[0]!='1'&&priority[0]!='3'&&priority[0]!='7')) throw 1;
    std::string user_name=line.NextToken();
    if(user_name.size()>30) throw 1;
    if(login_.back().user.GetPriority()<=int(priority[0]-'0')) throw 1;
    User new_user(user_id.GetUserID(),user_name,password,int(priority[0]-'0'));
    LogInAccount new_account;
    new_account.user=new_user;
    new_account.selected_book_id=-1;
    account_data_.open(file_name_account_data_);
    if(!account_data_){
        account_data_.open(file_name_account_data_,std::ofstream::out);
        account_data_.close();
        account_data_.open(file_name_account_data_);
    }
    int count_all=0;
    account_data_.seekg(0);
    account_data_.read(reinterpret_cast<char*>(&count_all),sizeof(int));
    account_data_.close();
    user_id_map_.Insert(user_id,0,4*sizeof(int)+count_all*sizeof(LogInAccount));
    account_data_.open(file_name_account_data_);
    account_data_.seekp(4*sizeof(int)+count_all*sizeof(LogInAccount));
    account_data_.write(reinterpret_cast<char*>(&new_account),sizeof(LogInAccount));
    count_all++;
    account_data_.seekp(0);
    account_data_.write(reinterpret_cast<char*>(&count_all),sizeof(int));
    if(int(priority[0]-'0')==1){
        int count_1=0;
        account_data_.seekg(3*sizeof(int));
        account_data_.read(reinterpret_cast<char*>(&count_1),sizeof(int));
        count_1++;
        account_data_.seekp(3*sizeof(int));
        account_data_.write(reinterpret_cast<char*>(&count_1),sizeof(int));
    }
    else if(int(priority[0]-'0')==3){
        int count_3=0;
        account_data_.seekg(2*sizeof(int));
        account_data_.read(reinterpret_cast<char*>(&count_3),sizeof(int));
        count_3++;
        account_data_.seekp(2*sizeof(int));
        account_data_.write(reinterpret_cast<char*>(&count_3),sizeof(int));
    }else{}
    account_data_.close();
    //for(unsigned long long int i=0;i<login_.size();i++){if(login_[i]==new_account) throw 1;}
} // useradd command

void AccountManagement::RemoveUser(TokenScanner& line, LogManagement& logs){
    if(login_.empty()||login_.back().user.GetPriority()<7) throw 1;
    line.SetDelimiter(' ');
    UserID user_id(line.NextToken());
    int location=user_id_map_.Get(user_id,0);
    account_data_.open(file_name_account_data_);
    if(!account_data_){
        account_data_.open(file_name_account_data_,std::ofstream::out);
        account_data_.close();
        account_data_.open(file_name_account_data_);
    }
    LogInAccount target_user;
    account_data_.seekg(location);
    account_data_.read(reinterpret_cast<char*>(&target_user),sizeof(LogInAccount));
    account_data_.close();
    for(unsigned long long int i=0;i<login_.size();i++){if(login_[i]==target_user) throw 1;}
    user_id_map_.Erase(user_id,0);
    account_data_.open(file_name_account_data_);
    /*
    int count_all=0;
    account_data_.seekg(0);
    account_data_.read(reinterpret_cast<char*>(&count_all),sizeof(int));
    count_all--;
    account_data_.seekp(0);
    account_data_.write(reinterpret_cast<char*>(&count_all),sizeof(int));
     */
    if(target_user.user.GetPriority()==3){
        int count_3=0;
        account_data_.seekg(2*sizeof(int));
        account_data_.read(reinterpret_cast<char*>(&count_3),sizeof(int));
        count_3--;
        account_data_.seekp(2*sizeof(int));
        account_data_.write(reinterpret_cast<char*>(&count_3),sizeof(int));
    }
    else if(target_user.user.GetPriority()==1){
        int count_1=0;
        account_data_.seekg(3*sizeof(int));
        account_data_.read(reinterpret_cast<char*>(&count_1),sizeof(int));
        count_1--;
        account_data_.seekp(3*sizeof(int));
        account_data_.write(reinterpret_cast<char*>(&count_1),sizeof(int));
    }else{}
    account_data_.close();
} // delete command

void AccountManagement::UserSelect(int book_id){
    if(login_.empty()||login_.back().user.GetPriority()<3) throw 1;
    login_.back().selected_book_id=book_id;
} // 对于当前用户选中对象

[[nodiscard]] int AccountManagement::GetCurrentPriority() const{
    return login_.back().user.GetPriority();
}

