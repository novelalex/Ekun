class Slide
  attr_accessor :update, :render
  def initialize
    @update = nil
    @render = nil
  end

  def update_block(&block)
    @update = block;
  end

  def render_block(&block)
    @render = block;
  end

end