#include "cpp-23-24-geometry.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

Vector::Vector(int64_t coord_x, int64_t coord_y)
    : coord_x_(coord_x), coord_y_(coord_y) {}
Vector::Vector() : Vector(0, 0) {}

int64_t Vector::GetX() const { return coord_x_; }
int64_t Vector::GetY() const { return coord_y_; }

Vector& Vector::operator*=(int64_t num) {
  this->coord_x_ *= num;
  this->coord_y_ *= num;
  return *this;
}
Vector& Vector::operator+=(const Vector& second) {
  this->coord_x_ += second.GetX();
  this->coord_y_ += second.GetY();
  return *this;
}
Vector& Vector::operator-=(const Vector& second) {
  *this += -second;
  return *this;
}

int64_t operator*(const Vector& first, const Vector& second) {
  return first.GetX() * second.GetX() + first.GetY() * second.GetY();
}

int64_t operator^(const Vector& first, const Vector& second) {
  return first.GetX() * second.GetY() - first.GetY() * second.GetX();
}
Vector operator+(const Vector& first, const Vector& second) {
  Vector third = first;
  third += second;
  return third;
}
Vector operator-(const Vector& first, const Vector& second) {
  return first + (-second);
}
Vector operator*(const Vector& vec, int64_t num) {
  Vector other = vec;
  other *= num;
  return other;
}
Vector operator*(int64_t num, const Vector& vec) { return vec * num; }
Vector operator-(const Vector& cur) { return {-cur.GetX(), -cur.GetY()}; }

Point::Point(int64_t coord_x, int64_t coord_y)
    : coord_x_(coord_x), coord_y_(coord_y) {}

int64_t Point::GetX() const { return this->coord_x_; }
int64_t Point::GetY() const { return this->coord_y_; }
Vector Point::ToVector() const { return {this->GetX(), this->GetY()}; }

Vector operator-(const Point& first, const Point& second) {
  return {first.GetX() - second.GetX(), first.GetY() - second.GetY()};
}
bool operator==(const Point& first, const Point& second) {
  return first.GetX() == second.GetX() && first.GetY() == second.GetY();
}

void Point::Move(const Vector& my_vector) {
  this->coord_x_ += my_vector.GetX();
  this->coord_y_ += my_vector.GetY();
}
bool Point::ContainsPoint(const Point& my_point) const {
  return *this == my_point;
}
bool Point::CrossSegment(const Segment& my_segment) const {
  return my_segment.ContainsPoint(*this);
}
IShape* Point::Clone() const { return new Point(GetX(), GetY()); }

Segment::Segment(Point begin, Point end)
    : begin_(std::move(begin)), end_(std::move(end)) {}

Point Segment::GetA() const { return this->begin_; }
Point Segment::GetB() const { return this->end_; }
Vector Segment::GetVector() const {
  return this->end_.ToVector() - this->begin_.ToVector();
}

void Segment::Move(const Vector& my_vector) {
  this->begin_.Move(my_vector);
  this->end_.Move(my_vector);
}

bool Segment::ContainsPoint(const Point& my_point) const {
  return (this->GetVector() ^ Segment(this->begin_, my_point).GetVector()) ==
             0 &&
         std::min(this->begin_.GetX(), this->end_.GetX()) <= my_point.GetX() &&
         my_point.GetX() <= std::max(this->begin_.GetX(), this->end_.GetX()) &&
         std::min(this->begin_.GetY(), this->end_.GetY()) <= my_point.GetY() &&
         my_point.GetY() <= std::max(this->begin_.GetY(), this->end_.GetY());
}

bool Segment::CrossSegment(const Segment& my_segment) const {
  int64_t cur_begin_x = begin_.GetX();
  int64_t cur_begin_y = begin_.GetY();
  int64_t cur_end_x = end_.GetX();
  int64_t cur_end_y = end_.GetY();
  int64_t other_begin_x = my_segment.GetA().GetX();
  int64_t other_begin_y = my_segment.GetA().GetY();
  int64_t other_end_x = my_segment.GetB().GetX();
  int64_t other_end_y = my_segment.GetB().GetY();

  int64_t dist1 =
      ((other_end_x - other_begin_x) * (cur_begin_y - other_begin_y)) -
      ((cur_begin_x - other_begin_x) * (other_end_y - other_begin_y));
  int64_t dist2 =
      ((other_end_x - other_begin_x) * (cur_end_y - other_begin_y)) -
      ((cur_end_x - other_begin_x) * (other_end_y - other_begin_y));
  int64_t dist3 = ((cur_end_x - cur_begin_x) * (other_begin_y - cur_begin_y)) -
                  ((other_begin_x - cur_begin_x) * (cur_end_y - cur_begin_y));
  int64_t dist4 = ((cur_end_x - cur_begin_x) * (other_end_y - cur_begin_y)) -
                  ((other_end_x - cur_begin_x) * (cur_end_y - cur_begin_y));

  if ((dist1 < 0 && dist2 > 0 || dist1 > 0 && dist2 < 0) &&
      (dist3 < 0 && dist4 > 0 || dist3 > 0 && dist4 < 0)) {
    return true;
  }
  if (dist1 == 0 && OnSegment(other_begin_x, other_begin_y, other_end_x,
                              other_end_y, cur_begin_x, cur_begin_y)) {
    return true;
  }
  if (dist2 == 0 && OnSegment(other_begin_x, other_begin_y, other_end_x,
                              other_end_y, cur_end_x, cur_end_y)) {
    return true;
  }
  if (dist3 == 0 && OnSegment(cur_begin_x, cur_begin_y, cur_end_x, cur_end_y,
                              other_begin_x, other_begin_y)) {
    return true;
  }
  if (dist4 == 0 && OnSegment(cur_begin_x, cur_begin_y, cur_end_x, cur_end_y,
                              other_end_x, other_end_y)) {
    return true;
  }

  return false;
}

bool Segment::OnSegment(int64_t cur_begin_x, int64_t cur_begin_y,
                        int64_t cur_end_x, int64_t cur_end_y, int64_t need_x,
                        int64_t need_y) {
  return Segment(Point(cur_begin_x, cur_begin_y), Point(cur_end_x, cur_end_y))
      .ContainsPoint(Point(need_x, need_y));
}

IShape* Segment::Clone() const { return new Segment(begin_, end_); }

Line::Line(Point begin, const Point& end)
    : begin_(std::move(begin)), direction_(end.ToVector() - begin.ToVector()) {}

int64_t Line::GetA() const { return -direction_.GetY(); }
int64_t Line::GetB() const { return direction_.GetX(); }
int64_t Line::GetC() const {
  return -direction_.GetX() * begin_.GetX() + direction_.GetY() * begin_.GetY();
}
Vector Line::GetVector() const { return direction_; }

void Line::Move(const Vector& my_vector) { begin_.Move(my_vector); }
bool Line::ContainsPoint(const Point& my_point) const {
  return (direction_ ^ Line(this->begin_, my_point).GetVector()) == 0;
}
bool Line::CrossSegment(const Segment& my_segment) const {
  return (direction_ ^ my_segment.GetVector()) != 0 ||
         this->ContainsPoint(my_segment.GetA());
}
IShape* Line::Clone() const {
  Point end = begin_;
  end.Move(direction_);
  return new Line(begin_, end);
}

Ray::Ray(Point begin, const Point& end)
    : begin_(std::move(begin)), direction_(end.ToVector() - begin.ToVector()) {}

Point Ray::GetA() const { return begin_; }
Vector Ray::GetVector() const { return direction_; }

void Ray::Move(const Vector& my_vector) { begin_.Move(my_vector); }
bool Ray::ContainsPoint(const Point& my_point) const {
  Point end = begin_;
  end.Move(direction_ * aminov::kVeryBig);
  return Segment(begin_, end).ContainsPoint(my_point);
}
bool Ray::CrossSegment(const Segment& my_segment) const {
  Point end = begin_;
  end.Move(direction_ * aminov::kVeryBig);
  return Segment(begin_, end).CrossSegment(my_segment);
}
IShape* Ray::Clone() const {
  Point end = begin_;
  end.Move(direction_);
  return new Ray(begin_, end);
}

Circle::Circle(Point center, std::size_t radius)
    : center_(std::move(center)), radius_(radius) {}

Point Circle::GetCentre() const { return center_; }
std::size_t Circle::GetRadius() const { return radius_; }
void Circle::Move(const Vector& my_vector) { center_.Move(my_vector); }
bool Circle::ContainsPoint(const Point& my_point) const {
  std::size_t distance =
      (my_point.GetX() - center_.GetX()) * (my_point.GetX() - center_.GetX()) +
      (my_point.GetY() - center_.GetY()) * (my_point.GetY() - center_.GetY());
  return distance <= radius_ * radius_;
}
bool Circle::CrossSegment(const Segment& my_segment) const {
  Point start = my_segment.GetA();
  Point end = my_segment.GetB();
  int64_t coefficient_a = end.GetY() - start.GetY();
  int64_t coefficient_b = start.GetX() - end.GetX();
  int64_t coefficient_c = end.GetX() * start.GetY() - start.GetX() * end.GetY();
  return std::abs(coefficient_a * center_.GetX() +
                  coefficient_b * center_.GetY() + coefficient_c) <=
         radius_ * radius_ * coefficient_a * coefficient_a +
             coefficient_b * coefficient_b;
}
IShape* Circle::Clone() const { return new Circle(center_, radius_); }
