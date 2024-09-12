
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
end


$slides << slide