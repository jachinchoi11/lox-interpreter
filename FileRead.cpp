//
// Created by Jachin Choi on 2/7/25.
//

#include "FileRead.h"
#include <fstream>

FileRead::FileRead(std::string file_name) : file_name(file_name) {};

void FileRead::read_file(const std::string file_name) {
    file_reader.open(file_name);
}

FileRead::~FileRead() {
    file_reader.close();
}

std::string FileRead::scan_file() {
    if (!file_reader.is_open()) {
        throw std::logic_error("FileRead::scan_file() is not open");
    }
    std::string content;

    std::ifstream ifs(file_name);
    std::string curr_line;
    while (std::getline(ifs, curr_line)) {
        content += curr_line + '\n';
    }
    return content;
}

