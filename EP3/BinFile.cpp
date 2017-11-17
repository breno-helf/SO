// Breno Helfstein Moura          NUSP: 9790972
// Lucas Daher                    NUSP: 8991769

#include "BinFile.hpp"
using namespace std;

BiFile::BiFile(int s, char *st) {
    size = s;
    file.open(st, std::fstream::in | std::fstream::out | std::fstream::binary);
    aux = new char[1];
    aux[0] = -1;
    for (int j = 0; j < s; j++)
	file.write(aux, 1);
}
        
BiFile::~BiFile() {
    delete[] aux;
}
        
void BiFile::write(int pos, int s, char c) {
    file.seekp(pos);
    aux[0] = c;
    for (int i = 0; i < s; i++)
	file.write(aux, 1);
}
        
void BiFile::read(int pos, int s, char *ret) {
    file.seekg(pos);
    file.read(ret, s);
}
    
void BiFile::copy(BiFile *origin, int pos, int s, int dest) {
    char *b = new char[s];
    origin->read(pos, s, b);
    file.seekp(dest);
    file.write(b, s);
}
        
void BiFile::print() {
    char *buff = new char[size];
    this->read(0, size, buff);
    for (int i = 0; i < size; i++) {
	if (buff[i] < 0) cout << " ";
	else if (buff[i] < 10) cout << "  ";
	else if (buff[i] < 100) cout << " ";
	cout << (short) buff[i] << " ";
    }
    cout << "\n";
}
