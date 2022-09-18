class_folder:= class/

csv_class_list =  class/CsvLine.cpp class/CsvReader.cpp class/TimeReport.cpp 

parser_class = class/ParamParser.cpp

csv_header_list := class/CsvLine.h class/CsvReader.h class/TimeReport.h 

parser_header = class/ParamParser.h

main_files = plain.cpp classes.cpp report.cpp

clang_format_files= $(main_files) $(csv_class_list) $(csv_header_list) $(parser_class) $(parser_header)



all: plain classes report

plain: plain.cpp
	g++ plain.cpp -o plain


classes: classes.cpp $(csv_header_list) $(csv_class_list)
	g++ classes.cpp $(csv_class_list) -o classes


report: report.cpp $(csv_header_list) $(csv_class_list) $(parser_class) $(parser_header)
	g++ report.cpp $(csv_class_list) $(parser_class) -o report

format:
	clang-format -i $(clang_format_files)

git-add:
	git add $(clang_format_files) Makefile help.txt input.csv README.md

clean :
	rm -fv *.ii *.o *.s classes report plain *output.csv 
	