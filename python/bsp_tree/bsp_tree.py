import Tkinter
import tk_colors
import random
import math
from segment import Segment

### SETUP

# maximum window size
maxCoord = 480

segmentCount = 4
segments = []

# random segments
for i in xrange(segmentCount):
  randX1 = random.randrange(maxCoord)
  randY1 = random.randrange(maxCoord)
  randX2 = random.randrange(maxCoord)
  randY2 = random.randrange(maxCoord)
  randCoord1 = (randX1, randY1)
  randCoord2 = (randX2, randY2)
  segment = Segment(randCoord1, randCoord2)
  segments.append(segment)

### Helper Methods

# rotate and array
def rotateAry(ary):
  ary.append(ary.pop(0))

# get a new color and rotate the color array
def color_and_rotate():
  ret = tk_colors.COLORS[0]
  rotateAry(tk_colors.COLORS)
  return ret

# find the intersection of 2 lines with 2 segments endpoints
def lineIntersectionT(begin1, end1, begin2, end2):
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

 # check if point inter is between points start and end
def isBetween(start, end, inter):
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

# get seg1 to split seg2 at their intersection, if the intersection is valid
def segseg(canvas, seg1, seg2):
  t1 = lineIntersectionT(seg1.begin, seg1.end, seg2.begin, seg2.end)
  t2 = lineIntersectionT(seg2.begin, seg2.end, seg1.begin, seg1.end)

  if not t1 or not t2:
    return

  ix = seg2.facX(t1)
  iy = seg2.facY(t1)
  iat = (ix, iy)
  intersectsPast = ix >= 0 and ix <= maxCoord and iy >= 0 and iy <= maxCoord
  intersects = t1 >= 0 and t1 <= 1 and t2 >= 0 and t2 <= 1
  intersectsOther = isBetween(seg2.end, seg2.begin, iat)

  # should we split the segment for the bsp?
  if intersects or (intersectsPast and intersectsOther):
    print seg1.color, 'intersects', seg2.color
    print 'split', seg2.color, 'at', iat
    canvas.create_rectangle(ix - 2, iy - 2, ix + 2, iy + 2)
    canvas.delete(seg2.line)
    canvas.delete(seg2.midline)
    newSegs = seg2.divide(iat)
    print 'into',
    for seg in newSegs:
      seg.color = color_and_rotate()
      print seg.color, ',',
      seg.line = canvas_seg(canvas, seg)
      seg.midline = canvas_seg_mid(canvas, seg)
    print

# create a canvas line from a segment
def canvas_seg(canvas, seg):
  return C.create_line(seg.x1(), seg.y1(),
    seg.x2(), seg.y2(), fill=seg.color)

# with segment begin->end, on which side is face?
def which_side(begin, end, face):
  segox = end[0] - begin[0]
  segoy = end[1] - begin[1]
  fox = face[0] - begin[0]
  foy = face[1] - begin[1]
  cross = (segox * foy) - (segoy * fox)
  segop = segox > 0
  side = cross < 0 if segop else cross > 0
  return side

# draw a line at the midpoint indicating which way the segment is facing
def canvas_seg_mid(canvas, segment):
  # test facing 0
  face = (0, 0)

  segMidX = segment.midX()
  segMidY = segment.midY()

  # segment slope degrees horiz is 0, rot clock is +deg else -deg
  deg = math.degrees(math.atan(segment.slope_inv()))

  # dot product of begin->end and begin->face vecs
  side = which_side(segment.begin, segment.end, face)

  # turn direction based on facing side
  ad_ndeg = 90 + deg # down
  cb_ndeg = -90 + deg # up
  real_deg = cb_ndeg if side else ad_ndeg
  rads = math.radians(real_deg)
  segMidX2 = 10 * math.cos(rads)
  segMidY2 = 10 * math.sin(rads)

  return canvas.create_line(segMidX, segMidY,
    segMidX + segMidX2, segMidY + segMidY2, fill=segment.color)

### TK

# create root and canvas
root = Tkinter.Tk()
C = Tkinter.Canvas(root, height=maxCoord, width=maxCoord)
root.resizable(False, False)

# draw segments
for segment in segments:
  lineX1 = segment.begin[0]
  lineY1 = segment.begin[1]
  lineX2 = segment.end[0]
  lineY2 = segment.end[1]
  segment.color = color_and_rotate()
  segment.line = canvas_seg(C, segment)
  segment.midline = canvas_seg_mid(C, segment)

# run calculations and redraw segments
rootSeg = segments.pop(0)
print 'root seg is', rootSeg.color

while len(segments) > 0:
  segment = segments.pop(0)
  segseg(C, rootSeg, segment)

# final canvas pack
C.pack()

# key binds
root.bind('<Escape>', lambda e: root.destroy())
root.bind('<Control-c>', lambda e: root.destroy())

# main loop
root.mainloop()
