

slide = Slide.new
slide.update_block do |args|

end

slide.render_block do |args|
  args[:out] << {
    font: :creato_title,
    color: Color.new(0, 0, 0).to_a,
    x: 50,
    y: 50,
    text: "MIDSTONE"
  }

  args[:out] << {
    font: :creato_body,
    color: Color.new(0, 0, 0).to_a,
    x: 50,
    y: 150,
    w: 500,
    text: "We want to create a visual novel about a bunch of people that dont die, and nothing messed up happens"
  }


end


$slides << slide