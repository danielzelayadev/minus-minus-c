int globalArr[5];

int anothaGlobal[2] = { 20, 40 };

char globalChars[3] = { 'a', 'b', 'c' };

void main() {
    int siz = 6;
    int iterate[6] = { 4, 100, 12, siz };
    int i;

    iterate[4] = 20;

    iterate[5] = 30;

    for (i = 0; i < 6; i++)
        printf("iterate[%d] = %d\n", i, iterate[i]);
}