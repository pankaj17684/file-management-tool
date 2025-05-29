#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Function prototypes
void displayMenu();
void createNewFile();
void readFile();
void appendToFile();
void displayFileStats(const string& filename);
void listAllFiles();
void deleteFile();

int main() {
    int choice;

    cout << "=== FILE MANAGEMENT TOOL ===" << endl;

    do {
        displayMenu();
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                createNewFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                appendToFile();
                break;
            case 4:
                displayFileStats("");
                break;
            case 5:
                listAllFiles();
                break;
            case 6:
                deleteFile();
                break;
            case 7:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while(choice != 7);

    return 0;
}

void displayMenu() {
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Create a new file" << endl;
    cout << "2. Read from a file" << endl;
    cout << "3. Append to a file" << endl;
    cout << "4. Display file statistics" << endl;
    cout << "5. List all text files in directory" << endl;
    cout << "6. Delete a file" << endl;
    cout << "7. Exit" << endl;
}

void createNewFile() {
    string filename, content;

    cout << "\n=== CREATE NEW FILE ===" << endl;
    cout << "Enter filename (with .txt extension): ";
    getline(cin, filename);

    // Check if file already exists
    ifstream fileExists(filename);
    if(fileExists) {
        cout << "File already exists. Use append option to add content." << endl;
        fileExists.close();
        return;
    }

    cout << "Enter content (press Enter twice to finish):" << endl;

    // Get multi-line input
    string line;
    content = "";
    while(true) {
        getline(cin, line);
        if(line.empty()) break;
        content += line + "\n";
    }

    // Write to file
    ofstream outFile(filename);
    if(outFile.is_open()) {
        outFile << content;
        outFile.close();
        cout << "File created successfully!" << endl;
        displayFileStats(filename);
    } else {
        cerr << "Error creating file!" << endl;
    }
}

void readFile() {
    string filename;

    cout << "\n=== READ FROM FILE ===" << endl;
    cout << "Enter filename to read: ";
    getline(cin, filename);

    ifstream inFile(filename);
    if(!inFile) {
        cerr << "Error: File not found or cannot be opened!" << endl;
        return;
    }

    cout << "\n=== FILE CONTENT ===" << endl;
    string line;
    while(getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

    displayFileStats(filename);
}

void appendToFile() {
    string filename, content;

    cout << "\n=== APPEND TO FILE ===" << endl;
    cout << "Enter filename to append: ";
    getline(cin, filename);

    // Check if file exists
    ifstream checkFile(filename);
    if(!checkFile) {
        cout << "File doesn't exist. Create it first." << endl;
        return;
    }
    checkFile.close();

    cout << "Enter content to append (press Enter twice to finish):" << endl;

    // Get multi-line input
    string line;
    content = "";
    while(true) {
        getline(cin, line);
        if(line.empty()) break;
        content += line + "\n";
    }

    // Append to file
    ofstream outFile(filename, ios::app);
    if(outFile.is_open()) {
        outFile << content;
        outFile.close();
        cout << "Content appended successfully!" << endl;
        displayFileStats(filename);
    } else {
        cerr << "Error appending to file!" << endl;
    }
}

void displayFileStats(const string& filename) {
    string fileToCheck = filename;

    if(fileToCheck.empty()) {
        cout << "\n=== FILE STATISTICS ===" << endl;
        cout << "Enter filename: ";
        getline(cin, fileToCheck);
    }

    ifstream file(fileToCheck, ios::binary | ios::ate);
    if(!file) {
        cerr << "Error: File not found or cannot be opened!" << endl;
        return;
    }

    // Get file size
    streampos size = file.tellg();
    file.close();

    // Count lines in file
    int lineCount = 0;
    string tempLine;
    ifstream countFile(fileToCheck);
    while(getline(countFile, tempLine)) {
        lineCount++;
    }
    countFile.close();

    cout << "\n=== FILE STATISTICS ===" << endl;
    cout << "Filename: " << fileToCheck << endl;
    cout << "Size: " << size << " bytes" << endl;
    cout << "Lines: " << lineCount << endl;
}

void listAllFiles() {
    cout << "\n=== LISTING FILES ===" << endl;
    cout << "This is a basic implementation. On a real system, you would use:" << endl;
    cout << "- Windows: dir *.txt" << endl;
    cout << "- Linux/macOS: ls *.txt" << endl;
    cout << "For a complete implementation, you would need platform-specific code." << endl;
}

void deleteFile() {
    string filename;

    cout << "\n=== DELETE FILE ===" << endl;
    cout << "Enter filename to delete: ";
    getline(cin, filename);

    // Check if file exists
    ifstream checkFile(filename);
    if(!checkFile) {
        cout << "File doesn't exist." << endl;
        return;
    }
    checkFile.close();

    if(remove(filename.c_str()) == 0) {
        cout << "File deleted successfully." << endl;
    } else {
        cerr << "Error deleting file." << endl;
    }
}
