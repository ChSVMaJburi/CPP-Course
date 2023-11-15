#include <utility>

std::pair<int, const int*> Range(int from, int to, int step = 1) {
  int sz = (to - from + step - 1) / step;
  int* answer = new int[sz];
  int counter = 0;
  for (int i = from; i < to; i += step) {
    answer[counter++] = i;
  }
  return {sz, answer};
}