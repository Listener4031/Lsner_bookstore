//
// Created by 韦捷 on 2021/12/18.
//

#ifndef UNTITLED2_BOOK_H
#define UNTITLED2_BOOK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include "token_scanner.h"
#include "unrolled_linked_list.h"
#include "log.h"
#include <iomanip>
struct ISBN {
    char value[21];
    ISBN(){memset(value,'\0',21);}
    ISBN(const std::string& s){
        if(s.size()>20) throw 1;
        for(unsigned long long int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    friend bool operator==(const ISBN& x,const ISBN& y){return (strcmp(x.value,y.value)==0);}
    friend bool operator<(const ISBN& x,const ISBN& y){return (strcmp(x.value,y.value)<0);}
    friend bool operator>(const ISBN& x,const ISBN& y){return (strcmp(x.value,y.value)>0);}
    friend bool operator!=(const ISBN& x,const ISBN& y){return strcmp(x.value,y.value)!=0;}
    friend bool operator<=(const ISBN &x,const ISBN &y){return (x==y||x<y);}
    friend bool operator>=(const ISBN &x,const ISBN &y){return (x==y||x>y);}
    ISBN& operator=(const ISBN& rhs){strcpy(value,rhs.value);return (*this);}
    friend std::ostream& operator<<(std::ostream& os,const ISBN &isbn){
        os << std::string(isbn.value);
        return os;
    }
};

struct BookName {
    char value[61];
    BookName(){memset(value,'\0',21);}
    BookName(const std::string& s){
        if(s.size()>60) throw 1;
        for(unsigned long long int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    friend bool operator==(const BookName& x,const BookName& y){return (strcmp(x.value,y.value)==0);}
    friend bool operator<(const BookName& x,const BookName& y){return (strcmp(x.value,y.value)<0);}
    friend bool operator>(const BookName& x,const BookName& y){return (strcmp(x.value,y.value)>0);}
    friend bool operator!=(const BookName& x,const BookName& y){return strcmp(x.value,y.value)!=0;}
    friend bool operator<=(const BookName &x,const BookName &y){return (x==y||x<y);}
    friend bool operator>=(const BookName &x,const BookName &y){return (x==y||x>y);}
    friend std::ostream& operator<<(std::ostream& os,const BookName &bookname){
        os <<std::string(bookname.value);
        return os;
    }
};

struct Author {
    char value[61];
    Author(){memset(value,'\0',21);}
    Author(const std::string& s){
        if(s.size()>60) throw 1;
        for(unsigned long long int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    friend bool operator==(const Author& x,const Author& y){return (strcmp(x.value,y.value)==0);}
    friend bool operator<(const Author& x,const Author& y){return (strcmp(x.value,y.value)<0);}
    friend bool operator>(const Author& x,const Author& y){return (strcmp(x.value,y.value)>0);}
    friend bool operator!=(const Author& x,const Author& y){return strcmp(x.value,y.value)!=0;}
    friend bool operator<=(const Author &x,const Author &y){return (x==y||x<y);}
    friend bool operator>=(const Author &x,const Author &y){return (x==y||x>y);}
    friend std::ostream& operator<<(std::ostream& os,const Author &author){
        os <<std::string(author.value);
        return os;
    }
};

struct Keyword {
    char value[61];
    Keyword(){memset(value,'\0',21);}
    Keyword(const std::string& s){
        if(s.size()>60) throw 1;
        for(int i=0;i<s.size();i++) value[i]=s[i];
        value[s.size()]='\0';
    }
    friend bool operator==(const Keyword& x,const Keyword& y){return (strcmp(x.value,y.value)==0);}
    friend bool operator<(const Keyword& x,const Keyword& y){return (strcmp(x.value,y.value)<0);}
    friend bool operator>(const Keyword& x,const Keyword& y){return (strcmp(x.value,y.value)>0);}
    friend bool operator!=(const Keyword& x,const Keyword& y){return strcmp(x.value,y.value)!=0;}
    friend bool operator<=(const Keyword &x,const Keyword &y){return (x==y||x<y);}
    friend bool operator>=(const Keyword &x,const Keyword &y){return (x==y||x>y);}
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
                                                                                                                                                                              book_name_(bookName),author_(author),quantity_(quantity),price_(price),total_cost_(_total_cost),keyword_(keyword){

    }// 这样方便构造，但注意 keyword 需要以升序重新排列
    Book(int id, const std::string& isbn):book_ID_(id),isbn_(isbn), book_name_(""), author_(""), keyword_(""),quantity_(0),price_(0),total_cost_(0){} // 将除 ISBN 以外的部分全部为空字符串或 0
    friend std::ostream& operator<<(std::ostream& os, const Book& book){
        os << book.isbn_ << '\t' << book.book_name_ << '\t' << book.author_ << '\t' << book.keyword_ << '\t';
        os << std::setiosflags(std::ios::fixed) << std::setprecision(2) << std::fixed << book.price_ << '\t';
        os << book.quantity_ << '\n';
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

    BookManagement(std::string name1,std::string name2,std::string name3,std::string name4,std::string name5,std::string name6,std::string name7,std::string name8,std::string name9);
    // 下面的指令请调用 accounts::getCurrentPriority() 来获取权限

    void Show(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 先判断是不是 show finance（都是以 show 开头），然后分四种情况讨论，如无参数，则按照 ISBN 输出全部（traverse 函数）

    void Buy(TokenScanner& line, AccountManagement& accounts, LogManagement& logs);

    void Select(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 检查是否有权限，检查是否有 ISBN，然后选中

    void Modify(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 检查是否有权限

    void ImportBook(TokenScanner& line, AccountManagement& accounts, LogManagement& logs); // 检查是否有权限
};


#endif //UNTITLED2_BOOK_H
