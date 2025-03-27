/*
insertIntpTable.cpp
By Bilash Sarkar

This class inserts data into a table
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void insertIntoTable(string& databaseName, const string& tableName, vector<string>& values){

    if(databaseName == ""){ //if database name is empty
        cout<<"No databases selected"<<endl;
        return;  
    }

    string filePath = databaseName + "/" + tableName + ".txt";

    ofstream tableFile(filePath, ios::app); //opening the table file in append mode

    if(!tableFile){ //checking if the file was successfully created
        cout<<"Error: \""<<tableName<<"\" table does not exist in database \""<<databaseName<<"\""<<endl;
        return;
    }

    for(int i = 0; i<values.size(); i++){
        tableFile<<values[i]; //adding column name to our created table file

        if(i < values.size()-1) tableFile<<" , "; //seperating column names by a comma
    }

    tableFile<<endl; //ending line in table file.

    tableFile.close(); //stops using the file.
    cout<<"Data successfully inserted into \""<<tableName<<"\" table!"<<endl;

}