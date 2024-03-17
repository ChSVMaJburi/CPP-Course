#include <cstdint>
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
  virtual void Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossSegment(const Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual ~IShape() = default;
};

class Point : public IShape {
 public:
  Point(int64_t coord_x, int64_t coord_y);

  int64_t GetX() const;
  int64_t GetY() const;
  Vector ToVector() const;

  void Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossSegment(const Segment&) const override;
  IShape* Clone() const override;

 private:
  int64_t coord_x_;
  int64_t coord_y_;
};

bool operator==(const Point& first, const Point& second);

class Segment : public IShape {
 public:
  Segment(Point begin, Point end);

  Point GetA() const;
  Point GetB() const;
  Vector GetDirection() const;

  void Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossSegment(const Segment&) const override;
  IShape* Clone() const override;

 private:
  Point begin_;
  Point end_;
};
