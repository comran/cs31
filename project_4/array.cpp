#include <iostream>
#include <string>
#include <cassert>

namespace cs31_project_4 {}  // namespace cs31_project_4

// TODO(comran): Check all returns.
int appendToAll(::std::string a[], int n, ::std::string value) {
  if (n < 0) return -1;

  for (int i = 0; i < n; i++) {
    a[i] = a[i] + value;
  }

  return n;  // TODO(comran): Check to see what needs to be returned here.
}

int lookup(const ::std::string a[], int n, ::std::string target) {
  for (int i = 0; i < n; i++) {
    if (a[i].compare(target) == 0) return i;
  }

  return -1;
}

int positionOfMax(const ::std::string a[], int n) {
  // TODO(comran): Return -1 on empty array.

  char max_letter = 'a';
  int max_index = 0;

  for (int i = 0; i < n; i++) {
    char first_letter = ::std::tolower(a[i].at(0));
    if (first_letter > max_letter) {
      max_letter = first_letter;
      max_index = i;
    }
  }

  return max_index;
}

int rotateLeft(::std::string a[], int n, int pos) {
  ::std::string a_at_pos = a[pos];
  for (int i = pos; i < n - 1; i++) {
    a[i] = a[i + 1];
  }
  a[n - 1] = a_at_pos;

  return pos;
}

int countRuns(const ::std::string a[], int n) {
  int elements_after_run_start = 0;

  for (int i = 0; i < n - 1; i++) {
    if (a[i] == a[i + 1]) {
      elements_after_run_start++;
    }
  }

  return n - elements_after_run_start;
}

int flip(::std::string a[], int n) {
  for (int i = 0; i < n / 2; i++) {
    int inverse_i = n - i;

    ::std::string inverse_i_string = a[inverse_i - 1];

    a[inverse_i - 1] = a[i];
    a[i] = inverse_i_string;
  }

  return n;
}

int differ(const ::std::string a1[], int n1, const ::std::string a2[], int n2) {
  for (int i = 0; i < n1 && i < n2; i++) {
    if (a1[i] != a2[i]) return i;
  }

  return n1 < n2 ? n1 : n2;
}

int subsequence(const ::std::string a1[], int n1, const ::std::string a2[],
                int n2) {
  for (int i = 0; i < n1 - n2; i++) {
    for (int j = 0; j < n2; j++) {
      if (a1[i + j] != a2[j]) break;
      if (j == n2 - 1) return i;
    }
  }

  return -1;
}

int lookupAny(const ::std::string a1[], int n1, const ::std::string a2[],
              int n2) {
  for(int i = 0;i < n1;i++) {
    for(int j = 0;j < n2;j++) {
      if(a1[i] == a2[j]) return i;
    }
  }

  return -1;
}

int separate(::std::string a[], int n, ::std::string separator) {
  for (int i = 0;i < n;i++) {
    for(int j = i; j < n;j++) {
      if(a[i] > a[j]) {
        ::std::string temp_later_element = a[j];
        a[j] = a[i];
        a[i] = temp_later_element;
      }
    }
  }

  for(int i = 0;i < n;i++) {
    if(a[i] >= separator) return i;
  }

  return n;
}

int main(int /*argc*/, char * /*argv*/ []) {
  ::std::string test_backup[] = {"hillary", "gary", "donald", "jill", "evan"};
  ::std::string test[5];
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];
  assert(appendToAll(test, 3, "!!!") == 3 && test[0] == "hillary!!!" &&
         test[1] == "gary!!!" && test[2] == "donald!!!" && test[3] == "jill" &&
         test[4] == "evan");
  for (int i = 0; i < 5; i++) test[i] = test_backup[i];

  assert(lookup(test, 5, "donald") == 2);
  assert(lookup(test, 5, "george") == -1);
  assert(positionOfMax(test, 5) == 3);

  test[0] = "evan";
  test[1] = "donald";
  test[2] = "gary";
  test[3] = "jill";
  test[4] = "hillary";
  assert(rotateLeft(test, 5, 1) == 1 && test[0] == "evan" &&
         test[1] == "gary" && test[2] == "jill" && test[3] == "hillary" &&
         test[4] == "donald");

  ::std::string count_runs_test[] = {"tim",    "ajamu",  "mike",
                                     "mike",   "donald", "donald",
                                     "donald", "mike",   "mike"};
  assert(countRuns(count_runs_test, 9) == 5);

  ::std::string test_flip[] = {"ajamu", "mike", "", "tim", "mindy", "bill"};
  assert(flip(test_flip, 4) == 4 && test_flip[0] == "tim" &&
         test_flip[1] == "" && test_flip[2] == "mike" &&
         test_flip[3] == "ajamu" && test_flip[4] == "mindy" &&
         test_flip[5] == "bill");

  ::std::string differ_test_1[6] = {"ajamu", "mike",  "",
                                    "tim",   "mindy", "bill"};
  ::std::string differ_test_2[5] = {"ajamu", "mike", "bill", "", "tim"};

  assert(differ(differ_test_1, 6, differ_test_2, 5) == 2);
  assert(differ(differ_test_1, 2, differ_test_2, 1) == 1);

  ::std::string subsequence_test_1[] = {"evan", "hillary", "mindy",
                                        "jill", "ajamu",   "gary"};
  ::std::string subsequence_test_2[] = {"hillary", "mindy", "jill"};
  assert(subsequence(subsequence_test_1, 6, subsequence_test_2, 3) == 1);
  ::std::string subsequence_test_3[] = {"evan", "jill"};
  assert(subsequence(subsequence_test_1, 5, subsequence_test_3, 2) == -1);

  ::std::string lookup_any_test_1[] = {"evan", "hillary", "mindy",
                                       "jill", "ajamu",   "gary"};
  ::std::string lookup_any_test_2[] = {"bill", "ajamu", "jill", "hillary"};
  assert(lookupAny(lookup_any_test_1, 6, lookup_any_test_2, 4) == 1);
  ::std::string lookup_any_test_3[] = {"tim", "donald"};
  assert(lookupAny(lookup_any_test_1, 6, lookup_any_test_3, 2) == -1);

  ::std::string separate_test_1[] = { "donald", "jill", "hillary", "tim", "evan", "bill" };
  assert(separate(separate_test_1, 6, "gary") == 3);

  ::std::string separate_test_2[] = { "gary", "hillary", "jill", "donald" };
  assert(separate(separate_test_2, 4, "hillary") == 2);

  ::std::cout << "ALL TESTS PASSED!!!" << ::std::endl;

  return 0;
}
