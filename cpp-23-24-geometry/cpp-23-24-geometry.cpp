#include "cpp-23-24-geometry.hpp"

#include <utility>

Vector::Vector(int64_t coord_x, int64_t coord_y)
    : coord_x_(coord_x), coord_y_(coord_y) {}

int64_t Vector::GetX() const { return coord_x_; }
int64_t Vector::GetY() const { return coord_y_; }
int64_t Vector::LengthSq() const {
  return coord_x_ * coord_x_ + coord_y_ * coord_y_;
}

Vector& Vector::operator*=(int64_t num) {
  coord_x_ *= num;
  coord_y_ *= num;
  return *this;
}
Vector& Vector::operator+=(const Vector& second) {
  coord_x_ += second.GetX();
  coord_y_ += second.GetY();
  return *this;
}
Vector& Vector::operator-=(const Vector& second) {
  *this += -second;
  return *this;
}

bool operator==(const Vector& first, const Vector& second) {
  return first.GetX() * second.GetY() == first.GetY() * second.GetX() &&
         first.GetX() * second.GetX() >= 0 && first.GetY() * second.GetY() >= 0;
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

int64_t Point::GetX() const { return coord_x_; }
int64_t Point::GetY() const { return coord_y_; }
Vector Point::GetVector() const { return {GetX(), GetY()}; }
int64_t Point::DistanceToSegment(const Segment& my_segment) const {
  Segment segment_ca(my_segment.GetA(), *this);
  Segment segment_cb(my_segment.GetB(), *this);
  if (my_segment.GetVector() * segment_ca.GetVector() <= 0 ||
      (-my_segment.GetVector()) * segment_cb.GetVector() <= 0) {
    return my_segment.GetVector() * segment_ca.GetVector() <= 0
               ? segment_ca.LengthSq()
               : segment_cb.LengthSq();
  }
  return (my_segment.GetVector() ^ segment_ca.GetVector()) *
         (my_segment.GetVector() ^ segment_ca.GetVector()) /
         my_segment.LengthSq();
}

Vector operator-(const Point& first, const Point& second) {
  return {first.GetX() - second.GetX(), first.GetY() - second.GetY()};
}
bool operator==(const Point& first, const Point& second) {
  return first.GetX() == second.GetX() && first.GetY() == second.GetY();
}

void Point::Move(const Vector& my_vector) {
  coord_x_ += my_vector.GetX();
  coord_y_ += my_vector.GetY();
}
bool Point::ContainsPoint(const Point& my_point) const {
  return *this == my_point;
}
bool Point::CrossSegment(const Segment& my_segment) const {
  return my_segment.ContainsPoint(*this);
}
IShape* Point::Clone() const { return new Point(GetX(), GetY()); }

Segment::Segment(const Point& begin, const Point& end)
    : begin_(begin), end_(end) {}

Point Segment::GetA() const { return begin_; }
Point Segment::GetB() const { return end_; }
Vector Segment::GetVector() const {
  return end_.GetVector() - begin_.GetVector();
}
int64_t Segment::LengthSq() const {
  return (begin_.GetX() - end_.GetX()) * (begin_.GetX() - end_.GetX()) +
         (begin_.GetY() - end_.GetY()) * (begin_.GetY() - end_.GetY());
}
void Segment::Move(const Vector& my_vector) {
  begin_.Move(my_vector);
  end_.Move(my_vector);
}

bool Segment::ContainsPoint(const Point& my_point) const {
  return (GetVector() ^ Segment(begin_, my_point).GetVector()) == 0 &&
         std::min(begin_.GetX(), end_.GetX()) <= my_point.GetX() &&
         my_point.GetX() <= std::max(begin_.GetX(), end_.GetX()) &&
         std::min(begin_.GetY(), end_.GetY()) <= my_point.GetY() &&
         my_point.GetY() <= std::max(begin_.GetY(), end_.GetY());
}

bool Segment::CrossSegment(const Segment& my_segment) const {
  int64_t this_x1 = begin_.GetX();
  int64_t this_y1 = begin_.GetY();
  int64_t this_x2 = end_.GetX();
  int64_t this_y2 = end_.GetY();
  int64_t seg_x1 = my_segment.GetA().GetX();
  int64_t seg_y1 = my_segment.GetA().GetY();
  int64_t seg_x2 = my_segment.GetB().GetX();
  int64_t seg_y2 = my_segment.GetB().GetY();

  int64_t dist1 = ((seg_x2 - seg_x1) * (this_y1 - seg_y1)) -
                  ((this_x1 - seg_x1) * (seg_y2 - seg_y1));
  int64_t dist2 = ((seg_x2 - seg_x1) * (this_y2 - seg_y1)) -
                  ((this_x2 - seg_x1) * (seg_y2 - seg_y1));
  int64_t dist3 = ((this_x2 - this_x1) * (seg_y1 - this_y1)) -
                  ((seg_x1 - this_x1) * (this_y2 - this_y1));
  int64_t dist4 = ((this_x2 - this_x1) * (seg_y2 - this_y1)) -
                  ((seg_x2 - this_x1) * (this_y2 - this_y1));

  if ((dist1 < 0 && dist2 > 0 || dist1 > 0 && dist2 < 0) &&
      (dist3 < 0 && dist4 > 0 || dist3 > 0 && dist4 < 0)) {
    return true;
  }
  if (dist1 == 0 &&
      OnSegment(seg_x1, seg_y1, seg_x2, seg_y2, Point(this_x1, this_y1))) {
    return true;
  }
  if (dist2 == 0 &&
      OnSegment(seg_x1, seg_y1, seg_x2, seg_y2, Point(this_x2, this_y2))) {
    return true;
  }
  if (dist3 == 0 &&
      OnSegment(this_x1, this_y1, this_x2, this_y2, Point(seg_x1, seg_y1))) {
    return true;
  }
  return (dist4 == 0 &&
          OnSegment(this_x1, this_y1, this_x2, this_y2, Point(seg_x2, seg_y2)));
}

bool Segment::OnSegment(int64_t cur_begin_x, int64_t cur_begin_y,
                        int64_t cur_end_x, int64_t cur_end_y,
                        const Point& need) {
  return Segment(Point(cur_begin_x, cur_begin_y), Point(cur_end_x, cur_end_y))
      .ContainsPoint(need);
}

IShape* Segment::Clone() const { return new Segment(begin_, end_); }

Line::Line(const Point& begin, const Point& end)
    : begin_(begin), direction_(end.GetVector() - begin.GetVector()) {}

int64_t Line::GetA() const { return -direction_.GetY(); }
int64_t Line::GetB() const { return direction_.GetX(); }
int64_t Line::GetC() const {
  return direction_.GetY() * begin_.GetX() - direction_.GetX() * begin_.GetY();
}
Vector Line::GetVector() const { return direction_; }

void Line::Move(const Vector& my_vector) { begin_.Move(my_vector); }
bool Line::ContainsPoint(const Point& my_point) const {
  return (direction_ ^ Line(begin_, my_point).GetVector()) == 0;
}
bool Line::CrossSegment(const Segment& my_segment) const {
  return (GetC() + my_segment.GetA().GetX() * GetA() +
          my_segment.GetA().GetY() * GetB()) *
             (GetC() + my_segment.GetB().GetX() * GetA() +
              my_segment.GetB().GetY() * GetB()) <=
         0;
}

IShape* Line::Clone() const {
  Point end = begin_;
  end.Move(direction_);
  return new Line(begin_, end);
}

Ray::Ray(const Point& begin, const Point& end)
    : begin_(begin), direction_(end.GetVector() - begin.GetVector()) {}

Point Ray::GetA() const { return begin_; }
Vector Ray::GetVector() const { return direction_; }

void Ray::Move(const Vector& my_vector) { begin_.Move(my_vector); }
bool Ray::ContainsPoint(const Point& my_point) const {
  return (Ray(begin_, my_point) == *this);
}
bool Ray::CrossSegment(const Segment& my_segment) const {
  Point first_end = begin_;
  first_end.Move(
      direction_ *
      (begin_.GetVector() - my_segment.GetA().GetVector()).LengthSq());
  if (Segment(begin_, first_end).CrossSegment(my_segment)) {
    return true;
  }
  Point second_end = begin_;
  second_end.Move(
      direction_ *
      (begin_.GetVector() - my_segment.GetB().GetVector()).LengthSq());
  return Segment(begin_, second_end).CrossSegment(my_segment);
}
IShape* Ray::Clone() const { return new Ray(*this); }

bool operator==(const Ray& first, const Ray& second) {
  return first.GetA() == second.GetA() &&
         first.GetVector() == second.GetVector();
}

Circle::Circle(const Point& center, std::size_t radius)
    : center_(center), radius_(radius) {}

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
  int64_t dist = center_.DistanceToSegment(my_segment);
  if (dist > static_cast<int64_t>(radius_) * static_cast<int64_t>(radius_)) {
    return false;
  }
  int64_t dist_to_a = Segment(my_segment.GetA(), center_).LengthSq();
  int64_t dist_to_b = Segment(my_segment.GetB(), center_).LengthSq();
  return std::max(dist_to_a, dist_to_b) >=
         static_cast<int64_t>(radius_) * static_cast<int64_t>(radius_);
}

IShape* Circle::Clone() const { return new Circle(center_, radius_); }
