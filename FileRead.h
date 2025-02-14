//
// Created by Jachin Choi on 2/7/25.
//

#ifndef FILEREAD_H
#define FILEREAD_H
#include <fstream>

class FileRead {
    ~FileRead();
public:
    FileRead(std::string file_name);
    std::ifstream file_reader;
    std::string file_name;
    void read_file(std::string file_name);
    std::string scan_file();
};
#endif //FILEREAD_H
