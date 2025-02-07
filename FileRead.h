//
// Created by Jachin Choi on 2/7/25.
//

#ifndef FILEREAD_H
#define FILEREAD_H
#include <fstream>

class FileRead {
    FileRead(std::string file_name);
    ~FileRead();
public:
    std::ifstream file_reader;
    std::string file_name;
    void read_file(const std::string file_name);
};
#endif //FILEREAD_H
