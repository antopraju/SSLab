/*
 * This is the Pass 2 of the two-pass assembler with the generation of object program
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

map<string, int> opcodes;
map<string, int> symbols;


class head{
	public:
		string name;
		int address, length;
		head(string n, int a, int l){
			name = n;
			address = a;
			length = l;
		}
		
		string getRecord(){
			stringstream s;
			s<<"H"
			<<left<<setw(6)<<setfill(' ')<<name
			<<right<<setw(6)<<setfill('0')<<hex<<address
			<<setw(6)<<setfill('0')<<hex<<length;
			return s.str();
		}
};

class text{
	public:
		int start;
		string opcodes;
		int Total, length;
		text(int a){
			start = a;
			length = 0;
			opcodes = "";
			Total = 30;
		}
		
		void add(string opcode){
			if(canAdd(opcode)){
				length += opcode.length()/2;
				opcodes.append(opcode);
			}
		}
		
		string getRecord(){
			stringstream s;
			s<<"T"
			<<setw(6)<<setfill('0')<<hex<<start
			<<setw(2)<<hex<<length
			<<opcodes;
			return s.str();
		}
		
		bool canAdd(string opcode){
			if(length + opcode.length() / 2 <= Total) return true;
			else return false;
		}
		
		void fill(){
			while(canAdd("  ")){
				opcodes.append("  ");
				Total--;
			}
		}
		
};

class end1{
	public:
		int address;
		end1(int a){
			address = a;
		}
		
		string getRecord(){
			stringstream s;
			s<<"E"
			<<setw(6)<<setfill('0')<<right<<hex<<address;
			return s.str();
		}
};

string assembly(int o, int a, bool x){
	stringstream s;
	s<<setw(2)<<hex<<setfill('0')<<o;
	if(x){
		a += 0x8000;
	}
	s<<setw(4)<<hex<<setfill('0')<<a;
	return s.str();
}




int main(){
	string label, mnumonic, operand, locstr, location, data;
	int startaddress, endaddress, code, locctr;
	ifstream input, optab, systab;
	ofstream listing, output;
	input.open("input.txt");
	optab.open("optab.txt");
	systab.open("systab.txt");
	listing.open("listing.txt");
	output.open("output.txt");
	
	while(!optab.eof()){
		optab>>mnumonic>>hex>>code;
		opcodes.insert(pair<string, int>(mnumonic, code));
	}
	
	while(!systab.eof()){
		systab>>mnumonic>>hex>>code;
		symbols.insert(pair<string, int>(mnumonic, code));
	}
	
	getline(input, data);
	stringstream ss(data);
	getline(ss, locstr, '\t');
	getline(ss, label, '\t');
	getline(ss, mnumonic, '\t');
	getline(ss, operand, '\t');
	
	if(!mnumonic.compare("START")){
		stringstream s(operand);
		s>>hex>>locctr;
		startaddress = locctr;
		listing<<locstr<<"\t"<<label<<"\t"<<mnumonic<<"\t"<<operand<<endl;
	}
	else{
		locctr = 0;
	}
	
	int length = 4218;
	head h(label, startaddress, length);
	output<<h.getRecord()<<endl;
	
	text *t = new text(startaddress);
	
	while(mnumonic.compare("END")){
		
		getline(input, data);
		stringstream sss(data);
		getline(sss, location, '\t');
		getline(sss, label, '\t');
		if(!label.compare(".")){
			listing<<data<<endl;
			continue;
		}
		getline(sss, mnumonic, '\t');
		getline(sss, operand, '\t');
		
		int address;
		string objectcode = "";
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
				map<string, int>::iterator it1 = symbols.find(op);
				if(it1 != symbols.end()){
					address = it1 -> second;
				}else{
					address = 0;
					cout<<"Symbol is Undefined\n";
				}
			}else{
				address = 0;
			}
			objectcode = assembly(opcodes.find(mnumonic) -> second, address, isIndex);
		}
		
		else if(!mnumonic.compare("BYTE")){
			if(operand.at(0) == 'C'){
				for(int i = 2; i < operand.length() - 1; i++){
					stringstream s;
					s<<hex<<(int)operand.at(i);
					objectcode += s.str();
				}
			}
			else if(operand.at(0) == 'X'){
				objectcode = operand.substr(2,operand.length() - 3);
			}
		}
		
		else if(!mnumonic.compare("WORD")){
			stringstream s;
			s<<hex<<setw(6)<<setfill('0')<<stoi(operand);
			objectcode = s.str();
		}
		
		else if(!mnumonic.compare("RESW")){
			t -> fill();
		}
		
		else if(!mnumonic.compare("RESB")){
			t -> fill();
		}
		
		if(!t -> canAdd(objectcode)){
			
			stringstream s(location);
			s>>hex>>locctr;
			output<<t -> getRecord()<<endl;
			t = new text(locctr);	
		}
		
		t -> add(objectcode);
		listing<<location<<"\t"<<label<<"\t"<<mnumonic<<"\t"<<operand<<"\t\t"<<objectcode<<endl;
	
	}
	output<<t->getRecord()<<endl;
	end1 e(startaddress);
	output<<e.getRecord()<<endl;
	
	input.close();
	systab.close();
	optab.close();
	listing.close();
}
