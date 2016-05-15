/* file: dictionary.cpp
   author:
   date:
*/
#include "include/dictionary.h"
Dictionary::Dictionary() {

}

Dictionary::Dictionary(std::string name) {
  file_.open(name.c_str());
  file__.open(name.c_str(), std::ios::app);
}

Dictionary::~Dictionary() {
  file_.close();
}

void Dictionary::Suggest(const std::string& patten, std::vector<suggestion_index>& suggestion) {
  std::string n_gram_patten;
  GetPatten(patten, n_gram_patten);

  GetNumPatten(n_gram_patten, suggestion);
  std::sort(suggestion.begin(), suggestion.end(),
            [](const suggestion_index &a, const suggestion_index &b) {
              return a.index > b.index;
            }
           );
}

void Dictionary::GetPatten(const std::string& patten, std::string& n_gram_patten) {
	int numspaces = 0;

	size_t position;

	for (size_t i = patten.length(); i > 0; i--) {
		if (std::isspace(patten[i])) {
			numspaces++;
    }

    if (numspaces > 3) {
      break;
    }
    position = i;
	}
  if (numspaces <= 3) {
    n_gram_patten = patten;
  } else {
    n_gram_patten = patten.substr(position);
  }
}

void Dictionary::GetNumPatten(std::string patten,
                          std::vector<suggestion_index>& suggest_vector) {
  if (file_ == NULL) {
    return ;
  }

  std::string line_of_file;
  while (getline(file_, line_of_file)) {
    std::vector<std::string> string_array_temp;
    FindPatten(line_of_file, patten, string_array_temp);
    for (unsigned int i = 0; i < string_array_temp.size(); i++) {
      bool check_exist = false;
      if (suggest_vector.size() > 0) {
        for (unsigned int j = 0; j < suggest_vector.size(); j++) {
          if (string_array_temp[i] == suggest_vector[j].patten) {
            suggest_vector[j].index++;
            check_exist = true;
            break;
          }
        }
      }

      if (!check_exist) {
        suggestion_index temp;
        temp.patten = string_array_temp[i];
        temp.index = 1;
        suggest_vector.push_back(temp);
      }
    }
  }

}

void Dictionary::BadCharHeuristic(std::string& str, int size, int badchar[NO_OF_CHARS]) {
  int i;
  for (i = 0; i < NO_OF_CHARS; i++) {
    badchar[i] = -1;
  }
  for (i = 0; i < size; i++) {
      badchar[(int)str[i]] = i;
  }
}

unsigned int Dictionary::FindPatten(std::string text, std::string patten,
                        std::vector<std::string>& str_return) {
  unsigned int num_result = 0;

  int m = patten.length();
  int n = text.length();
  int badchar[NO_OF_CHARS];
  BadCharHeuristic(patten, m, badchar);
  int s = 0;
  while (s <= (n - m)) {
    int j = m - 1;
    while (j >= 0 && patten[j] == text[s + j]) {
      j--;
    }
    if (j < 0) {
      unsigned int x = s + m;
      while (text[x] != ' ') {
        x++;
      }
      std::string foo = text.substr(s + m, x - (s + m));
      str_return.push_back(foo);
      num_result++;
      s += ((s + m) < n) ? m - badchar[(int)text[s + m]] : 1;
    } else {
          s += std::max(1, j - badchar[(int)text[s + j]]);
    }
  }
  return num_result;
}
