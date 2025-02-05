
#include <cmath>
#include <iostream>

using namespace std;

long long int power(long long int a, long long int b,
                    long long int P)
{
    if (b == 1)
        return a;

    else
        return (((long long int)pow(a, b)) % P);
}

int main()
{
    long long int P, G, x, a, y, b, ka, kb;
    cout << "HELLMAN" << "\n";
    P = 20; 
    cout << "The value of P : " << P << endl;

    G = 8; 
    cout << "The value of G : " << G << endl;

    a = 8; 
    cout << "The private key a for Suyog : " << a << endl;

    x = power(G, a, P); 
   
    b = 4;
    cout << "The private key b for Hari : " << b << endl;

    y = power(G, b, P); 

    ka = power(y, a, P); 
    kb = power(x, b, P); 
    cout << "Secret key for the Suyog is : " << ka << endl;

    cout << "Secret key for the Hari is : " << kb << endl;

    return 0;
}

