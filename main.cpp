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

    /*
    Everyclass currently has "database" as the default database. Lets change that later to pass database name as an argument to each function

    make it more like sql

    create database dbname
    
    use dbname

    etc.

    do more accurate error messages (specify the syntax for each command)
    
    */
    
    string databaseName = ""; //stores database name
    bool databaseSelected = false;

    /*
    while (!databaseSelected) {
        cout << "Select a database: ";
        cin >> databaseName;
        cin.ignore(); //ignores leftover newline character

        if (!fs::exists(databaseName)) { //ff the database doesn't exist...

            string response;

            while (true) { //keep prompting until valid input
                
                cout << "\"" << databaseName << "\" does not currently exist.\nWould you like to create a new database? (yes/no): ";
                getline(cin, response);

                transform(response.begin(), response.end(), response.begin(), ::tolower); // Convert to lowercase for case insensitivity

                if (response == "yes") {
                    fs::create_directory(databaseName); //creates the new database directory
                    cout << "New Database \"" << databaseName << "\" created!" << endl;
                    databaseSelected = true; //breaks loop to continue
                    break;
                } 
                else if (response == "no") {
                    cout << "Please enter another database name." << endl;
                    break; //goes back to asking for a database name
                } 
                else {
                    cout << "Invalid input. Please enter \"yes\" or \"no\"." << endl;
                }
            }
        } 
        else { // If database already exists
            cout << "\"" << databaseName << "\" exists." << endl;
            databaseSelected = true;
        }
    }

    cout << "You've entered the database \"" << databaseName << "\"" << endl;

    */


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