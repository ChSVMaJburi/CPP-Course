#include "cpp-23-24-geometry.hpp"

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

void Point::Move(const Vector& vec) {
  this->coord_x_ += vec.GetX();
  this->coord_y_ += vec.GetY();
}
bool Point::ContainsPoint(const Point& my_point) const {
  return *this == my_point;
}
bool Point::CrossSegment(const Segment& my_seg) const {
  return my_seg.ContainsPoint(*this);
}
IShape* Point::Clone() const { return new Point(GetX(), GetY()); }

Segment::Segment(Point begin, Point end)
    : begin_(std::move(begin)), end_(std::move(end)) {}

Point Segment::GetA() const { return this->begin_; }
Point Segment::GetB() const { return this->end_; }
Vector Segment::GetDirection() const {
  return this->end_.ToVector() - this->begin_.ToVector();
}

void Segment::Move(const Vector& vec) {
  this->begin_.Move(vec);
  this->end_.Move(vec);
}

bool Segment::ContainsPoint(const Point& my_point) const {
  return this->GetDirection() ^
             Segment(this->begin_, my_point).GetDirection() &&
         this->begin_.GetX() <= my_point.GetX() &&
         my_point.GetX() <= this->end_.GetX() &&
         this->begin_.GetY() <= my_point.GetY() &&
         my_point.GetY() <= this->end_.GetY();
}
bool Segment::CrossSegment(const Segment& other) const {
  Vector thisVector(this->GetB().GetX() - this->GetA().GetX(),
                    this->GetB().GetY() - this->GetA().GetY());
  Vector otherVector(other.GetB().GetX() - other.GetA().GetX(),
                     other.GetB().GetY() - other.GetA().GetY());

  Vector thisToOther(this->GetA().GetX() - other.GetA().GetX(),
                     this->GetA().GetY() - other.GetA().GetY());

  int64_t thisCrossOtherStart = thisVector ^ thisToOther;
  int64_t thisCrossOtherEnd =
      thisVector ^ Vector(other.GetB().GetX() - this->GetA().GetX(),
                          other.GetB().GetY() - this->GetA().GetY());
  int64_t otherCrossThisStart =
      otherVector ^ Vector(this->GetB().GetX() - other.GetA().GetX(),
                           this->GetB().GetY() - other.GetA().GetY());
  int64_t otherCrossThisEnd =
      otherVector ^ Vector(other.GetB().GetX() - other.GetA().GetX(),
                           other.GetB().GetY() - other.GetA().GetY());

  return thisCrossOtherStart * thisCrossOtherEnd <= 0 &&
         otherCrossThisStart * otherCrossThisEnd <= 0;
}
IShape* Segment::Clone() const {
  return new Segment(begin_, end_);
}
