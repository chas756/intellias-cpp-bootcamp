/*
Intellias С++ engineering Bootcamp Technical Task

Test assignment: Time tracking report
Goal: test basic C++ skills with something more sophisticated than "Hello World"
Language: C++
Approximate time needed: 2 to 8 hours
Send your task here: bootcamps@intellias.com

Author: Ihor Chastkovskyi (chasigor@gmail.com)
Formatted with clang-format :)

PLAIN SOLUTION
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <map>
#include <utility>
#include <vector>

using namespace std;

struct TimeRecord {
  string year = "";
  string month = "";
  string day = "";
  int logged_hours = 0;
};

struct FullRecord {
  /* Name;email;department;position;project;task;date;logged hours

  Maybe will add random header
  and no header processing later
  */
  string name = "";
  string email = "";
  string department = "";
  string position = "";
  string project = "";
  string task = "";
  string dateString = "";
  TimeRecord dateRecord;
};

struct ReportRecord {
  string name = "";
  string year = "";
  string month = "";
  int logged_hours = 0;
};

// GET MONTH NAME F-N
string resolveMonth(const string s) {
  int m = atoi(s.c_str());
  switch (m) {
  case 1:
    return "January";
    break;
  case 2:
    return "February";
    break;
  case 3:
    return "March";
    break;
  case 4:
    return "April";
    break;
  case 5:
    return "May";
    break;
  case 6:
    return "June";
    break;
  case 7:
    return "July";
    break;
  case 8:
    return "August";
    break;
  case 9:
    return "September";
    break;
  case 10:
    return "October";
    break;
  case 11:
    return "November";
    break;
  case 12:
    return "December";
    break;
  default:
    return "Not a valid month!";
  }

  return "";
}

// LINE PARSING F-N

void parseLine(string line, struct FullRecord &fr) {
  stringstream inputString(line);

  string tempString = "";

  getline(inputString, fr.name, ';');
  getline(inputString, fr.email, ';');
  getline(inputString, fr.department, ';');
  getline(inputString, fr.position, ';');
  getline(inputString, fr.project, ';');
  getline(inputString, fr.task, ';');
  getline(inputString, fr.dateString, ';');

  // parsing Date
  if (fr.dateString != "") {
    stringstream Date(fr.dateString);
    getline(Date, fr.dateRecord.year, '-');
    getline(Date, fr.dateRecord.month, '-');
    getline(Date, fr.dateRecord.day, '-');
  }

  // logged hours
  getline(inputString, tempString, ';');
  stringstream(tempString) >> fr.dateRecord.logged_hours;
}

// FILE PARSING F-N
void parseFile(string fileName, vector<FullRecord> &records) {

  ifstream inputFile;
  inputFile.open(fileName);
  string line = "";

  // Skipping header for now

  getline(inputFile, line);
  line = "";

  // going trough file
  while (getline(inputFile, line)) {
    FullRecord fr;
    parseLine(line, fr);   // add try..catch  parseLineSolver();
    records.push_back(fr); // inserting
    line = "";
  }
}

// AGREGATION
void generateReport(vector<FullRecord> &records,
                    map<string, ReportRecord> &report) {

  ReportRecord reportRecord;

  for (auto fullRecord : records) {

    reportRecord.name = fullRecord.name;
    reportRecord.year = fullRecord.dateRecord.year;
    reportRecord.month = resolveMonth(fullRecord.dateRecord.month);
    reportRecord.logged_hours = fullRecord.dateRecord.logged_hours;
    map<string, ReportRecord>::iterator it;
    it = report.find(reportRecord.name);

    if (it == report.end()) {
      report.insert(make_pair(reportRecord.name, reportRecord));
    }

    /*
        Section for multi years/month processing  ... later
    */

    // if record exists --  adding more hours
    else {
      report[reportRecord.name].logged_hours += reportRecord.logged_hours;
    }
  }
}

void printReport(map<string, ReportRecord> &report) {

  for (auto tmp_rr : report) {
    cout << " Name:" << tmp_rr.first << endl;
    cout << " Year:" << tmp_rr.second.year << endl;
    cout << "Month:" << tmp_rr.second.month << endl;
    cout << "Hours:" << tmp_rr.second.logged_hours << endl;
    cout << endl;
  }
}

void writeFile(string filename, map<string, ReportRecord> &report) {
  ofstream outputFile;
  outputFile.open(filename);
  // Printing header
  outputFile << "Name;Month;Total hours" << endl;
  for (auto reportRecord : report) {
    outputFile << reportRecord.first << ";" << reportRecord.second.month << " "
               << reportRecord.second.year << ";"
               << reportRecord.second.logged_hours << endl;
  }
}

int main(int argc, char **argv)

{

  fstream inputFile;
  string delim = ",";                     // default delimeter=","
  string inputFileName = "./input.csv";   // default input file
  string outputFileName = "./output.csv"; // default output file

  /*USED CONTAINERS
   also structures  up there

  */

  vector<FullRecord> records;       // parsing all lines into here
  map<string, ReportRecord> report; // generted report

  parseFile(inputFileName, records); // parsing function

  generateReport(records, report); // aggregation into report

  // printReport(report);  //test if working

  writeFile(outputFileName, report); // writing to a file

  return 0;
}