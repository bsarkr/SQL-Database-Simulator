/*
parsing.cpp
By Bilash Sarkar

This class parses user inputs
*/


#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include "createTable.cpp"
#include "insertIntoTable.cpp"
#include "select.cpp"

using namespace std;

void parseInputs(const string& input){

    // R"(...)" is where the we define the structure
    // regex::icase makes the input case insensitive, but the R"()"" makes sure that the exact keywords are used
    // \s* means many or no spaces. - optional... remember * always stands for optional in regex
    // \w stands for any character, A-Z, a-z, 0-9_ and the + means that there can be multiple characters (a full word)
    // \((.*?)\) captures column list. \( and \) match actual parentheses ( and ) (escaped with \ to avoid confusion). 
    // *? means as few as possible (lazy matching)
    // $ represents the end of the string

    regex createTableRegex(R"(^\s*CREATE\s+TABLE\s+(\w+)\s*\((.*?)\)\s*$)", regex::icase);
    regex inputIntoTableRegex(R"(^\s*INSERT\s+INTO\s+(\w+)\s*VALUES\s*\((.*?)\)\s*$)", regex::icase);
    regex selectAllRegex(R"(^\s*SELECT\s+\*\s+FROM\s+(\w+)\s*$)", regex::icase);
    regex selectColumnsRegex(R"(^\s*SELECT\s+([\w\s,]+?)\s+FROM\s+(\w+)\s*$)", regex::icase);

    smatch match; //used to store the results of a regex search or match.

    //CREATE TABLE regex parsing
    if(regex_match(input, match, createTableRegex)){ //checking if the input matches the regex structure created

        string tableName = match[1]; //extracting the table name
        string columns = match[2]; //extracting column names (list)

        //converting list into a vector
        vector<string> columnNames;

        regex columnNamesRegex(R"(\s*,\s*)"); // locating a ',' to split the list into elements. The sytanx means that anything can be before or after the ','

        //splitting the string into parts
        sregex_token_iterator iter(columns.cbegin(), columns.cend(), columnNamesRegex, -1); //iterates through the entire list stores in columns var. Then, ehecks for the ','
        sregex_token_iterator end;  //end of sequence                                     //the -1 means it grabs everything except the ','

        while(iter != end){ //loops through the iterator we created and adds each element into our vector
            columnNames.push_back(*iter);
            ++iter; //incrememnting the iterator
        }

        //now i can call the createTable function
        createTable(tableName, columnNames);

    }
    else if(regex_match(input, match, inputIntoTableRegex)){ //INSERT INTO regex parsing

        string tableName = match[1]; //extracting the table name
        string valuesStr = match[2]; //extracting column names (list)

        //converting list into a vector
        vector<string> values;

        regex inputIntoTableRegex(R"(\s*,\s*)"); // locating a ',' to split the list into elements. The sytanx means that anything can be before or after the ','

        //splitting the string into parts
        sregex_token_iterator iter(valuesStr.cbegin(), valuesStr.cend(), inputIntoTableRegex, -1); //iterates through the entire list stores in columns var. Then, ehecks for the ','
        sregex_token_iterator end;  //end of sequence                                     //the -1 means it grabs everything except the ','

        while(iter != end){
            string value = *iter;
                values.push_back(value);
            ++iter;
        }

        insertIntoTable(tableName, values);

    }
    else if(regex_match(input, match, selectAllRegex)){
        string tableName = match[1];
        selectFrom(tableName, vector<string>{});       
    }
    else if(regex_match(input, match, selectColumnsRegex)){
        string colNamesStr = match[1];
        string tableName = match[2];

        //cout<<tableName<<"====="<<colNamesStr<<endl; //this is not the problem

        vector<string> selectedCols = split(colNamesStr);

        /*
        for(int i = 0; i<selectedCols.size(); i++){

            cout<<selectedCols[i]<<" ";

        }

        for(string& col : selectedCols){
            col.erase(0, col.find_first_not_of(" \t")); //trims leading spaces
            col.erase(col.find_first_not_of(" \t") + 1); //trims remaining spaces
        }
            */

        selectFrom(tableName, selectedCols);

    }
    else{
        cout<<"There was something wrong with this command. Please check for syntax errors"<<endl;
        return;
    }

}