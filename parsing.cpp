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


    smatch match; //used to store the results of a regex search or match.

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

}