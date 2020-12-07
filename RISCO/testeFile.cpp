#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

	ifstream inDataFile;
	string linha1, linha2;

	inDataFile.open("inDataFile.txt");
	if(!inDataFile.is_open()){
		cout << "Falha ao abrir arquivo" << endl;
		return 0;
	}

	while(getline(inDataFile, linha1) and getline(inDataFile, linha2)){
		cout << linha1.c_str() << " " << linha2.c_str() << endl;
	}
	inDataFile.close();
	return 0;
}