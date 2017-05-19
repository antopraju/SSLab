/*
 * This the code for implementation of pass 2 of the two-pass Assembler
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <cstdlib>

using namespace std;

map<string, int> opcodes;
map<string, int> symbols;

string assembly(int o, int a, int x){
	stringstream sa;
	sa<<setw(2)<<setfill('0')<<hex<<o;
	if(x){
		a += 0x8000;
	}
	sa<<setw(4)<<setfill('0')<<hex<<a;
	return sa.str();
}

int main(){
	string locstr, label, mnumonic, operand, data;
	int startaddress, locctr, code;
	ifstream input, optab, systab;
	ofstream listing;
	input.open("input1.txt");
	optab.open("optab.txt");
	systab.open("systab.txt");
	listing.open("listing.txt");
	
	while(!optab.eof()){
		optab>>mnumonic>>hex>>code;
		opcodes.insert(pair<string, int>(mnumonic, code));
	}
	
	
	while(!systab.eof()){
		systab>>mnumonic>>hex>>code;
		symbols.insert(pair<string, int>(mnumonic, code));
	}
	
	getline(input, data);
	stringstream i(data);
	getline(i, locstr, '\t');
	getline(i, label, '\t');
	getline(i, mnumonic, '\t');
	getline(i, operand, '\t');
	
	if(!mnumonic.compare("START")){
		stringstream s(operand);
		s>>hex>>startaddress;
		locctr = startaddress;
		listing<<locstr<<"\t"<<label<<"\t"<<mnumonic<<"\t"<<operand<<"\t"<<endl;
	}
	
	
	
	while(mnumonic.compare("END")){
		getline(input, data);
		stringstream is(data);
		getline(is, locstr, '\t');
		getline(is, label, '\t');
		if(!label.compare(".")){
			listing<<data<<endl;
			continue;
		}
		getline(is, mnumonic, '\t');
		getline(is, operand, '\t');
		
		string objectcode = "";
		int address = 0;
		bool isIndex = false;
		
	 	map<string, int>::iterator it = opcodes.find(mnumonic);
	 	
	 	if(it != opcodes.end()){
	 		if(operand.compare("")){
	 			size_t found = operand.find(",X");
	 			string op = operand;
	 			if(found != string::npos){
	 				op.replace(found, 2, "");
					isIndex = true;
	 			}
	 			
	 			map<string, int>::iterator i1 = symbols.find(op);
	 			if(i1 != symbols.end()){
	 				address = i1 -> second;
	 			}else{
	 				address = 0;
	 				cout<<"Undefined Symbol\n";
	 			}
	 		}else{
	 			address = 0;
	 		}
	 		objectcode = assembly(opcodes.find(mnumonic) -> second, address, isIndex);
	 	}
	 	
	 	else if(!mnumonic.compare("BYTE")){
	 		
	 		if(operand.at(0) == 'C'){
	 			for(int i = 2; i < operand.length() - 1; i++){
	 				stringstream ss;
	 				ss<<hex<<(int)operand.at(i);
	 				objectcode += ss.str();
	 			}
	 		}
	 		if(operand.at(0) == 'X'){
	 			objectcode = operand.substr(2, operand.length() - 3);
	 		}
	 	}
	 	
	 	else if(!mnumonic.compare("WORD")){
	 		stringstream ss;
	 		ss<<setw(6)<<setfill('0')<<hex<<stoi(operand);
	 		objectcode = ss.str();
	 	}
	 	
	 	listing<<locstr<<"\t"<<label<<"\t"<<mnumonic<<"\t"<<operand<<"\t\t"<<objectcode<<endl;
	}
	
	input.close();
	optab.close();
	systab.close();
	listing.close();
	
}
