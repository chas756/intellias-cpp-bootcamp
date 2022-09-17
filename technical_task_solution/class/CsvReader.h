#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "CsvLine.h"

using namespace std;

class CsvReader {

public:
  /* CsvReader();
   ~CsvReader();*/

  vector<CsvLine> lines;
  void readFile(string fileName, char delim, vector<CsvLine> &lines);

  void writeFile(string fileName, char delim, vector<CsvLine> lines);
};