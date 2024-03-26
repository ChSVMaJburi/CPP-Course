#include <cstdint>

namespace aminov {
const int64_t kVeryBig = 1e9 + 7;
}

class Vector {
 public:
  Vector(int64_t coord_x, int64_t coord_y);
  Vector();

  int64_t GetX() const;
  int64_t GetY() const;

  Vector& operator*=(int64_t num);
  Vector& operator+=(const Vector& second);
  Vector& operator-=(const Vector& second);

 private:
  int64_t coord_x_;
  int64_t coord_y_;
};

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
  Vector ToVector() const;

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
  Segment(Point begin, Point end);

  Point GetA() const;
  Point GetB() const;
  Vector GetVector() const;

  void Move(const Vector& my_vector) override;
  bool ContainsPoint(const Point& my_point) const override;
  bool CrossSegment(const Segment& my_segment) const override;
  IShape* Clone() const override;

 private:
  Point begin_;
  Point end_;
  bool static OnSegment(int64_t cur_begin_x, int64_t cur_begin_y,
                        int64_t cur_end_x, int64_t cur_end_y, int64_t need_x,
                        int64_t need_y);
};

class Line : public IShape {
 public:
  Line(Point begin, const Point& end);

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
  Ray(Point begin, const Point& end);

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

class Circle : public IShape {
 public:
  Circle(Point center, std::size_t radius);

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
