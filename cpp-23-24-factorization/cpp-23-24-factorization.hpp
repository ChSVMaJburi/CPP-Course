#pragma once
#include <vector>

std::vector<int> Factorize(unsigned int n) {
  std::vector<int> answer;
  for (unsigned int i = 2; i * i <= n; ++i) {
    while (n % i == 0) {
      answer.push_back(i);
      n /= i;
    }
  }
  if (n != 1) {
    answer.push_back(n);
  }
  return answer;
}