#include <utility>
#include <valarray>

std::pair<int, const int*> Range(int from, int to, int step = 1) {
  if (from <= to && step <= 0 || from > to && step > 0) {
    return {};
  }
  int sz = (abs(to - from) + abs(step) - 1) / abs(step);
  int* answer = new int[sz];
  int counter = 0;
  if (step < 0) {
    for (int i = from; i > to; i += step) {
      answer[counter++] = i;
    }
  } else {
    for (int i = from; i < to; i += step) {
      answer[counter++] = i;
    }
  }
  return {sz, answer};
}