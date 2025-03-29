#include <vector>

using namespace std;

/// Creates a list of `n` booleans, `true` means prime
inline vector<bool> sieveOfEratosthenes(size_t n) {
    vector<bool> prime(n + 1, true);
    prime[0] = false;
    prime[1] = false;

    for (int p = 2; p * p <= n; p++) {

        if (prime[p] == true) {

            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    return prime;
}
