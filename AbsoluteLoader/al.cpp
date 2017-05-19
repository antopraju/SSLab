/*
 * This is the code by Anthony Prajwal P
 *
 * Implementation of Absolute Loader
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

int main(){
	string data;
	char type;
	ifstream input;
	ofstream output;
	
	input.open("input.txt");
	output.open("output.txt");
	
	getline(input,data);
	type = data.at(0);
	
	while(type != 'E'){
		getline(input, data);
		type = data.at(0);
		
		if(type == 'T'){
			string opcode = data.substr(9);
			string start = data.substr(1,6);
			int loc;
			stringstream ss(start);
			ss>>hex>>loc;
			while(opcode.length() > 0){
				output<<hex<<loc<<" "<<opcode.substr(0,2)<<endl;
				opcode.erase(0,2);
				loc ++;
			}
		}
	}
}
