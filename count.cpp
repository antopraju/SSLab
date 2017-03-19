#include<iostream>
#include<fstream>
#include<cstring>

#define size 2000

using namespace std;

int main() {

	char data[size];
	int len;
	int chars = 0;
	int words = 0;
	int lines = 0;
	fstream file;
	file.open("input.txt", ios::in);

	file.read(data, size );

	file.close();
	
	len = strlen(data);

	for( int i = 0; i < len; i++ )
	{
		if ( data[i] == '\n' )
			lines++;
	}

	int j = 0;
	while(j < len )
	{
		if ( data[j] == ' ' || data[j] == '\t' || data[j] == '\n' || data[j] == '.' ||  data[j] == '!' ||  data[j] == '?' || data[j] == ',' || data[j] == ':'|| data[j] == ';')
		{
			while( !isalnum(data[j]) )
				j++;
			words++;
		}
		else
			j++;
	}

	cout <<"Number of Characters " << len << endl ;
	cout <<"Number of Words " << words << endl ;
	cout <<"Number of Lines " << lines << endl ;

	return 0;

}
