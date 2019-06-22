#ifndef KADANES
#define KADANES

#include <algorithm>

struct KadanesResult {
  int max;
  int itemsLen;
  int* items;
} KadanesResult;

void Kadanes(struct KadanesResult* res, int* ary, int aryLen) {
  int maxSub = 0;
  int maxTotal = 0;
  int subItems[aryLen];
  int subItemsLen = 0;
  int maxItems[aryLen];
  int maxItemsLen = 0;

  for (int i = 0; i < aryLen; i++) {
    int item = ary[i];
    maxSub = std::max(0, maxSub + item);

    bool didGoHigher = maxSub > maxTotal;
    bool didZeroSub = maxSub == 0;

    maxTotal = std::max(maxTotal, maxSub);

    bool didSyncMax = maxTotal != 0 && maxTotal == maxSub;
    bool didNotSyncAndNotZero = !didSyncMax && !didZeroSub;

    if (didZeroSub) {
      subItemsLen = 0;
    }
    if (didSyncMax || didNotSyncAndNotZero) {
      subItems[subItemsLen++] = item;
    }
    if (didSyncMax && didGoHigher) {
      maxItemsLen = subItemsLen;
      for (int i = 0; i < maxItemsLen; i++) {
        maxItems[i] = subItems[i];
      }
    }
  }

  res->max = maxTotal;
  res->itemsLen = maxItemsLen;
  res->items = (int*) calloc(maxItemsLen, sizeof(int));
  for (int i = 0; i < maxItemsLen; i++) {
    res->items[i] = maxItems[i];
  }

}

void KadanesResult_Free(struct KadanesResult* res) {
  free(res->items);
} 

#endif