from PIL import Image, ImageTk

class ImagePlayer:
  def __init__(self, img_src, size):
    self.location = (0, 0)
    self.pilImg = Image.open(img_src).resize(size, Image.ANTIALIAS)
    self.photoImg = ImageTk.PhotoImage(self.pilImg)

  def rotate(self, deg):
    self.pilImg = self.pilImg.rotate(deg)
    self.photoImg = ImageTk.PhotoImage(self.pilImg)

  def rotateLeft(self):
    self.rotate(90)

  def rotateRight(self):
    self.rotate(-90)

  def moveTo(self, newLocation):
    self.location = newLocation
