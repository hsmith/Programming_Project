//Notes++ Command Line UI
//Creating a Menu asking the user to either:
//1) Make a File
//2) Make a Note
//3) Assign Tags
//4) Search
//5) Exit Program

//Error Check: Make sure a proper selection is made!

#include <iostream>
using namespace std;

int main(){
    
    cout<<"Welcome to Notes++: A Note Organizer" <<endl;
    cout<<endl <<"Please type your selection from one of the options below:" <<endl;
    
    cout<<"1) Make a File" <<endl
        <<"2) Make a Note" <<endl
        <<"3) Assign Tags" <<endl
        <<"4) Search" <<endl
        <<"5) Exit Program" <<endl;

    
    int selection = 0;
    
    //Initiate loop, continue until option 5 to exit is chosen
    while(selection != 5 ){
        
        bool isValid = false;
        while(!isValid){
            cout<<endl <<"Your selection: ";
            cin>> selection;
            
            if(cin.good())
            {
                isValid = true;
            }
            
            else{
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout<<endl <<"Wrong Input! Please re-enter a proper selection!" <<endl;
            }
        }
        
        //The Selection is an integer, but is it a number between 1 and 5 (inclusive)?
        if(selection > 5 || selection < 1){
            continue;
        }
        
        //Option 1 was Chosen
        else if(selection == 1){
            
        }
        
        //Option 2 was Chosen
        else if(selection == 2){
            
        }
        
        //Option 3 was Chosen
        else if(selection == 3){
            
        }
        
        //Option 4 was Chosen
        else if(selection == 4){
            
        }
        
    }
    
    
    return 1;
}