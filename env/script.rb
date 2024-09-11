# frozen_string_literal: true

require './scripts/core/core.rb'

$x = 1
$y = 150
$down = true
def on_create(args)
  args[:load][:sprite][:reckoning2] = "sprites/thereckoningv2.png"
  args[:load][:sprite][:reckoning] = "sprites/thereckoning.png"
  args[:load][:font][:creato] = ["fonts/CreatoDisplay-Regular.otf", 30]
end

def handle_events(args)

end

def update(args)
  if $down
    $x += 1
    $y -= 1
  else
    $x -= 1
    $y += 1
  end

  if $x < 0
    $down = true
  elsif $x > 150
    $down = false
  end
end

def render(args)
  args[:out] << {
    sprite: :reckoning,
    x: $x,
    y: $x,
    w: $x,
    h: $x,
  }
  args[:out] << {
    sprite: :reckoning2,
    x: 150,
    y: $y,
    w: $y,
    h: $y,
  }
  args[:out] << {
    sprite: :reckoning2,
    dest: Rect.new(200, $x, $x, $x).to_a
  }

  args[:out] << {
    font: :creato,
    color: Color.new(0, 0, 0).to_a,
    x: 30,
    y: 30,
    text: "FPS: %.2f" % args[:in][:fps]
  }

end

