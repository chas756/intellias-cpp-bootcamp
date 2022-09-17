/*
Intellias С++ engineering Bootcamp Technical Task

Test assignment: Time tracking report
Goal: test basic C++ skills with something more sophisticated than "Hello World"
Language: C++
Approximate time needed: 2 to 8 hours
Send your task here: bootcamps@intellias.com

Author: Ihor Chastkovskyi (chasigor@gmail.com)
Formatted with clang-format :)

CLASSES SOLUTION
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <map>

#include <vector>

#include "class/CsvLine.h"
#include "class/CsvReader.h"
#include "class/TimeReport.h"

using namespace std;

void printReport(vector<CsvLine> report) {

  for (auto line : report) {
    cout << "       Name:" << line.values[0] << endl;
    cout << "      Month:" << line.values[1] << endl;
    cout << "Total hours:" << line.values[2] << endl;
    cout << endl;
  }
}

int main(int argc, char **argv)

{

  fstream inputFile;
  char delim = ';';                       // default delimeter=";"
  string inputFileName = "./input.csv";   // default input file
  string outputFileName = "./output.csv"; // default output file

  vector<CsvLine> lines;  // parsing all lines into here
  vector<CsvLine> report; // generted report

  CsvReader reader;    // class to read/write csv file
  TimeReport reporter; // generates report from readed lines

  reader.readFile(inputFileName, delim, lines);
  reporter.generateReport(lines);
  report = reporter.getData();
  reader.writeFile(outputFileName, delim, report); // output report to a file

  // printReport(report);  //test if working

  return 0;
}