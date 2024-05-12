#include "map.h"

Map::Map() {
  std::string fileName = "input.txt";
  while (true) {
    std::string input;

    std::cout << "Enter the file name (or press Enter to use "
                 "default(\"input.txt\")): ";
    std::getline(std::cin, input);

    if (input.empty()) {
      break;
    }
  }

  std::fstream file;
  // open the file
  file.open(fileName, std::ios::in);
  // check if the file is opened
  if (!file.is_open()) {
    std::cout << "File not found!" << std::endl;
    std::cout << "Exiting..." << std::endl;
    exit(1);
  }

  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    originMap.push_back(line);
  }

  file.close();

  for (int i = 0; i < originMap.size(); i++) {
    for (int j = 0; j < originMap[i].size(); j++) {
      Object obj(i, j, originMap[i][j]);
    }
  }