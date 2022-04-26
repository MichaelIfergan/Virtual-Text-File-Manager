//
// Created by micha on 18/04/2021.
//
#ifndef TERMINAL_RCFILE_H
#define TERMINAL_RCFILE_H

#include "fstream"
#include <iostream>

using namespace std;

struct IndexOutOfBounds : public exception{
    const char* what() const throw() { return "Error: Index is out of bounds!"; }
};

class RCFile {
    struct RCValue {
        int rc;
        fstream *file;
        RCValue(fstream *f) : rc(1), file(f) {};
        ~RCValue() {file->close(); delete file; };
    };

private:
    RCValue *value;
    string fname;
public:
    // C'tor opens new file with flags:in, out, trunc(override file if exist already)
    RCFile(const string &s) : value(new RCValue(new fstream(s.c_str(), ios_base::in | ios_base::out | ios_base::trunc))), fname(s) {};
    // D'tor decrement rc and if it's the last reference delete it and remove it from computer.
    ~RCFile() { if (--value->rc == 0) {delete value; std::remove(fname.c_str());} }
    RCFile(const RCFile& rcf): value(rcf.value), fname(rcf.fname) {};
    RCFile& operator=(const RCFile&);
    const RCFile& operator[](unsigned int) const;
    RCFile& operator[](unsigned int);
    RCFile& operator=(const char&);
    operator char() const;
    void cat();
    void wc();
    void copy(RCFile&);
    int getRC() const { return value->rc; }
    void touch();
};
#endif //TERMINAL_RCFILE_H
