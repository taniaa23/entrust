#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_CHARACTERS_PER_LINE = 80;
const int MAX_LINES_PER_PAGE = 25;

void paginateDocument(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);

    if (!inputFile.is_open()) {
        cerr << "Failed to open input file." << endl;
        return;
    }

    if (!outputFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        inputFile.close();
        return;
    }

    string line;
    string word;
    int lineCount = 0;
    int pageCount = 1;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        ostringstream oss;

        while (iss >> word) {
            if (lineCount == MAX_LINES_PER_PAGE) {
                outputFile << string(MAX_CHARACTERS_PER_LINE, '-') << "\n";
                outputFile << "Page " << pageCount << "\n";
                lineCount = 0;
                pageCount++;
            }

            if (oss.tellp() + word.length() <= MAX_CHARACTERS_PER_LINE) {
                oss << word << " ";
            } else {
                outputFile << oss.str().substr(0, oss.str().length() - 1) << "\n";
                oss.str("");
                oss.clear();
                oss << word << " ";
                lineCount++;
            }
        }

        if (!oss.str().empty()) {
            outputFile << oss.str().substr(0, oss.str().length() - 1) << "\n";
            outputFile << string(MAX_CHARACTERS_PER_LINE, '-') << "\n";
            outputFile << "Page " << pageCount << "\n";
            lineCount++;
        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    string inputFilename = "document.txt";
    string outputFilename = "paged_document.txt";

    paginateDocument(inputFilename, outputFilename);

    cout << "Pagination complete. Output written to " << outputFilename << endl;

    return 0;
}
