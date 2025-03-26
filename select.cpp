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
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

//helper function to split a string by commas and return a vector of trimmed values
vector<string> split(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string item;

    while (getline(ss, item, ',')) {

        item.erase(0, item.find_first_not_of(" \t"));  //trims leading spaces
        item.erase(item.find_last_not_of(" \t") + 1);  //trims trailing spaces

        result.push_back(item);
    }
    return result;
}

void selectFrom(string& tableName, const vector<string>& selectedColumns) {

    //opens the table file for reading
    ifstream file("database/" + tableName + ".txt");
    if (!file) {
        //error message if the table does not exist
        cout << "ERROR: Table \"" << tableName << "\" does not exist" << endl;
        return;
    }

    //reads the header row to get column names
    string header;
    getline(file, header);
    vector<string> colNames = split(header);
    vector<int> colIndexes;

    //if no specific columns are selected, includes all columns
    if (selectedColumns.empty()) {
        colIndexes.resize(colNames.size());
        iota(colIndexes.begin(), colIndexes.end(), 0); //fills with indices 0 to n-1
    } 
    else {
        //finds the indexes of the selected columns in the header
        for (const string& col : selectedColumns) {
            auto it = find(colNames.begin(), colNames.end(), col);
            if (it == colNames.end()) {
                //error message if a selected column does not exist
                cout << "Error: Column \"" << col << "\" does not exist in table \"" << tableName << "\"" << endl;
                return;
            }
            
            colIndexes.push_back(distance(colNames.begin(), it));
        }
    }

    //prints the selected column headers
    for (int i : colIndexes) {
        cout << setw(25) << left << colNames[i] << " | ";
    }

    cout << endl << string(colIndexes.size() * 30, '-') << endl;

    //reads and print each row with selected column values
    string row;
    while (getline(file, row)) {

        vector<string> values = split(row);

        for (int i : colIndexes) {
            cout << setw(25) << left << values[i] << " | ";
        }
        cout << endl;
    }

    //closes the file after reading
    file.close();
}

void selectFromWhere(string& tableName, const vector<string>& selectedColumns, const string& whereColumn, const string& whereValue) {

    ifstream file("database/" + tableName + ".txt"); //opens the table file for reading

    if (!file) { //check if the file exists
        cout << "ERROR: Table \"" << tableName << "\" does not exist" << endl;
        return;
    }

    string header;
    getline(file, header); //reads the header row containing column names
    vector<string> colNames = split(header);
    vector<int> colIndexes;
    int whereIndex = -1;

    //finds the index of the WHERE column
    for (int i = 0; i < colNames.size(); i++) {
        if (colNames[i] == whereColumn) {
            whereIndex = i;
            break;
        }
    }

    if (whereIndex == -1) { //if WHERE column does not exist, returns an error
        cout << "ERROR: Column \"" << whereColumn << "\" does not exist in table \"" << tableName << "\"" << endl;
        return;
    }

    if (selectedColumns.empty()) { //if no specific columns are selected, includes all columns
        colIndexes.resize(colNames.size());
        iota(colIndexes.begin(), colIndexes.end(), 0); //fills with indices 0 to n-1
    } 
    else {
        for (const string& col : selectedColumns) { //finds the indexes of the selected columns
            auto it = find(colNames.begin(), colNames.end(), col);

            if (it == colNames.end()) { //if column is not found, displays an error
                cout << "Error: Column \"" << col << "\" does not exist in table \"" << tableName << "\"" << endl;
                return;
            }

            colIndexes.push_back(distance(colNames.begin(), it));
        }
    }

    //prints the selected column headers
    for (int i : colIndexes) {
        cout << setw(25) << left << colNames[i] << " | ";
    }
    cout << endl << string(colIndexes.size() * 30, '-') << endl; //prints a separator line

    string row;
    while (getline(file, row)) { //reads each row from the file
        vector<string> values = split(row);
        
        //ensures the WHERE index is within the values range
        if (whereIndex >= values.size()) {
            continue;
        }

        string tableValue = values[whereIndex]; //extracts the value from the WHERE column

        //remove single quotes if present in the value from the table
        if (!tableValue.empty() && tableValue.front() == '\'' && tableValue.back() == '\'') {
            tableValue = tableValue.substr(1, tableValue.size() - 2);
        }

        string searchValue = whereValue; //extracts the search value

        //removes single quotes if present in the search value
        if (!searchValue.empty() && searchValue.front() == '\'' && searchValue.back() == '\'') {
            searchValue = searchValue.substr(1, searchValue.size() - 2);
        }

        //checks if both values are numeric
        bool isNumeric = !searchValue.empty() && all_of(searchValue.begin(), searchValue.end(), ::isdigit);
        bool tableValueIsNumeric = !tableValue.empty() && all_of(tableValue.begin(), tableValue.end(), ::isdigit);

        if (isNumeric && tableValueIsNumeric) { //compares numeric values
            if (stoll(tableValue) == stoll(searchValue)) {
                for (int i : colIndexes) {
                    cout << setw(25) << left << values[i] << " | ";
                }
                cout << endl;
            }
        } else if (tableValue == searchValue) { //compares string values
            for (int i : colIndexes) {
                cout << setw(25) << left << values[i] << " | ";
            }
            cout << endl;
        }
    }
    cout << endl; //prints a newline for better formatting

    //closes the file after reading
    file.close();
}



void selectFromJoin(string& table1, string& table2, vector<string> selectedCols, string& joinCol1, string& joinCol2, string whereCol = "", string whereVal = "") {
    
    //opens the files for both tables
    ifstream file1("database/" + table1 + ".txt");
    ifstream file2("database/" + table2 + ".txt");

    if (!file1 || !file2) { //checks if files exist
        cout << "ERROR: One or both tables do not exist" << endl;
        return;
    }

    //reads and splits the headers to get column names
    string header1, header2;
    getline(file1, header1);
    getline(file2, header2);
    vector<string> cols1 = split(header1);
    vector<string> cols2 = split(header2);

    //finds indexes for join columns in each table
    auto it1 = find(cols1.begin(), cols1.end(), joinCol1);
    auto it2 = find(cols2.begin(), cols2.end(), joinCol2);

    if (it1 == cols1.end() || it2 == cols2.end()) { //ensures join columns exist
        cout << "ERROR: Join column does not exist in one of the tables" << endl;
        return;
    }

    int joinIndex1 = distance(cols1.begin(), it1);
    int joinIndex2 = distance(cols2.begin(), it2);

    //finds index for WHERE condition (if applicable)
    int whereIndex = -1;
    bool hasWhere = !whereCol.empty();

    if (hasWhere) {

        auto itWhere = find(cols1.begin(), cols1.end(), whereCol);

        if (itWhere != cols1.end()) { //WHERE column found in first table
            whereIndex = distance(cols1.begin(), itWhere);
        } 
        else { //search in second table
            itWhere = find(cols2.begin(), cols2.end(), whereCol);

            if (itWhere != cols2.end())
                whereIndex = distance(cols2.begin(), itWhere) + cols1.size();
        }
    }

    //reads table contents into vectors
    vector<vector<string>> tableData1, tableData2;
    string row;

    while (getline(file1, row)) { //reads data from first table
        tableData1.push_back(split(row));
    }

    while (getline(file2, row)) { //reads data from second table
        tableData2.push_back(split(row));
    }

    //determines column indexes for output
    vector<int> colIndexes;
    if (selectedCols.empty()) { //if 'SELECT *' (select all columns)

        for (int i = 0; i < cols1.size(); i++) colIndexes.push_back(i);

        for (int i = 0; i < cols2.size(); i++) colIndexes.push_back(i + cols1.size());

    } 
    else { //finds specific selected columns
        for (const string& col : selectedCols) {

            auto it = find(cols1.begin(), cols1.end(), col);

            if (it != cols1.end()) { //columns exists in first table
                colIndexes.push_back(distance(cols1.begin(), it));
                continue;
            }

            it = find(cols2.begin(), cols2.end(), col);

            if (it != cols2.end()) { //columns exists in second table
                colIndexes.push_back(distance(cols2.begin(), it) + cols1.size());
                continue;
            }

            cout << "ERROR: Column \"" << col << "\" does not exist in either table" << endl;
            return;
        }
    }

    //prints column headers for the selected output
    for (int i : colIndexes) {
        cout << setw(20) << left << ((i < cols1.size()) ? cols1[i] : cols2[i - cols1.size()]) << " | ";
    }

    cout << endl << string(colIndexes.size() * 23, '-') << endl; //prints separator line

    //performs INNER JOIN and apply WHERE condition if needed
    for (auto& row1 : tableData1) {
        for (auto& row2 : tableData2) {

            if (row1[joinIndex1] == row2[joinIndex2]) { //checks if rows match on JOIN column
                vector<string> combinedRow = row1;

                combinedRow.insert(combinedRow.end(), row2.begin(), row2.end()); //merges rows

                if (hasWhere) { //applying WHERE condition if provided
                    if (whereIndex >= combinedRow.size() || combinedRow[whereIndex] != whereVal) {
                        continue;
                    }
                }

                //prints selected columns
                for (int i : colIndexes) cout << setw(20) << left << combinedRow[i] << " | ";
                
                cout << endl;
            }
        }
    }

    //closes the files after reading
    file1.close();
    file2.close();
}