#pragma once

#include <math.h>

#include <algorithm>

/*
 * Верните 0 если и только если треугольник невозможно построить
 * Верните 1 если и только если треугольник вырожденный
 * Верните 2 если и только если треугольник остроугольный
 * Верните 3 если и только если треугольник прямоугольный
 * Верните 4 если и только если треугольник тупоугольный
 */

int WhichTriangle(int a, int b, int c) {
  if (a > b) {
    std::swap(a, b);
  }
  if (a > c) {
    std::swap(a, c);
    std::swap(b, c);
  }
  if (b > c) {
    std::swap(b, c);
  }
  if (c > a + b) {
    return 0;
  }
  if (c == a + b) {
    return 1;
  }
  const double alpha =
      acos((1LL * c * c - 1LL * a * a - 1LL * b * b) * 1.0 / (-2LL * b * a));
  const double pi = acos(-1);
  if (alpha < pi / 2) {
    return 2;
  }
  if (alpha > pi / 2) {
    return 4;
  }
  return 3;
}