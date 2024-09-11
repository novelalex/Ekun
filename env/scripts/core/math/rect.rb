class Rect
  attr_accessor :x, :y, :width, :height
  def initialize(x = 0, y = 0, width = 0, height = 0)
    @x, @y, @width, @height = x, y, width, height
  end

  def to_a
    [@x, @y, @width, @height]
  end
end