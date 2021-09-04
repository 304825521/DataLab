#include <algorithm>
#include <iostream>
#include <vector>
template <typename Object>

class myVector {
public:
public:
  explicit myVector(int initSize = 0)
      : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY} {
    objects = new Object[theCapacity];
  }

  myVector(const myVector &rhs)
      : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr} {
    objects = new Object[theCapacity];
    for (int k = 0; k < theSize; ++k)
      objects[k] = rhs.objects[k];
  }

  myVector(const std::vector<Object> &rhs) {
    theSize = rhs.size();
    theCapacity = rhs.capacity();
    objects = new Object[theCapacity];
    for (int k = 0; k < theSize; ++k)
      objects[k] = rhs[k];
  }

  void push_back(const Object &x) {
    if (theSize == theCapacity)
      reserve(2 * theCapacity + 1);
    objects[theSize++] = x;
  }

  myVector<Object> &append(const myVector<Object> &rhs) {

    for (size_t i = 0; i < rhs.theSize; i++) {

      push_back(rhs.objects[i]);
    }
    return *this;
  }

  void pop_back() { --theSize; }

  void push_back(Object &&x) {
    if (theSize == theCapacity)
      reserve(2 * theCapacity + 1);
    objects[theSize++] = std::move(x);
  }

  int size() { return theSize; }

  int capacity() { return theCapacity; }

  bool empty() {
    if (size() == 0)
      return true;
    return false;
  }

  Object &operator[](int index) { return objects[index]; }

  myVector &operator=(const myVector &rhs) {
    myVector copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  ~myVector() { delete[] objects; }

  myVector &operator=(myVector &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(theCapacity, rhs.theCapacity);
    std::swap(objects, rhs.objects);
    return *this;
  }

  void resize(int newSize) {
    if (newSize > theCapacity)
      reserve(newSize * 2);
    theSize = newSize;
  }

  void reserve(int newCapacity) {
    if (newCapacity < theSize)
      return;

    Object *newArray = new Object[newCapacity];
    for (int k = 0; k < theSize; ++k)
      newArray[k] = std::move(objects[k]);

    theCapacity = newCapacity;
    std::swap(objects, newArray);
    delete[] newArray;
  }

  const Object &operator[](int index) const { return objects[index]; }

  const Object &back() const { return objects[theSize - 1]; }

  typedef Object *iterator;
  typedef const Object *const_iterator;

  iterator begin() { return &objects[0]; }
  const_iterator begin() const { return &objects[0]; }

  iterator end() { return &objects[size()]; }
  const_iterator end() const { return &objects[size()]; }

  static const int SPARE_CAPACITY = 16;

private:
  int theSize;
  int theCapacity;
  Object *objects;
};