/*
main.cpp
By Bilash Sarkar

This class simulates a SQL database
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm> // Required for transform()
#include "parsing.cpp"

using namespace std;
namespace fs = std::filesystem;

int main() {
    
    cout << "Welcome to the Database Simulator!" << endl;

    string databaseName = ""; //stores database name
    bool databaseSelected = false;

    if(databaseName == ""){
        cout<<"No Database Selected"<<endl;
    }

    string input; //for user inputs

    //continuously prompts user for a command
    while (true) {
        cout << databaseName << " > ";
        getline(cin, input);

        string lowerCaseInput = input;
        transform(lowerCaseInput.begin(), lowerCaseInput.end(), lowerCaseInput.begin(), ::tolower); //converts to lowercase for case-insensitive commands

        if (lowerCaseInput == "quit" || lowerCaseInput == "exit") { //exit condition
            cout << "Exiting Database Simulator" << endl;
            break;
        }

        parseInputs(input, databaseName); //processes user input command
    }

    return 0;
}