# frozen_string_literal: true

require './scripts/core/core.rb'

$slide_number = 0
$slides = []

require './scripts/slides/slide.rb'
require './scripts/slides/slide1.rb'
require './scripts/slides/slide2.rb'
require './scripts/slides/slide3.rb'


def on_create(args)
  args[:load][:sprite][:reckoning2] = "sprites/thereckoningv2.png"
  args[:load][:sprite][:reckoning] = "sprites/thereckoning.png"
  args[:load][:font][:creato_title] = ["fonts/CreatoDisplay-Regular.otf", 70]
  args[:load][:font][:creato_head] = ["fonts/CreatoDisplay-Regular.otf", 40]
  args[:load][:font][:creato_body] = ["fonts/CreatoDisplay-Regular.otf", 20]
end

def next_slide
  if $slide_number < ($slides.length - 1)
    $slide_number += 1
  end
end

$prev_scancode = 0
def handle_events(args)
  #puts args[:in][:keyboard]
  if args[:in][:keyboard] == 44 and $prev_scancode == 0
    next_slide
  end

  $prev_scancode = args[:in][:keyboard]
end

def update(args)
  $slides[$slide_number].update.call(args)
end

def render(args)
  $slides[$slide_number].render.call(args)

  # args[:out] << {
  #   sprite: :reckoning2,
  #   dest: Rect.new(200, $x, $x, $x).to_a
  # }

  # args[:out] << {
  #   font: :creato,
  #   color: Color.new(0, 0, 0).to_a,
  #   x: 30,
  #   y: 30,
  #   text: "FPS: %.2f" % args[:in][:fps]
  # }



end

