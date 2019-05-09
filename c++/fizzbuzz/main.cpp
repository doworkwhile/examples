#include <iostream>

using namespace std;

void oneEndl()
{
  for (int i = 1; i <= 100; ++i) {
    bool imod3 = i % 3 == 0;
    bool imod5 = i % 5 == 0;
    if (imod3) {
      cout << "Fizz";
    }
    if (imod5) {
      cout << "Buzz";
    }
    if (!imod3 && !imod5) {
      cout << i;
    }
    cout << endl;
  }
}

void fourComp()
{
  for (int i = 1; i <= 100; ++i) {
    bool imod3 = i % 3 == 0;
    bool imod5 = i % 5 == 0;
    if (imod3 && imod5) {
      cout << "FizzBuzz" << endl;
    } else if (imod3) {
      cout << "Fizz" << endl;
    } else if (imod5) {
      cout << "Buzz" << endl;
    } else {
      cout << i << endl;
    }
  }
}

int main()
{
  fourComp();
}