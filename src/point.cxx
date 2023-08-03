#include "point.hxx"

Point::Point():val({0,0,0}){}

Point::Point(const Point &p):val(p.val){
}

Point &Point::operator=(const Point &p){
  if (this != &p) {
    this->val[0] = p.val[0];
    this->val[1] = p.val[1];
    this->val[2] = p.val[2];
  } 
  return *this;
}

Point & Point::operator+=(const Point &p){
  for(auto k =0 ; k < 3; ++k) {
    this->val[k] += p.val[k];
  }
  return *this;
}

Point Point::operator+(const Point &p){
  return Point(p.val[0]+val[0],p.val[1]+val[1],p.val[2]+val[2]);
}

Point & Point::operator*=(double s){
  for(auto k =0 ; k < 3; ++k) {
    val[k] *= s;
  }
  return *this;
}

Point Point::operator*(double s){
  return Point(s*val[0], s*val[1], s*val[2]);
}

double &Point::operator()(int k){
    return val[k];
}

double Point::operator()(int k) const {
    return val[k];
}


std::ostream & operator<<(std::ostream & out, const Point & p){
  for(auto v:p.val){
    out<<v<<" ";
  }
  return out;
}

Point operator+(const Point &p1, const Point &p2){
  return Point(p1.val[0] + p2.val[0], p1.val[1] + p2.val[1], p1.val[2] + p2.val[2]);
}

Point::~Point(){}

Point::Point(double x, double y, double z){
  val = {x,y,z};
}

Point operator*(double v, const Point &p1){
  return Point(v * p1.val[0], v * p1.val[1], v * p1.val[2]);
}

Point operator-(const Point &p1, const Point &p2){
  return Point(p1.val[0] - p2.val[0], p1.val[1] - p2.val[1], p1.val[2] - p2.val[2]);
}