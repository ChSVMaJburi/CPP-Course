int** MakeSpiral(int n) {
 int** array = new int*[n];
 for (int i = 0; i < n; ++i) {
	array[i] = new int[n];
 }
 int counter = 0;
 for (int it = 0; it < (n + 1) / 2; ++it) {
	int l = it;
	int r = n - it - 1;
	for (int i = l; i < r + (l == r); ++i) {
	 array[l][i] = ++counter;
	}
	for (int i = l; i < r; ++i) {
	 array[i][r] = ++counter;
	}
	for (int i = r; i > l; --i) {
	 array[r][i] = ++counter;
	}
	for (int i = r; i > l; --i) {
	 array[i][l] = ++counter;
	}
 }
 return array;
}