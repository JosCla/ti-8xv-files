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

        /*
        calcfile.set_name("BURGER");
        calcfile.set_comment("burger time!");
        calcfile.set_data("burger moment");
        calcfile.set_archived(false);

        calcfile.write();
        */
    }

    return 0;
}
