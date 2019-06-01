#include <stdio.h>
#include <string>

int kpmStringSearch(std::string* toSearch, std::string* toFind)
{
  int i = 0;
  int j = 0;
  int endLen = toFind->size();
  int maxSearchLen = toSearch->size();

  while(i < maxSearchLen) {
    char searchVal = toSearch->c_str()[i];
    char findVal = toFind->c_str()[j];
    // check if the 2 chars match
    if (searchVal != findVal) {
      // matched >0 chars? reset the match and don't move foward
      if (j > 0) {
        j = 0;
      } else {
        i++;
      }
    } else {
      // try to match the next char also
      j++;
      i++;
      // after matching every char, return the index of the first char
      if (j == endLen) {
        return i - j;
      }
    }
  }

  // not found
  return -1;
}

int main()
{
  std::string toFind = "jump";
  std::string toSearch = "the quick brown fox jumps over the lazy dog";
  printf("%d\n", kpmStringSearch(&toSearch, &toFind));

  // false start
  toSearch = " jumjumps over the lazy dog";
  printf("%d\n", kpmStringSearch(&toSearch, &toFind));

  // -1, not in string
  toSearch = "the quick brown fox over the lazy dog";
  printf("%d\n", kpmStringSearch(&toSearch, &toFind)); 

  // another test
  toFind = "example";
  toSearch = "here is a simple example";
  printf("%d\n", kpmStringSearch(&toSearch, &toFind)); 

}