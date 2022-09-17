#include "TimeReport.h"
#include "CsvLine.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

void TimeReport::generateReport(vector<CsvLine> lines) {
  CsvLine tmp_line;
  string name = "";
  string month = "";
  int logged_hours = 0;

  // lines.erase(lines.begin());      // header already skipped

  for (auto line : lines) {
    string name = line.values[0];

    string month = "";
    int logged_hours = 0;

    // checking for length. If wrong delimeter - there are less lines throws
    // SEGMENTATION FAULT
    if ((line.values.size()) >= 7) {
      month = line.getMonth(6) + " " + line.getYear(6);
    } // geting month

    if ((line.values.size()) >= 8) {
      logged_hours = line.getInt(7);
    }

    month_hours tmp_month_hours;
    tmp_month_hours.hours = logged_hours;
    tmp_month_hours.month = month;

    map<string, month_hours>::iterator it = report.find(name);

    if (it == report.end()) { // name not found in report
      report.insert(make_pair(name, tmp_month_hours)); // inserting a record
      continue;
    }

    report[name].hours += logged_hours; // adding more hours
    continue;
  }
}

vector<CsvLine> TimeReport::getData() {
  /* convert report to vector<CsvLine> for output into file using
   * CsvReader::writeFile()*/
  vector<CsvLine> lines;
  CsvLine tempCsvLine;
  tempCsvLine.values.push_back("Name");
  tempCsvLine.values.push_back("Month");
  tempCsvLine.values.push_back("Total hours");
  lines.push_back(tempCsvLine);
  for (auto record : report) {
    tempCsvLine.values[0] = record.first;
    tempCsvLine.values[1] = record.second.month;
    tempCsvLine.values[2] = to_string(record.second.hours);
    lines.push_back(tempCsvLine);
  }
  return lines;
}