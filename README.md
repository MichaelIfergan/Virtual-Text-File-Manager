# Virtual-Text-File-Manager
Linux based text file manager.

I created a class called RCFile that contains the file name(path with '/' transformed to '_')
and pointer to struct RCValue(holds rc counter and pointer to fstream).
The second class I created is FileManager that contains variable drive that is a map with string keys(folder name) 
and value is another map that contains string keys(file name without path transformation) and value is pointer to RCFile.
FileManager also contains variable cursor that points to files map of certain folder(default = "V/").
All the functions work on global path except copy that can recieve file name in the folder the cursor holds.

Classes functions:

RCFile:
1) operator[] for writing sets seekp in the index given and uses overloaded operator=(char) to change the character in tellp index.
2) operator[] for read sets seekg in the index given and uses conversion operator to char to retrieve the character in tellg index.
3) In all functions I uses clear() to reset file flags, and after every write operation i use flush() on the buffer.

FileManager:
FileManager is responsible for creating and deleting RCFiles(the only dynamic allocations in program).
Helper Functions:
1) searchFile - check if folder and file exist. return *RCFile or throw exception.
2)fileExist - boolean check if file exists.
3)pathToFolder - recieve full path of file and return the substring of the folder.
4)pathTransformation - returns path but changes all '/' in path to '_' in order to save on computer and avoid overwriting.
Example: V/test.txt and V/tmp/test.txt. if I saved just the file name one of them would be overwritten.
5)isFile - boolean check if string recieved contains just file name. Used only for copy function to check if source file in cursor folder.
6)checkFolderPath - boolean check if folder path recieved is correct, check that all folders along the path exist.
General Functions:
1)lproot - print first drive folder("V/") and files in it, then in lexicographic order the subfolders and their files.
2)move - use RCFile operator= then delete source file.
3)copy - check if source file string is full path or local file name, destination file must be full path, and do deep copy from source to destination.
4)ln - use RCFile operator=.
5) remove, touch - works on full path to file.
6)mkdir, chdir, rmdir, ls - works on full path to folder(ends with '/')

Terminal:
I used main as my terminal. each line entered to terminal check if command exist and using switch case check the rest of the arguments.
in each case first check arguments are correct and there is no more argument in line, then try to execute command and catch exception if was thrown.
