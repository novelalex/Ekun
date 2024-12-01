create_story do
  character :wizard, "Wizzo the Wizard", :blue
  character :tarnished, "Tarnished", :green


  scene :start do
    description "You are at a crossroad in a forest."
    dialogue :tarnished, "Which path should I take?"
    choice "Take the left path", :left_path
    choice "Take the right path", :right_path
    choice "Take the cookie path", :cookie_path
  end


  @count = 0
  scene :cookie_path do
    description do "There is a cookie, you have #{@count} cookies" end
    choice "Click the cookie", :cookie_path do
      @count += 1
    end
    choice "Leave", :start
  end

  scene :left_path do
    description "You encounter a wise old wizard."
    dialogue :wizard do "Greetings, traveler with #{@count} cookies" end
    dialogue :tarnished, "Where do i gooo?"
    choice "Ask for advice", :wizard_advice
    choice "Ignore and continue", :mountain
  end

  scene :right_path do
    description "You come across a river."
    dialogue :tarnished, "This river looks funny. What should I do?"
    choice "Try to swim across", :river_swim
    choice "Look for a bridge", :river_bridge
  end

  scene :wizard_advice do
    description "The wizard tells you about a hidden treasure in the mountain."
    dialogue :wizard, "Tharr be treasure"
    dialogue :tarnished, "Thank you!"
    description "You think that the wizard might actually be a pirate"
    choice "Search for the treasure", :mountain
    choice "Thank him and leave", :forest_exit
  end

  scene :mountain do
    description "You find the treasure chest!"
    dialogue :tarnished, "I can't believe it!"
    description "In front of you is a gold chest"
    continue :one_piece
  end

  scene :river_swim do
    description "The current is too strong. You're cant swim."
    dialogue :tarnished, "Help! I'm drowning!"
  end

  scene :river_bridge do
    description "You find a bridge and cross the river."
    choice "Continue your journey", :forest_exit
  end


  scene :forest_exit do
    description "You left the forest."
    dialogue :tarnished, "I need to sleep."
  end

  scene :one_piece do
    description "You've successfully found the one piece."
    dialogue :tarnished, "THE ONE PIECE IS REAL!!!!"
  end

end