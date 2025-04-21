#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Convert to lowercase
void lower(string& s) { transform(s.begin(), s.end(), s.begin(), ::tolower); }

// Remove spaces
string remove_spaces(const string& s) {
    string res = "";
    for (char c : s) if (c != ' ') res += c;
    return res;
}

// Generate 5x5 key table
void key_table(const string& key, char table[5][5]) {
    string k = remove_spaces(key);
    lower(k);
    string chars = "";
    vector<bool> used(26, false);
    auto add_char = [&](char c) {
        if (c == 'j') c = 'i';
        if (!used[c - 'a']) {
            chars += c;
            used[c - 'a'] = true;
        }
    };
    for (char c : k) add_char(c);
    for (char c = 'a'; c <= 'z'; ++c) add_char(c);
    if (chars.length() > 25) chars.erase(remove(chars.begin(), chars.end(), 'j'), chars.end());
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            table[i][j] = chars[i * 5 + j];
}

// Find char position
pair<int, int> find_pos(char table[5][5], char c) {
    if (c == 'j') c = 'i';
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (table[i][j] == c) return {i, j};
    return {-1, -1}; // Should not happen
}

// Prepare plaintext
string prepare(string s) {
    lower(s);
    s = remove_spaces(s);
    string res = "";
    for (size_t i = 0; i < s.length(); i += 2) {
        res += s[i];
        if (i + 1 < s.length()) {
            res += (s[i] == s[i + 1] ? 'x' : s[i + 1]);
        } else {
            res += 'z';
        }
    }
    return res;
}

// Encrypt digraph
string encrypt_digraph(char table[5][5], char a, char b) {
    pair<int, int> pos1 = find_pos(table, a);
    pair<int, int> pos2 = find_pos(table, b);
    if (pos1.first == pos2.first) { // Same row
        return string(1, table[pos1.first][(pos1.second + 1) % 5]) + table[pos2.first][(pos2.second + 1) % 5];
    } else if (pos1.second == pos2.second) { // Same column
        return string(1, table[(pos1.first + 1) % 5][pos1.second]) + table[(pos2.first + 1) % 5][pos2.second];
    } else { // Rectangle
        return string(1, table[pos1.first][pos2.second]) + table[pos2.first][pos1.second];
    }
}

// Playfair encrypt
string playfair_encrypt(string text, string key) {
    char table[5][5];
    key_table(key, table);
    string prepared_text = prepare(text);
    string ciphertext = "";
    for (size_t i = 0; i < prepared_text.length(); i += 2) {
        ciphertext += encrypt_digraph(table, prepared_text[i], prepared_text[i + 1]);
    }
    return ciphertext;
}

int main() {
    string key = "Suyogranamagar";
    string plaintext = "student";
    cout << "Key text: " << key << endl;
    cout << "Plain text: " << plaintext << endl;
    string ciphertext = playfair_encrypt(plaintext, key);
    cout << "Cipher text: " << ciphertext << endl;
    return 0;
}