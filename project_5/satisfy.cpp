#define _CRT_SECURE_NO_WARNINGS

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

    // Check for any non-alpha chars.
    for (size_t j = 0; j < strlen(word1[i]) && !remove; j++) {
      if (!isalpha(word1[i][j])) {
        remove = true;
      }
    }
    for (size_t j = 0; j < strlen(word2[i]) && !remove; j++) {
      if (!isalpha(word2[i][j])) {
        remove = true;
      }
    }

    // Find duplicates.
    for (int j = 0; j < nRules && !remove; j++) {
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

  return nRules;
}

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH + 1],
                          const char word2[][MAX_WORD_LENGTH + 1],
                          const int distance[], int nRules,
                          const char document[]) {
  char words[201][201];
  int words_found = 0, last_space = -1;

  // Move unformatted words into an array.
  for (size_t i = 0; i < strlen(document); i++) {
    if (document[i] == ' ') {
      bool alpha_found = false;
      for (size_t j = last_space + 1; j < i; j++) {
        if (isalpha(document[j])) {
          alpha_found = true;
          break;
        }
      }

      if (alpha_found) {
        strncpy(words[words_found], document + last_space + 1,
                i - last_space - 1);
        words[words_found++][i - last_space - 1] = 0;
      }

      last_space = i;
    }

    // Edge case to find the last word.
    if (i >= strlen(document) - 1) {
      bool alpha_found = false;
      for (size_t j = last_space + 1; j < strlen(document); j++) {
        if (isalpha(document[j])) {
          alpha_found = true;
          break;
        }
      }

      if (alpha_found) {
        strncpy(words[words_found], document + last_space + 1, i - last_space);
        words[words_found++][i - last_space] = 0;
      }
    }
  }

  // Format every word.
  for (int i = 0; i < words_found; i++) {
    for (size_t j = 0; j < strlen(words[i]); j++) {
      if (!isalpha(words[i][j])) {
        size_t k;
        for (k = j; k < strlen(words[i]) - 1; k++) {
          words[i][k] = words[i][k + 1];
        }

        // Move the null char over to account for the deleted char.
        words[i][k] = 0;
        j--;  // To re-examine the letter moved down to replace the removed one.
      } else {
        words[i][j] = tolower(words[i][j]);
      }
    }
  }

  // Perform the search.
  int satisfaction = 0;
  for (int i = 0; i < nRules; i++) {
    // 0 = not found, 1 = found in first word of rule, 2 = found in second word
    // of rule.
    int first_word_lookup_result = 0;
    int first_word_index = 0;
    for (int j = 0; first_word_lookup_result == 0 && j < words_found; j++) {
      if (!strcmp(word1[i], words[j])) first_word_lookup_result = 1;
      if (!strcmp(word2[i], words[j])) first_word_lookup_result = 2;
      first_word_index = j;
    }

    for (int j = first_word_index + 1;
         j < first_word_index + distance[i] + 1 && j < words_found &&
             first_word_lookup_result > 0;
         j++) {
      if (first_word_lookup_result == 1 && !strcmp(word2[i], words[j])) {
        satisfaction++;
        break;
      }
      if (first_word_lookup_result == 2 && !strcmp(word1[i], words[j])) {
        satisfaction++;
        break;
      }
    }
  }

  return satisfaction;
}

int main(int /*argc*/, char * /*argv*/ []) {
  // Test normalizeRules to see if it corrects capitalization.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
    char testw1_OUTPUT[TEST_NRULES][MAX_WORD_LENGTH + 1] = {
        "mad", "deranged", "nefarious", "have"};
    char testw2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                     "plot", "mad"};
    char testw2_OUTPUT[TEST_NRULES][MAX_WORD_LENGTH + 1] = {
        "scientist", "robot", "plot", "mad"};
    int testdist[TEST_NRULES] = {2, 4, 1, 13};
    int testdist_OUTPUT[TEST_NRULES] = {2, 4, 1, 13};

    assert(normalizeRules(testw1, testw2, testdist, TEST_NRULES) == 4);
    for (int i = 0; i < TEST_NRULES; i++) {
      assert(!strcmp(testw1[i], testw1_OUTPUT[i]));
      assert(!strcmp(testw2[i], testw2_OUTPUT[i]));
      assert(testdist[i] == testdist_OUTPUT[i]);
    }
  }

  // Test normalizeRules to see if it removes empty cstrings that appear in
  // either array.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"", "deranged",
                                                     "nefarious", "have"};
    char testw1_OUTPUT[2][MAX_WORD_LENGTH + 1] = {"nefarious", "have"};
    char testw2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "", "plot",
                                                     "mad"};
    char testw2_OUTPUT[2][MAX_WORD_LENGTH + 1] = {"plot", "mad"};
    int testdist[TEST_NRULES] = {2, 4, 1, 13};
    int testdist_OUTPUT[TEST_NRULES] = {1, 13};

    assert(normalizeRules(testw1, testw2, testdist, TEST_NRULES) == 2);
    for (int i = 0; i < 2; i++) {
      assert(!strcmp(testw1[i], testw1_OUTPUT[i]));
      assert(!strcmp(testw2[i], testw2_OUTPUT[i]));
      assert(testdist[i] == testdist_OUTPUT[i]);
    }
  }

  // Test normalizeRules to see if it removes duplicates.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged", "mad",
                                                     "have"};
    char testw1_OUTPUT[3][MAX_WORD_LENGTH + 1] = {"mad", "deranged", "have"};
    char testw2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                     "scientist", "mad"};
    char testw2_OUTPUT[3][MAX_WORD_LENGTH + 1] = {"scientist", "robot", "mad"};
    int testdist[TEST_NRULES] = {2, 4, 1, 13};
    int testdist_OUTPUT[TEST_NRULES] = {2, 4, 13};

    assert(normalizeRules(testw1, testw2, testdist, TEST_NRULES) == 3);
    for (int i = 0; i < 3; i++) {
      assert(!strcmp(testw1[i], testw1_OUTPUT[i]));
      assert(!strcmp(testw2[i], testw2_OUTPUT[i]));
      assert(testdist[i] == testdist_OUTPUT[i]);
    }
    assert(normalizeRules(testw1, testw2, testdist, 0) == 0);
  }

  // Test normalizeRules to see if it removes rules with special chars.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "george*", "have"};
    char testw1_OUTPUT[3][MAX_WORD_LENGTH + 1] = {"deranged", "have"};
    char testw2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scien.tist", "robot",
                                                     "bob", "mad"};
    char testw2_OUTPUT[3][MAX_WORD_LENGTH + 1] = {"robot", "mad"};
    int testdist[TEST_NRULES] = {2, 4, 1, 13};
    int testdist_OUTPUT[TEST_NRULES] = {4, 13};

    assert(normalizeRules(testw1, testw2, testdist, TEST_NRULES) == 2);
    for (int i = 0; i < 2; i++) {
      assert(!strcmp(testw1[i], testw1_OUTPUT[i]));
      assert(!strcmp(testw2[i], testw2_OUTPUT[i]));
      assert(testdist[i] == testdist_OUTPUT[i]);
    }

    assert(normalizeRules(testw1, testw2, testdist, 0) == 0);
  }

  // Test normalizeRules to see if it handles 20 char and 1 char cstrings.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"madmadmadmadmadmadma",
                                                     "d", "bob", "have"};
    char testw1_OUTPUT[TEST_NRULES][MAX_WORD_LENGTH + 1] = {
        "madmadmadmadmadmadma", "d", "bob", "have"};
    char testw2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"aadmadmadmadmadmadma",
                                                     "b", "boba", "havee"};
    char testw2_OUTPUT[TEST_NRULES][MAX_WORD_LENGTH + 1] = {
        "aadmadmadmadmadmadma", "b", "boba", "havee"};
    int testdist[TEST_NRULES] = {2, 4, 1, 13};
    int testdist_OUTPUT[TEST_NRULES] = {2, 4, 1, 13};

    assert(normalizeRules(testw1, testw2, testdist, TEST_NRULES) == 4);
    for (int i = 0; i < 4; i++) {
      assert(!strcmp(testw1[i], testw1_OUTPUT[i]));
      assert(!strcmp(testw2[i], testw2_OUTPUT[i]));
      assert(testdist[i] == testdist_OUTPUT[i]);
    }
  }

  // See if calculateSatisfaction can handle a normal sentence with a period.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
    char test5w2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                      "plot", "mad"};
    int test5dist[TEST_NRULES] = {2, 4, 1, 13};
    assert(
        calculateSatisfaction(
            testw1, test5w2, test5dist, TEST_NRULES,
            "The mad UCLA scientist unleashed a deranged evil giant robot.") ==
        2);
  }

  // See if calculateSatisfaction can handle a sentence with back-to-back
  // spaces.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
    char test5w2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                      "plot", "mad"};
    int test5dist[TEST_NRULES] = {2, 4, 1, 13};
    assert(calculateSatisfaction(
               testw1, test5w2, test5dist, TEST_NRULES,
               "The mad UCLA scientist unleashed    a deranged robot.") == 2);
  }

  // See if calculateSatisfaction can handle a document with no letters.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
    char test5w2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                      "plot", "mad"};
    int test5dist[TEST_NRULES] = {2, 4, 1, 13};
    assert(calculateSatisfaction(testw1, test5w2, test5dist, TEST_NRULES,
                                 "**** 2016 ****") == 0);
  }

  // See if calculateSatisfaction can handle a document with a mix of uppercase,
  // lowercase special characters, and trailing whitespace.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
    char test5w2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                      "plot", "mad"};
    int test5dist[TEST_NRULES] = {2, 4, 1, 13};
    assert(calculateSatisfaction(testw1, test5w2, test5dist, TEST_NRULES,
                                 "  That plot: NEFARIOUS!") == 1);
  }

  // See if calculateSatisfaction correctly searches for rules in a document
  // with multiple copies of the same word.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
    char test5w2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                      "plot", "mad"};
    int test5dist[TEST_NRULES] = {2, 4, 1, 13};
    assert(calculateSatisfaction(
               testw1, test5w2, test5dist, TEST_NRULES,
               "deranged deranged robot deranged robot robot") == 1);
  }

  // Check to see if words separated by special characters instead of just a
  // space are concatenated together and searched through as such.
  {
    const int TEST_NRULES = 4;
    char testw1[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"mad", "deranged",
                                                     "nefarious", "have"};
    char test5w2[TEST_NRULES][MAX_WORD_LENGTH + 1] = {"scientist", "robot",
                                                      "plot", "mad"};
    int test5dist[TEST_NRULES] = {2, 4, 1, 13};
    assert(
        calculateSatisfaction(testw1, test5w2, test5dist, TEST_NRULES,
                              "That scientist said two mad scientists suffer "
                              "from deranged-robot fever.") == 0);
  }

  // Test calculateSatisfaction to see if it can handle being passed no rules.
  {
    const int TEST_NRULES = 4;
    char testw1[0][MAX_WORD_LENGTH + 1] = {};
    char test5w2[0][MAX_WORD_LENGTH + 1] = {};
    int test5dist[TEST_NRULES] = {};
    assert(
        calculateSatisfaction(
            testw1, test5w2, test5dist, TEST_NRULES,
            "The mad UCLA scientist unleashed a deranged evil giant robot.") ==
        0);
  }

  cout << "All tests succeeded" << endl;

  return 0;
}
