//
// Created by micha on 21/04/2021.
//

#ifndef TERMINAL_FILEMANAGER_H
#define TERMINAL_FILEMANAGER_H
#include "map"
#include "RCFile.h"

struct FileNotFound : public exception{
    const char* what() const throw() { return "Error: File Not Found!"; }
};
struct WrongPath : public exception{
    const char* what() const throw() { return "Error: Path Not Found!"; }
};
struct DirectoryExist : public exception{
    const char* what() const throw() { return "Error: Directory Already Exist!"; }
};


class FileManager {
private:
    map<const string, map<const string, RCFile*> > drive;
    pair<string, map<const string, RCFile*> > cursor;
public:
    FileManager();
    ~FileManager();
    void mkdir(const string&);
    void chdir(const string&);
    void rmdir(const string&);
    void ls(const string&);
    void lproot();
    void pwd() const;
    void move(const string&, const string&);
    void copy(const string&, const string&);
    void ln(const string&, const string&);
    void remove(const string&);
    void touch(const string&);
    // Helper Functions
    RCFile* searchFile(const string&);
    bool fileExist(const string&);
    static string pathToFolder(const string& path);
    string pathTransformation(const string&);
    bool isFile(const string&);
    bool checkFolderPath(const string&);
};


#endif //TERMINAL_FILEMANAGER_H
