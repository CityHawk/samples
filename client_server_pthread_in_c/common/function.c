#include <string.h>

// simple fuction that reverses the string supplied
void reverse(char *s) {
    int s_len = strlen(s);
    int i = 0;
    int j = s_len - 1;
    char t;
    while (i < j) {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++; j--;
    }

    return;
}
