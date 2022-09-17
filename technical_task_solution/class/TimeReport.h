#pragma once

#include "CsvLine.h"

#include <map>
#include <vector>

using namespace std;

struct month_hours {
  month_hours() {
    month = "";
    hours = 0;
  }
  string month = "";
  int hours = 0;
};

class TimeReport {

public:
  map<string, month_hours> report;

  /*TimeReport();
  ~TimeReport();*/

  void generateReport(vector<CsvLine> lines);

  vector<CsvLine> getData();
};