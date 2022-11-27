#include "../../models/soa/message_cycle.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>

void MessageCycle::notationsInput(std::istream &strval) {
  // Attribution:
  // https://stackoverflow.com/questions/12240010/how-to-read-from-a-texts
  // -file-character-by-character-in-c
  // https://stackoverflow.com/a/12240354
  std::ifstream fileInputs("../../../.share/conf/events/app_user_default.conf");
  // char putCh = getchar();
  // int idx = putCh - '0'; // integer distinguishing value
  // char matcher = letters[idx];
  /*
      for (auto i = 0; i < GAME_BOARD_GRID_MAX_SIZE; ++i) {
          for (auto j = 0; j < GAME_BOARD_GRID_MAX_SIZE; ++j) {
              std::vector<std::vector<int>> temporaryVectorMatrix(i,
                                                      std::vector<int>
                                                                  (j, 0)); */
  for (std::string strval; fileInputs >> strval >> key >> value;) {
    while (fileInputs.is_open() && fileInputs.get(key)) {
      std::cout << strval << key << value << std::endl;
      // How to read a file into vector in C++?
      // https://stackoverflow.com/a/15138839
      std::istream_iterator<char> puts(fileInputs), prints;
      std::vector<char> tempVec(puts, prints);
      // std::ostream_iterator<char> pins(std::cout, " ");

      std::copy(tempVec.begin(), tempVec.end(), &std::cout);
    }
  }
  // Attribution for regex with lookahead for an empty-space character:
  // https://stackoverflow.com/a/14353976/10189198
  // Regex for ScrabbleList.txt: "^(?!.* )[A-Z 1-9]*$"
  //    std::regex letter_regex("^(?!.* )[A-Z 1-9]*$");
  //    this is supposed to be a 'regex' placed for lookahead
  fileInputs.close();
}

auto MessageCycle::read_cin(std::istream &cinput) {
  // std::istream is the modern C++ equivalent to std::cin
  // with auto keyword you must always initialise with an expression
  std::string strval;
  cinput >> strval;
  tail_manager.push_back(strval);
  return strval;
}

auto MessageCycle::get_read_cin() {
  std::string strval;
  strval = tail_manager.back();
  return strval;
}

auto MessageCycle::expressionMatch(std::string) {
  auto x = new std::sregex_iterator;
  std::ifstream fileInputs(get_read_cin());
  std::string fileContents;

  while (fileInputs.get(key)) {
    std::getline(fileInputs, fileContents);
    auto msg = MessageCycle(fileContents.c_str());
    // std::string is not used ...
    // due to weird compatibility with generic or primitive functions
    tail_manager.push_back(get_read_cin()); // TODO(Daniel): missing
    // user-input functionality
    // General idea of this code:
    // back of a std::string Struct-of-Arrays
    /* NOTE(Daniel): trying to write:
     * tempMatrix[i][j] = exampleInput->pseudo_back();
     * tempMatrix[i][j] = exampleInput->pseudo_insert_data();
     * */

    std::regex note_regex(fileContents, std::regex_constants::ECMAScript);
    std::regex_search(fileContents, note_regex);

    // Attribution for regex with lookahead for an empty-space character:
    // https://stackoverflow.com/a/14353976/10189198
    std::regex key_value_regex("^(?!.* )[A-Z 1-9]*$");
    // an empty space character is placed for lookahead
    *x = std::sregex_iterator(fileContents.begin(), fileContents.end(),
                              key_value_regex);
  }
  return x;
}