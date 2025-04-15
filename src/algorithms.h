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

inline long long modpow(long long base, long long exp, long long modulus) {
    long long res = 1;
    base = base % modulus;
    if (base == 0)
        return 0;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % modulus;
        exp = exp >> 1; // y = y/2
        base = (base * base) % modulus;
    }
    return res;
}
