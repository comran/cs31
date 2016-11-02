#include <iostream>
#include <string>

using namespace std;

namespace cs31_project_3 {
namespace {
static const string kAmericanStates[] = {
    "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "DC", "FL", "GA",
    "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA",
    "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY",
    "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD", "TN", "TX",
    "UT", "VT", "VA", "WA", "WV", "WI", "WY"};
static const int kNumberOfStates =
    sizeof(kAmericanStates) / sizeof(*kAmericanStates);

}  // namespace
}  // namespace cs31_project_3

bool hasCorrectSyntax(string poll_data) {
  size_t poll_data_check_index = 0;

  // Convert to upper case.
  for (size_t i = 0; i < poll_data.length(); i++) {
    // If the character is not an alphanum, return an error.
    if (!(isalpha(poll_data[i]) || isdigit(poll_data[i]))) {
      return false;
    }

    if(isalpha(poll_data[i])) poll_data[i] = toupper(poll_data[i]);
  }

  // Check all characters in the poll data string.
  while (poll_data_check_index < poll_data.length()) {
    string search_state = poll_data.substr(poll_data_check_index, 2);

    for(size_t i = 0;i < search_state.length();i++) {
      if (!isalpha(search_state[i])) return false;
    }

    // Search for the state (converted to all caps) in the array of accepted
    // states.
    bool found = false;
    for (int i = 0; i < ::cs31_project_3::kNumberOfStates; i++) {
      if (search_state == ::cs31_project_3::kAmericanStates[i]) {
        found = true;  // Search state was found in the array, so break.
        break;
      }
    }
    if (!found) return false;

    // Scroll to where the first digit should be.
    poll_data_check_index += 2;

    int numbers_found = 0;
    while (poll_data_check_index < poll_data.length()) {
      // Find current character and move the index to the next character.
      char current_char = poll_data[poll_data_check_index++];

      // Check that the final character in the poll data string is a party
      // party letter. (edge case)
      if (poll_data_check_index >= poll_data.length() &&
          !isalpha(current_char)) {
        return false;
      }

      if(isdigit(current_char)) {
        numbers_found++;
      } else {
        break;
      }
    }

    if (numbers_found == 0) return false;
  }

  return true;
}

int countVotes(string poll_data, char party, int &vote_count) {
  if (!hasCorrectSyntax(poll_data)) return 1;  // Poll data must be parsable.
  if (!isalpha(party)) return 3;               // Party must be a letter.

  int vote_count_sum = 0;

  // Put cursor at the first number.
  size_t poll_data_check_index = 2;

  while (poll_data_check_index < poll_data.length()) {
    int initial_number_index = poll_data_check_index;

    // Scroll to the end of the number.
    while (!isalpha(poll_data[poll_data_check_index++]))
      ;

    // Subtract one so that we are at the last digit again.
    poll_data_check_index--;

    // Convert captured substring of number to electoral votes.
    int number_of_electoral_vote_digits =
        poll_data_check_index - initial_number_index;
    string electoral_votes_substring =
        poll_data.substr(initial_number_index, number_of_electoral_vote_digits);
    int electoral_votes = atoi(electoral_votes_substring.c_str());

    if (electoral_votes == 0) return 2;  // All states have electoral votes.

    // Check for a party match, regardless of character case.
    if (toupper(party) == toupper(poll_data[poll_data_check_index])) {
      vote_count_sum += electoral_votes;
    }

    // Scroll to the next first electoral vote digit.
    poll_data_check_index += 3;
  }

  // Set reference of vote count to local count.
  vote_count = vote_count_sum;

  return 0;
}

int main(int /*argc*/, char * /*argv*/ []) {
  return 0;
}
