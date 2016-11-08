#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value) {
  if (n < 0) return -1;

  for (int i = 0; i < n; i++) {
    a[i] = a[i] + value;
  }

  return n;
}

int lookup(const string a[], int n, string target) {
  for (int i = 0; i < n; i++) {
    if (a[i] == target) return i;
  }

  return -1;
}

int positionOfMax(const string a[], int n) {
  string max_string = "";
  int max_index = -1;

  for (int i = 0; i < n; i++) {
    if (max_index == -1) max_index = i;

    if (max_string < a[i]) {
      max_string = a[i];
      max_index = i;
    }
  }

  return max_index;
}

int rotateLeft(string a[], int n, int pos) {
  if (pos > n) return -1;
  if (pos < 0) return -1;

  string a_at_pos = a[pos];
  for (int i = pos; i < n - 1; i++) {
    a[i] = a[i + 1];
  }
  a[n - 1] = a_at_pos;

  return pos;
}

int countRuns(const string a[], int n) {
  if (n < 0) return -1;

  int elements_after_run_start = 0;

  for (int i = 0; i < n - 1; i++) {
    if (a[i] == a[i + 1]) {
      elements_after_run_start++;
    }
  }

  return n - elements_after_run_start;
}

int flip(string a[], int n) {
  if (n < 0) return -1;

  for (int i = 0; i < n / 2; i++) {
    int inverse_i = n - i;

    string inverse_i_string = a[inverse_i - 1];

    a[inverse_i - 1] = a[i];
    a[i] = inverse_i_string;
  }

  return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
  if (n1 < 0 || n2 < 0) return -1;

  for (int i = 0; i < n1 && i < n2; i++) {
    if (a1[i] != a2[i]) return i;
  }

  return n1 < n2 ? n1 : n2;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
  if (n2 == 0) return 0;

  for (int i = 0; i < n1 - n2; i++) {
    for (int j = 0; j < n2; j++) {
      if (a1[i + j] != a2[j]) break;
      if (j == n2 - 1) return i;
    }
  }

  return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n2; j++) {
      if (a1[i] == a2[j]) return i;
    }
  }

  return -1;
}

int separate(string a[], int n, string separator) {
  if (n < 0) return -1;

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (a[i] > a[j]) {
        string temp_later_element = a[j];
        a[j] = a[i];
        a[i] = temp_later_element;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (a[i] >= separator) return i;
  }

  return n;
}

int main(int /*argc*/, char * /*argv*/ []) {
  string test_backup[] = {"hillary", "gary", "donald", "jill", "evan"};
  string test[5];

  // ///// appendToAll test /////
  // Test appendToAll to see if it appends !!! from the first element to n.
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];
  assert(appendToAll(test, 5, "!!!") == 5 && test[0] == "hillary!!!" &&
         test[1] == "gary!!!" && test[2] == "donald!!!" &&
         test[3] == "jill!!!" && test[4] == "evan!!!");
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];
  assert(appendToAll(test, 3, "!!!") == 3 && test[0] == "hillary!!!" &&
         test[1] == "gary!!!" && test[2] == "donald!!!" && test[3] == "jill" &&
         test[4] == "evan");
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];
  assert(appendToAll(test, 1, "!!!") == 1 && test[0] == "hillary!!!" &&
         test[1] == "gary" && test[2] == "donald" && test[3] == "jill" &&
         test[4] == "evan");
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];

  // Test appendToAll to see if it handles a n of 0 correctly.
  assert(appendToAll(test, 0, "!!!") == 0 && test[0] == "hillary" &&
         test[1] == "gary" && test[2] == "donald" && test[3] == "jill" &&
         test[4] == "evan");
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];

  // Test appendToAll to see if it handles a negative n correctly.
  assert(appendToAll(test, -10, "!!!") == -1 && test[0] == "hillary" &&
         test[1] == "gary" && test[2] == "donald" && test[3] == "jill" &&
         test[4] == "evan");
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];

  // ///// lookup test /////
  // Test lookup to see if it can find an element that exists in the array.
  assert(lookup(test, 5, "donald") == 2);
  // Test lookup to see if it returns -1 on failure to find an element in an
  // array.
  assert(lookup(test, 5, "george") == -1);

  // Test lookup to see if case matters.
  assert(lookup(test, 5, "donald") == 2 && lookup(test, 5, "doNald") == -1);

  // Test lookup to see if it returns -1 on failure to find an element in an
  // array of length 0.
  assert(lookup(test, 0, "donald") == -1);

  // Test lookup to see that the logic still holds for empty strings.
  test[1] = "";
  assert(lookup(test, 5, "") == 1);
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];

  // Test lookup to see if it handles a negative n correctly.
  assert(lookup(test, -10, "donald") == -1);

  // ///// positionOfMax test /////
  // Test positionOfMax to see if it can find the highest alphabetically-ranked
  // string in the whole array.
  assert(positionOfMax(test, 5) == 3);

  // Test positionOfMax to see if it returns -1 for arrays with no elements.
  assert(positionOfMax(test, 0) == -1);

  // Test positionOfMax to see if it returns the smallest number of the greatest
  // string, if two strings in the array are equal.
  test[0] = "hillary";
  test[1] = "donald";
  test[2] = "hillary";
  assert(positionOfMax(test, 3) == 0);
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];

  // Test positionOfMax to see if it can handle empty string elements.
  test[0] = "";
  test[1] = "";
  assert(positionOfMax(test, 2) == 0);
  test[2] = "hillary";
  assert(positionOfMax(test, 3) == 2);
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];

  // Test positionOfMax to see if it returns -1 if given a negative array
  // length.
  assert(positionOfMax(test, -10) == -1);

  // ///// rotateLeft test /////
  // Test rotateLeft to see if it can move the eliminated element to the last
  // place.
  test[0] = "evan";
  test[1] = "donald";
  test[2] = "gary";
  test[3] = "jill";
  test[4] = "hillary";
  assert(rotateLeft(test, 5, 1) == 1 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");

  // Test rotateLeft to make sure it doesn't go out of bounds.
  assert(rotateLeft(test, 1, 1000) == -1 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");

  // Test rotateLeft to see if it can handle rotating an array with only one
  // element.
  assert(rotateLeft(test, 1, 0) == 0 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");

  // Test rotateLeft to see if it returns -1 when given a 0 or negative n.
  assert(rotateLeft(test, 0, 1) == -1 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");
  assert(rotateLeft(test, -1, 1) == -1 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");

  // Test rotateLeft to see if it can handle a bad pos input.
  assert(rotateLeft(test, 5, -1) == -1 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");
  assert(rotateLeft(test, -1, -1) == -1 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");

  // ///// countRuns test /////
  // Test countRuns to see if it can count multiple runs.
  string count_runs_test[] = {"tim",    "ajamu",  "mike", "mike", "donald",
                              "donald", "donald", "mike", "mike"};
  assert(countRuns(count_runs_test, 9) == 5);

  // Test countRuns to see if it handles empty strings correctly.
  count_runs_test[0] = "";
  count_runs_test[1] = "";
  count_runs_test[2] = "";
  assert(countRuns(count_runs_test, 3) == 1);

  // Test countRuns to see if it handles counting an empty array.
  assert(countRuns(count_runs_test, 0) == 0);

  // Test countRuns to see if it returns -1 when given a negative n.
  count_runs_test[0] = "tim";
  count_runs_test[1] = "ajamu";
  count_runs_test[2] = "mike";
  count_runs_test[3] = "mike";
  count_runs_test[4] = "donald";
  count_runs_test[5] = "donald";
  count_runs_test[6] = "donald";
  count_runs_test[7] = "mike";
  count_runs_test[8] = "mike";
  assert(countRuns(count_runs_test, -10) == -1);

  // ///// flip test /////
  // Test flip to see if it can flip an array.
  string test_flip[] = {"ajamu", "mike", "", "tim", "mindy", "bill"};
  assert(flip(test_flip, 4) == 4 && test_flip[0] == "tim" &&
         test_flip[1] == "" && test_flip[2] == "mike" &&
         test_flip[3] == "ajamu" && test_flip[4] == "mindy" &&
         test_flip[5] == "bill");

  // Test flip to see if an n of 0 causes the function to return 0 without
  // changing the array.
  assert(flip(test_flip, 0) == 0 && test_flip[0] == "tim" &&
         test_flip[1] == "" && test_flip[2] == "mike" &&
         test_flip[3] == "ajamu" && test_flip[4] == "mindy" &&
         test_flip[5] == "bill");

  // Test flip to see if it can flip a single element array.
  test_flip[0] = "";
  test_flip[1] = "test1";
  test_flip[2] = "test2";
  assert(flip(test_flip, 1) == 1 && test_flip[0] == "");

  // Test flip to see if it can flip a double element array.
  assert(flip(test_flip, 2) == 2 && test_flip[0] == "test1" &&
         test_flip[1] == "");

  // Test flip to see if it returns -1 when given a bad n.
  test_flip[0] = "ajamu";
  test_flip[1] = "mike";
  test_flip[2] = "";
  test_flip[3] = "tim";
  test_flip[4] = "mindy";
  test_flip[5] = "bill";
  assert(flip(test_flip, -10) == -1);

  // ///// differ test /////
  string differ_test_1[6] = {"ajamu", "mike", "", "tim", "mindy", "bill"};
  string differ_test_2[5] = {"ajamu", "mike", "bill", "", "tim"};

  // Test differ to see if it can find a difference along the entire length of
  // both arrays.
  assert(differ(differ_test_1, 6, differ_test_2, 5) == 2);

  // Test differ to see if it can find a difference along a section of both
  // arrays.
  assert(differ(differ_test_1, 2, differ_test_2, 1) == 1);

  // Test differ to see if it returns the greater n if both arrays are equal up
  // to one or both of the array lengths.
  differ_test_2[2] = "";
  differ_test_2[3] = "tim";
  differ_test_2[4] = "mindy";
  assert(differ(differ_test_1, 5, differ_test_2, 5) == 5);
  assert(differ(differ_test_1, 6, differ_test_2, 5) == 5);
  assert(differ(differ_test_1, 0, differ_test_2, 5) == 0);
  assert(differ(differ_test_1, 6, differ_test_2, 0) == 0);
  assert(differ(differ_test_1, 0, differ_test_2, 0) == 0);

  // Test differ to see if it returns -1 if either n provided is negative.
  assert(differ(differ_test_1, -10, differ_test_2, 5) == -1);
  assert(differ(differ_test_1, 6, differ_test_2, -10) == -1);
  assert(differ(differ_test_1, -10, differ_test_2, -10) == -1);

  // ///// subsequence test /////
  // Test subsequence to see if it can find a subsequence within a bigger array.
  string subsequence_test_1[] = {"evan", "hillary", "mindy",
                                 "jill", "ajamu",   "gary"};
  string subsequence_test_2[] = {"hillary", "mindy", "jill"};
  assert(subsequence(subsequence_test_1, 6, subsequence_test_2, 3) == 1);
  subsequence_test_2[0] = subsequence_test_2[1];
  assert(subsequence(subsequence_test_1, 6, subsequence_test_2, 1) == 2);

  // Test subsequence to see if it returns -1 if it fails to find a subsequence
  // within a bigger array.
  string subsequence_test_3[] = {"evan", "jill"};
  assert(subsequence(subsequence_test_1, 5, subsequence_test_3, 2) == -1);
  assert(subsequence(subsequence_test_1, 6, subsequence_test_2, 2) == -1);

  // Test subsequence to see if it returns -1 if given a negative n.
  subsequence_test_2[0] = "hillary";
  subsequence_test_2[1] = "mindy";
  subsequence_test_2[2] = "jill";
  assert(subsequence(subsequence_test_1, -1, subsequence_test_2, 3) == -1);
  assert(subsequence(subsequence_test_1, -1, subsequence_test_2, -1) == -1);
  assert(subsequence(subsequence_test_1, 6, subsequence_test_2, -1) == -1);

  // Test subsequence to see if a subsequence of 0 is found at the beginning of
  // any sequence.
  assert(subsequence(subsequence_test_1, 6, subsequence_test_2, 0) == 0);
  assert(subsequence(subsequence_test_1, 0, subsequence_test_2, 0) == 0);

  // ///// lookupAny test /////
  // Test lookupAny to see if it can find any element within one array that
  // also exists in another & whether it returns the right position.
  string lookup_any_test_1[] = {"evan", "hillary", "mindy",
                                "jill", "ajamu",   "gary"};
  string lookup_any_test_2[] = {"bill", "ajamu", "jill", "hillary"};
  assert(lookupAny(lookup_any_test_1, 6, lookup_any_test_2, 4) == 1);

  // Test lookupAny to see if it returns -1 if it cannot find an element from
  // one
  // array that also exists in another.
  string lookup_any_test_3[] = {"tim", "donald"};
  assert(lookupAny(lookup_any_test_1, 6, lookup_any_test_3, 2) == -1);

  // Test lookupAny to see if it returns -1 if given a n of 0 or a negative n.
  assert(lookupAny(lookup_any_test_1, 0, lookup_any_test_3, 4) == -1);
  assert(lookupAny(lookup_any_test_1, 6, lookup_any_test_3, 0) == -1);
  assert(lookupAny(lookup_any_test_1, 0, lookup_any_test_3, 0) == -1);
  assert(lookupAny(lookup_any_test_1, -1, lookup_any_test_3, 4) == -1);
  assert(lookupAny(lookup_any_test_1, -1, lookup_any_test_2, -1) == -1);
  assert(lookupAny(lookup_any_test_1, 6, lookup_any_test_2, -1) == -1);

  // ///// separate test
  // Test separate to see if it can split an array into two sides based around
  // elements on one side being greater than a provided string, and vice versa.
  string separate_test_1[] = {"donald", "jill", "hillary",
                              "tim",    "evan", "bill"};
  assert(separate(separate_test_1, 6, "gary") == 3);

  // Test separate to see if it can handle splitting an array where one side
  // only has one element.
  string separate_test_2[] = {"gary", "hillary", "jill", "donald"};
  assert(separate(separate_test_2, 4, "hillary") == 2);

  // Test separate to see if it returns n if no elements are less than the
  // separator.
  separate_test_1[0] = "b";
  separate_test_1[1] = "c";
  separate_test_1[2] = "d";
  separate_test_1[3] = "e";
  separate_test_1[4] = "f";
  separate_test_1[5] = "g";
  assert(separate(separate_test_1, 6, "z") == 6);
  assert(separate(separate_test_1, 5, "z") == 5);
  assert(separate(separate_test_1, 0, "hillary") == 0);

  // Test separate to see if it returns -1 if given a negative n.
  assert(separate(separate_test_2, -10, "hillary") == -1);

  cout << "ALL TESTS PASSED!!!" << endl;

  string h[7] = {"jill", "hillary", "donald", "tim", "", "evan", "gary"};
  assert(lookup(h, 7, "evan") == 5);
  assert(lookup(h, 7, "donald") == 2);
  assert(lookup(h, 2, "donald") == -1);
  assert(positionOfMax(h, 7) == 3);

  string g[4] = {"jill", "hillary", "gary", "mindy"};
  assert(differ(h, 4, g, 4) == 2);
  assert(appendToAll(g, 4, "?") == 4 && g[0] == "jill?" && g[3] == "mindy?");
  assert(rotateLeft(g, 4, 1) == 1 && g[1] == "gary?" && g[3] == "hillary?");

  string e[4] = {"donald", "tim", "", "evan"};
  assert(subsequence(h, 7, e, 4) == 2);

  string d[5] = {"hillary", "hillary", "hillary", "tim", "tim"};
  assert(countRuns(d, 5) == 2);

  string f[3] = {"gary", "donald", "mike"};
  assert(lookupAny(h, 7, f, 3) == 2);
  assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "gary");

  assert(separate(h, 7, "gary") == 3);

  cout << "Their tests succeeded too." << endl;

  return 0;
}
