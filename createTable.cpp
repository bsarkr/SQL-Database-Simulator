/*
createTable.cpp
By Bilash Sarkar

This class initializes a new table.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void createTable(string& databaseName, const string& tableName, const vector<string>& column)
{
    //temporary fix to making sure database is created before creating a table:

    //string databaseName = "database"; //i need to pull this from the user... ****************

    if(databaseName == ""){ //if database name is empty
        cout<<"No databases selected"<<endl;
        return;  
    }
    
    string filePath = databaseName+ "/" + tableName+ ".txt"; //initializing new file destination

    //checking if tablename already exists
    if(fs::exists(filePath)){
        cout<<"Error: \""<<tableName<<"\" already exists in database \""<<databaseName<<"\"!"<<endl;
        return;
    }

    ofstream tableFile(filePath); //creating and opening the file

    if(!tableFile){ //checking if the file was successfully created
        cout<<"Oops! There was an error while creating this table. Ensure that a database was initialized before proceeding."<<endl;
        return;
    }
    
    for(int i = 0; i<column.size(); i++){ //iterating through column

        tableFile<<column[i]; //adding column name to our created table file

        if(i < column.size()-1) tableFile<<" , "; //seperating column names by a comma

    }

    tableFile<<endl; //ending line in table file.

    tableFile.close(); //stops using the file.
    cout<<"Table \""<<tableName<<"\" created successfully"<<endl;

}
