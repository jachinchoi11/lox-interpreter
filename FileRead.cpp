//
// Created by Jachin Choi on 2/7/25.
//

#include "FileRead.h"

FileRead::FileRead(std::string file_name) : file_name(file_name) {};

void FileRead::read_file(const std::string file_name) {
    file_reader.open(file_name);
}

FileRead::~FileRead() {
    file_reader.close();
}

