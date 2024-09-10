# frozen_string_literal: true

# class Hash
#   def << (hash)
#     hash.keys.each { |key|
#       self[key] += hash[key]
#     }
#   end
# end

$x = 1
$y = 150
$down = true
def on_create(args)
  args[:load][:sprite][:reckoning2] = "sprites/thereckoningv2.png"
  args[:load][:sprite][:reckoning] = "sprites/thereckoning.png"
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
    name: :reckoning,
    x: $x,
    y: $x,
    w: $x,
    h: $x,
  }
  args[:out] << {
    name: :reckoning2,
    x: 150,
    y: $y,
    w: $y,
    h: $y,
  }
  args[:out] << {
    name: :reckoning2,
    x: 200,
    y: $x,
    w: $x,
    h: $x,
  }
end

