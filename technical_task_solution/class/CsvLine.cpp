#include "CsvLine.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void CsvLine::parse(string line, char delim) {

  if (line.find_first_of(delim) !=
      string::npos) { // This checks if there is delim in line. If not then it's
                      // probably wrong!

    stringstream inputString(line);

    string tempString = "";

    while (getline(inputString, tempString, delim)) {

      values.push_back(tempString); // It crashes with wrong delimeter!!!
      tempString = "";
    }

  } else
    cout << "Missing delimeter in line. You should check if you specified "
            "correct delimeter";
}

string CsvLine::getString(int column) { return values.at(column); }

double CsvLine::getDouble(int column) {
  return atof(values.at(column).c_str());
}

int CsvLine::getInt(int column) { return atoi(values.at(column).c_str()); }

string CsvLine::getMonth(int column) {

  CsvLine date(values.at(column), '-');
  string not_valid = "Not a valid month! ";
  not_valid += values[1];
  switch (date.getInt(1)) {
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
    return not_valid;
  }

  return "";
}

string CsvLine::getYear(int column) {
  CsvLine date(values.at(column), '-');
  return date.getString(0);
}

string CsvLine::getDay(int column) {
  CsvLine date(values.at(column), '-');
  return date.getString(2);
}
