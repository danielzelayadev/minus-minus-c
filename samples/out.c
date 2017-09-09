int a, b, c, d, e;

int hehe[4 * 17 + 38 + 45 * 7];

int partition(int arr[], int l, int h){
	int x = arr[h];
	int i = l - 1;
	int j;

	for (j = l; j <= h - 1;j++) {
		if (arr[j] <= x) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[h]);
	return i + 1;
}

void quickSort(int A[], int l, int h){
	if (l < h) {
		int p = partition(A, l, h);

		quickSort(A, l, p - 1);
		quickSort(A, p + 1, h);
	}
}


