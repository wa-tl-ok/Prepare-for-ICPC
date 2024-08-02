int gcd(int a, int b) {
    while (b != 0) {
        int temp = b; 
        b = a % b; 
        a = temp;
    }
    return a;
}

int mathnod(int a, int b) { 
    return gcd(a, b); 
}

int mathnok(int a, int b) { 
    return a * b / mathnod(a, b); 
}
