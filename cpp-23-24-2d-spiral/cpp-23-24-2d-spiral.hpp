int** MakeSpiral(unsigned int n) {
  int** array = new int*[n];
  for (unsigned int i = 0; i < n; ++i) {
    array[i] = new int[n];
  }
  unsigned int counter = 0;
  for (unsigned int it = 0; it < (n + 1) / 2; ++it) {
    unsigned int left = it;
    unsigned int right = n - it - 1;
    for (unsigned int i = left; i < right + (left == right); ++i) {
      array[left][i] = ++counter;
    }
    for (unsigned int i = left; i < right; ++i) {
      array[i][right] = ++counter;
    }
    for (unsigned int i = right; i > left; --i) {
      array[right][i] = ++counter;
    }
    for (unsigned int i = right; i > left; --i) {
      array[i][left] = ++counter;
    }
  }
  return array;
}
