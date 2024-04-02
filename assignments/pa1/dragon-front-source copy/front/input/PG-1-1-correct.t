{
    int[4] a;
    int i;
    int j;
    int temp;
    a[0] = 1; a[1] = 3; a[2] = 2; a[3] = 4;
    for (i = 0; i < 3; i = i + 1;) {
        for(j = 0; j < 3 - i; j = j + 1;) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
