#ifndef CALCFILE_H
#define CALCFILE_H
// calcfile.h
// Defines a utility class for working with .8Xv files
// File format specification found at https://github.com/calc84maniac/tiboyce/blob/master/tiboyce-convertsav/convertsav.c

// C++ Standard Library
#include <iostream>
#include <fstream>
#include <string>

const static char expected_sig[] = "**TI83F*\x1A\x0A";
const static int sig_len = 11;
const static int com_len = 42;
const static int name_len = 8;
const static int short_char_len = 1;
const static int long_char_len = 2;

enum VAR_TYPE {
    APPVAR = 0x15
};

enum VAR_FLAG {
    UNARCHIVED = 0x00,
    ARCHIVED = 0x80
};

class Calc8XvFile {
public:
    // constructor
    Calc8XvFile();

    // reading contents of file
    int read(const std::string &filename);
    int read(std::istream &in);

    // print file information
    void print(std::ostream &out = std::cout);

    // getters
    int get_var_length();
    std::string get_data();
    int get_checksum();

    // validation
    bool sig_valid();
    bool checksum_valid();

    // setters for various fields
    void set_name(const std::string &name, bool recalc_sum = true);
    void set_comment(const std::string &comment);
    void set_data(const std::string &data, bool recalc_sum = true);
    void set_archived(bool archived, bool recalc_sum = true);

    // function for writing back to another file
    void write(const std::string &base_path = "");

private:
    // file extension (for if we read the file)
    std::string _file_ext;

    // file header
    char _signature[sig_len];
    char _comment[com_len];
    int _file_length;

    // body header
    int _header_length;
    int _data_length;
    VAR_TYPE _data_type;
    char _name[name_len];
    int _version;
    VAR_FLAG _flag;

    // body
    int _data_length_body;
    int _var_length;
    std::string _data;

    // checksum
    int _target_checksum;
    int _checksum;

    // helper method for calculating checksum
    void calc_checksum(std::istream &in);
    void calc_checksum();
    void recalc_checksum();
};

#endif // CALCFILE_H
