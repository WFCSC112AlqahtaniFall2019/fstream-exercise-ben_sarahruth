#include <iostream>
#include <fstream>
using namespace std;

void readEntry(ifstream& in, int& entry);

int main() {
    ifstream inFile;
    ofstream outFile;
    inFile.open("../table");
    outFile.open("../output");

    if(!inFile.is_open()){
        cout << "Could not open file." << endl;
    }

    // read table dimensions and allocate 2D array
    int nRows, nCols;
    inFile >> nRows >> nCols;
    int** table = new int*[nRows];
    for(int i = 0; i < nRows; i++) {
        table[i] = new int[nCols];
    }

    // read table data
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            try {
              readEntry(inFile, table[i][j]);
            }
            catch (int x) {
                    cout << "Entry " << i << "," << j << " not an integer, was set to " << x << ", now setting it to 0" << endl;
                    table[i][j] = 0;
                    inFile.clear();
                    string tmp;
                    inFile >> tmp;
            }
            inFile.clear();
        }
    }


    // write table data to the screen in transposed order
    outFile << nCols << " " << nRows << endl;
    for(int i = 0; i < nCols; i++) {
        for(int j = 0; j < nRows; j++) {
            outFile << table[j][i] << " ";
        }
        outFile << endl;
    }

    outFile.flush();
    inFile.close();
    outFile.close();


    // free memory
    for(int i = 0; i < nRows; i++) {
        delete [] table[i];
    }
    delete [] table;

}

void readEntry(ifstream& in, int& entry) {
    in >> entry;
    if(in.fail()) {
        throw entry;
    }
}