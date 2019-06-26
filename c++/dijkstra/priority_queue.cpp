#include <cstdlib>

class NullablePriorityQueueElement {
public:
  int key;
  int priority;
  bool null;
  NullablePriorityQueueElement(int key, int priority, bool null) :
    key(key), priority(priority), null(null) {};
  ~NullablePriorityQueueElement() {};
};

class PriorityQueue {
public:
  int size;
  int currentSize;
  NullablePriorityQueueElement* queue;

  PriorityQueue(int);
  ~PriorityQueue();

  void add(int key, int priority);
  NullablePriorityQueueElement poll();
  void toPrint();

private:
  void heapUp();
  void heapDown();
  bool isOrdered(int, int);
  bool isParentDisordered(int);
  bool isRightLeftOrdered(int);
  NullablePriorityQueueElement* parent(int);
  NullablePriorityQueueElement* left(int);
  NullablePriorityQueueElement* right(int);
  bool hasParent(int);
  bool hasLeft(int);
  bool hasRight(int);
  int getParentIndex(int);
  int getLeftIndex(int);
  int getRightIndex(int);

  void swap(int, int);
};

PriorityQueue::PriorityQueue(int size)
{
  this->currentSize = 0;
  this->size = size;
  this->queue = (NullablePriorityQueueElement*) calloc(size,
    sizeof(NullablePriorityQueueElement));
}

PriorityQueue::~PriorityQueue() {
  free(this->queue);
}

void PriorityQueue::add(int key, int priority)
{
  if (this->currentSize == this->size) {
    return;
  }

  this->queue[this->currentSize++] = NullablePriorityQueueElement(key, priority,
    false);
  this->heapUp();
}

NullablePriorityQueueElement PriorityQueue::poll()
{
  if (this->currentSize == 0) {
    return NullablePriorityQueueElement(0, 0, true);
  }

  NullablePriorityQueueElement ret = this->queue[0];
  if (this->currentSize == 1) {
    this->currentSize--;
    return ret;
  }

  this->queue[0] = this->queue[--this->currentSize];
  this->heapDown();
  return ret;

}

void PriorityQueue::heapUp()
{
  int currentIndex = this->currentSize - 1;

  while(this->isParentDisordered(currentIndex)) {
    int parentIndex = this->getParentIndex(currentIndex);
    this->swap(currentIndex, parentIndex);
    currentIndex = parentIndex;
  }
}

void PriorityQueue::heapDown()
{
  int currentIndex = 0;
  int nxtIndex = 0;

  while (this->hasLeft(currentIndex)) {
    if (this->isRightLeftOrdered(currentIndex)) {
      nxtIndex = this->getRightIndex(currentIndex);
    } else {
      nxtIndex = this->getLeftIndex(currentIndex);
    }

    if (this->isOrdered(currentIndex, nxtIndex)) {
      break;
    }

    this->swap(currentIndex, nxtIndex);
    currentIndex = nxtIndex;
  }
}

bool PriorityQueue::isOrdered(int above, int below)
{
  return this->queue[above].priority < this->queue[below].priority;
}

bool PriorityQueue::isParentDisordered(int i)
{
  return this->hasParent(i) && !this->isOrdered(this->getParentIndex(i), i);
}

bool PriorityQueue::isRightLeftOrdered(int i)
{
  return this->hasRight(i) &&
    this->isOrdered(this->getRightIndex(i), this->getLeftIndex(i));
}

NullablePriorityQueueElement* PriorityQueue::parent(int i)
{
  return &this->queue[this->getParentIndex(i)];
}

NullablePriorityQueueElement* PriorityQueue::left(int i)
{
  return &this->queue[this->getLeftIndex(i)];
}

NullablePriorityQueueElement* PriorityQueue::right(int i)
{
  return &this->queue[this->getRightIndex(i)];
}

bool PriorityQueue::hasParent(int i)
{
  return this->getParentIndex(i) >= 0;
}

bool PriorityQueue::hasLeft(int i)
{
  return this->getLeftIndex(i) < this->currentSize;
}

bool PriorityQueue::hasRight(int i)
{
  return this->getRightIndex(i) < this->currentSize;
}

int PriorityQueue::getParentIndex(int i)
{
  if (i - 1 < 0) {
    return -1;
  }
  return (i - 1) / 2;
}

int PriorityQueue::getLeftIndex(int i)
{
  return (2 * i) + 1;
}

int PriorityQueue::getRightIndex(int i)
{
  return (2 * i) + 2;
}

void PriorityQueue::swap(int x, int y)
{
  NullablePriorityQueueElement temp = this->queue[x];
  this->queue[x] = this->queue[y];
  this->queue[y] = temp;
}
