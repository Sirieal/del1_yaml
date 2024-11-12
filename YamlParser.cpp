// YamlParser.cpp

#include "YamlParser.h"      // Include the corresponding header file
#include <fstream>           // Include for file handling
#include <sstream>           // Include for string stream processing
#include <stdexcept>         // Include for throwing exceptions

using namespace std;         // Use the standard namespace for cleaner code

// Constructor implementation, takes the filename and attempts to parse it
YamlParser::YamlParser(const string& filename) {
    ifstream file(filename); // Open the file for reading
    if (!file) {             // Check if the file was opened successfully
        throw runtime_error("Unable to open file: " + filename); // Throw an error if the file can't be opened
    }
    parseFile(file);         // Call parseFile to process the file's content
}

// Method to retrieve a string by key from the parsed data
string YamlParser::getString(const string& key) const {
    auto it = data.find(key); // Look for the key in the data map
    // Check if the key exists and is of type string
    if (it != data.end() && holds_alternative<string>(it->second)) {
        return get<string>(it->second); // Return the string value
    }
    throw runtime_error("Key not found or wrong type: " + key); // Throw an error if key doesn't exist or type mismatch
}

// Method to retrieve an integer by key from the parsed data
int YamlParser::getInt(const string& key) const {
    auto it = data.find(key); // Look for the key in the data map
    // Check if the key exists and is of type int
    if (it != data.end() && holds_alternative<int>(it->second)) {
        return get<int>(it->second); // Return the integer value
    }
    throw runtime_error("Key not found or wrong type: " + key); // Throw an error if key doesn't exist or type mismatch
}

// Method to retrieve a list of strings by key from the parsed data
vector<string> YamlParser::getStringList(const string& key) const {
    auto it = data.find(key); // Look for the key in the data map
    // Check if the key exists and is of type vector<string>
    if (it != data.end() && holds_alternative<vector<string>>(it->second)) {
        return get<vector<string>>(it->second); // Return the list of strings
    }
    throw runtime_error("Key not found or wrong type: " + key); // Throw an error if key doesn't exist or type mismatch
}

// Private helper function to parse the file line-by-line and populate the `data` container
void YamlParser::parseFile(ifstream& file) {
    string line, currentKey;           // Variables for each line and the current key being processed
    vector<string> currentList;         // Temporary storage for a list of strings
    bool parsingList = false;           // Flag to indicate if we're currently parsing a list

    // Read each line from the file
    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t")); // Trim leading whitespace from the line
        if (line.empty() || line[0] == '#') continue; // Skip empty lines or comments

        // Check if the line starts with a list item marker '-'
        if (parsingList && line[0] == '-') {
            line.erase(0, 1);            // Remove the '-'
            line.erase(0, line.find_first_not_of(" \t")); // Trim leading spaces after '-'
            currentList.push_back(line); // Add item to the current list
        } else {
            // If we're finishing parsing a list, save it to the data map
            if (parsingList) {
                data[currentKey] = currentList;
                currentList.clear();     // Clear the temporary list
                parsingList = false;     // Reset list parsing flag
            }
            
            size_t sepPos = line.find(":"); // Find the position of the ':' separator
            if (sepPos != string::npos) {   // If ':' is found
                currentKey = line.substr(0, sepPos);      // Extract the key part
                currentKey.erase(currentKey.find_last_not_of(" \t") + 1); // Trim trailing whitespace
                string value = line.substr(sepPos + 1);   // Extract the value part
                value.erase(0, value.find_first_not_of(" \t")); // Trim leading whitespace

                if (value.empty()) {        // If the value is empty, it's the start of a list
                    parsingList = true;
                } else if (isdigit(value[0])) { // If the value is a number, store it as an int
                    data[currentKey] = stoi(value);
                } else {                    // Otherwise, store it as a string
                    data[currentKey] = value;
                }
            }
        }
    }

    // If a list was being parsed at the end, save it
    if (parsingList) {
        data[currentKey] = currentList;
    }
}
