from tk_colors import TKColors

class Segment:
  def __init__(self, begin, end):
    self.begin = begin
    self.end = end

    # used as a name, but also for drawing
    self.color = TKColors.next()

  def x1(self):
    return self.begin[0]

  def y1(self):
    return self.begin[1]

  def x2(self):
    return self.end[0]

  def y2(self):
    return self.end[1]

  def xD(self):
    return self.begin[0] - self.end[0]

  def yD(self):
    return self.begin[1] - self.end[1]

  def slope(self):
    return float(self.xD()) / float(self.yD())

  def slope_inv(self):
    return float(self.yD()) / float(self.xD())

  def midX(self):
    return self.facX(0.5)

  def midY(self):
    return self.facY(0.5)

  def mid(self):
    return (self.midX(), self.midY())

  def facX(self, f):
    return int(self.begin[0] - (self.xD() * f))

  def facY(self, f):
    return int(self.begin[1] - (self.yD() * f))

  def divide(self, at):
    return [Segment(self.begin, at), Segment(at, self.end)]

