// YamlParser.h

#ifndef YAMLPARSER_H         // Include guard to prevent multiple inclusions of this header file
#define YAMLPARSER_H

#include <string>            // Include for string handling
#include <unordered_map>     // Include for unordered_map data structure
#include <variant>           // Include for std::variant to hold different data types
#include <vector>            // Include for vector data structure to hold lists

using namespace std;         // Use the standard namespace to avoid prefixing std:: to standard library components

// Declaration of the YamlParser class
class YamlParser {
public:
    // Alias for a map holding different types of data: string, int, or vector of strings
    using YamlData = unordered_map<string, variant<string, int, vector<string>>>;

    // Constructor that takes a filename and parses the YAML content
    YamlParser(const string& filename);

    // Method to retrieve a string value from the parsed data by key
    string getString(const string& key) const;

    // Method to retrieve an integer value from the parsed data by key
    int getInt(const string& key) const;

    // Method to retrieve a list of strings from the parsed data by key
    vector<string> getStringList(const string& key) const;

private:
    YamlData data;           // Container to store parsed YAML data

    // Helper method to parse the file content into the `data` container
    void parseFile(ifstream& file);
};

#endif // YAMLPARSER_H
