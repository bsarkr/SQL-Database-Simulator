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

void insertIntoTable(const string& tableName, vector<string>& values){

    string filePath = "database/" + tableName + ".txt";

    ofstream tableFile(filePath, ios::app); //opening the table file in append mode

    if(!tableFile){ //checking if the file was successfully created
        cout<<"Error: \""<<tableName<<"\" table does not exist"<<endl;
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