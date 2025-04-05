#include<iostream>
#include<vector>
using namespace std;
class DynamicTable{
    vector<int> table;
    int capacity;
    int size;
    void resize(){
        capacity*=2;
        vector<int> newTable(capacity);
        for(int i=0;i<size;i++){
            newTable[i]=table[i];
        }
        table=newTable;
    }
    public:
        DynamicTable():capacity(1),size(0){
            table.resize(capacity);
        }
        void insert(int value){
            if(size==capacity){
                resize();
                cout<<"Table is resizing from "<<size<<" to "<<capacity<<endl;
            }
            table[size++]=value;
        }
        void display()const{
            /*for(int i=0;i<size*2;i++){
                cout<<" ";
                if(i==0){
                    cout<<"+ ";
                }
                if(i==(size*2)-1){
                    cout<<"+";
                    break;
                }
                cout<<"-";    
            }
            cout<<endl;*/
            for(int i=0;i<size;i++){
                cout<<table[i]<<" ";
            }
            cout<<endl;
            /*for(int i=0;i<size*2;i++){
                cout<<" ";
                if(i==0){
                    cout<<"+ ";
                }
                if(i==(size*2)-1){
                    cout<<"+";
                    break;
                }
                cout<<"-";    
            }
            cout<<endl;*/
        }
};
int main(){
    DynamicTable dt;
    dt.insert(1);
    dt.display();
    dt.insert(2);
    dt.display();
    dt.insert(3);
    dt.display();
    dt.insert(4);
    dt.display();
    dt.insert(5);
    dt.display();
    dt.insert(6);
    dt.display();
    dt.insert(7);
    dt.display();
    dt.insert(8);
    dt.display();
    return 0;
}
