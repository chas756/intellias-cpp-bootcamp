#include "CsvReader.h"
#include "CsvLine.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void CsvReader::readFile(string fileName, char delim, vector<CsvLine> &lines) {

  ifstream inputFile;
  inputFile.open(fileName);
  string line = "";

  // Skipping header for now

  getline(inputFile, line);
  line = "";

  // going trough file
  while (getline(inputFile, line)) {
    CsvLine csv_line;
    csv_line.parse(line, delim); // add try..catch  parseLineSolver();
    lines.push_back(csv_line);   // inserting
    line = "";
  }
}

void CsvReader::writeFile(string fileName, char delim, vector<CsvLine> lines) {
  ofstream outputFile;
  outputFile.open(fileName);
  for (auto line : lines) {
    for (auto column : line.values) {
      outputFile << column << delim;
    }
    outputFile << endl;
  }
}