#include <algorithm>
#include <cmath>
#include <cstdint>
#include <utility>

class Vector {
 public:
  Vector(int64_t coord_x, int64_t coord_y);
  Vector() = default;
  int64_t GetX() const;
  int64_t GetY() const;
  int64_t LengthSq() const;

  Vector& operator*=(int64_t num);
  Vector& operator+=(const Vector& second);
  Vector& operator-=(const Vector& second);

 private:
  int64_t coord_x_;
  int64_t coord_y_;
};

bool operator==(const Vector& first, const Vector& second);
int64_t operator*(const Vector& first, const Vector& second);
int64_t operator^(const Vector& first, const Vector& second);
Vector operator+(const Vector& first, const Vector& second);
Vector operator-(const Vector& first, const Vector& second);
Vector operator*(const Vector& vec, int64_t num);
Vector operator*(int64_t num, const Vector& vec);
Vector operator-(const Vector& cur);

class Point;
class Segment;

class IShape {
 public:
  virtual void Move(const Vector& my_vector) = 0;
  virtual bool ContainsPoint(const Point& my_point) const = 0;
  virtual bool CrossSegment(const Segment& my_segment) const = 0;
  virtual IShape* Clone() const = 0;
  virtual ~IShape() = default;
};

class Point : public IShape {
 public:
  Point(int64_t coord_x, int64_t coord_y);

  int64_t GetX() const;
  int64_t GetY() const;
  Vector GetVector() const;
  int64_t DistanceToSegment(const Segment& my_segment) const;

  void Move(const Vector& my_vector) override;
  bool ContainsPoint(const Point& my_point) const override;
  bool CrossSegment(const Segment& my_segment) const override;
  IShape* Clone() const override;

 private:
  int64_t coord_x_;
  int64_t coord_y_;
};
Vector operator-(const Point& first, const Point& second);
bool operator==(const Point& first, const Point& second);

class Segment : public IShape {
 public:
  Segment(const Point& begin, const Point& end);

  Point GetA() const;
  Point GetB() const;
  Vector GetVector() const;
  int64_t LengthSq() const;
  void Move(const Vector& my_vector) override;
  bool ContainsPoint(const Point& my_point) const override;
  bool CrossSegment(const Segment& my_segment) const override;
  IShape* Clone() const override;

 private:
  Point begin_;
  Point end_;
  bool static OnSegment(int64_t cur_begin_x, int64_t cur_begin_y,
                        int64_t cur_end_x, int64_t cur_end_y,
                        const Point& need);
};

class Line : public IShape {
 public:
  Line(const Point& begin, const Point& end);

  int64_t GetA() const;
  int64_t GetB() const;
  int64_t GetC() const;
  Vector GetVector() const;

  void Move(const Vector& my_vector) override;
  bool ContainsPoint(const Point& my_point) const override;
  bool CrossSegment(const Segment& my_segment) const override;
  IShape* Clone() const override;

 private:
  Point begin_;
  Vector direction_;
};

class Ray : public IShape {
 public:
  Ray(const Point& begin, const Point& end);

  Point GetA() const;
  Vector GetVector() const;

  void Move(const Vector& my_vector) override;
  bool ContainsPoint(const Point& my_point) const override;
  bool CrossSegment(const Segment& my_segment) const override;
  IShape* Clone() const override;

 private:
  Point begin_;
  Vector direction_;
};
bool operator==(const Ray& first, const Ray& second);

class Circle : public IShape {
 public:
  Circle(const Point& center, std::size_t radius);

  Point GetCentre() const;
  std::size_t GetRadius() const;

  void Move(const Vector& my_vector) override;
  bool ContainsPoint(const Point& my_point) const override;
  bool CrossSegment(const Segment& my_segment) const override;
  IShape* Clone() const override;

 private:
  Point center_;
  std::size_t radius_;
};
