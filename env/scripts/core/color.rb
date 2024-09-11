class Color
  attr_accessor :r, :g, :b, :a
  def initialize(r = 0, g = 0, b = 0, a = 255)
    @r, @g, @b, @a = r, g, b, a
  end
  def to_a
    [@r, @g, @b, @a]
  end
end