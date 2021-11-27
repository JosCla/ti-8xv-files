// calcfile.cpp
// Implements calcfile.h.

// C++ Standard Library
#include <iostream>
using std::cout; using std::cerr; using std::endl;
using std::istream; using std::ostream;
#include <fstream>
using std::ifstream; using std::ofstream;
#include <cstring>
using std::strcmp; using std::memset; using std::memcpy; using std::strlen;
#include <string>
using std::string;

// Our files
#include "calcfile.h"
#include "fileutils.h"

Calc8XvFile::Calc8XvFile() {
    memcpy(_signature, expected_sig, sig_len);
    _header_length = 13;

    set_name("VAR");
    set_comment("");
    set_data("");

    _data_type = APPVAR;
    _version = 0;
    _flag = UNARCHIVED;

    calc_checksum();
    _target_checksum = _checksum;
}

int Calc8XvFile::read(const string &filename) {
    ifstream fin;
    fin.open(filename);
    if (!fin) {
        cerr << "Failed to open file: " << filename << endl;
        return 1;
    }

    return read(fin);
}

int Calc8XvFile::read(istream &in) {
    // reading and validating signature
    for (int i = 0; i < sig_len; i++) {
        char c;
        in.get(c);
        _signature[i] = c;
    }

    if (!sig_valid()) {
        cerr << "Invalid file signature!" << endl;
        return 1;
    }

    // reading comment
    for (int i = 0; i < com_len; i++) {
        char c;
        in.get(c);
        _comment[i] = c;
    }

    // getting file, header, and data length
    _file_length = readIntFromHex(in, long_char_len);
    _header_length = readIntFromHex(in, long_char_len);
    _data_length = readIntFromHex(in, long_char_len);

    // getting file type
    char c_type;
    in.get(c_type);
    _data_type = (VAR_TYPE)c_type;

    // getting file name
    for (int i = 0; i < name_len; i++) {
        char c;
        in.get(c);
        _name[i] = c;
    }

    // getting file version
    _version = (int)readIntFromHex(in, short_char_len);

    // getting file flags
    char c_flag;
    in.get(c_flag);
    _flag = (VAR_FLAG)c_flag;

    // getting data length from the body
    _data_length_body = readIntFromHex(in, long_char_len);
    _var_length = readIntFromHex(in, long_char_len);

    // getting body of the variable
    char data[_var_length];
    for (int i = 0; i < _var_length; i++) {
        char c;
        in.get(c);
        data[i] = c;
    }
    _data = data;

    // getting checksum
    _target_checksum = readIntFromHex(in, long_char_len);
    calc_checksum();
    
    // returning 0 for a successful read
    return 0;
}

void Calc8XvFile::print(ostream &out) {
    cout << "Full 8Xv file:" << endl;
    cout << "-------------------------" << endl;
    cout << "Signature Valid: " << sig_valid() << endl;
    cout << "Checksum Valid: " << checksum_valid() << endl;
    cout << endl;
    cout << "Var Name: " << _name << endl;
    cout << "Comment: " << _comment << endl;
    cout << endl;
    cout << "Full File Length: " << _file_length << endl;
    cout << "Header Length: " << _header_length << endl;
    cout << "Data Length: " << _data_length << endl;
    cout << "Data Length (body): " << _data_length_body << endl;
    cout << "Var Length: " << _var_length << endl;
    cout << endl;
    cout << "Data Type: " << _data_type << endl;
    cout << "Data Flags: " << _flag << endl;
    cout << endl;
    cout << "Target Checksum: " << _target_checksum << endl;
    cout << "Actual Checksum: " << _checksum << endl;
}

bool Calc8XvFile::sig_valid() {
    return (strcmp(_signature, expected_sig) == 0);
}

bool Calc8XvFile::checksum_valid() {
    return _checksum == _target_checksum;
}

void Calc8XvFile::set_name(const string &name) {
    for (unsigned int i = 0; i < name_len; i++) {
        if (i < name.size()) {
            _name[i] = name[i];
        } else {
            _name[i] = '\0';
        }
    }
}


void Calc8XvFile::set_comment(const string &comment) {
    for (unsigned int i = 0; i < com_len; i++) {
        if (i < comment.size()) {
            _comment[i] = comment[i];
        } else {
            _comment[i] = '\0';
        }
    }
}

void Calc8XvFile::set_data(const string &data) {
    // finding new file sizes
    _var_length = data.size();
    _data_length = _var_length + 2;
    _data_length_body = _var_length + 2;
    _file_length = _data_length + _header_length + 4;

    // copying in the data
    char new_data[data.size()];
    for (unsigned int i = 0; i < data.size(); i++) {
        new_data[i] = data[i];
    }
    _data = new_data;
}

void Calc8XvFile::set_archived(bool archived) {
    if (archived) {
        _flag = ARCHIVED;
    } else {
        _flag = UNARCHIVED;
    }
}

void Calc8XvFile::write() {
    // todo
}

void Calc8XvFile::calc_checksum(istream &in) {
    in.seekg(sig_len + com_len + 2);
    int checksum = 0;
    for (int i = 0; i < _file_length; i++) {
        char c;
        in.get(c);
        int val = (int)c;
        if (val < 0) {val += 256;}

        checksum += val;
    }

    _checksum = (checksum & 65535);
}

void Calc8XvFile::calc_checksum() {
    int checksum = 0;

    checksum += checksumVal(_header_length);
    checksum += checksumVal(_data_length);
    checksum += (unsigned char)_data_type;

    for (int i = 0; i < name_len; i++) {
        checksum += (unsigned char)_name[i];
    }

    checksum += checksumVal(_version);
    checksum += (unsigned char)_flag;
    checksum += checksumVal(_data_length_body);
    checksum += checksumVal(_var_length);

    for (int i = 0; i < _var_length; i++) {
        checksum += (unsigned char)_data[i];
    }

    _checksum = (checksum & 65535);
}
