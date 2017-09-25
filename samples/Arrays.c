int globalArr[5];

int anothaGlobal[2] = { 20, 40 };

char globalChars[3] = { 'a', 'b', 'c' };

void main() {
    int numbers[10];
    int siz = 6;
    int iterate[6] = { 4, 100, 12, siz };
    char letters[] = { 'a', 'b', 'c', 'd', 'z' }; 
    char c = 'e';
    int x, i;

    srand(time(0));

    numbers[3] = 10;

    numbers[0] = 2;

    numbers[5] = 100;

    numbers[1] = numbers[5];

    letters[4] = c;

    x = numbers[5] + numbers[3];
    x = x * numbers[0];

    letters[1] = globalChars[1];

    for (i = 0; i < siz; i++) {
        iterate[i] = rand() % 20 + 1;
    }

    for (i = 0; i < siz; i++) {
        printf("iterate[%d] = %d\n", i, iterate[i]);
    }
}