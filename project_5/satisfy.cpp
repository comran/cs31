#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int normalizeRules(char word1[][MAX_WORD_LENGTH + 1],
                   char word2[][MAX_WORD_LENGTH + 1], int distance[],
                   int nRules) {
  // Remove empty rules and those with a distance that is not positive.
  for (int i = 0; i < nRules; i++) {
    bool remove = false;
    if (word1[i][0] == 0 || word2[i][0] == 0 || distance[i] < 1) remove = true;

    // Find duplicates.
    for (int j = 0; j < nRules; j++) {
      if (j == i) continue;

      if (((!strcmp(word1[i], word1[j]) &&
            !strcmp(word2[i], word2[j] /* || */)) ||
           (!strcmp(word1[i], word2[j]) &&
            !strcmp(word1[j], word2[i]) /* X  */)) &&
          distance[i] < distance[j])
        remove = true;
    }

    if (remove) {
      for (int j = i; j < nRules - 1; j++) {
        strcpy(word1[j], word1[j + 1]);
        strcpy(word2[j], word2[j + 1]);
        distance[j] = distance[j + 1];
      }

      nRules--;
      i--;  // To re-examine the index that was moved down.
    }
  }
  // Convert all words to lower case.
  for (int i = 0; i < nRules; i++) {
    for (size_t j = 0; j < strlen(word1[i]); j++) {
      word1[i][j] = tolower(word1[i][j]);
    }

    for (size_t j = 0; j < strlen(word2[i]); j++) {
      word2[i][j] = tolower(word2[i][j]);
    }
  }

  return nRules;  // TODO(comran): Fix.
}

/*
int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH + 1],
                          const char word2[][MAX_WORD_LENGTH + 1],
                          const int distance[], int nRules,
                          const char document[]) {
}*/

int main(int /*argc*/, char * /*argv*/ []) {
  // Test normalizeRules to see if it corrects capitalization.
  const int TEST1_NRULES = 4;
  char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
  char test1w1_OUTPUT[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
      "mad", "deranged", "nefarious", "have"};
  char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                     "plot", "mad"};
  char test1w2_OUTPUT[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
      "scientist", "robot", "plot", "mad"};
  int test1dist[TEST1_NRULES] = {2, 4, 1, 13};
  int test1dist_OUTPUT[TEST1_NRULES] = {2, 4, 1, 13};

  assert(normalizeRules(test1w1, test1w2, test1dist, TEST1_NRULES) == 4);
  for (int i = 0; i < TEST1_NRULES; i++) {
    assert(!strcmp(test1w1[i], test1w1_OUTPUT[i]));
    assert(!strcmp(test1w2[i], test1w2_OUTPUT[i]));
    assert(test1dist[i] == test1dist_OUTPUT[i]);
  }

  // Test normalizeRules to see if it removes empty cstrings that appear in
  // either array.
  const int TEST2_NRULES = 4;
  char test2w1[TEST2_NRULES][MAX_WORD_LENGTH + 1] = {"", "deranged",
                                                     "nefarious", "have"};
  char test2w1_OUTPUT[2][MAX_WORD_LENGTH + 1] = {"nefarious", "have"};
  char test2w2[TEST2_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "", "plot",
                                                     "mad"};
  char test2w2_OUTPUT[2][MAX_WORD_LENGTH + 1] = {"plot", "mad"};
  int test2dist[TEST2_NRULES] = {2, 4, 1, 13};
  int test2dist_OUTPUT[TEST2_NRULES] = {1, 13};

  assert(normalizeRules(test2w1, test2w2, test2dist, TEST2_NRULES) == 2);
  for (int i = 0; i < 2; i++) {
    assert(!strcmp(test2w1[i], test2w1_OUTPUT[i]));
    assert(!strcmp(test2w2[i], test2w2_OUTPUT[i]));
    assert(test2dist[i] == test2dist_OUTPUT[i]);
  }

  const int TEST3_NRULES = 4;
  char test3w1[TEST3_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "mad", "have"};
  char test3w1_OUTPUT[3][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                            "have"};
  char test3w2[TEST3_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                     "scientist", "mad"};
  char test3w2_OUTPUT[3][MAX_WORD_LENGTH + 1] = {
      "scientist", "robot", "mad"};
  int test3dist[TEST3_NRULES] = {2, 4, 1, 13};
  int test3dist_OUTPUT[TEST3_NRULES] = {2, 4, 13};

  assert(normalizeRules(test3w1, test3w2, test3dist, TEST3_NRULES) == 3);
  for (int i = 0; i < 3; i++) {
    assert(!strcmp(test3w1[i], test3w1_OUTPUT[i]));
    assert(!strcmp(test3w2[i], test3w2_OUTPUT[i]));
    assert(test3dist[i] == test3dist_OUTPUT[i]);
  }

  return 0;
}
