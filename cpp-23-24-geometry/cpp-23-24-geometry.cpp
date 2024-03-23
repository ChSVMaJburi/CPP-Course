#include "cpp-23-24-geometry.hpp"

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
         this->begin_.GetX() <= my_point.GetX() &&
         my_point.GetX() <= this->end_.GetX() &&
         this->begin_.GetY() <= my_point.GetY() &&
         my_point.GetY() <= this->end_.GetY();
}

bool Segment::CrossSegment(const Segment& my_segment) const {
  Vector this_vector(this->GetB().GetX() - this->GetA().GetX(),
                     this->GetB().GetY() - this->GetA().GetY());
  Vector other_vector(my_segment.GetB().GetX() - my_segment.GetA().GetX(),
                      my_segment.GetB().GetY() - my_segment.GetA().GetY());

  Vector this_to_other(this->GetA().GetX() - my_segment.GetA().GetX(),
                       this->GetA().GetY() - my_segment.GetA().GetY());

  int64_t this_cross_other_start = this_vector ^ this_to_other;
  int64_t this_cross_other_end =
      this_vector ^ Vector(my_segment.GetB().GetX() - this->GetA().GetX(),
                           my_segment.GetB().GetY() - this->GetA().GetY());
  int64_t other_cross_this_start =
      other_vector ^ Vector(this->GetB().GetX() - my_segment.GetA().GetX(),
                            this->GetB().GetY() - my_segment.GetA().GetY());
  int64_t other_cross_this_end =
      other_vector ^
      Vector(my_segment.GetB().GetX() - my_segment.GetA().GetX(),
             my_segment.GetB().GetY() - my_segment.GetA().GetY());

  return this_cross_other_start * this_cross_other_end <= 0 &&
         other_cross_this_start * other_cross_this_end <= 0;
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
  end.Move(direction_ * Aminov::kVeryBig);
  return Segment(begin_, end).ContainsPoint(my_point);
}
bool Ray::CrossSegment(const Segment& my_segment) const {
  Point end = begin_;
  end.Move(direction_ * Aminov::kVeryBig);
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
  int64_t coefficient_C = end.GetX() * start.GetY() - start.GetX() * end.GetY();
  return std::abs(coefficient_a * center_.GetX() +
                  coefficient_b * center_.GetY() + coefficient_C) <=
         radius_ * radius_ * coefficient_a * coefficient_a +
             coefficient_b * coefficient_b;
}
IShape* Circle::Clone() const { return new Circle(center_, radius_); }
