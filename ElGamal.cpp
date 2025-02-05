#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long long mod_pow(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b = b / 2;
    }
    return result;
}

long long generate_prime(int bits) {
    long long num;
    int is_prime = 0;
    while (!is_prime) {
        num = rand() % (1 << bits) + (1 << (bits - 1));
        is_prime = 1;
        for (long long i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
    }
    return num;
}

long long find_primitive_root(long long p) {
    long long phi = p - 1;
    long long factors[100];
    int count = 0;

    long long n = phi;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            factors[count++] = i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors[count++] = n;
    }

    for (long long g = 2; g <= p; g++) {
        int is_primitive = 1;
        for (int i = 0; i < count; i++) {
            if (mod_pow(g, phi / factors[i], p) == 1) {
                is_primitive = 0;
                break;
            }
        }
        if (is_primitive) {
            return g;
        }
    }
    return -1;
}

void generate_keys(long long *p, long long *g, long long *y, long long *x) {
    srand(time(NULL));
    *p = generate_prime(16); // 16-bit prime for simplicity
    *g = find_primitive_root(*p);
    *x = rand() % (*p - 2) + 1; // Private key
    *y = mod_pow(*g, *x, *p);  // Public key
}

void encrypt(long long p, long long g, long long y, long long m, long long *c1, long long *c2) {
    long long k = rand() % (p - 2) + 1; // Random session key
    *c1 = mod_pow(g, k, p);
    *c2 = (m * mod_pow(y, k, p)) % p;
}

long long decrypt(long long p, long long x, long long c1, long long c2) {
    long long s = mod_pow(c1, x, p);
    return (c2 * mod_pow(s, p - 2, p)) % p; // Using Fermat's little theorem for modular inverse
}

int main() {
    long long p, g, y, x;
    long long c1, c2;
    long long m = 1234; 
    
    printf("ELGamal");
    // Key generation
    generate_keys(&p, &g, &y, &x);
    printf("Public Key (p, g, y): (%lld, %lld, %lld)\n", p, g, y);
    printf("Private Key (x): %lld\n", x);

    // Encryption
    encrypt(p, g, y, m, &c1, &c2);
    printf("Encrypted Message (c1, c2): (%lld, %lld)\n", c1, c2);

    // Decryption
    long long decrypted_m = decrypt(p, x, c1, c2);
    printf("Decrypted Message: %lld\n", decrypted_m);

    return 0;
}