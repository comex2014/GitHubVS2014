/*************************
@ This cpp could be used for reading log files of laser data, aka, offline test
@ Name:comex
@ Email:another_sf@126.com
@ Function:
		@define file name
		@read from file
		@write into file
****************************/
#include <fstream>
#include <istream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <string.h>
//#include <file>

using namespace std;
const char* filename = "readin.txt";
void read_log_file()
{
	char* buffer;
	int size;
	char c;
	/***** define file name by date *****/
	
	/***** define file by user *****/
	
	/***** file operations *****/
	fstream testByCharFile;
	while (!testByCharFile.eof())
	{
		testByCharFile >> c;
	}
	testByCharFile.close();
	//testByCharFile.open("1saic05.txt", ios::in);
	////ofstream file("Log\\log20140822.txt", ios::out);//open and rewrite; otherwise create new
	////ofstream file("D:\\VS2013\\Projects\\SLAM\\SLAM\\Log\\log01.txt", ios::ate);//open and move to end
	////ofstream file("D:\\VS2013\\Projects\\SLAM\\SLAM\\Log\\log01.txt",ios::app);//open and add; otherwise create new
	////string str;
	////fgets(str, 1, file);

	//size = in.tellg();
	//in.seekg(0, ios::beg);
	//buffer = new char[size];
	//in.read(buffer, size);
	//cout << "read from file: " << buffer<<endl;
	////file << setw(20) << "name:" << "comex2014" << endl;//write
	//delete[] buffer;
	//in.close();
	//
}