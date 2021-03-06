
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<int64_t> Vector;

int64_t chineseRemainderTheorem(const Vector n, const Vector a);
int64_t modularInverse(const int64_t a, const int64_t n);

int main()
{
    Vector aList;
    Vector nList;

    std::string line;
    std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');

    int64_t busId   = -1;
    int64_t minutes = -1;

    std::stringstream _line(line);
    std::string subLine;

    while (_line >> subLine)
    {
        minutes++;

        if (subLine == "x")
        {
            continue;
        }

        busId = stol(subLine);
        aList.push_back(busId - minutes);
        nList.push_back(busId);
    }

    std::cout << chineseRemainderTheorem(nList, aList) << std::endl;

    return 0;
}

int64_t chineseRemainderTheorem(const Vector n, const Vector a)
{
    int64_t product = 1;

    for (int64_t mod : n)
    {
        product *= mod;
    }

    int64_t sum = 0;

    for (size_t i = 0; i < n.size(); i++)
    {
        const int64_t b = product / n[i];
        sum += a[i] * b * modularInverse(b, n[i]);
    }

    return sum % product;
}

int64_t modularInverse(const int64_t a, const int64_t n)
{
    int64_t t     = 0;
    int64_t r     = n;
    int64_t new_t = 1;
    int64_t new_r = a;

    while (new_r != 0)
    {
        const int64_t quotient = r / new_r;

        const int64_t tmp_t = t;
        t     = new_t;
        new_t = tmp_t - (quotient * new_t);

        const int64_t tmp_r = r;
        r     = new_r;
        new_r = tmp_r - (quotient * new_r);
    }

    if (r > 1)
    {
        std::cout << a << " is not invertible" << std::endl;
        exit(1);
    }

    if (t < 0)
    {
        t = t + n;
    }

    return t;
}
