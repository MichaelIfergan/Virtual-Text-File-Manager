#include <sstream>
#include "FileManager.h"

inline void error_arg1() { cerr << "First argument not recieved!" << endl; }
inline void error_arg2() { cerr << "Second argument not recieved!" << endl; }
inline void error_arg3() { cerr << "Third argument not recieved!" << endl; }
inline void error_args() { cerr << "Too many arguments recieved!" << endl; }

// template function that checks if argument was correct.
template<class T>
bool checkArg(stringstream& ss, T& arg){
    ss >> arg;
    if(ss.fail())
        return true;
    return false;
}

int main() {
    // command map for switch case
    const map<const string, int> commands = { {"read",1}, {"write", 2}, {"touch", 3}, {"copy", 4},
                                         {"remove", 5}, {"move", 6}, {"cat", 7}, {"wc", 8},
                                         {"ln", 9}, {"mkdir",10}, {"chdir", 11}, {"rmdir", 12},
                                         {"ls", 13}, {"lproot", 14}, {"pwd", 15}, {"exit", 16}};
    // create new virtual file manager
    FileManager fm;
    // on is the condition that continues the terminal. exit turn it off.
    bool on = true;
    // variables needed for commands
    string line, command, s1, s2;
    int index;
    char ch;
    // begining loop of terminal by reading line from user and search for matching command.
    while(on){
        getline(cin, line);
        stringstream ss(line);
        ss >> command;
        const auto& iter = commands.find(command);
        if(iter == commands.end()){
            cerr << "Unknown Command!" << endl;
            continue;
        }
        // go to case according to map commands, check arguments for command and activate correct FileManager function.
        switch (iter->second) {
            case 1:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(checkArg(ss, index)) {
                    error_arg2();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                cout << (*fm.searchFile(s1))[index] << endl;
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 2:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(checkArg(ss, index)) {
                    error_arg2();
                    break; }
                if(checkArg(ss, ch)) {
                    error_arg3();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    (*fm.searchFile(s1))[index] = ch;
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 3:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.touch(s1);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 4:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(checkArg(ss, s2)) {
                    error_arg2();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.copy(s1, s2);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 5:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.remove(s1);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 6:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(checkArg(ss, s2)) {
                    error_arg2();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.move(s1, s2);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 7:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.searchFile(s1)->cat();
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 8:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.searchFile(s1)->wc();
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 9:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(checkArg(ss, s2)) {
                    error_arg2();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.ln(s1, s2);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 10:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.mkdir(s1);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 11:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.chdir(s1);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 12:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.rmdir(s1);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 13:
                if(checkArg(ss, s1)) {
                    error_arg1();
                    break; }
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                try{
                    fm.ls(s1);
                }
                catch(exception& ex){
                    cerr << ex.what() << endl;
                }
                break;
            case 14:
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                fm.lproot();
                break;
            case 15:
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                fm.pwd();
                break;
            case 16:
                if(!(ss.tellg() == -1 || ss.tellg() == (unsigned int)line.length())) {
                    error_args();
                    break; }
                on = false;
                break;
            default:
                cerr << "Unknown Command!" << endl;
                break;
        }
    }
    return 0;
}
