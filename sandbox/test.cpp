#include <iostream>
#include <cstring>
#include <string>
using namespace std;

void char_machine (const char *a) {
  for (int i = 0;i < 100;i++) {
    cout << i << ": " << *(a + i);

    if (*(a + i) == 0) cout << " which is the null character!";

    cout << endl;
  }
}

int main(int /*argc*/, char * /*argv*/ []) {
  string test_string = "abcdefg";
  char_machine(test_string.c_str());
  switch(test_string[0]) {
    case 'a':
      cout << "found!";
      break;
  }

  return 0;
}
