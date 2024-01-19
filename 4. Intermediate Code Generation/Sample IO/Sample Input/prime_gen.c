int is_prime(int a) {
    int i;
    for (i = 2; i * i <= a; i++) {
        if (!(a % i)) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int i;
    for (i = 2; i <= 100; i++) {
        if (is_prime(i)) {
            println(i);
        }
    }
}