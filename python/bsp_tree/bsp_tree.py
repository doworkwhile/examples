import math
from bsp_node import BSPNode

class BSPTree():
  def __init__(self, segments, maxCoord):
    self.head = BSPNode(segments.pop(0))
    self.maxCoord = maxCoord
    self.construct(self.head, segments)

  def construct(self, top, segments):
    front = []
    back = []

    for segment in segments:
      intersection = self.__lineIntersectPoint(top.segment, segment)
      if intersection:
        splitSegments = segment.divide(intersection)
        for splitted in splitSegments:
          isBack = self.__lineCategorizeBack(top.segment, splitted, intersection)
          if isBack:
            back.append(splitted)
          else:
            front.append(splitted)
      else:
        isBack = self.__lineCategorizeBack(top.segment, segment)
        if isBack:
          back.append(segment)
        else:
          front.append(segment)

    if len(front) > 0:
      nextFront = front.pop(0)
      top.front = BSPNode(nextFront)
      self.construct(top.front, front)

    if len(back):
      nextBack = back.pop(0)
      top.back = BSPNode(nextBack)
      self.construct(top.back, back)

  def __lineIntersectionT(self, begin1, end1, begin2, end2):
    ex = end1[0] - begin1[0]
    ey = end1[1] - begin1[1]
    fx = end2[0] - begin2[0]
    fy = end2[1] - begin2[1]
    px = -ey
    py = ex

    inter = fx*px + fy*py
    if inter == 0:
      return None

    nx = (begin1[0] - begin2[0]) * px
    ny = (begin1[1] - begin2[1]) * py

    ret = float((nx + ny)) / inter
    return ret

  def __isBetween(self, start, end, inter):
    isx = inter[0] - start[0]
    isy = inter[1] - start[1]
    esx = end[0] - start[0]
    esy = end[1] - start[1]

    cross = isy*esx - isx*esy
    if cross == 0:
      return False

    dot = isx*esx + isy*esy
    if dot < 0:
      return False

    length = esx*esx + esy*esy
    if dot > length:
      return False

    return True

  def __lineIntersectPoint(self, seg1, seg2):
    t1 = self.__lineIntersectionT(seg1.begin, seg1.end, seg2.begin, seg2.end)
    t2 = self.__lineIntersectionT(seg2.begin, seg2.end, seg1.begin, seg1.end)

    if not t1 or not t2:
      return

    ix = seg2.facX(t1)
    iy = seg2.facY(t1)
    iat = (ix, iy)
    intersectsPast = ix >= 0 and ix <= self.maxCoord and iy >= 0 and iy <= self.maxCoord
    intersects = t1 >= 0 and t1 <= 1 and t2 >= 0 and t2 <= 1
    intersectsOther = self.__isBetween(seg2.end, seg2.begin, iat)

    # should we split the segment for the bsp?
    if intersects or (intersectsPast and intersectsOther):
      return iat

    return None

  def __lineCategorizeBack(self, top, seg, possibleIntersection=None):
    if not possibleIntersection or seg.begin == possibleIntersection:
      return self.__lineIsBack(top.begin, top.end, seg.end)
    else:
      return self.__lineIsBack(top.begin, top.end, seg.begin)

  def __lineIsBack(self, begin, end, facing):
    segox = end[0] - begin[0]
    segoy = end[1] - begin[1]
    fox = facing[0] - begin[0]
    foy = facing[1] - begin[1]
    cross = (segox * foy) - (segoy * fox)
    segop = segox > 0
    side = cross < 0 if segop else cross > 0
    return side

  def printTree(self):
    print '### Example ###'
    print '----|Front'
    print 'Root'
    print '----|Behind'
    print
    print '### Result ###'
    self.printTreeRecurse(self.head)

  def printTreeRecurse(self, top, depth=0):
    if not top:
      return
    self.printTreeRecurse(top.front, depth + 1)
    for i in xrange(depth):
      print '----|',
    print top.segment.color
    self.printTreeRecurse(top.back, depth + 1)
