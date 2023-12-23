#include <iostream>
#include <string>
#include <climits>
#include <cstring>

using namespace std;

#define d 256

void rabinKarp(const char pattern[], const char text[], int q) {
    int m = strlen(pattern);
    int n = strlen(text);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    for (i = 0; i < m - 1; i++){
        h = (h * d) % q;
    }

    // Calculate hash value for pattern and text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Find the match
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m){
                cout << i + 1 << " ";
            }
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0){
                t = (t + q);
            }
        }
    }
}

int main() {
    std::string inPattern, inText;

    while (getline(cin, inPattern) && getline(cin, inText)) {
        const char* pattern = inPattern.c_str();
        const char* text = inText.c_str();

        int q = INT_MAX;
        rabinKarp(pattern, text, q);

        cout << endl;
    }

    return 0;
}
