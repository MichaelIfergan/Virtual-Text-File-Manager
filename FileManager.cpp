//
// Created by micha on 21/04/2021.
//

#include "set"
#include "FileManager.h"
#include "iterator"
#include "list"

// C'tor create map with default constructor and insert the drive folder V. also update to cursor to it.
FileManager::FileManager() {
    drive.insert(make_pair("V/", map<const string, RCFile*>()));
    cursor = *drive.begin();
}

// Iterate over all folders, and in each folder delete all the files in it. maps pairs deleted from stack at the end.
FileManager::~FileManager() {
    for (auto& folder : drive){
        for(auto& file : folder.second)
            delete file.second;
    }
}

// check if path is correct and all folders leading to it exist except the last. if true create new folder else throw exception.
void FileManager::mkdir(const string& path) {
    if(drive.find(path) != drive.end())
        throw DirectoryExist();
    if(!checkFolderPath(path))
        throw WrongPath();
    drive.insert(make_pair(path,  map<const string, RCFile*>() ));
}

// check if path is correct and all folders leading to it exist. if true update cursor to it.
void FileManager::chdir(const string& path) {
    if(!checkFolderPath(path))
        throw WrongPath();
    cursor = *drive.find(path);
}

void FileManager::rmdir(const string& path) {
    //check if path is correct and all folders leading to it exist.
    if(!checkFolderPath(path))
        throw WrongPath();
    list<string> to_delete;
    // delete files for each folder that is a subfolder of path, and enter it to_delete list.
    for(auto& folder : drive){
        if(path.length() <= folder.first.length() && path == folder.first.substr(0, path.length())) {
            if(cursor.first == folder.first)
                cursor = *drive.begin();
            for(auto& files : folder.second)
                delete files.second;
            to_delete.push_front(folder.first);
        }
    }
    // erase folders from drive map, that activates erase of all the pairs in it.
    for(auto& folder : to_delete)
        drive.erase(folder);
}

// add all folder paths to order(lexicographic sort), then print folder name and files in it by order.
void FileManager::lproot() {
    set<string> order;
    for(auto& folder : drive)
        order.insert(folder.first);
    for(auto& folder_name : order){
        const auto& folder = drive.find(folder_name);
        cout << folder_name << ":" << endl;
        for(const auto& file : folder->second)
            cout << file.first << ' ' << file.second->getRC() << endl;
    }
}

// print the folder path of cursor.
void FileManager::pwd() const {
    cout << cursor.first  << endl;
}

// uses RCFile operator= to make hard link between src and dst.
void FileManager::ln(const string& src, const string& dst) {
    *searchFile(src) = *searchFile(dst);
}

// check that source exist, then check path for dst, if not exist create it. then hard link src with dst and finally delete src.
void FileManager::move(const string& src, const string& dst) {
    searchFile(src);
    if(!checkFolderPath(pathToFolder(dst)))
        throw WrongPath();
    if(!fileExist(dst))
        drive.find(pathToFolder(dst))->second.insert(make_pair(dst, new RCFile(pathTransformation(dst))));
    *searchFile(dst) = *searchFile(src);
    delete searchFile(src);
    drive.find(pathToFolder(src))->second.erase(src);
}

// check if src is a local path or global path, and if it exist. then check dst, if not exist create it and use RCFile copy.
void FileManager::copy(const string& src, const string& dst) {
    RCFile* src_ptr;
    if(isFile(src)){
        string path = cursor.first + src;
        src_ptr = searchFile(path);
    }
    else
        src_ptr = searchFile(src);
    if(!checkFolderPath(pathToFolder(dst)))
        throw WrongPath();
    if(!fileExist(dst))
        drive.find(pathToFolder(dst))->second.insert(make_pair(dst, new RCFile(pathTransformation(dst))));
    src_ptr->copy(*(searchFile(dst)));
}

// delete the file and erase it from map, throws exceptions if failed.
void FileManager::remove(const string& path) {
    delete searchFile(path);
    drive.find(pathToFolder(path))->second.erase(path);
}

// check that file path is correct and if file exist use RCFile touch, else create file.
void FileManager::touch(const string& file) {
    if(!checkFolderPath(pathToFolder(file)))
        throw WrongPath();
    if(fileExist(file))
        searchFile(file)->touch();
    else {
        drive.find(pathToFolder(file))->second.insert(make_pair(file, new RCFile(pathTransformation(file))));
    }
}

// prints folder name and files in it.
void FileManager::ls(const string& folder) {
    if(!checkFolderPath(folder))
        throw WrongPath();
    cout << drive.find(pathToFolder(folder))->first << ':' << endl;
    for(auto& file : drive.find(pathToFolder(folder))->second)
        cout << file.first << endl;
}

// return pointer to file if found, else throws exceptions
RCFile* FileManager::searchFile(const string& path) {
    if(!checkFolderPath((pathToFolder(path))))
        throw WrongPath();
    for(auto& file : drive.find(pathToFolder(path))->second){
        if(file.first == path)
            return file.second;
    }
    throw FileNotFound();
}

// check if folder path exist.
bool FileManager::checkFolderPath(const string& path) {
    if (path[0] != 'V' || path[1] != '/' || path[path.length()-1] != '/' || path.length() < 2)
        return false;
    for (unsigned int i = 2; i < path.length() - 1; i++) {
        if (path[i] == '/' && drive.find(path.substr(0, i+1)) == drive.end())
            return false;
    }
    return true;
}

// return string without file name.
string FileManager::pathToFolder(const string &path) {
    unsigned int i =path.length()-1;
    for(; i > 0; i--) {
        if (path[i] == '/')
            break;
    }
    return path.substr(0, i + 1);
}

// check if file exist in path folder.
bool FileManager::fileExist(const string& path) {
    if(drive.find(pathToFolder(path)) != drive.end() &&
       drive.find(pathToFolder(path))->second.find(path) != drive.find(pathToFolder(path))->second.end())
        return true;
    return false;
}

// return string of path exchanging all '/' with '_'
string FileManager::pathTransformation(const string& path) {
    string transformation = path;
    for(unsigned int i=0; i<transformation.length();i++) {
        if(transformation[i] == '/')
            transformation[i] = '_';
    }
    return transformation;
}

// check if path recieved is global path or local path.
bool FileManager::isFile(const string& src) {
    for(auto& ch : src) {
        if(ch =='/')
            return false;
    }
    return true;
}




