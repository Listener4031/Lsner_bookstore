//
// Created by 韦捷 on 2021/12/24.
//

#ifndef UNTITLED2_BOOKSTORE_H
#define UNTITLED2_BOOKSTORE_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include "unrolled_linked_list.h"
#include "token_scanner.h"

int str_to_int(const std::string &a) {
    if (a.empty()) return 0;
    else if (a[0] == '-') {
        if (a.size() == 1) return 0;
        else {
            int ans = 0;
            for (unsigned int i = 1; i < a.size(); i++) {
                ans *= 10;
                ans += int(a[i] - '0');
            }
            return -ans;
        }
    }
    else {
        int ans = 0;
        for (unsigned int i = 0; i < a.size(); i++) {
            ans *= 10;
            ans += int(a[i] - '0');
        }
        return ans;
    }
}

struct UserID {
    char value[31];
    UserID(std::string userID){
        if(userID.size()>30) throw(int(1));
        for(int i=0;i<userID.size();i++) value[i]=userID[i];
        value[userID.size()]='\0';
    }
    UserID(){memset(value,'\0',31);}
    std::string GetUserID() const{return std::string(value);}
    bool operator==(const UserID& rhs) const{return (strcmp(value,rhs.value)==0);}
    bool operator!=(const UserID& rhs) const{return (strcmp(value,rhs.value)!=0);}
    bool operator<(const UserID& rhs) const{return (strcmp(value,rhs.value)<0);}
    bool operator>(const UserID& rhs) const{return (strcmp(value,rhs.value)>0);}
};

class User {
private:
    UserID user_id;
    char user_name[31];
    int priority;
public:
    char password[31];
    User()=default;
    User(const std::string& data){

    }
    User(const std::string& ID, const std::string& name, const std::string& passworD, int prioritY): user_id(ID){
        if(name.size()>30||passworD.size()>30||(prioritY!=0&&prioritY!=1&&prioritY!=3&&prioritY!=7)) throw(int(1));
        for(int i=0;i<passworD.size();i++) password[i]=passworD[i];
        password[passworD.size()]='\0';
        for(int i=0;i<name.size();i++) user_name[i]=name[i];
        user_name[name.size()]='\0';
        this->priority=prioritY;
    }
    void ChangePassword(const std::string& newPassword){
        if(newPassword.size()>30) throw(int(1));
        for(int i=0;i<newPassword.size();i++) password[i]=newPassword[i];
        password[newPassword.size()]='\0';
    }
    [[nodiscard]] int GetPriority() const{return this->priority;}
    friend bool operator==(const User &a,const User &b){return (a.priority==b.priority&&a.user_id==b.user_id&&strcmp(a.user_name,b.user_name)==0);}
};

struct LogInAccount {
    User user;
    int selected_book_id=0;
    bool operator==(const LogInAccount &rhs){return (user==rhs.user);}
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

    void AddUser(TokenScanner& line, LogManagement& logs); // useradd command

    void RemoveUser(TokenScanner& line, LogManagement& logs); // delete command

    void UserSelect(int book_id); // 对于当前用户选中对象

    [[nodiscard]] int GetCurrentPriority() const;
};

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

struct ISBN {
    char value[21];
    ISBN(){memset(value,'\0',21);}
    ISBN(const std::string& s){
        if(s.size()>20) throw(int(1));
        for(unsigned long long int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    bool operator==(const ISBN& rhs) const{return (strcmp(value,rhs.value)==0);}
    bool operator<(const ISBN& rhs) const{return (strcmp(value,rhs.value)<0);}
    friend std::ostream& operator<<(std::ostream& os,const ISBN &isbn){
        os << std::string(isbn.value);
        return os;
    }
};

struct BookName {
    char value[61];
    BookName(){memset(value,'\0',21);}
    BookName(const std::string& s){
        if(s.size()>60) throw(int(1));
        for(unsigned long long int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    bool operator==(const BookName& rhs) const{return (strcmp(value,rhs.value)==0);}
    bool operator<(const BookName& rhs) const{return (strcmp(value,rhs.value)<0);}
    friend std::ostream& operator<<(std::ostream& os,const BookName &bookname){
        os <<std::string(bookname.value);
        return os;
    }
};

struct Author {
    char value[61];
    Author(){memset(value,'\0',21);}
    Author(const std::string& s){
        if(s.size()>60) throw(int(1));
        for(unsigned long long int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    bool operator==(const Author& rhs) const{return (strcmp(value,rhs.value)==0);}
    bool operator<(const Author& rhs) const{return (strcmp(value,rhs.value)<0);}
    friend std::ostream& operator<<(std::ostream& os,const Author &author){
        os <<std::string(author.value);
        return os;
    }
};

struct Keyword {
    char value[61];
    Keyword(){memset(value,'\0',21);}
    Keyword(const std::string& s){
        if(s.size()>60) throw(int(1));
        for(unsigned long long int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    bool operator==(const Keyword& rhs) const{return (strcmp(value,rhs.value)==0);}
    bool operator<(const Keyword& rhs) const{return (strcmp(value,rhs.value)<0);}
    friend std::ostream& operator<<(std::ostream& os,const Keyword &keyword){
        os <<std::string(keyword.value);
        return os;
    }
};

class Book {
private:

public:
    ISBN isbn_;
    BookName book_name_;
    Author author_;
    Keyword keyword_;
    int quantity_ = 0;
    double price_ = 0;
    double total_cost_ = 0;
    int book_ID_=0;
    Book()=default;
    Book(int id, const std::string& isbn, const std::string& bookName, const std::string& author, const std::string& keyword, int quantity, double price, double _total_cost):book_ID_(id),isbn_(isbn),
                                                                                                                                                                              book_name_(bookName),author_(author),quantity_(quantity),price_(price),total_cost_(_total_cost){
        TokenScanner keyw(keyword,'|');
        std::string array_key[61];
        int count=0;
        std::string new_key=keyw.NextToken();
        while(new_key!=""&&count<61){
            array_key[count++]=new_key;
            new_key=keyw.NextToken();
        }
        std::sort(array_key,array_key+count);
        int p=0;
        for(int i=0;i<count;i++){
            for(int j=0;j<array_key[i].size();j++) keyword_.value[p++]=array_key[i][j];
            if(p<=60) keyword_.value[p++]='|';
        }
        keyword_.value[p]='\0';
    }// 这样方便构造，但注意 keyword 需要以升序重新排列
    Book(int id, const std::string& isbn):book_ID_(id),isbn_(isbn), book_name_(""), author_(""), keyword_(""),quantity_(0),price_(0),total_cost_(0){} // 将除 ISBN 以外的部分全部为空字符串或 0

    friend std::ostream& operator<<(std::ostream& os, const Book& book){
        os << book.isbn_ << " " << book.book_name_ << " " << book.author_ << " " << book.keyword_;
        os << std::setiosflags(std::ios::fixed) << std::setprecision(2) << std::fixed << book.price_ << " ";
        os << book.quantity_ << std::endl;
        return os;
    } // 用于输出
};

class BookManagement {
private:
    std::fstream book_data_; // 用于储存所有数据的文件
    UnrolledLinkedList<ISBN, int, int> isbn_map_; // 第一个 int 忽略即可，填入时用 0 就行
    UnrolledLinkedList<BookName, ISBN, int> book_name_index_;
    UnrolledLinkedList<Author, ISBN, int> author_map_index_;
    UnrolledLinkedList<Keyword, ISBN, int> keyword_index_;

    // Other private variables ...
public:
    std::string file_name_book_data_;
    int count_book_max=0;
    //std::string file_name_isbn_map_all;
    //std::string file_name_isbn_map_lead;
    //std::string file_name_book_name_index_all;
    //std::string file_name_book_name_index_lead;
    //std::string file_name_author_map_index_all;
    //std::string file_name_author_map_index_lead;
    //std::string file_name_keyword_index_all;
    //std::string file_name_keyword_index_lead;
    BookManagement(std::string name1,std::string name2,std::string name3,std::string name4,std::string name5,std::string name6,std::string name7,std::string name8,std::string name9);
    // 下面的指令请调用 accounts::getCurrentPriority() 来获取权限

    void Show(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 先判断是不是 show finance（都是以 show 开头），然后分四种情况讨论，如无参数，则按照 ISBN 输出全部（traverse 函数）

    void Buy(TokenScanner& line, AccountManagement& accounts, LogManagement& logs);

    void Select(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 检查是否有权限，检查是否有 ISBN，然后选中

    void Modify(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 检查是否有权限

    void ImportBook(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 检查是否有权限
};


BookManagement::BookManagement(std::string name1,std::string name2,std::string name3,std::string name4,std::string name5,std::string name6,std::string name7,std::string name8,std::string name9):file_name_book_data_(name1),isbn_map_(name2,name3),book_name_index_(name4,name5),author_map_index_(name6,name7),keyword_index_(name8,name9){}

// 下面的指令请调用 accounts::getCurrentPriority() 来获取权限

void BookManagement::Show(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<1) throw 1;
    std::string next=line.NextToken();
    if(next=="finance"){

    }
    else if(next==""){
        std::vector<int>* v_all=isbn_map_.Traverse();
        if(v_all->size()==0){
            std::cout << std::endl;
            delete v_all;
        }
        else{
            book_data_.open(file_name_book_data_);
            if(!book_data_){
                book_data_.open(file_name_book_data_,std::ofstream::out);
                book_data_.close();
                book_data_.open(file_name_book_data_);
            }
            Book test_book;
            for(int i=0;i<v_all->size();i++){
                book_data_.seekg((*v_all)[i]);
                book_data_.read(reinterpret_cast<char*>(&test_book),sizeof(Book));
                std::cout << test_book;
            }
            book_data_.close();
            delete v_all;
        }
    }
    else{

    }
} // 先判断是不是 show finance（都是以 show 开头），然后分四种情况讨论，如无参数，则按照 ISBN 输出全部（traverse 函数）

void BookManagement::Buy(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<1) throw 1;
    std::string targeted_isbn=line.NextToken();
    ISBN targeted_ISBN(targeted_isbn);
    const int location=isbn_map_.Get(targeted_ISBN,0);
    book_data_.open(file_name_book_data_);
    if(!book_data_){
        book_data_.open(file_name_book_data_,std::ofstream::out);
        book_data_.close();
        book_data_.open(file_name_book_data_);
    }
    Book target_book;
    book_data_.seekg(location);
    book_data_.read(reinterpret_cast<char*>(&target_book),sizeof(Book));
    book_data_.close();
    std::string q=line.NextToken();
    if(q.size()>10) throw 1;
    int quantitY= str_to_int(q);
    if(quantitY<0||quantitY>target_book.quantity_) throw 1;
    double cost=quantitY*target_book.price_;
    printf("%.2f\n",cost);
    target_book.quantity_-=quantitY;
    book_data_.open(file_name_book_data_);
    book_data_.seekp(location);
    book_data_.write(reinterpret_cast<char*>(&target_book),sizeof(Book));
    book_data_.close();

}

void BookManagement::Select(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<3) throw 1;
    std::string isbn_new=line.NextToken();
    ISBN new_isbn(isbn_new);
    book_data_.open(file_name_book_data_);
    if(!book_data_){
        book_data_.open(file_name_book_data_,std::ofstream::out);
        book_data_.close();
        book_data_.open(file_name_book_data_);
    }
    int book_count=0;
    book_data_.seekg(0);
    book_data_.read(reinterpret_cast<char*>(&book_count),sizeof(int));
    if(!(isbn_map_.Exist(new_isbn))){
        Book new_book(++count_book_max,isbn_new);
        accounts.login_[accounts.login_.size()-1].selected_book_id=count_book_max;
        isbn_map_.Insert(new_isbn,0,sizeof(int)+book_count*sizeof(Book));
        book_name_index_.Insert(new_book.book_name_,new_isbn,sizeof(int)+book_count*sizeof(Book));
        author_map_index_.Insert(new_book.author_,new_isbn,sizeof(int)+book_count*sizeof(Book));
        keyword_index_.Insert(new_book.keyword_,new_isbn,sizeof(int)+book_count*sizeof(Book));
        book_data_.seekp(sizeof(int)+book_count*sizeof(Book));
        book_data_.write(reinterpret_cast<char*>(&new_book),sizeof(Book));
        book_count++;
        book_data_.seekp(0);
        book_data_.write(reinterpret_cast<char*>(&book_count),sizeof(int));
    }
    else{
        int loction=isbn_map_.Get(new_isbn,0);
        Book targeted_book;
        book_data_.seekg(loction);
        book_data_.read(reinterpret_cast<char*>(&targeted_book),sizeof(Book));
        accounts.login_[accounts.login_.size()-1].selected_book_id=targeted_book.book_ID_;
    }
    book_data_.close();
} // 检查是否有权限，检查是否有 ISBN，然后选中

void BookManagement::Modify(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<3||accounts.login_.back().selected_book_id==-1) throw 1;
    std::string test_token=line.NextToken();
    if(test_token=="") throw 1;
    std::string test_content;
    int ck[5]={0,0,0,0,0};
    book_data_.open(file_name_book_data_);
    book_data_.seekg(sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    Book targeted_book;
    book_data_.read(reinterpret_cast<char*>(&targeted_book),sizeof(Book));
    while(test_token!=""){
        if(test_token.substr(0,5)=="-ISBN"){
            if(ck[0]){book_data_.close();throw 1;}
            ck[0]=1;
            test_content=test_token.substr(6,test_token.size()-6);
            if(test_content.size()==0||test_content.size()>20){book_data_.close();throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.isbn_.value[i]=test_content[i];
            targeted_book.isbn_.value[test_content.size()]='\0';
        }
        else if(test_token.substr(0,5)=="-name"){
            if(ck[1]){book_data_.close();throw 1;}
            ck[1]=1;
            test_content=test_token.substr(7,test_token.size()-7);
            if(test_content.size()==0||test_content.size()>60){book_data_.close();throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.book_name_.value[i]=test_content[i];
            targeted_book.book_name_.value[test_content.size()]='\0';
        }
        else if(test_token.substr(0,6)=="-price"){
            if(ck[2]){book_data_.close();throw 1;}
            ck[2]=1;
            test_content=test_token.substr(7,test_token.size()-7);
            if(test_content.size()==0){book_data_.close();throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.isbn_.value[i]=test_content[i];
            targeted_book.isbn_.value[test_content.size()]='\0';
        }
        else if(test_token.substr(0,7)=="-author"){
            if(ck[3]){book_data_.close();throw 1;}
            ck[3]=1;
            test_content=test_token.substr(9,test_token.size()-9);
            if(test_content.size()==0||test_content.size()>60){book_data_.close();throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.author_.value[i]=test_content[i];
            targeted_book.author_.value[test_content.size()]='\0';
        }
        else if(test_token.substr(0,8)=="-keyword"){
            if(ck[4]){book_data_.close();throw 1;}
            ck[4]=1;
            test_content=test_token.substr(10,test_token.size()-10);
            if(test_content.size()==0||test_content.size()>60){book_data_.close();throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.keyword_.value[i]=test_content[i];
            targeted_book.keyword_.value[test_content.size()]='\0';
        }else{book_data_.close();throw 1;}
        test_token=line.NextToken();
    }
    book_data_.seekp(sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    book_data_.write(reinterpret_cast<char*>(&targeted_book),sizeof(Book));
    book_data_.close();
} // 检查是否有权限

void BookManagement::ImportBook(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<3||accounts.login_.back().selected_book_id==-1) throw 1;

}

enum Behavior {AddUser, Delete, Show, Buy, Select, Modify, Import};
struct Log {
    User user;
    Behavior behavior;
    char description[150];
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

    void AddLog(Log& log); // 把 log 放进文件的同时还需要检查是否有交易

    void ShowFinance(int Limit = -1); // 若为 -1，则显示全部

    void Log(TokenScanner& line); // log command，检查有无额外的 token
};

LogManagement::LogManagement(){

}

void LogManagement::Report(TokenScanner& line, AccountManagement& accounts){

}

void LogManagement::AddLog(Log& log){

} // 把 log 放进文件的同时还需要检查是否有交易

void LogManagement::ShowFinance(int Limit){

} // 若为 -1，则显示全部

void LogManagement::Log(TokenScanner& line){

}



#endif //UNTITLED2_BOOKSTORE_H
