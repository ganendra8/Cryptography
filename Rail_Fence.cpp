#include <iostream>
#include <vector>
#include <string>

using namespace std;

string encryptRailFence(string text, int rails) {
    if (rails <= 1) return text;

    vector<string> rail(rails);
    int dir = 1, row = 0;

    for (char ch : text) {
        rail[row] += ch;
        row += dir;
        
        if (row == rails - 1 || row == 0) dir *= -1;
    }

    string ciphertext;
    for (string r : rail) {
        ciphertext += r;
    }
    
    return ciphertext;
}

string decryptRailFence(string ciphertext, int rails) {
    if (rails <= 1) return ciphertext;

    vector<int> railPos(ciphertext.size());
    vector<string> rail(rails);
    int dir = 1, row = 0;

    for (size_t i = 0; i < ciphertext.size(); i++) {
        railPos[i] = row;
        row += dir;

        if (row == rails - 1 || row == 0) dir *= -1;
    }

    int index = 0;
    for (int r = 0; r < rails; r++) {
        for (size_t i = 0; i < ciphertext.size(); i++) {
            if (railPos[i] == r) {
                rail[r] += ciphertext[index++];
            }
        }
    }

    string plaintext;
    row = 0, dir = 1;
    vector<int> railIndex(rails, 0);
    
    for (size_t i = 0; i < ciphertext.size(); i++) {
        plaintext += rail[row][railIndex[row]++];
        row += dir;

        if (row == rails - 1 || row == 0) dir *= -1;
    }
    
    return plaintext;
}

int main() {
    string text;

    cout << "Enter the text to encrypt: ";
    getline(cin, text);

    int rails = 4;

    string encryptedText = encryptRailFence(text, rails);
    cout << "Encrypted Text: " << encryptedText << endl;

    string decryptedText = decryptRailFence(encryptedText, rails);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
