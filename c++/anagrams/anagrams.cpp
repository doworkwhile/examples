#include <iostream>
#include <string>

// because we don't store/check the anagrams, this will print duplicates

using namespace std;

string input;
int length;

void rotate(int fromIndex) {
  if (fromIndex >= length) {
    return;
  }

  char t = input[fromIndex];
  for (int i = fromIndex; i < length - 1; i++) {
    input[i] = input[i + 1];
  }
  input[length - 1] = t;
}

void anagram(int fromIndex) {
  int partEnd = length - fromIndex;
  if (partEnd == 1) {
    return;
  }

  for (int i = 0; i < partEnd; i++) {
    anagram(fromIndex + 1);
    if (partEnd == 2) {
      cout << input << endl;
    }
    rotate(fromIndex);
  }
}

int main()
{
  cout << "input > ";
  cin >> input;
  length = input.length();

  anagram(0);

  return 0;
}