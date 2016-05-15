/* file: dictionary.h
   author:
   date:
*/
#ifndef DICTIONARY_H
#define DICTIONARY_H
 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream>
 
# define NO_OF_CHARS 256
 
struct suggestion_index {
  std::string patten;
  unsigned int index;
};
 
 
class Dictionary {
 public:
  Dictionary();
  Dictionary(std::string name);
  ~Dictionary();
  void Suggest(const std::string&, std::vector<suggestion_index>&);

  void GetNumPatten(std::string patten,
                    std::vector<suggestion_index>& suggest_vector);

  void Write(std::string patten) {
    file__ << patten << std::endl;
  file__.close();
  }
 
 private:

  void GetPatten(const std::string& patten, std::string& n_gram_patten);

  void BadCharHeuristic(std::string& str, int size, int badchar[NO_OF_CHARS]);
 
  unsigned int FindPatten(std::string text, std::string patten,
                          std::vector<std::string>& str_return);
 private:
  std::ifstream file_;
  std::ofstream file__;
};
#endif //ending file dictionary.h
