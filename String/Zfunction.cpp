int z[maxn];

void z_function(string s) {
    for (i = 1; i < n; i++) {
        if (i <= r)  
            z[i] = min(r - i + 1, z[i - l]);

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        } 
    }
}
