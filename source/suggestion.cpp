/* file suggestion.cpp
   author
   date
*/

#include "suggestion.h"

Suggestion::Suggestion(const std::string& dic_path) {
  DIR *dir;
  dirent *pdir;
  dir = opendir(path_folder.c_str());
  if (dir == NULL) {
    return false;
  }

  /*actach '/' at end of path*/
  std::string _path_folder;
  if (path_folder.at(path_folder.length() - 1) != '/') {
    _path_folder = path_folder;
    _path_folder = _path_folder + '/';
  } else { 
    _path_folder = path_folder;
  }

  /*get folder to send name*/
  std::string foldername;
//  foldername = _path_folder.at(_path_folder.length() - 1) + foldername;
  int i = _path_folder.length() - 1;
  do {
    foldername = _path_folder.at(i) + foldername;
    if (i == 0) break;
    i--;
  } while (_path_folder.at(i) != '/');

  path_filename.push_back(foldername);
  path_sub_foldername.push_back(foldername);

  /* get path filename and path subfolder*/
  while (pdir = readdir(dir)) {
    struct stat st;

    if(strcmp(pdir->d_name, ".") == 0 || strcmp(pdir->d_name, "..") == 0) {
      continue;
    }

    if (fstatat(dirfd(dir), pdir->d_name, &st, 0) < 0) {
      std::cout << "Some error in fstatat\n";
      continue;
    }

    if (S_ISREG(st.st_mode)) {
      std::string dname(pdir->d_name);
      path_filename.push_back(_path_folder + pdir->d_name);
    } else if (S_ISDIR(st.st_mode)) {
      std::string dname(pdir->d_name);
      path_sub_foldername.push_back(_path_folder + pdir->d_name);
    }
  }

  closedir(dir);
}
