import Tkinter
import random
import math
from segment import Segment
from bsp_tree import BSPTree

### SETUP

# maximum window size
maxCoord = 480

# starting segment count
segmentCount = 5
segments = []

# random segments
# (this can produce broken segments which trigger a 'divide by 0')
for i in xrange(segmentCount):
  randX1 = random.randrange(maxCoord)
  randY1 = random.randrange(maxCoord)
  randX2 = random.randrange(maxCoord)
  randY2 = random.randrange(maxCoord)
  randCoord1 = (randX1, randY1)
  randCoord2 = (randX2, randY2)
  segment = Segment(randCoord1, randCoord2)
  segments.append(segment)

### TK

# create root and canvas
root = Tkinter.Tk()
C = Tkinter.Canvas(root, height=maxCoord, width=maxCoord)
root.resizable(False, False)

# run calculations
bspt = BSPTree(segments, maxCoord)


# print/draw the nodes
bspt.printTree()

def drawTree(top):
  if not top:
    return

  drawNode(top)
  drawTree(top.front)
  drawTree(top.back)

def drawNode(top):
  s = top.segment

  # draw segment
  C.create_line(s.x1(), s.y1(), s.x2(), s.y2(), fill=s.color)

  # draw front/back indicator at midpoint
  mx = s.midX()
  my = s.midY()
  deg = math.degrees(math.atan(s.slope_inv()))
  real_deg = 90 + deg # down
  # real_deg = -90 + deg # up
  rads = math.radians(real_deg)
  mx2 = 10 * math.cos(rads)
  my2 = 10 * math.sin(rads)
  C.create_line(mx, my, mx + mx2, my + my2, fill=s.color)

drawTree(bspt.head)

# final canvas pack
C.pack()

# key binds
root.bind('<Escape>', lambda e: root.destroy())
root.bind('<Control-c>', lambda e: root.destroy())

# main loop
root.mainloop()
