#ifndef DOUBLE_LINK_H
#define DOUBLE_LINK_H
class DoubleLink
{
public:
  DoubleLink(int value);
  ~DoubleLink();

  int value;
  DoubleLink* next;
  DoubleLink* prev;
};
DoubleLink::DoubleLink(int _value) {
  value = _value;
  next = NULL;
  prev = NULL;
}
DoubleLink::~DoubleLink() {}
#endif