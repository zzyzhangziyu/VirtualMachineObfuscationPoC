# A system bus

## Values
CODE | VALUE
--- | ---
DIR_CREATED | 200000
DIR_CREATED_ERROR | 200001
DIR_EXIST | 200002
DELETE_DIR | 200011
MOVE_DIR | 200003
COPY_DIR | 200004
OTHER_DIR_ERROR | 200005
FILE_CREATED | 200006
FILE_EXIST | 200007
DELETE_FILE | 200012
MOVE_FILE | 200008
COPY_FILE | 200009
OTHER_FILE_ERROR | 200010
NO_IMPLEMENTED_ERROR | 200110

## Functions

```c++
int createDirectory(std::string, int))
int deleteDirectory(std::string);
int moveDirectory(std::string, std::string);
int copyDirectory(std::string, std::string);
int createFile(std::string, VBYTE *);
int deleteFile(std::string);
int moveFile(std::string, std::string);
int copyFile(std::string, std::string);
```
## OS support
FUNC | Windows | Linux | MacOS
--- | --- | --- | ---
createDirectory | YES | YES | NO |
deleteDirectory | YES | YES | NO |
moveDirectory | YES | NO | NO |
copyDirectory | YES | NO | NO |
createFile | YES | YES | NO |
deleteFile | YES | YES | NO |
moveFile | YES | YES | NO |
copyFile | YES | YES | NO |