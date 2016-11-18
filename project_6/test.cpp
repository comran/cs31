#include <iostream>
using namespace std;

/*
// 1a
int main() {
  int arr[3] = {5, 10, 15};
  int *ptr = arr;

  *ptr = 30;      // set arr[0] to 30
  *(ptr + 1) = 20;  // set arr[1] to 20
  ptr += 2;
  ptr[0] = 10;  // set arr[2] to 10

  int *ptr_2 = arr;
  do {
    cout << *ptr_2 << endl;  // print values
    ptr_2++;
  } while (ptr >= ptr_2);
}*/
/*
// 1b
// ?????????????????
void findMax(int arr[], int n, int* pToMax) {
  if (n <= 0) return;  // no items, no maximum!

  (void)arr;

  pToMax = new int;
  cout << pToMax << endl;

  for (int i = 1; i < n; i++) {
    //if (arr[i] > *pToMax) pToMax = arr + i;
    //cout << arr[i] << " -- " << *pToMax << endl;
  }
}

int main() {
  int nums[4] = {5, 3, 15, 6};
  int* ptr;

  findMax(nums, 4, ptr);
  cout << ptr << endl;
  cout << "The maximum is at address " << ptr << endl;
  cout << "It's at position " << ptr - nums << endl;
  cout << "Its value is " << *ptr << endl;
}*/

/*
void computeCube(int n, int *ncubed) { *ncubed = n * n * n; }

int main() {
  int *ptr = new int;
  computeCube(5, ptr);
  cout << "Five cubed is " << *ptr << endl;
}
*/

/*
// 1d
// To fix the functionality of strequal, every part of the code in the strequal
// function where the current character is supposed to be compared needs a
// dereference * operator. Otherwise, the entire array is being compared instead
// of a single character. The incremental lines should not be changed since
// those are shifting the 0 index of the array over to the right to proceed to
// the next character.

// return true if two C strings are equal
bool strequal(const char str1[], const char str2[]) {
  while (*str1 != 0 && *str2 != 0) {
    cout << *str1 << " -- " << *str2 << endl;
    if (*str1 != *str2)  // compare corresponding characters
      return false;
    str1++;  // advance to the next character
    str2++;
  }
  return *str1 == *str2;  // both ended at same time?
}

int main() {
  char a[15] = "Zhou";
  char b[15] = "Zhou";

  if (strequal(a, b)) cout << "They're the same person!\n";
}
*/

// 1e
// This program is attempting to return a local pointer in the function getPtrToArray that would be cleared off the stack after the function terminates. Currently, the address of stack memory associated with the local variable *anArray is returned, which would not be accessible outside the function in the way that was intended.
int *getPtrToArray(int &m) {
  int *anArray = new int[100];
  for (int j = 0; j < 100; j++) anArray[j] = 100 - j;
  m = 100;
  return anArray;
}

void f() {
  int junk[100];
  for (int k = 0; k < 100; k++) junk[k] = 123400000 + k;
}

int main() {
  int n;
  int *ptr = getPtrToArray(n);
  f();
  for (int i = 0; i < 3; i++) cout << ptr[i] << ' ';
  for (int i = n - 3; i < n; i++) cout << ptr[i] << ' ';
  cout << endl;
}
