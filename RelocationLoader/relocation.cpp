/* 
 * This is the code by Anthony Prajwal P
 *
 * Implementation of Relocation Loader
 * Input is taken from the user for the start address and from input.txt file we get output.txt file.
 *
 */


#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

int main(){
	string data;
	char type;
	int start;
	
	ifstream input;
	ofstream output;
	input.open("input.txt");
	output.open("output.txt");
	
	getline(input, data);
	type = data.at(0);
	
	cout<<"Enter the starting address: ";
	cin>>hex>>start;
	
	while(type != 'E'){
		getline(input, data);
		type = data.at(0);
		
		if(type == 'T'){
			string opcode = data.substr(10);
			string locstr = data.substr(1,6);
			string modifier = data.substr(7,3);
			
			stringstream ss(locstr);
			int loc = 0, mod, add;
			int mask = 0x800;
			ss>>hex>>loc;
			
			loc += start;
			
			stringstream s(modifier);
			s>>hex>>mod;
			
			while(opcode.length() > 0){
				string obj = opcode.substr(0,6);
				stringstream sss(obj);
				sss>>hex>>add;
				int a = mod;
				if(a & mask){
					add += start;
				}
				mod = mod << 1;
				a = mod;
				opcode.erase(0,6);
	    			output<<hex<<loc<<" "<<add<<endl;
	    			loc += 3;
			}
		}
	}
}
