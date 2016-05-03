#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unistd.h>
#include <vector>
using namespace std;

vector<string> reg = {"A","B","C","I","J","X","Y","Z"};

int valid (string command){
	int counter = 4;
	for(string val : reg){
		if(val == command){
			return counter;
		}
		counter++;
	}
	return -1;
}

using namespace std;

void die(int line_no = 0) {
	cout << "Syntax Error on line " << line_no << endl;
	exit(1);
}

int main(int argc, char **argv) {
	//If we pass any parameters, we'll just generate an assembly file 
	//Otherwise we will generate an assembly file, assemble it, and run it
	bool assemble_only = false;
	if (argc > 1) assemble_only = true;
	ofstream outs("main.s"); //This is the assembly file we're creating
	if (!outs) {
		cout << "Error opening file.\n";
		return -1;
	}
	outs << ".global main\nmain:\n"; //Get the file ready to rock
	outs << "\tPUSH {LR}\n\tPUSH {R4-R12}\n\n";

	int line_no = 0;
	while (cin) {
		string s;
		getline(cin,s);
		line_no++;
		if (!cin) break;
		transform(s.begin(), s.end(), s.begin(), ::toupper); //Uppercaseify
		auto it = s.find("END"); //TERMINATE COMPILER
		if (it != string::npos) break;
		stringstream ss(s); //Turn s into a stringstream
		int label;
		ss >> label;
		if (!ss) die(line_no);
		outs << "line_" << label << ":\n"; //Write each line number to the file ("line_20:")
		string command;
		ss >> command;
		if (!ss) die(line_no);

		if (command == "REM") {
			continue;
		}
		else if (command == "GOTO") {
			int target;
			ss >> target;
			if (!ss) die(line_no);
			outs << "\tBAL line_" << target << endl;
			continue;
		}
		else if (command == "EXIT") {
			outs << "\tBAL quit\n";
			continue;
		}

		//YOU: COMMANDS
		else if (command == "LET") {
			ss >> command;
			int reg_num = valid(command);
			if(reg_num != -1){
				ss >> command;
				if(command == "="){
					ss >> command;
					int reg_num2 = valid(command);
					//First check if it's an immediate value
					if(reg_num2 == -1){
						outs << "\tMOV R" << reg_num << ", #" << command << endl;
						continue;
					}
					ss >> command;
					if(!ss){
						outs << "\tMOV R" << reg_num << ", R" << reg_num2 << endl;
					}
					else{
						string sign = command;
						ss >> command;
						int reg_num3 = valid(command);
						if(reg_num3 != -1){
							if(sign == "+")
								outs << "\tADD ";
							else if(sign == "-")
								outs << "\tSUB ";
							else if(sign == "*")
								outs << "\tMUL ";
							outs << "R" << reg_num << ", R" << reg_num2 << ", R" << reg_num3 << endl;
						}
					}
				}
			}
		}
	
		else if (command == "IF") {
			ss >> command;
			int register1 = valid(command);
			
			ss >> command;
			string comparison = command;
			
			ss >> command;
			int register2 = valid(command);
			
			ss >> command;
			string then = command;
			
			ss >> command;
			string go_to = command;
			
			ss >> command;
			string lineNum = command;

			if (register1 != -1 && register2 != -1) {
				outs << "\tCMP R" << register1 << ", R" << register2 << "\n";
				if (then == "THEN" && go_to == "GOTO") {
					if (comparison == ">"){
						outs << "\tBGT line_" << lineNum << "\n";
					}
					else if (comparison == "<"){
						outs << "\tBLT line_" << lineNum << "\n";
					}
					else if (comparison == "=="){
						outs << "\tBEQ line_" << lineNum << "\n";
					}
					else if (comparison == "<="){
						outs << "\tBLE line_" << lineNum << "\n";
					}
					else if (comparison == ">="){
						outs << "\tBGE line_" << lineNum << "\n";
					}
					else if (comparison == "!="){
						outs << "\tBNE line_" << lineNum << "\n";
					}
				}
			}
		}
	}

	//Clean up the file at the bottom
	outs << "\nquit:\n\tMOV R0, #42\n\tPOP {R4-R12}\n\tPOP {PC}\n"; //Finish the code and return
	outs.close(); //Close the file

	if (assemble_only) return 0; //When you're debugging you should run bb8 with a parameter

	if (system("g++ main.s")) { //Compile your assembler code and check for errors
		cout << "Assembling failed, which means your compiler screwed up.\n";
		return 1;
	}
	//We've got an a.out now, so let's run it!
	cout << "Compilation successful. Executing program now." << endl;
	execve("a.out",NULL,NULL);
}
