import random

class TKColors:
  COLORS = [
      "white", "gray53", "black",
      "red", "salmon", "hot pink", "deep pink",
      "maroon", "violet red", "medium orchid", "dark violet", "plum3",
      "blue", "turquoise1", "deepskyblue3",
      "yellow", "khaki1",
      "green", "lawn green", "darkgreen", "olivedrab1",
      "thistle"
    ]
  SHUFFLED = False

  @classmethod
  def rotate(klass):
    klass.COLORS.append(klass.COLORS.pop(0))

  @classmethod
  def next(klass):
    if not klass.SHUFFLED:
      random.shuffle(klass.COLORS)
      klass.SHUFFLED = True
    ret = klass.COLORS[0]
    klass.rotate()
    return ret
