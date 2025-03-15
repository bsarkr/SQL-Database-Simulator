/*
sqlSimulator.cpp
By Bilash Sarkar

*/


#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
//using namespace std::filesystem; //simplifying fs calls

int main(){

    
    string databaseName = "database"; //making the name a variable to enable future modification

    if(!fs::exists(databaseName)){ //is the database doesn't already exist..
        fs::create_directory(databaseName); //we create a new directory for it
        cout<<"New Database \"" <<databaseName<< "\" created!"<<endl;
    }
    else{
        cout<<"\""<<databaseName<<"\" exists";
    }
 

}