// main.cpp

#include <iostream>          // Include for input and output operations
#include "YamlParser.h"      // Include the YamlParser header to use the class

using namespace std;         // Use the standard namespace

// Main function demonstrating the use of YamlParser
int main() {
    try {
        YamlParser parser("example.yaml"); // Create YamlParser object and load data from "example.yaml"

        // Retrieve and print data from the parsed YAML file
        string name = parser.getString("name");           // Get the "name" as a string
        int age = parser.getInt("age");                   // Get the "age" as an integer
        vector<string> items = parser.getStringList("items"); // Get the "items" as a list of strings

        // Print the retrieved values
        cout << "Name: " << name << endl;                 // Print the name
        cout << "Age: " << age << endl;                   // Print the age
        cout << "Items: " << endl;                        // Print the header for items list
        for (const auto& item : items) {                  // Loop through each item in the items list
            cout << "- " << item << endl;                 // Print each item with a dash
        }
    } catch (const exception& e) {                        // Catch any exceptions thrown by the parser
        cerr << "Error: " << e.what() << endl;            // Print the error message to standard error
    }

    return 0;                                             // Return 0 to indicate successful execution
}
