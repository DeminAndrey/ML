#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class CSVReader {
  std::ifstream filestream;
  unsigned int vectorsize;

  std::pair<float, std::vector<float>> parse_row(const std::string & str) {
    std::vector<float> row;
    row.reserve(vectorsize);
    std::stringstream ss(str);
    std::string token;
    bool first_elem = true;
    float res;
    while(!ss.eof()) {
      std::getline(ss, token, ',');
      if(first_elem) {
        res = atoi(token.c_str());
        first_elem = false;
      }
      else
        row.push_back(atoi(token.c_str()));
    }
    return std::make_pair(res, row);
  }

public:
  CSVReader(const std::string & filename, int vector_size)
    : vectorsize(vector_size) {
    filestream.open(filename);
    if (!filestream.is_open()) {
      std::cout << "failed to open file"<<std::endl;
    }
  }

  std::pair<float, std::vector<float>>  read() {
    if (!filestream.is_open()) {
      std::cout << "failed to open file"<<std::endl;
    }

    std::string row;
    while(!filestream.eof()) {
      std::getline(filestream, row);
      if(row.empty())
        break;
      return parse_row(row);
    }

    return std::make_pair(-1, std::vector<float>());
  }
};
