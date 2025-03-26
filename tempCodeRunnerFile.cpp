/*
main.cpp
By Bilash Sarkar

This class simulates a SQL database
*/


#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "parsing.cpp"

using namespace std;
namespace fs = std::filesystem;

int main(){

    //i'll change this to cin>> or something but i dont want it to ask everytime. *************** maybe prompt the user to select a database when starting? **********
    string databaseName = "database"; //making the name a variable to enable future modification

    if(!fs::exists(databaseName)){ //is the database doesn't already exist..
        fs::create_directory(databaseName); //we create a new directory for it
        cout<<"New Database \"" <<databaseName<< "\" created!"<<endl;
    }
    else{
        cout<<"\""<<databaseName<<"\" exists"<<endl;
    }


    string input; //for user inputs

    //continously prompts user for a command.
    while(true){ //all user calls are here
        cout<<"> ";
        getline(cin, input);

        string lowerCaseInput = input;
        transform(lowerCaseInput.begin(), lowerCaseInput.end(), lowerCaseInput.begin(), ::tolower); //getting a lowercase version of input to check for case insensitve quit or exit

        if(lowerCaseInput == "quit" || lowerCaseInput == "exit"){ //stops programming when these keywords are detected
            cout<<"Exiting Database Simulator"<<endl;
            break;
        }

        parseInputs(input); //parses command, calling appropriate function 
    }
    

    return 0;
 







    
    
    //testing =================================

    
    vector<string> testCNames = {"fname", "lname", "ID", "SSN", "Phone Number"};
    string tableName1 = "Students";

    //createTable(tableName1, testCNames); //this works!!!!!


    //testing end ==============================

}
