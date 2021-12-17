```c++
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
const int sup=720;
const int inf=160;
int str_to_int(const string &a){
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
struct element{
    char index[66]="";
    int value;
};
struct block{
    element element_array[sup+5];
    int block_size;
};
struct lead{
    long long int location;
    char index[66]="";
    int value;
    long long int last;
    long long int next;
    int block_size;
};
int Element_cmp(const element &x,const element &y){
    const int cmp=strcmp(x.index,y.index);
    if(cmp==0&&x.value==y.value) return 0;
    else if((cmp==0&&x.value<y.value)||cmp<0) return -1;
    else return 1;
}
int Element_Lead_cmp(const element &x,const lead &y){
    const int cmp=strcmp(x.index,y.index);
    if(cmp==0&&x.value==y.value) return 0;
    else if((cmp==0&&x.value<y.value)||cmp<0) return -1;
    else return 1;
}
fstream element_all;//only for all the elements
fstream lead_search;//int element_count | int lead_count | long long int head_location | lead ...
fstream lead_max_count;
void Insert(const char* index,const int &value){
    lead_search.clear();
    lead_search.open("file00_lead");
    if(!lead_search){
        lead_search.open("file00_lead",ofstream::out);
        lead_search.close();
        lead_search.open("file00_lead");
    }
    lead_search.seekg(0,ios::beg);
    int m;
    lead_search.read(reinterpret_cast<char*>(&m),sizeof(int));
    lead_search.close();
    if(m==0) {
        element new_ele;
        strcpy(new_ele.index, index);
        new_ele.value = value;
        element_all.clear();
        element_all.open("file00_element");
        if (!element_all) {
            element_all.open("file00_element", ofstream::out);
            element_all.close();
            element_all.open("file00_element");
        }
        element_all.seekp(sizeof(block), ios::beg);
        element_all.write(reinterpret_cast<char *>(&new_ele), sizeof(element));
        element_all.close();
        lead new_lead;
        new_lead.block_size = 1;
        strcpy(new_lead.index, index);
        new_lead.last = 2 * sizeof(int) + sizeof(long long int);
        new_lead.location = sizeof(block);
        new_lead.next = 2 * sizeof(int) + sizeof(long long int);
        new_lead.value = value;//finish the assignment
        lead_search.clear();
        lead_search.open("file00_lead");
        if (!lead_search) {
            lead_search.open("file00_lead", ofstream::out);
            lead_search.close();
            lead_search.open("file00_lead");
        }
        long long int loc = 2 * sizeof(int) + sizeof(long long int);
        lead_search.seekp(2 * sizeof(int), ios::beg);
        lead_search.write(reinterpret_cast<char *>(&loc), sizeof(long long int));
        lead_search.seekp(2 * sizeof(int) + sizeof(long long int) + sizeof(lead), ios::beg);
        lead_search.write(reinterpret_cast<char *>(&new_lead), sizeof(lead));
        int lead_count = 2;
        lead_search.seekp(sizeof(int), ios::beg);
        lead_search.write(reinterpret_cast<char *>(&lead_count), sizeof(int));
        int element_count = 1;
        lead_search.seekp(0, ios::beg);
        lead_search.write(reinterpret_cast<char *>(&element_count), sizeof(int));
        lead_search.seekg(2 * sizeof(int) + sizeof(long long int));
        lead_search.read(reinterpret_cast<char *>(&new_lead), sizeof(lead));
        new_lead.last = 2 * sizeof(int) + sizeof(long long int) + sizeof(lead);
        new_lead.next = 2 * sizeof(int) + sizeof(long long int) + sizeof(lead);
        lead_search.seekp(2 * sizeof(int) + sizeof(long long int));
        lead_search.write(reinterpret_cast<char *>(&new_lead), sizeof(lead));
        lead_search.close();
        lead_max_count.clear();
        lead_max_count.open("file00_max_count");
        if(!lead_max_count){
            lead_max_count.open("file00_max_count", ofstream::out);
            lead_max_count.close();
            lead_max_count.open("file00_max_count");
        }
        int max_count=2;
        lead_max_count.seekp(0);
        lead_max_count.write(reinterpret_cast<char*>(&max_count),sizeof(int));
        lead_max_count.close();
        return;
    }
    else{
        element new_ele;
        strcpy(new_ele.index,index);
        new_ele.value=value;//finish the assignment
        lead_search.clear();
        lead_search.open("file00_lead");
        if(!lead_search){
            lead_search.open("file00_lead",ofstream::out);
            lead_search.close();
            lead_search.open("file00_lead");
        }
        element_all.clear();
        element_all.open("file00_element");
        if(!element_all){
            element_all.open("file00_element",ofstream::out);
            element_all.close();
            element_all.open("file00_element");
        }
        int lead_count;
        lead_search.seekg(sizeof(int));
        lead_search.read(reinterpret_cast<char*>(&lead_count),sizeof(int));
        long long int loc;
        lead_search.seekg(2*sizeof(int));
        lead_search.read(reinterpret_cast<char*>(&loc),sizeof(long long int));
        lead test_lead;
        for(int i=0;i<lead_count;++i){//search the lead
            lead_search.seekg(loc,ios::beg);
            lead_search.read(reinterpret_cast<char*>(&test_lead),sizeof(lead));
            int cmp=Element_Lead_cmp(new_ele,test_lead);
            if(cmp==0){lead_search.close();element_all.close();return;}
            else if(cmp<0||(cmp>0&&i==lead_count-1)) {
                if (i == 0 && cmp < 0) {
                    lead_search.close();
                    element_all.close();
                    return;
                }
                else {
                    if (cmp < 0) {
                        loc = test_lead.last;
                        lead_search.seekg(loc, ios::beg);
                        lead_search.read(reinterpret_cast<char *>(&test_lead), sizeof(lead));
                    }
                    const long long int all_loc = test_lead.location;
                    const int block_size = test_lead.block_size;
                    block test_block;
                    element_all.clear();
                    element_all.seekg(all_loc);
                    element_all.read(reinterpret_cast<char *>(&test_block), sizeof(block));
                    element test_element;
                    if (block_size == 1) {
                        element_all.seekg(all_loc);
                        element_all.read(reinterpret_cast<char *>(&test_element), sizeof(element));
                        int element_cmp = Element_cmp(new_ele, test_element);
                        if (element_cmp != 0) {
                            test_lead.block_size++;
                            lead_search.seekp(loc, ios::beg);
                            lead_search.write(reinterpret_cast<char *>(&test_lead), sizeof(lead));
                            test_block.element_array[1].value=new_ele.value;
                            strcpy(test_block.element_array[1].index,new_ele.index);
                        }
                        element_all.clear();
                        element_all.seekp(all_loc, ios::beg);
                        element_all.write(reinterpret_cast<char *>(&test_block), sizeof(block));
                        element_all.close();
                        lead_search.close();
                        return;
                    }
                    int h = 0, t = block_size - 1, j = 0;
                    int element_cmp;
                    while (h < t) {
                        j = (h + t + 1) / 2;
                        element_cmp = Element_cmp(test_block.element_array[j], new_ele);
                        if (element_cmp > 0) t = j - 1;
                        else h = j;
                    }
                    j = (h + t) / 2;
                    element_cmp = Element_cmp(test_block.element_array[j], new_ele);
                    if (element_cmp == 0) {
                        element_all.close();
                        lead_search.close();
                        return;
                    }
                    ++j;
                    for (int k = block_size - 1; k >= j; --k) {
                        test_block.element_array[k + 1].value = test_block.element_array[k].value;
                        strcpy(test_block.element_array[k + 1].index, test_block.element_array[k].index);
                    }
                    test_block.element_array[j].value = new_ele.value;
                    strcpy(test_block.element_array[j].index, new_ele.index);
                    test_lead.block_size++;//change here
                    if (test_lead.block_size < sup) {
                        int element_count = 0;
                        lead_search.seekg(0, ios::beg);
                        lead_search.read(reinterpret_cast<char *>(&element_count), sizeof(int));
                        element_count++;
                        lead_search.seekp(0, ios::beg);
                        lead_search.write(reinterpret_cast<char *>(&element_count), sizeof(int));
                        lead_search.seekp(loc, ios::beg);
                        lead_search.write(reinterpret_cast<char *>(&test_lead), sizeof(lead));
                        element_all.clear();
                        element_all.seekp(all_loc);
                        element_all.write(reinterpret_cast<char *>(&test_block), sizeof(block));
                        lead_search.close();
                        element_all.close();
                        return;
                    } else {
                        const int mid = sup / 2;
                        lead_max_count.clear();
                        lead_max_count.open("file00_max_count");
                        if (!lead_max_count) {
                            lead_max_count.open("file00_max_count", ofstream::out);
                            lead_max_count.close();
                            lead_max_count.open("file00_max_count");
                        }
                        int max_count = 0;
                        lead_max_count.seekg(0);
                        lead_max_count.read(reinterpret_cast<char *>(&max_count), sizeof(int));
                        const long long int new_block_loc = max_count * sizeof(block);
                        block new_block;
                        for (int k = mid; k < test_lead.block_size; k++) {
                            strcpy(new_block.element_array[k - mid].index, test_block.element_array[k].index);
                            new_block.element_array[k - mid].value = test_block.element_array[k].value;
                        }
                        element_all.clear();
                        element_all.seekp(new_block_loc, ios::beg);
                        element_all.write(reinterpret_cast<char *>(&new_block), sizeof(block));
                        lead new_lead;
                        new_lead.block_size = test_lead.block_size - mid;
                        strcpy(new_lead.index, new_block.element_array[0].index);
                        new_lead.location = new_block_loc;
                        new_lead.value = new_block.element_array[0].value;
                        new_lead.last = loc;
                        new_lead.next = test_lead.next;
                        const long long int new_lead_loc =
                                2 * sizeof(int) + sizeof(long long int) + max_count * sizeof(lead);
                        lead_search.seekp(new_lead_loc, ios::beg);
                        lead_search.write(reinterpret_cast<char *>(&new_lead), sizeof(lead));
                        lead_search.seekg(test_lead.next, ios::beg);
                        lead_search.read(reinterpret_cast<char *>(&new_lead), sizeof(lead));
                        new_lead.last = new_lead_loc;
                        lead_search.seekp(test_lead.next, ios::beg);
                        lead_search.write(reinterpret_cast<char *>(&new_lead), sizeof(lead));
                        test_lead.block_size = mid;
                        test_lead.next = new_lead_loc;
                        lead_search.seekp(loc, ios::beg);
                        lead_search.write(reinterpret_cast<char *>(&test_lead), sizeof(lead));
                        int lead_count;
                        lead_search.seekg(sizeof(int));
                        lead_search.read(reinterpret_cast<char *>(&lead_count), sizeof(int));
                        lead_count++;
                        lead_search.seekp(sizeof(int), ios::beg);
                        lead_search.write(reinterpret_cast<char *>(&lead_count), sizeof(int));
                        element_all.clear();
                        element_all.seekp(all_loc);
                        element_all.write(reinterpret_cast<char *>(&test_block), sizeof(block));
                        int element_count;
                        lead_search.seekg(0, ios::beg);
                        lead_search.read(reinterpret_cast<char *>(&element_count), sizeof(int));
                        element_count++;
                        lead_search.seekp(0, ios::beg);
                        lead_search.write(reinterpret_cast<char *>(&element_count), sizeof(int));
                        lead_search.close();
                        element_all.close();
                        max_count++;
                        lead_max_count.seekp(0);
                        lead_max_count.write(reinterpret_cast<char *>(&max_count), sizeof(int));
                        lead_max_count.close();
                        return;
                    }
                }
            }
            else{
                loc=test_lead.next;
                continue;
            }
        }
        lead_search.close();
        element_all.close();
        return;
    }
}
void Delete(const char* index,const int &value){
    element targeted_element;
    strcpy(targeted_element.index,index);
    targeted_element.value=value;
    lead_search.clear();
    lead_search.open("file00_lead");
    if(!lead_search){
        lead_search.open("file00_lead",ofstream::out);
        lead_search.close();
        lead_search.open("file00_lead");
    }
    int lead_count;
    lead_search.seekg(sizeof(int));
    lead_search.read(reinterpret_cast<char*>(&lead_count),sizeof(int));
    long long int lead_loc;
    lead_search.seekg(2*sizeof(int));
    lead_search.read(reinterpret_cast<char*>(&lead_loc),sizeof(long long int));
    lead test_lead;
    int lead_cmp=0;
    element_all.clear();
    element_all.open("file00_element");
    if(!element_all){
        element_all.open("file00_element",ofstream::out);
        element_all.close();
        element_all.open("file00_element");
    }
    for(int i=0;i<lead_count;++i) {
        lead_search.seekg(lead_loc,ios::beg);
        lead_search.read(reinterpret_cast<char *>(&test_lead), sizeof(lead));
        lead_cmp = Element_Lead_cmp(targeted_element, test_lead);
        if (lead_cmp < 0) {
            element_all.close();
            lead_search.close();
            return;
        } else if (lead_cmp > 0) {
            const long long int all_loc = test_lead.location;
            const int block_size = test_lead.block_size;
            if(block_size==1){
                lead_loc = test_lead.next;
                continue;
            }
            block test_block;
            element_all.clear();
            element_all.seekg(all_loc);
            element_all.read(reinterpret_cast<char*>(&test_block),sizeof(block));
            int h = 0, t = block_size - 1, j = 0;
            int element_cmp = 0;
            while (h < t) {
                j = (h + t + 1) / 2;
                element_cmp = Element_cmp(test_block.element_array[j], targeted_element);
                if (element_cmp > 0) t = j - 1;
                else h = j;
            }
            j = (h + t) / 2;
            element_cmp = Element_cmp(test_block.element_array[j], targeted_element);
            if(element_cmp!=0){
                lead_loc = test_lead.next;
                continue;
            }
            else{
                for(int k=j+1;k<block_size;k++) {
                    strcpy(test_block.element_array[k-1].index,test_block.element_array[k].index);
                    test_block.element_array[k-1].value=test_block.element_array[k].value;
                }
                element_all.seekp(all_loc,ios::beg);
                element_all.write(reinterpret_cast<char*>(&test_block),sizeof(block));
                test_lead.block_size--;
                lead_search.seekp(lead_loc,ios::beg);
                lead_search.write(reinterpret_cast<char*>(&test_lead),sizeof(lead));
                element_all.close();
                lead_search.close();
                return;
            }
        } else {
            long long int all_loc = test_lead.location;
            const int block_size = test_lead.block_size;
            if(block_size==1){
                lead_count--;
                lead_search.seekp(sizeof(int),ios::beg);
                lead_search.write(reinterpret_cast<char*>(&lead_count),sizeof(int));
                long long int next=test_lead.next;
                long long int last=test_lead.last;
                lead_search.seekg(next,ios::beg);
                lead_search.read(reinterpret_cast<char *>(&test_lead), sizeof(lead));
                test_lead.last=last;
                lead_search.seekp(next,ios::beg);
                lead_search.write(reinterpret_cast<char *>(&test_lead), sizeof(lead));
                lead_search.seekg(last,ios::beg);
                lead_search.read(reinterpret_cast<char *>(&test_lead), sizeof(lead));
                test_lead.next=next;
                lead_search.seekp(last,ios::beg);
                lead_search.write(reinterpret_cast<char *>(&test_lead), sizeof(lead));
            }
            else{
                block test_block;
                element_all.clear();
                element_all.seekg(all_loc,ios::beg);
                element_all.read(reinterpret_cast<char*>(&test_block),sizeof(block));
                for(int j = 1; j < block_size; j++) {
                    strcpy(test_block.element_array[j-1].index,test_block.element_array[j].index);
                    test_block.element_array[j-1].value=test_block.element_array[j].value;
                }
                element_all.clear();
                element_all.seekp(all_loc,ios::beg);
                element_all.write(reinterpret_cast<char*>(&test_block),sizeof(block));
                strcpy(test_lead.index,test_block.element_array[0].index);
                test_lead.value=test_block.element_array[0].value;
                test_lead.block_size--;
                lead_search.seekp(lead_loc,ios::beg);
                lead_search.write(reinterpret_cast<char*>(&test_lead),sizeof(lead));
            }
            int element_count=0;
            lead_search.seekg(0,ios::beg);
            lead_search.read(reinterpret_cast<char*>(&element_count),sizeof(int));
            element_count--;
            lead_search.seekp(0,ios::beg);
            lead_search.write(reinterpret_cast<char*>(&element_count),sizeof(int));
            element_all.close();
            lead_search.close();
            return;
        }
    }
    element_all.close();
    lead_search.close();
    return;
}
void Find(const char* index){
    lead_search.clear();
    lead_search.open("file00_lead");
    if(!lead_search){
        lead_search.open("file00_lead",ofstream::out);
        lead_search.close();
        lead_search.open("file00_lead");
    }
    element_all.clear();
    element_all.open("file00_element");
    if(!element_all){
        element_all.open("file00_element",ofstream::out);
        element_all.close();
        element_all.open("file00_element");
    }
    int lead_count;
    lead_search.seekg(sizeof(int),ios::beg);
    lead_search.read(reinterpret_cast<char*>(&lead_count),sizeof(int));
    long long int loc;
    lead_search.seekg(2*sizeof(int),ios::beg);
    lead_search.read(reinterpret_cast<char*>(&loc),sizeof(long long int));
    int index_cmp=0;
    int count_out=0;
    lead test_lead;
    for(int i=0;i<lead_count;++i){
        lead_search.seekg(loc,ios::beg);
        lead_search.read(reinterpret_cast<char*>(&test_lead),sizeof(lead));
        index_cmp=strcmp(test_lead.index,index);
        if(index_cmp<=0) {
            long long int loc_all = test_lead.location;
            int block_size = test_lead.block_size;
            block test_block;
            element_all.clear();
            element_all.seekg(loc_all);
            element_all.read(reinterpret_cast<char *>(&test_block), sizeof(block));
            for (int j = 0; j < block_size; ++j) {
                index_cmp = strcmp(test_block.element_array[j].index, index);
                if (index_cmp == 0) {
                    cout << test_block.element_array[j].value << " ";
                    count_out++;
                }
            }
            loc = test_lead.next;
            continue;
        }
        else break;
    }
    element_all.close();
    lead_search.close();
    if(!count_out) cout << "null" << endl;
    else cout << endl;
}
void Initialize(){
    lead_search.clear();
    lead_search.open("file00_lead");
    if(!lead_search){
        lead_search.open("file00_lead",ofstream::out);
        lead_search.close();
        lead_search.open("file00_lead");
    }
    int m=0;
    lead_search.seekg(0,ios::beg);
    lead_search.read(reinterpret_cast<char*>(&m),sizeof(int));
    lead_search.close();
    if(m>0) return;
    else {
        lead_search.clear();
        lead_search.open("file00_lead");
        if(!lead_search){
            lead_search.open("file00_lead",ofstream::out);
            lead_search.close();
            lead_search.open("file00_lead");
        }
        m = 0;
        lead_search.seekp(0,ios::beg);
        lead_search.write(reinterpret_cast<char *>(&m), sizeof(int));
        m = 1;
        lead_search.seekp(sizeof(int),ios::beg);
        lead_search.write(reinterpret_cast<char *>(&m), sizeof(int));
        long long int head_location = 2 * sizeof(int) + sizeof(long long int);
        lead_search.seekp(2 * sizeof(int),ios::beg);
        lead_search.write(reinterpret_cast<char *>(&head_location), sizeof(long long int));
        lead min;
        min.block_size = 1;
        min.last = head_location;
        min.location = 0;
        min.next = head_location;
        min.value = -2147483648;
        lead_search.seekp(head_location,ios::beg);
        lead_search.write(reinterpret_cast<char *>(&min), sizeof(lead));
        lead_search.close();
        element_all.clear();
        element_all.open("file00_element");
        if(!element_all){
            element_all.open("file00_element",ofstream::out);
            element_all.close();
            element_all.open("file00_element");
        }
        element min_ele;
        min_ele.value = min.value;
        element_all.seekp(0,ios::beg);
        element_all.write(reinterpret_cast<char *>(&min_ele), sizeof(element));
        element_all.close();
        return;
    }
}
int main() {
    Initialize();
    int n;
    cin >> n;
    string op;
    getchar();
    for (int i = 0; i < n; i++) {
        getline(cin, op);
        const unsigned long int l = op.size();
        unsigned int h, t;
        if (op[0] == 'i') {
            h = 6;
            while (op[h] == ' ') h++;
            t = h;
            while (op[t] != ' ' && t < l) t++;
            string a = op.substr(h, t - h);
            h = t;
            char index[66];
            for (int i = 0; i < a.size(); i++) index[i] = a[i];
            index[a.size()] = '\0';
            while (op[h] == ' ') h++;
            t = h;
            while (op[t] != ' ' && t < l) t++;
            string b = op.substr(h, t - h);
            h = t;
            Insert(index, str_to_int(b));
            continue;
        }
        if (op[0] == 'd') {
            h = 6;
            while (op[h] == ' ') h++;
            t = h;
            while (op[t] != ' ' && t < l) t++;
            string a = op.substr(h, t - h);
            h = t;
            char index[66];
            for (int i = 0; i < a.size(); i++) index[i] = a[i];
            index[a.size()] = '\0';
            while (op[h] == ' ') h++;
            t = h;
            while (op[t] != ' ' && t < l) t++;
            string b = op.substr(h, t - h);
            h = t;
            Delete(index, str_to_int(b));
            continue;
        }
        if (op[0] == 'f') {
            h = 5;
            while (op[h] == ' ') h++;
            t = h;
            while (op[t] != ' ' && t < l) t++;
            string a = op.substr(h, t - h);
            h = t;
            char index[66];
            for (int i = 0; i < a.size(); i++) index[i] = a[i];
            index[a.size()] = '\0';
            Find(index);
            continue;
        }
    }
    return 0;
}
```

