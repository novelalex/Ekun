$title = {}
$heading = {}

# ---------   Slide 0     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :creato_title,
    color: Color.new(0, 0, 0).to_a,
    x: args[:in][:window][:w] / 2,
    y: args[:in][:window][:h] / 2 - 30,
    centered: true,
    text: "Welcome to [GAME]"
  }
  args[:out] << {
    font: :h2,
    color: Color.new(60, 60, 60).to_a,
    x: args[:in][:window][:w] / 2,
    y: args[:in][:window][:h] / 2 + 40,
    centered: true,
    text: "Developed by Matthew and Novel"
  }
end
$slides << slide

# ---------   Slide 1     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :h2,
    color: Color.new(0, 0, 0).to_a,
    x: 120,
    y: 70,
    text: "Game Idea"
  }
  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 150,
    text: "We're making a 2D/3D hybrid visual novel(VN)."
  }
  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 210,
    w: 1000,
    text: "VN's are interactive, story based games that are told through the first person narrative."
  }

  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 300,
    w: 1000,
    text: "Players can make decisions on how the story goes through interactive choices."
  }

  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 390,
    w: 1000,
    text: "Players will be guided through the story and will affect how characters interact."
  }

end
$slides << slide

# ---------   Slide 2     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :h2,
    color: Color.new(0, 0, 0).to_a,
    x: 120,
    y: 70,
    text: "Story Concept"
  }
  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 150,
    w: 1100,
    text: "The game's story is our take on classic murder mystery stories, and we were inspired by games like Steins;Gate, a popular sci-fi VN, and Danganronpa, an murder mystery adventure VN."
  }

  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 300,
    w: 1100,
    text: "We've combined the storytelling of Steins;Gate with Danganronpa's infamous first person 3D gameplay, which allows players to roam around and break from the standard click-through-story gameplay of a regular visual novel."
  }

  danganronpa_scale_factor = 0.5
  steins_scale_factor = 0.2
  args[:out] << {
    sprite: :danganronpa,
    dest: Rect.new(200, 450, 640 * danganronpa_scale_factor, 360 * danganronpa_scale_factor)
  }

  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 360,
    y: 650,
    centered: true,
    text: "Danganronpa: Trigger Happy Havoc (2010)"
  }

  args[:out] << {
    sprite: :steins,
    dest: Rect.new(750, 450, 1800 * steins_scale_factor, 900 * steins_scale_factor)
  }

  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 930,
    y: 650,
    centered: true,
    text: "Steins;Gate (2009)"
  }

end
$slides << slide

# ---------   Slide 3     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :h2,
    color: Color.new(0, 0, 0).to_a,
    x: 120,
    y: 70,
    text: "Gameplay"
  }
  args[:out] << {
    font: :h3,
    color: Color.grayscale(100).to_a,
    x: 120,
    y: 150,
    text: "Visual Novel Sections"
  }

  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 200,
    w: 500,
    text: "The visual novel sections are used for the first initial section of the game to adjust players into the usual visual \
novel format. We also use this format to save a bit of time on art production."
  }
  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 330,
    w: 500,
    text: "This section is the most basic of the game in which players are shown dialogue/thoughts at the bottom of the \
screen, an small text above to indicate the speaker, the 2D background setting, and the a sprite of the characters. \
Players advance the story by clicking the text, or pressing a button."
  }
  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 500,
    w: 500,
    text: "Players are occasionally given choices that can direct the story and increase the game's \"friendship meter\""
  }

  args[:out] << {
    font: :h3,
    color: Color.grayscale(100).to_a,
    x: 670,
    y: 150,
    text: "Exploration Sections"
  }

  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 670,
    y: 200,
    w: 500,
    text: "The main portion of the game sees players roaming and exploring a 3D environment. Within the environment, \
players can interact with characters, and other things in the world. The characters remain as 2D sprites that face the player.
"
  }
  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 670,
    y: 350,
    w: 500,
    text: "This section is the most basic of the game in which players are shown dialogue/thoughts at the bottom of the \
screen, an small text above to indicate the speaker, the 2D background setting, and the a sprite of the characters. \
Players advance the story by clicking the text, or pressing a button."
  }
  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 670,
    y: 520,
    w: 500,
    text: "Players are occasionally given choices that can direct the story and increase the game's \"friendship meter\""
  }

end
$slides << slide

# ---------   Slide 4     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :h2,
    color: Color.new(0, 0, 0).to_a,
    x: 120,
    y: 70,
    text: "Story"
  }
  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 130,
    y: 130,
    w: 500,
    text: "Our story primarily takes place on a train and we follow our main characters as they try to get off the \
train before their last stop."
  }
  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 130,
    y: 230,
    w: 500,
    text: "The story is broken down into a 5 act structure with a prologue and epilogue, with each chapter representing \
Kubler-Ross' five stages of grief."
  }

  args[:out] << {
    font: :p,
    color: Color.new(100, 100, 100).to_a,
    x: 130,
    y: 330,
    w: 500,
    text: "Our story is also built for replayability with a major component requiring players to rebuild \
relationships with characters in order to achieve the true ending."
  }

  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 700,
    y: 130,
    w: 500,
    text: "Chapter I - Denial\n\nChapter II - Anger\n\nChapter III - Bargaining\n\nChapter IV - Depression\n\nChapter V - Acceptance"
  }
end
$slides << slide

# ---------   Slide 5     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :creato_title,
    color: Color.new(0, 0, 0).to_a,
    x: args[:in][:window][:w] / 2,
    y: args[:in][:window][:h] / 2,
    centered: true,
    text: "Story Breakdown"
  }
end
$slides << slide


# ---------   Slide 6     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :h2,
    color: Color.new(0, 0, 0).to_a,
    x: 120,
    y: 70,
    text: "Prologue"
  }

  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 150,
    w: 1100,
    text: "During the prologue, characters are introduced to our main character, and the rest of the cast of characters. Players discover more of the characters, and begin developing relationships with the other characters. In an instant, the train changes, and our main cast of characters discover that they're the only ones on the train, and no longer on the same train that they originally boarded. The characters find the train's driver dead in the washroom."  }

end
$slides << slide

# ---------   Slide 7     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :h2,
    color: Color.new(0, 0, 0).to_a,
    x: 120,
    y: 70,
    text: "Chapter 1"
  }

  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 150,
    w: 1100,
    text: "The characters all accuse each other of killing the driver, while all trying to make sense of what's going on. The group argues with each other, some trying to calm other people down, some are freaking out about the situation, and the group blames our main character for the engineer's murder."  }

end
$slides << slide

# ---------   Slide 8     ---------

slide = Slide.new
slide.render do |args|
  args[:out] << {
    font: :h2,
    color: Color.new(0, 0, 0).to_a,
    x: 120,
    y: 70,
    text: "Chapter 2"
  }

  args[:out] << {
    font: :h3,
    color: Color.new(100, 100, 100).to_a,
    x: 120,
    y: 150,
    w: 1100,
    text: "All five characters go their separate ways, and the main character tries to reason with them, and get them back together. They discuss the situation, as the main character works to regain everyone's sanity and memories. They return to the engineer's body to discover the body missing. They argue once more to figure out who moved the body, and find a recent stamp on a cleaning duties chart.
"  }

end
$slides << slide