int a, b;

int gcd(int a, int b);

void main() {
    int x, y, z;
    a = 10;
    b = 20;
    
    x = a;
    y = b;
    z = gcd(x, y);

    printf("GCD(%d, %d) = %d\n", a, b, z);
}

// Funcion que calcula el maximo comun divisor
int gcd(int a, int b) {
    if (b == 0) { return(a); }
    else { return( gcd(b, a % b) ); }
}

