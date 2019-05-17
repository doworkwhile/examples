#include <iostream>

using namespace std;

int factorial(int i)
{
  if (i < 2) {
    return 1;
  }
  return i * factorial(i - 1);
}

int main()
{
  cout << "0!: " << factorial(0) << endl;
  cout << "1!: " << factorial(1) << endl;
  cout << "2!: " << factorial(2) << endl;
  cout << "3!: " << factorial(3) << endl;
  cout << "4!: " << factorial(4) << endl;
  cout << "5!: " << factorial(5) << endl;
  cout << "6!: " << factorial(6) << endl;
}