int* PointwiseSum(const int* a, const int* b, int n) {
  int* answer = new int[n];
  for (unsigned int i = 0; i < n; ++i) {
    answer[i] = a[i] + b[i];
  }
  return answer;
}