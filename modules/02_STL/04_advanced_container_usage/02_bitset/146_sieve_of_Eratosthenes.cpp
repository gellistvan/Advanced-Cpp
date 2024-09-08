#include <bitset>
#include <iostream>
#include <cmath>

const int MAX_NUM = 100;

int main() {
    std::bitset<MAX_NUM + 1> is_prime;
    is_prime.set(); // Set all bits to true
    is_prime[0] = is_prime[1] = 0; // 0 and 1 are not primes

    for (int i = 2; i <= std::sqrt(MAX_NUM); ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_NUM; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    std::cout << "Prime numbers up to " << MAX_NUM << ": ";
    for (int i = 2; i <= MAX_NUM; ++i) {
        if (is_prime[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    return 0;
}