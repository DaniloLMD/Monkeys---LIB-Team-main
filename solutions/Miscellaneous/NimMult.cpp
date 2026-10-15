#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define all(c) begin(c), end(c)

#define SIZE(c) int((c).size())

typedef unsigned long long Nimber;
    
vector<int> exponents(Nimber value)
{
    vector<int> ret;
    unsigned long long x = value;
    for (; x; x = (x-1)&x)
        ret.push_back(__builtin_ctzll(x));
    return ret;
}

map<pair<Nimber,Nimber>, Nimber> cache;

Nimber nimProduct(Nimber a, Nimber b)
{
    auto it = cache.find(make_pair(a,b));
    if (it != cache.end())
        return it->second;
    Nimber &ret = cache[make_pair(a,b)];
    if (a == 0 || b == 0)
        ret = 0;
    else if (a == 1 || b == 1)
        ret = a^b^1;
    else
    {
        vector<int> aExponents = exponents(a);
        vector<int> bExponents = exponents(b);
        if (aExponents.size() == 1 && bExponents.size() == 1)
        {
            // Computes nim product of 2^a and 2^b
            // Decompose exponents = write as product of fermats
            vector<int> aExpBits = exponents(aExponents[0]);
            vector<int> bExpBits = exponents(bExponents[0]);
            #define FERMAT(index) Nimber(1ULL<<(1ULL<<(index)))
            ret = Nimber(1);
            int i = 0, j = 0;
            while (i < SIZE(aExpBits) && j < SIZE(bExpBits))
            {
                if (aExpBits[i] < bExpBits[j])
                    ret *= FERMAT(aExpBits[i++]);
                else if (aExpBits[i] > bExpBits[j])
                    ret *= FERMAT(bExpBits[j++]);
                else
                {
                    ret = (ret * FERMAT(aExpBits[i])) ^ nimProduct(ret, FERMAT(aExpBits[i])/2);
                    i++;
                    j++;
                }
            }
            for (; i < SIZE(aExpBits); i++) ret = ret * FERMAT(aExpBits[i]);
            for (; j < SIZE(bExpBits); j++) ret = ret * FERMAT(bExpBits[j]);
        }
        else
        {
            ret = 0;
            for (int aExp : aExponents)
            for (int bExp : bExponents)
                ret ^= nimProduct(1ULL<<aExp, 1ULL<<bExp);
        }
    }
    return ret;
}


int main()
{
    forn(i,16)
    forn(j,16)
        cout << i << " " << j << " " << nimProduct(i,j) << endl;
    return 0;
}