# frozen_string_literal: true

require './scripts/core/core.rb'

$slide_number = 0
$slides = []

require './scripts/slide.rb'
require './scripts/slides/slide1.rb'

def on_create(args)
  args[:load][:sprite][:reckoning2] = "sprites/thereckoningv2.png"
  args[:load][:sprite][:reckoning] = "sprites/thereckoning.png"
  args[:load][:sprite][:steins] = "sprites/steins.png"
  args[:load][:sprite][:timeline] = "sprites/timeline.png"
  args[:load][:sprite][:choice] = "sprites/choice.png"
  args[:load][:sprite][:danganronpa] = "sprites/danganronpa.png"
  args[:load][:font][:creato_title] = ["fonts/CreatoDisplay-Regular.otf", 70]
  args[:load][:font][:h1] = ["fonts/CreatoDisplay-Regular.otf", 50]
  args[:load][:font][:h2] = ["fonts/CreatoDisplay-Regular.otf", 40]
  args[:load][:font][:h3] = ["fonts/CreatoDisplay-Regular.otf", 30]
  args[:load][:font][:p] = ["fonts/CreatoDisplay-Regular.otf", 20]
  args[:load][:font][:creato_small] = ["fonts/CreatoDisplay-Regular.otf", 10]

  if $slides[$slide_number].on_create_block
    $slides[$slide_number].on_create_block.call(args)
  end
end

def next_slide
  if $slide_number < ($slides.length - 1)
    $slide_number += 1
  end
end

def prev_slide
  if $slide_number > 0
    $slide_number -= 1
  end
end

$prev_scancode = 0
def handle_events(args)
  if args[:in][:keyboard] == 44 and $prev_scancode == 0 # SPACE
    next_slide
  elsif args[:in][:keyboard] == 79 and $prev_scancode == 0 # RIGHT
    next_slide
  elsif args[:in][:keyboard] == 80 and $prev_scancode == 0 # LEFT
    prev_slide
  end

  $prev_scancode = args[:in][:keyboard]
end

def update(args)
  if $slides[$slide_number].update_block
    $slides[$slide_number].update_block.call(args)
  end
end

def print_debug_info(args)
  args[:out] << {
    font: :creato_small, x: 10, y: 10, text: "fps: %.2f" % args[:in][:fps]
  }
  args[:out] << {
    font: :creato_small, x: 10, y: 20, text: "mouse: "
  }
  args[:out] << {
    font: :creato_small, x: 20, y: 30, text: "x: #{args[:in][:mouse][:x]}"
  }
  args[:out] << {
    font: :creato_small, x: 20, y: 40, text: "y: #{args[:in][:mouse][:y]}"
  }
  args[:out] << {
    font: :creato_small, x: 10, y: 50, text: "keyboard: #{args[:in][:keyboard]}"
  }
  args[:out] << {
    font: :creato_small, x: 10, y: 60, text: "slide: #{$slide_number}"
  }
end

def render(args)
  if $slides[$slide_number].render_block
    $slides[$slide_number].render_block.call(args)
  end

  print_debug_info(args)
end

