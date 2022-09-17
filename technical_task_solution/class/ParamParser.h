#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

class ParamParser {
public:
  vector<string> params;
  string inputFileName = "input.csv";   // default input file
  string outputFileName = "output.csv"; // default uotput file
  string helpFileName = "help.txt";     // help file location
  char delim = ';';                     // default delimeter
  bool verbose = false;
  bool help = false;
  bool custom_input_file = false;
  bool custom_output_file = false;
  bool verbose_only = false;
  bool input_file_exists = true;
  bool delim_flag = false;
  bool QUIT_WITH_ERROR = false;
  bool QUIT_SUCCESS = false;
  bool BAD_PARAM = false;
  bool BAD_DELIM = false;
  bool BAD_FILE = false;
  bool stream_mode =
      false; // possibly will add stream mode later for file streaming

  void readParams(int argc, char **argv);
  int handleParams();
  int parseParams();
};