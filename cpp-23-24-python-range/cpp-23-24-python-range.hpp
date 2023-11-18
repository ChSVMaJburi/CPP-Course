#include <utility>

int Abs(int num) { return (num > 0 ? num : -num); }

std::pair<int, const int*> Range(int from, int to, int step = 1) {
  if (from <= to && step <= 0 || from > to && step >= 0) {
    return {};
  }
  const unsigned int kSize = (Abs(to - from) + Abs(step) - 1) / Abs(step);
  int* answer = new int[kSize];
  unsigned int counter = 0;
  for (int i = from; counter < kSize; i += step) {
    answer[counter++] = i;
  }
  return {kSize, answer};
}
