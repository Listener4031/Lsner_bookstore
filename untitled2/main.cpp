#include "token_scanner.h"
#include "accounts.h"
#include "book.h"
#include "unrolled_linked_list.h"
#include "log.h"

//using namespace std;

void Initialization();
//先检查文件是否存在，如不存在，则建立文件。
void ProcessLine(AccountManagement& accounts, BookManagement& books);
//调用相应类或者函数。
void StringToChar(const std::string& source, char* target, int targetMaxLength);
//将 source 转为 char
//注意：一定要设置最大长度！
int main(){
    AccountManagement accounts("file_data_all","file_acoount_all","file_acount_lead");
    BookManagement books("file_1","file_2","file_3","file_4","file_5","file_6","file_7","file_8","file_9");
    LogManagement logs;
    std::string op;
    while(true){
        try{
            getline(std::cin,op);
            TokenScanner scanner(op,' ');
            std::string op_real=scanner.NextToken();
            if(op_real.empty()) throw 1;
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
                accounts.AddUser(scanner,logs);
            }
            else if(op_real=="useradd"){
                accounts.AddUser(scanner,logs);
            }
            else if(op_real=="delete"){
                accounts.RemoveUser(scanner,logs);
            }
            else if(op_real=="buy"){
                books.Buy(scanner,accounts,logs);
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
            else throw 1;
        }catch(int){std::cout << "Invalid" << std::endl;}
    }
    return 0;
}
void Initialization(){

}

void ProcessLine(AccountManagement& accounts, BookManagement& books){

}

void StringToChar(const std::string& source, char* target, int targetMaxLength){
    target=new char[targetMaxLength+1];
    for(unsigned long long int i=0;i<source.size();i++) target[i]=source[i];
    target[source.size()]='\0';
}