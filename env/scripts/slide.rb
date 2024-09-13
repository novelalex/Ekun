class Slide
  attr_accessor :on_create_block, :update_block, :render_block
  def initialize
    @on_create_block = nil
    @update_block = nil
    @render_block = nil
  end

  def on_create(&block)
    @on_create_block = block
  end

  def update(&block)
    @update_block = block;
  end

  def render(&block)
    @render_block = block;
  end

end