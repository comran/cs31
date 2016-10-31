#include <iostream>
using namespace std;

int main() {
  int side;

  cout << "Enter a number: ";
  cin >> side;

  int i = 0;
  do {
    if (i >= side) break;

    int j = i;
    do {
      cout << "#";
    } while (--j >= 0);

    cout << "\n";
  } while (++i < side);
}
