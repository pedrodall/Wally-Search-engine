include<iostream>
#include<fstream>
#include<sstream>

using namespace std;
//ios::app		opens a text file for appending. (appending means to add text at the end).
//ios::ate		opens a file for output and move the read/write control to the end of the file.
//ios::in		opens a text file for reading.
//ios::out		opens a text file for writing.
//ios::trunc	truncates the content before opening a file, if file exists.

void cut_file(int lines){
	ifstream file_original;
	ofstream file_copy;
	file_original.open("titles.txt");
	file_copy.open("titulos.txt");
	string line;
    char p='\"';
    string str="\'";
	for(int i = 0; i < lines; i ++){
		getline(file_original, line);
        for(int j=0;j<line.size();j++){
            if(line[j]==p){
                line.replace(j,1,str);
            }
        }
        file_copy << line << endl;
    }
	cout << "Ultima linha: " << endl;
	cout << line;
}
int main(){
	//create_file(200500);
	cut_file(10000);
	return(0);
}
