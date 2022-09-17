#pragma once

#include <sstream>
#include <string>
#include <vector>

using namespace std;

class CsvLine {
public:
  vector<string> values;

  CsvLine() {}

  CsvLine(string line) { parse(line, ';'); }

  CsvLine(string line, char delim) { parse(line, delim); }
  // copy constructor
  CsvLine(const CsvLine &other) { values = other.values; }
  // assignment
  /*CsvLine operator=(const CsvLine& other) {
          values = other.values;
  }*/

  ~CsvLine() {}
  void parse(string line, char delim);
  string getString(int column);
  double getDouble(int column);
  int getInt(int column);
  string getMonth(int column);
  string getYear(int column);

  string getDay(int column);
};
