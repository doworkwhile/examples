import Tkinter
from undirected_graph import UndirectedGraph
from canvas_image_player import CanvasImagePlayer
from player_graph_path import Path
import random

### Config
cellSize = 30
halfCellSize = cellSize / 2
cells = 10
cellOffset = 1
width = cellSize * cells
height = cellSize * cells
canvasWidth = width + 1
canvasHeight = height + 1
canvasBG = "white"
targetBG = "red"
blockedBG = "black"
playerImgSrc = "bug.png"
moveSpeedMS = 100
blockCount = 10

### TK & Canvas
top = Tkinter.Tk()
C = Tkinter.Canvas(top, bg=canvasBG, height=canvasHeight, width=canvasWidth)
top.resizable(False, False)

### Player
player = CanvasImagePlayer(C, playerImgSrc, (cellSize, cellSize), cellOffset)

### Grid
rects = []
for x in xrange(cells):
  rects.append([])
  for y in xrange(cells):
    newX = cellOffset + (x * cellSize)
    newY = cellOffset + (y * cellSize)
    newX2 = newX + cellSize
    newY2 = newY + cellSize
    newRect = C.create_rectangle(newX, newY, newX2, newY2)
    rects[x].append(newRect)

### Graph
ug = UndirectedGraph()
possibleBlocks = random.sample(xrange(1, cells * cells), blockCount)
blocked = [(i % cells, i / cells) for i in possibleBlocks]
# create graph paths
for x in xrange(cells):
  for y in xrange(cells):
    if not (x, y) in blocked:
      if x + 1 < cells and not (x + 1, y) in blocked:
        ug.addPath((x, y), (x + 1, y), 1)
      if x - 1 >= 0 and not (x - 1, y) in blocked:
        ug.addPath((x, y), (x - 1, y), 1)
      if y + 1 < cells and not (x, y + 1) in blocked:
        ug.addPath((x, y), (x, y + 1), 1)
      if y - 1 >= 0 and not (x, y - 1) in blocked:
        ug.addPath((x, y), (x, y - 1), 1)
# change the fill of the blocked grid locations
for block in blocked:
  C.itemconfig(rects[block[0]][block[1]], fill=blockedBG)

### Pathing
path = Path(player, ug)

### Movement
def scheduleMovement():
  top.after(moveSpeedMS, doMovement)

def doMovement():
  if path.canMove():
    path.doMove()
  else:
    if path.end:
      C.itemconfig(rects[path.end[0]][path.end[1]], fill=canvasBG)
    path.newPath()
    C.itemconfig(rects[path.end[0]][path.end[1]], fill=targetBG)
  scheduleMovement()

scheduleMovement()

### Final Pack
C.pack()

### Start
top.mainloop()
