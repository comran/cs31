// License fee computation

#include <iostream>
#include <string>
using namespace std;

int main()
{
      // Get and validate identification

    cout << "Identification: ";
    string identification;
    getline(cin, identification);
    if (identification == "")
    {
        cout << "---\nYou must enter a property identification." << endl;
        return 1;
    }

      // Get and validate expected revenue

    cout << "Expected revenue (in millions): ";
    double expectedRevenue;
    cin >> expectedRevenue;
    cin.ignore(10000, '\n');
    if (expectedRevenue < 0)
    {
        cout << "---\nThe expected revenue must be nonnegative." << endl;
        return 1;
    }

      // Get and validate country

    cout << "Country: ";
    string country;
    getline(cin, country);
    if (country == "")
    {
        cout << "---\nYou must enter a country." << endl;
        return 1;
    }

      // Expected revenue cutoff points and license fee rates

    const double CUTOFF_1       = 20;
    const double CUTOFF_2       = 50;
    const double RATE_1         = 0.181;
    const double RATE_2_USUAL   = 0.203;
    const double RATE_2_SPECIAL = 0.217;
    const double RATE_3         = 0.23;

      // Compute license fee

    double licenseFee;

    if (expectedRevenue <= CUTOFF_1)
        licenseFee = expectedRevenue * RATE_1;
    else
    {
          // Compute license fee for the portion of expectedRevenue in first bracket

        licenseFee = CUTOFF_1 * RATE_1;

          // Determine rate for second bracket

        double rate_2 = RATE_2_USUAL;
        if (country == "UAE"  ||  country == "Turkey")
            rate_2 = RATE_2_SPECIAL;

        if (expectedRevenue <= CUTOFF_2)
        {
              // Add license fee for remainder of expectedRevenue (in 2nd bracket)

            licenseFee += (expectedRevenue - CUTOFF_1) * rate_2;
        }
        else
        {
              // Add license fee for the portion of expectedRevenue in 2nd bracket
              // and the remainder of expectedRevenue (in 3rd bracket)

            licenseFee += (CUTOFF_2 - CUTOFF_1) * rate_2 +
                          (expectedRevenue - CUTOFF_2) * RATE_3;
        }   
    }

      // Print license fee

    cout.setf(ios::fixed);
    cout.precision(3);
    cout << "---\n" << "The license fee for " << identification << " is $" << licenseFee
         << " million." << endl;
}
