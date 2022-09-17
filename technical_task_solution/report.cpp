/*
Intellias С++ engineering Bootcamp Technical Task

Test assignment: Time tracking report
Goal: test basic C++ skills with something more sophisticated than "Hello World"
Language: C++


Author: Ihor Chastkovskyi (chasigor@gmail.com)

Formatted with clang-format :)

BETTER SOLUTION with
Optional nice-to-haves:

- Handling different CSV separators.
- console parameters and help

*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <map>
#include <utility>
#include <vector>

#include "class/CsvLine.h"
#include "class/CsvReader.h"
#include "class/ParamParser.h"
#include "class/TimeReport.h"

using namespace std;

/*void printHelp() {
  ifstream helpFile;
  helpFile.open("help.txt");
  string line;
  while (getline(helpFile, line)) {
    cout << line << endl;
  }
  cout << endl;
}*/

void printReport(vector<CsvLine> report, char delim) {

  for (auto line : report) {
    for (auto column : line.values) {
      cout << column << delim;
    }
    cout << endl;
  }
}

void main_functionality(ParamParser &p) {

  vector<CsvLine> lines;  // parsing all lines into here
  vector<CsvLine> report; // generted report

  CsvReader reader;    // class to read/write csv file
  TimeReport reporter; // generates report from readed lines
  fstream f;
  reader.readFile(p.inputFileName, p.delim, lines);
  reporter.generateReport(lines);
  report = reporter.getData();
  f.open(p.outputFileName);
  if (!p.verbose_only)
    reader.writeFile(p.outputFileName, p.delim, report); // output report

  if (p.verbose)
    printReport(report, p.delim); // write to console
}

int main(int argc, char **argv)

{

  ParamParser p;
  p.readParams(argc, argv);
  p.parseParams();
  p.handleParams();

  if (p.help)
    return 0; // if help just quit (it pwas printed in handleParams())

  if (p.QUIT_SUCCESS) {
    cout << endl << "Program finished succesfully!" << endl;
    return 0;
  }

  if (p.QUIT_WITH_ERROR) {
    cout << endl << "An ERROR occured!Program terminated! " << endl;
    return 0;
  }

  // if there is no interruption flags -- proceed with main functionality

  main_functionality(p);

  return 0;
}