from player import ImagePlayer
from enum import Enum

Ordinals = Enum('Ordinals', 'NORTH EAST SOUTH WEST')

class CanvasImagePlayer():
  def __init__(self, canvas, img_src, size, offset=0):
    self.canvas = canvas
    self.moveSize = size[0]
    self.sizeOffset = offset + (self.moveSize / 2)
    self.player = ImagePlayer(img_src, size)
    self.lastDir = Ordinals.NORTH
    self.canvasImg = None

    self.buildPlayerCanvas()

  def location(self):
    return self.player.location

  def buildPlayerCanvas(self):
    # delete the old image
    if self.canvasImg:
      self.canvas.delete(self.canvasImg)

    # redraw at our location
    locX = (self.location()[0] * self.moveSize) + self.sizeOffset;
    locY = (self.location()[1] * self.moveSize) + self.sizeOffset;
    self.canvasImg = self.canvas.create_image(locX, locY, image=self.player.photoImg)

  def rotateLeft(self):
    self.player.rotateLeft()

  def rotateRight(self):
    self.player.rotateRight()

  def moveTo(self, newLoc):
    if newLoc[0] > self.location()[0]:
      self.moveRight(newLoc)
    elif newLoc[0] < self.location()[0]:
      self.moveLeft(newLoc)
    elif newLoc[1] > self.location()[1]:
      self.moveDown(newLoc)
    elif newLoc[1] < self.location()[1]:
      self.moveUp(newLoc)
    self.buildPlayerCanvas()

  def moveRight(self, newLoc):
    self.player.location = newLoc
    if self.lastDir is Ordinals.NORTH:
      self.rotateRight()
    elif self.lastDir is Ordinals.SOUTH:
      self.rotateLeft()
    elif self.lastDir is Ordinals.WEST:
      self.rotateLeft()
      self.rotateLeft()
    self.lastDir = Ordinals.EAST

  def moveLeft(self, newLoc):
    self.player.location = newLoc
    if self.lastDir is Ordinals.NORTH:
      self.rotateLeft()
    elif self.lastDir is Ordinals.SOUTH:
      self.rotateRight()
    elif self.lastDir is Ordinals.EAST:
      self.rotateRight()
      self.rotateRight()
    self.lastDir = Ordinals.WEST

  def moveUp(self, newLoc):
    self.player.location = newLoc
    if self.lastDir is Ordinals.WEST:
      self.rotateRight()
    elif self.lastDir is Ordinals.EAST:
      self.rotateLeft()
    elif self.lastDir is Ordinals.SOUTH:
      self.rotateLeft()
      self.rotateLeft()
    self.lastDir = Ordinals.NORTH

  def moveDown(self, newLoc):
    self.player.location = newLoc
    if self.lastDir is Ordinals.WEST:
      self.rotateLeft()
    elif self.lastDir is Ordinals.EAST:
      self.rotateRight()
    elif self.lastDir is Ordinals.NORTH:
      self.rotateRight()
      self.rotateRight()
    self.lastDir = Ordinals.SOUTH



