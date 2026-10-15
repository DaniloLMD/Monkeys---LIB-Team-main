#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Sieve of Eratosthenes — returns all primes <= limit
vector<ll> prime_sieve(ll limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= limit; i++)
        if (is_prime[i])
            for (ll j = i * i; j <= limit; j += i)
                is_prime[j] = false;
    vector<ll> primes;
    for (ll i = 2; i <= limit; i++)
        if (is_prime[i]) primes.push_back(i);
    return primes;
}

// Boolean sieve — returns is_prime[0..limit]
vector<bool> prime_sieve_bool(ll limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= limit; i++)
        if (is_prime[i])
            for (ll j = i * i; j <= limit; j += i)
                is_prime[j] = false;
    return is_prime;
}

// Lucy_Hedgehog prime counting sieve
// O(n^(3/4) / log n) time | O(sqrt(n)) space
// Counts primes in [1, n] — works up to ~10^11 comfortably
ll primepi(ll n) {
    if (n < 2) return 0;

    ll sqrtn = (ll)sqrt((double)n);
    // Ensure sqrtn is exactly floor(sqrt(n))
    while ((sqrtn + 1) * (sqrtn + 1) <= n) sqrtn++;
    while (sqrtn * sqrtn > n) sqrtn--;

    // small[i] = S(i)     for 1 <= i <= sqrtn
    // large[i] = S(n/i)   for 1 <= i <= sqrtn
    // Initially S(v) = v - 1  (integers in [2, v])
    vector<ll> small(sqrtn + 2), large(sqrtn + 2);
    for (ll i = 1; i <= sqrtn; i++) {
        small[i] = i - 1;
        large[i] = n / i - 1;
    }

    for (ll p = 2; p <= sqrtn; p++) {
        if (small[p] == small[p - 1]) continue; // p is not prime
        ll pcnt = small[p - 1];  // pi(p-1) = number of primes strictly less than p
        ll p2   = p * p;

        // --- Update large[i] = S(n/i) ---
        // Need n/i >= p^2, i.e. i <= n/p^2
        for (ll i = 1; i <= sqrtn && i * p2 <= n; i++) {
            ll w = n / i / p;                           // floor(n / (i*p))
            ll contrib = (w <= sqrtn ? small[w] : large[i * p]) - pcnt;
            large[i] -= contrib;
        }

        // --- Update small[i] = S(i) ---
        // Process in reverse so we don't use already-updated values
        for (ll i = sqrtn; i >= p2; i--)
            small[i] -= small[i / p] - pcnt;
    }

    return large[1]; // S(n/1) = S(n) = pi(n)
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin>>n;
    cout<<primepi(n)<<endl;

    return 0;
}