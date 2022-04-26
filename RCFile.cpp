//
// Created by micha on 18/04/2021.
//

#include "RCFile.h"
#include <iostream>
#include <sstream>

// create strong link between this and rcf.
RCFile &RCFile::operator=(const RCFile& rcf) {
    if(this == &rcf)
        return *this;
    if(--value->rc == 0)
        delete value;
    value = rcf.value;
    value->rc++;
    return *this;
}

// operator for reading character, set seekg at the right index for the char conversion.
const RCFile& RCFile::operator[](unsigned int i) const {
    value->file->clear();
    value->file->seekg(0, ios::end);
    if(value->file->tellg() < i || i < 0)
        throw IndexOutOfBounds();
    value->file->seekg(i);
    return *this;
}

// writing operator, set seekp in right index before the overloaded operator=
RCFile& RCFile::operator[](unsigned int i) {
    value->file->clear();
    value->file->seekp(0, ios::end);
    if(value->file->tellp() < i || i < 0)
        throw IndexOutOfBounds();
    value->file->seekp(i);
    return *this;
}

RCFile& RCFile::operator=(const char& ch) {
    value->file->put(ch);
    value->file->flush();
    value->file->clear();
    return *this;
}

RCFile::operator char() const {
    char ch = value->file->get();
    value->file->flush();
    value->file->clear();
    return ch;
}

// clear flags and seekg to begining, then print file line by line.
void RCFile::cat() {
    value->file->clear();
    value->file->seekg(0, ios::beg);
    string line;
    while(getline(*value->file, line))
        cout << line << endl;
}
// clear flags and seekg to begining to count chars, words and lines.
void RCFile::wc() {
    value->file->clear();
    value->file->seekg(0, ios::end);
    int lines = 0, words = 0, chars;
    chars = (int) value->file->tellg();
    value->file->seekg(0, ios::beg);
    string line, word;
    while(getline(*value->file, line)){
        lines++;
        stringstream ss(line);
        while(ss >> word)
            words++;
    }
    cout << lines << ' ' << words << ' ' << chars << endl;
}

// deep copy this to rcf without strong link.
void RCFile::copy(RCFile& rcf) {
    rcf.value->file->close();
    rcf.value->file->open(rcf.fname.c_str(), ios::in | ios::out | ios::trunc);
    value->file->clear();
    value->file->seekg(0, ios::beg);
    rcf.value->file->clear();
    rcf.value->file->seekp(0, ios::beg);
    string line;
    while(getline(*value->file, line))
        *rcf.value->file << line << endl;
    rcf.value->file->flush();
    value->file->flush();
}

// flush the buffer to update last modified time.
void RCFile::touch() {
    value->file->flush();
}



