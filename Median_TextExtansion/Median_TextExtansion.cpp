#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void formatAndPrint(string text) {
    text.erase(remove(text.begin(), text.end(), '<'), text.end());
    text.erase(remove(text.begin(), text.end(), '>'), text.end());
    bool isBold = text.size() >= 4 && text.substr(0, 2) == "**" && text.substr(text.size() - 2) == "**";
    bool isItalic = text.size() >= 2 && text[0] == '*' && text[text.size() - 1] == '*';
    bool isUnderlined = text.size() >= 6 && text.substr(0, 3) == "***" && text.substr(text.size() - 3) == "***";
    if (isBold) {
        text = text.substr(2, text.size() - 4);
        cout << "\033[1m" << text << "\033[0m";
    }
    else if (isItalic) {
        text = text.substr(1, text.size() - 2);
        cout << "\033[3m" << text << "\033[0m";
    }
    else if (isUnderlined) {
        text = text.substr(3, text.size() - 6);
        cout << "\033[4m" << text << "\033[0m";
    }
    else {
        cout << text;
    }
}
void readFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error 0: Failed to open the specified text file: " << filename << endl;
        return;
    }
    string line;
    clearConsole();
    while (getline(inputFile, line)) {
        size_t startPos = 0;
        while ((startPos = line.find('<', startPos)) != string::npos) {
            size_t endPos = line.find('>', startPos);
            if (endPos != string::npos) {
                string text = line.substr(startPos + 1, endPos - startPos - 1);
                formatAndPrint(text);
                cout << endl;
                startPos = endPos + 1;
            }
            else {
                break;
            }
        }
    }
    inputFile.close();
}
int main() {
    string filename;
    cout << "Enter the name of the text file with the .median extension (or specify its path): " << endl;
    getline(cin, filename);
    readFile(filename);
    return 0;
}
