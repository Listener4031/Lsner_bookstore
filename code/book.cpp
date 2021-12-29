//
// Created by 韦捷 on 2021/12/18.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "token_scanner.h"
#include "unrolled_linked_list.h"
#include "log.h"
#include "book.h"
#include <iomanip>
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

template <class T>
T String_to_t(const std::string a){std::istringstream iss(a);T ans;iss >> ans;return ans;}

BookManagement::BookManagement(std::string name1,std::string name2,std::string name3,std::string name4,std::string name5,std::string name6,std::string name7,std::string name8,std::string name9):file_name_book_data_(name1),isbn_map_(name2,name3),book_name_index_(name4,name5),author_map_index_(name6,name7),keyword_index_(name8,name9){
    book_data_.open(file_name_book_data_);
    if(!book_data_){
        book_data_.open(file_name_book_data_,std::ofstream::out);
        book_data_.close();
        book_data_.open(file_name_book_data_);
        int count_book=0;
        book_data_.seekp(0);
        book_data_.write(reinterpret_cast<char*>(&count_book),sizeof(int));
    }
    book_data_.close();
}

// 下面的指令请调用 accounts::getCurrentPriority() 来获取权限

void BookManagement::Show(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    //if(accounts.login_.empty()) std::cout << "www" << std::endl;
    //else if(accounts.login_[accounts.login_.size()-1].user.GetPriority()<1) std::cout << "eee" << std::endl;
    if(accounts.login_.empty()) throw 1;
    std::string next=line.NextToken();
    if(next=="finance"){
        if(accounts.login_.back().user.GetPriority()<7) throw 1;
        next=line.NextToken();
        if(line.if_left()) throw 1;
        if(next.empty()){
            logs.ShowFinance(-1);
        }
        else{
            int t= String_to_t<int>(next);
            logs.ShowFinance(t);
        }
    }
    else if(next.empty()){
        if(accounts.login_.back().user.GetPriority()<1) throw 1;
        std::vector<int> v_all=isbn_map_.Traverse();
        if(v_all.empty()){
            std::cout << std::endl;
        }
        else{
            book_data_.open(file_name_book_data_);
            Book test_book;
            for(int i=0;i<v_all.size();i++){
                book_data_.seekg(v_all[i]);
                book_data_.read(reinterpret_cast<char*>(&test_book),sizeof(Book));
                std::cout << test_book;
            }
            book_data_.close();
        }
    }
    else{
        if(accounts.login_.back().user.GetPriority()<1) throw 1;
        if(line.if_left()) throw 1;
        if(next.substr(0,5)=="-ISBN"){
            if(next.size()<=6) throw 1;
            ISBN targeted_isbn(next.substr(6,next.size()-6));
            std::vector<int> v_all=isbn_map_.Traverse(targeted_isbn);
            if(v_all.empty()) std::cout << std::endl;
            else{
                book_data_.open(file_name_book_data_);
                Book test_book;
                for(int i=0;i<v_all.size();i++){
                    book_data_.seekg(v_all[i]);
                    book_data_.read(reinterpret_cast<char*>(&test_book),sizeof(Book));
                    std::cout << test_book;
                }
                book_data_.close();
            }
        }
        else if(next.substr(0,5)=="-name"){
            if(next.size()<=8) throw 1;
            BookName targeted_bookname(next.substr(7,next.size()-8));
            std::vector<int> v_all=book_name_index_.Traverse(targeted_bookname);
            if(v_all.empty()) std::cout << std::endl;
            else{
                book_data_.open(file_name_book_data_);
                Book test_book;
                for(int i=0;i<v_all.size();i++){
                    book_data_.seekg(v_all[i]);
                    book_data_.read(reinterpret_cast<char*>(&test_book),sizeof(Book));
                    std::cout << test_book;
                }
                book_data_.close();
            }
        }
        else if(next.substr(0,7)=="-author"){
            if(next.size()<=10) throw 1;
            Author targeted_author(next.substr(9,next.size()-10));
            std::vector<int> v_all=author_map_index_.Traverse(targeted_author);
            if(v_all.empty()) std::cout << std::endl;
            else{
                book_data_.open(file_name_book_data_);
                Book test_book;
                for(int i=0;i<v_all.size();i++){
                    book_data_.seekg(v_all[i]);
                    book_data_.read(reinterpret_cast<char*>(&test_book),sizeof(Book));
                    std::cout << test_book;
                }
                book_data_.close();
            }
        }
        else if(next.substr(0,8)=="-keyword"){
            if(next.size()<=11) throw 1;
            std::string c_key=next.substr(10,next.size()-11);
            if(c_key.empty()||c_key.size()>60) throw 1;
            for(int i=0;i<c_key.size();i++){
                if(c_key[i]=='|'||c_key[i]==' ') throw 1;
            }
            Keyword targeted_keyword(c_key);
            std::vector<int> v_all=keyword_index_.Traverse(targeted_keyword);
            if(v_all.empty()) std::cout << std::endl;
            else{
                book_data_.open(file_name_book_data_);
                Book test_book;
                for(int i=0;i<v_all.size();i++){
                    book_data_.seekg(v_all[i]);
                    book_data_.read(reinterpret_cast<char*>(&test_book),sizeof(Book));
                    std::cout << test_book;
                }
                book_data_.close();
            }
        }else throw 1;
    }
} // 先判断是不是 show finance（都是以 show 开头），然后分四种情况讨论，如无参数，则按照 ISBN 输出全部（traverse 函数）

void BookManagement::Buy(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<1) throw 1;
    std::string targeted_isbn=line.NextToken();
    ISBN targeted_ISBN(targeted_isbn);
    const int location=isbn_map_.Get(targeted_ISBN,0);
    book_data_.open(file_name_book_data_);
    Book target_book;
    book_data_.seekg(location);
    book_data_.read(reinterpret_cast<char*>(&target_book),sizeof(Book));
    book_data_.close();
    std::string q=line.NextToken();
    if(q.size()>10) throw 1;
    int quantitY= str_to_int(q);
    if(quantitY<0||quantitY>target_book.quantity_) throw 1;
    double cost=quantitY*target_book.price_;
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) << std::fixed << cost << std::endl;
    target_book.quantity_-=quantitY;
    book_data_.open(file_name_book_data_);
    book_data_.seekp(location);
    book_data_.write(reinterpret_cast<char*>(&target_book),sizeof(Book));
    book_data_.close();
    logs.Addfinance(true,cost);
}

void BookManagement::Select(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<3) throw 1;
    std::string isbn_new=line.NextToken();
    ISBN new_isbn(isbn_new);
    book_data_.open(file_name_book_data_);
    int book_count=0;
    book_data_.seekg(0);
    book_data_.read(reinterpret_cast<char*>(&book_count),sizeof(int));
    book_data_.close();
    if(!(isbn_map_.Exist(new_isbn))){
        Book new_book(book_count,isbn_new);
        accounts.login_[accounts.login_.size()-1].selected_book_id=book_count;
        isbn_map_.Insert(new_isbn,0,sizeof(int)+book_count*sizeof(Book));
        //book_name_index_.Insert(new_book.book_name_,new_isbn,sizeof(int)+book_count*sizeof(Book));
        //author_map_index_.Insert(new_book.author_,new_isbn,sizeof(int)+book_count*sizeof(Book));
        //keyword_index_.Insert(new_book.keyword_,new_isbn,sizeof(int)+book_count*sizeof(Book));
        book_data_.open(file_name_book_data_);
        book_data_.seekp(sizeof(int)+book_count*sizeof(Book));
        book_data_.write(reinterpret_cast<char*>(&new_book),sizeof(Book));
        book_count++;
        book_data_.seekp(0);
        book_data_.write(reinterpret_cast<char*>(&book_count),sizeof(int));
        book_data_.close();
    }
    else{
        int loction=isbn_map_.Get(new_isbn,0);
        book_data_.open(file_name_book_data_);
        Book targeted_book;
        book_data_.seekg(loction);
        book_data_.read(reinterpret_cast<char*>(&targeted_book),sizeof(Book));
        book_data_.close();
        accounts.login_[accounts.login_.size()-1].selected_book_id=targeted_book.book_ID_;
    }
} // 检查是否有权限，检查是否有 ISBN，然后选中

void BookManagement::Modify(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<3||accounts.login_.back().selected_book_id==-1) throw 1;
    line.SetDelimiter(' ');
    std::string test_token=line.NextToken();
    if(test_token.empty()) throw 1;
    std::string test_content;
    int ck[5]={0,0,0,0,0};
    book_data_.open(file_name_book_data_);
    Book targeted_book;
    book_data_.clear();
    book_data_.seekg(sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    book_data_.read(reinterpret_cast<char*>(&targeted_book),sizeof(Book));
    book_data_.close();
    Book old_book=targeted_book;
    while(!(test_token.empty())){
        if(test_token.size()<5) throw 1;
        if(test_token.substr(0,5)=="-ISBN"){
            if(ck[0]){throw 1;}
            ck[0]=1;
            if(test_token.size()<=6) throw 1;
            test_content=test_token.substr(6,test_token.size()-6);
            if(test_content.empty()||test_content.size()>20||test_content==std::string(targeted_book.isbn_.value)){throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.isbn_.value[i]=test_content[i];
            targeted_book.isbn_.value[test_content.size()]='\0';
        }
        else if(test_token.substr(0,5)=="-name"){
            if(ck[1]){throw 1;}
            ck[1]=1;
            if(test_token.size()<=8) throw 1;
            test_content=test_token.substr(7,test_token.size()-8);
            if(test_content.empty()||test_content.size()>60){throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.book_name_.value[i]=test_content[i];
            targeted_book.book_name_.value[test_content.size()]='\0';
        }
        else if(test_token.substr(0,6)=="-price"){
            if(ck[2]){throw 1;}
            ck[2]=1;
            if(test_token.size()<=7||test_token.size()>20) throw 1;
            test_content=test_token.substr(7,test_token.size()-7);
            for(int i=0;i<test_content.size();i++){
                if(test_content[i]!='.'&&!(test_content[i]>='0'&&test_content[i]<='9')) throw 1;
            }
            double ans= String_to_t<double>(test_content);
            if(ans<0) throw 1;
            targeted_book.price_=ans;
        }
        else if(test_token.substr(0,7)=="-author"){
            if(ck[3]){throw 1;}
            ck[3]=1;
            if(test_token.size()<=10) throw 1;
            test_content=test_token.substr(9,test_token.size()-10);
            if(test_content.empty()||test_content.size()>60){throw 1;}
            for(int i=0;i<test_content.size();i++) targeted_book.author_.value[i]=test_content[i];
            targeted_book.author_.value[test_content.size()]='\0';
        }
        else if(test_token.substr(0,8)=="-keyword"){
            if(ck[4]){throw 1;}
            ck[4]=1;
            if(test_token.size()<=11) throw 1;
            test_content=test_token.substr(10,test_token.size()-11);
            if(test_content.empty()||test_content.size()>60){throw 1;}
            TokenScanner a_key(test_content,'|');
            std::string b_key=a_key.NextToken();
            std::unordered_map<std::string,int> map1;
            map1.clear();
            while(!b_key.empty()){
                if(map1.count(b_key)) throw 1;
                map1.insert(std::pair<std::string,int>(b_key,0));
                b_key=a_key.NextToken();
            }
            for(int i=0;i<test_content.size();i++) targeted_book.keyword_.value[i]=test_content[i];
            targeted_book.keyword_.value[test_content.size()]='\0';
        }else{throw 1;}
        test_token=line.NextToken();
    }
    book_data_.open(file_name_book_data_);
    book_data_.seekp(sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    book_data_.write(reinterpret_cast<char*>(&targeted_book),sizeof(Book));
    book_data_.close();
    if(ck[0]){
        isbn_map_.Erase(old_book.isbn_,0);
        isbn_map_.Insert(targeted_book.isbn_,0,sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    }
    if(ck[1]){
        book_name_index_.Erase(old_book.book_name_,old_book.isbn_);
        book_name_index_.Insert(targeted_book.book_name_,targeted_book.isbn_,sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    }
    if(ck[3]){
        author_map_index_.Erase(old_book.author_,old_book.isbn_);
        author_map_index_.Insert(targeted_book.author_,targeted_book.isbn_,sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    }
    if(ck[4]){
        TokenScanner old_key(std::string(old_book.keyword_.value),'|');
        std::string test_key_token=old_key.NextToken();
        while(!(test_key_token.empty())){
            Keyword test_old(test_key_token);
            keyword_index_.Erase(test_old,old_book.isbn_);
            test_key_token=old_key.NextToken();
        }
        TokenScanner new_key(std::string(targeted_book.keyword_.value),'|');
        test_key_token=new_key.NextToken();
        while(!(test_key_token.empty())){
            Keyword test_new(test_key_token);
            keyword_index_.Insert(test_new,targeted_book.isbn_,sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
            test_key_token=new_key.NextToken();
        }
    }
} // 检查是否有权限

void BookManagement::ImportBook(TokenScanner& line, AccountManagement& accounts, LogManagement& logs){
    if(accounts.login_.empty()||accounts.login_.back().user.GetPriority()<3||accounts.login_.back().selected_book_id==-1) throw 1;
    line.SetDelimiter(' ');
    std::string q=line.NextToken();
    if(q.empty()||q.size()>10) throw 1;
    std::string t=line.NextToken();
    if(t.empty()||t.size()>13) throw 1;
    if(line.if_left()) throw 1;
    if(q[0]=='-') throw 1;
    int quantitY = 0;
    for(int i=0;i<q.size();i++){
        if(!(q[0]>='0'&&q[0]<='9')) throw 1;
        quantitY*=10;
        quantitY+=int(q[i]-'0');
    }
    double total_cost= 0.00;
    for(int i=0;i<t.size();i++){
        if(t[i]!='.'&&(t[i]<'0'||t[i]>'9')) throw 1;
    }
    total_cost=String_to_t<double>(t);
    book_data_.open(file_name_book_data_);
    Book selected_book;
    book_data_.seekg(sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    book_data_.read(reinterpret_cast<char*>(&selected_book),sizeof(Book));
    selected_book.quantity_+=quantitY;
    selected_book.total_cost_+=total_cost;
    book_data_.seekp(sizeof(int)+accounts.login_.back().selected_book_id*sizeof(Book));
    book_data_.write(reinterpret_cast<char*>(&selected_book),sizeof(Book));
    book_data_.close();
    logs.Addfinance(false,total_cost);
} // 检查是否有权限

