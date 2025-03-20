/*
select.cpp
By Bilash Sarkar

This function selects table data
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>

using namespace std;
namespace fs = std::filesystem;


//helper function to return a vector. based on a given string
vector<string> split(const string& str){

    vector<string> result;
    stringstream ss(str);
    string item;

    while(getline(ss, item, ',')){

        item.erase(0, item.find_first_not_of(" \t"));  // Trim leading spaces
        item.erase(item.find_last_not_of(" \t") + 1);  // Trim trailing spaces
        result.push_back(item);
    }

    return result;

}


void selectFrom(string& tableName, const vector<string>& selectedColumns){

    ifstream file("database/" + tableName + ".txt");
    if(!file){
        cout<<"ERROR: Table \""<<tableName<<"\" does not exist"<<endl;
    }

    string header;
    getline(file, header);

    vector<string> colNames = split(header);
    vector<int> colIndexes;

    if(selectedColumns.empty()){

        colIndexes.resize(colNames.size());
        iota(colIndexes.begin(), colIndexes.end(), 0);

    }
    else{
        for(const string& col: selectedColumns){
            auto it = find(colNames.begin(), colNames.end(), col);

            if(it == colNames.end()){
                cout<<"Error: Column \""<<col<<"\" does not exist in table \""<<tableName<<"\""<<endl;
                return;
            }

            colIndexes.push_back(distance(colNames.begin(), it));
        }
    }

    for (int i : colIndexes) {
        cout << setw(20) << left << colNames[i] << " | ";
    }
    cout << endl << string(colIndexes.size() * 18, '-') << endl; 

    string row;
    while (getline(file, row)) {
        vector<string> values = split(row);
        for (int i : colIndexes) {
            cout << setw(20) << left << values[i] << " | ";
        }
        cout << endl;
    }

    file.close();

}

