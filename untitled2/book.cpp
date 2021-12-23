//
// Created by 韦捷 on 2021/12/18.
//

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "token_scanner.h"
#include "unrolled_linked_list.h"
#include "log.h"
#include "book.h"

int str_to_int(const std::string &a){
    if(a.empty()) return 0;
    else if(a[0]=='-'){
        if(a.size()==1) return 0;
        else{
            int ans=0;
            for(unsigned int i=1;i<a.size();i++){ans*=10;ans+=int(a[i]-'0');}
            return -ans;
        }
    }
    else{
        int ans=0;
        for(unsigned int i=0;i<a.size();i++){ans*=10;ans+=int(a[i]-'0');}
        return ans;
    }
}

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

} // 检查是否有权限

