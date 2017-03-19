#include<iostream>
#include<fstream>
using namespace std;

int main() {

	char data[100];
	fstream file;
	file.open("hello.txt",ios::in |  ios::out | ios::app);

	file.write("I love chicken", 30 );
	//file << " I like Yellow";

	file.seekg(10, ios::beg);
	/*file >> data;
	cout << data << endl;*/

	file.read(data, 100 );
	cout << data << endl;
	file.seekg(0, ios::beg);
	file.read(data, 100 );

	cout << data << endl;

	file.close();
	
	return 0;

}
