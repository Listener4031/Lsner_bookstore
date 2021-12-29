//#include "bookstore.h"

/*
#include "token_scanner.h"
#include "accounts.h"
#include "book.h"
#include "unrolled_linked_list.h"
#include "log.h"
 */
#include "token_scanner.h"
#include "accounts.h"
#include "book.h"
#include "unrolled_linked_list.h"
#include "log.h"


int main(){
    AccountManagement accounts("file44444444_data_all","file44444444_acoount_all","file44444444_acount_lead");
    BookManagement books("file44444444_1","file44444444_2","file44444444_3","file44444444_4","file44444444_5","file44444444_6","file44444444_7","file44444444_8","file44444444_9");
    LogManagement logs("file44444444_log_all","file44444444_finance_all");
    std::string op;
    while(true){
        try{
            getline(std::cin,op);
            TokenScanner scanner(op,' ');
            std::string op_real=scanner.NextToken();
            if(op_real.empty()){
                accounts.login_.clear();
                break;
            }
            if(op_real=="su"){
                accounts.SwitchUser(scanner);
            }
            else if(op_real=="logout"){
                accounts.LogOut(scanner);
            }
            else if(op_real=="register"){
                accounts.RegisterUser(scanner);
            }
            else if(op_real=="passwd"){
                accounts.ChangePassword(scanner);
            }
            else if(op_real=="useradd"){
                accounts.AddUser(scanner);
            }
            else if(op_real=="delete"){
                accounts.RemoveUser(scanner);
            }
            else if(op_real=="buy"){
                books.Buy(scanner,accounts,logs);
            }
            else if(op_real=="show"){
                books.Show(scanner,accounts,logs);
            }
            else if(op_real=="select"){
                books.Select(scanner,accounts,logs);
            }
            else if(op_real=="modify"){
                books.Modify(scanner,accounts,logs);
            }
            else if(op_real=="import"){
                books.ImportBook(scanner,accounts,logs);
            }
            else if(op_real=="quit"||op_real=="exit"){accounts.login_.clear();break;}
            else throw 1;
        }catch(int){std::cout << "Invalid\n";}
    }
    return 0;
}

/*
su root sjtu
useradd rbq rbq 3 rbq
su rbq rbq
select 1
modify -ISBN=1 -name="1" -author="1" -keyword="1" -price=1.0
modify -name="name1" -author="author1" -keyword="keyword1" -price=10.00
buy name1 0
buy name1 1
import name1 1
import 1 1
buy name1 0
buy name1 1
buy 1 0
buy 1 1
buy 1 2
exit
 
 
Invalid
Invalid
Invalid
Invalid
Invalid
Invalid
0.00
10.00
Invalid
 
 */