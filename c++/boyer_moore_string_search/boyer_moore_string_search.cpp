#include <stdio.h>
#include <string>

void fillBoyerMooreComparisionIndexes(
  char* indexes, int indexesLen, std::string* toFind)
{
  int findLen = toFind->size();
  const char* findCstr = toFind->c_str();
  for (int i = 0; i < indexesLen; i++) {
    indexes[i] = -1;
  }
  for (int i = 0; i < findLen; i++) {
    indexes[findCstr[i]] = i;
  }
}

int boyerMooreStringSearch(std::string* toSearch, std::string* toFind)
{
  int endLen = toFind->size();
  int maxSearchLen = toSearch->size();
  int i = endLen - 1;
  int j = endLen - 1;
  char c1;
  char c2;
  int indexCount = 256;
  char indexes[indexCount];
  fillBoyerMooreComparisionIndexes(&indexes[0], indexCount, toFind);

  while(i < maxSearchLen) {
    c1 = toSearch->c_str()[i];
    c2 = toFind->c_str()[j];

    if (c1 != c2) {
      j = endLen - 1;
      // is c1 in c2?
      if (indexes[c1] > -1) {
        i += endLen - (indexes[c1] + 1);
      } else {
        i += j + 1;
      }
    } else {
      j--;
      i--;
      if (j == 0) {
        return i - j;
      }
    }
  }
  return -1;
}

int main()
{
  std::string toFind = "jump";
  std::string toSearch = "the quick brown fox jumps over the lazy dog";
  printf("%d\n", boyerMooreStringSearch(&toSearch, &toFind));

  // false start
  toSearch = " jum jumps over the lazy dog";
  printf("%d\n", boyerMooreStringSearch(&toSearch, &toFind));

  // -1, not in string
  toSearch = "the quick brown fox over the lazy dog";
  printf("%d\n", boyerMooreStringSearch(&toSearch, &toFind));

  // another test
  toFind = "example";
  toSearch = "here is a simple example";
  printf("%d\n", boyerMooreStringSearch(&toSearch, &toFind)); 
}