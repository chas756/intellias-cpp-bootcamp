#include "ParamParser.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

void ParamParser::readParams(int argc, char **argv) {

  // cout<<"Reading "<<argc<<" parameters:"<<endl;

  for (int i = 0; i < argc; i++) {
    string param;
    param = string(argv[i]);
    // cout<<"param ["<<i<<"]  is  "<<param<<endl;
    params.push_back(param);
  }
}

int ParamParser::parseParams() {
  if (params.size() > 1) { // skipping if there are no parameters

    for (int i = 1; i < params.size(); i++) {
      string s = params[i];
      bool match = false;

      if (s == "--help") {
        help = true;
        break;
      }

      if (s == "-v") {
        verbose = true;
        continue;
      }

      if (s == "--verbose-only") {
        verbose = true;
        verbose_only = true;
        continue;
      }

      if (s == "-d=") {
        if (params[i + 1].size() == 1) {
          delim_flag = true;
          delim = (params[i + 1])[0];
          i++; // skipping next one
          continue;
        } else {
          BAD_DELIM = true;
          BAD_PARAM = true;
          QUIT_WITH_ERROR = true;
          break;
        }
      }

      if (s == "-o") {
        bool file_access;
        ofstream str;
        str.open(params[i + 1]);
        if (!str.good()) {
          str.close();
          BAD_PARAM = true;
          BAD_FILE = true;
          QUIT_WITH_ERROR = true;
          break;
        } else {
          str.close();
          custom_output_file = true;
          outputFileName = params[i + 1];
          i++; // skipping next one
          continue;
        }
      }

      if (s == "-i") {
        bool file_access;
        ifstream str;
        str.open(params[i + 1]);
        if (!str.good()) {
          str.close();
          BAD_PARAM = true;
          BAD_FILE = true;
          QUIT_WITH_ERROR = true;
          break;
        } else {
          str.close();
          custom_input_file = true;
          inputFileName = params[i + 1];
          i++; // skipping next one
          continue;
        }
      }

      BAD_PARAM = true;
      break; // if no matches
    }

    if (input_file_exists) { // check if input file exists
      bool file_access;
      ifstream str;
      str.open(inputFileName);
      if (!str.good()) {
        str.close();
        BAD_FILE = true;
        QUIT_WITH_ERROR = true;
        input_file_exists = false;
        return 0;
      }
    }

    if (delim_flag) { // check if input file can be parsed with this delim
      bool file_access;
      ifstream str;
      str.open(inputFileName);
      string s;
      getline(str, s);
      // looking for thr first occurance of delim in first line of the file
      // if there is no delimeter    then probably delimeter is wrong
      int firstDelimPos = s.find_first_of(delim);
      if (firstDelimPos == string::npos) {
        BAD_DELIM = true;
        QUIT_WITH_ERROR = true;
        cout << "This file cannot be parsed with specified delimeter. "
                "Terminating ..."
             << endl;
      }
    }

    if (BAD_PARAM)
      help = true; // if wrong params
  }
  return 0;
}

int ParamParser::handleParams() {
  if (help) {
    ifstream file;
    file.open(helpFileName);
    string line;
    while (getline(file, line)) {
      cout << line << endl;
    }
    cout << endl;
    QUIT_SUCCESS = true;
    return 0;
  }

  if (delim_flag) {

    cout << endl << "Delimeter was changed to \'" << delim << "\'" << endl;
  }

  if (custom_input_file) {

    cout << endl
         << "Input file  was changed to:" << endl
         << inputFileName << endl;
  }

  if (custom_output_file) {

    cout << endl
         << "Output file  was changed to:" << endl
         << outputFileName << endl;
  }

  if (BAD_DELIM) {

    cout << endl << "Bad delimeter parameter" << endl;
    QUIT_WITH_ERROR = true;
    return 0;
  }

  if (BAD_FILE) {

    cout << endl << "Bad filename or no file exists!" << endl;

    QUIT_WITH_ERROR = true;
    return 0;
  }

  // oops! other will be handled in main functionality

  return 0;
}