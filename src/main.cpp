#include <iostream>
#include <string>
using namespace std;

#include "calcfile.h"

int main() {
    string filename;
    cout << "Enter file to read: ";
    cin >> filename;

    Calc8XvFile calcfile;
    int res = calcfile.read(filename);

    if (res) {
        cerr << "Bad file read! Aborting..." << endl;
        return 1;
    } else {
        calcfile.print();
    }

    return 0;
}
