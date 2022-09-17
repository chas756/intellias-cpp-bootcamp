#include "CsvLine.h"
#include "TimeReport.h"


#include <vector>
#include <map>

using namespace std;




void TimeReport::generateReport(vector<CsvLine> lines){
    CsvLine tmp_line;
    string name="";
    string month="";
    int logged_hours=0;
    
    

    for(auto line:lines){
        string name=line.values[0];

        string month="";

        month=line.getMonth(6)+" "+line.getYear(6);
        
        int logged_hours=line.getInt(7);

        /*month_hours tmp_month_hours;
        tmp_month_hours.hours=logged_hours;
        tmp_month_hours.month=month;*/

        month_hours tmp_month_hours;
        tmp_month_hours.hours=logged_hours;
        tmp_month_hours.month=month;

        map<string,month_hours>::iterator it=report.find(name);

        if(it==report.end()) { // name not found in report
            report.insert(make_pair(name,tmp_month_hours)); //inserting a record
            continue;
        }

        //report[name].second+=logged_hours; // adding more hours
        continue;   
    }
}


vector<CsvLine> TimeReport::getData(){ 
    /* convert report to vector<CsvLine> for output into file using CsvReader::writeFile()*/
    vector<CsvLine> lines;
    CsvLine tempCsvLine;
    tempCsvLine.values[0]="Name";
    tempCsvLine.values[1]="Month";
    tempCsvLine.values[2]="Total hours";
    lines.push_back(tempCsvLine);
    for(auto record:report){
        tempCsvLine.values[0]=record.first;
        tempCsvLine.values[1]=record.second.month;
        tempCsvLine.values[2]=record.second.hours;
        lines.emplace_back(tempCsvLine);
    }
    return lines;
}