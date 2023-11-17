#include <utility>

int Abs(int num) { return (num > 0 ? num : -num); }

std::pair<int, const int *> Range(int from, int to, int step = 1) {
  if (from <= to && step <= 0 || from > to && step >= 0) {
    return {};
  }
  unsigned int sz = (Abs(to - from) + Abs(step) - 1) / Abs(step);
  int *answer = new int[sz];
  unsigned int counter = 0;
  for (int i = from; counter < sz; i += step) {
    answer[counter++] = i;
  }
  return {sz, answer};
}