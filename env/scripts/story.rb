create_story do
  character :riley, "Riley", "sprites/Riley.png"
  character :elle, "Elle", "sprites/Elle.png"
  character :guide, "Guide", "sprites/Nay.png"
  character :nay, "Nay", "sprites/Nay.png"
  character :bigguy, "Big Guy", "sprites/Jones.png"
  character :nerdygirl, "Nerdy Girl", "sprites/Aya.png"
  character :aya, "Aya", "sprites/Aya.png"
  character :loch, "Loch", "sprites/Untitled_Artwork.png"

  scene :start do
    description "Riley walks up to the station platform, bag in hand."
    description "Of course, as he expected, Elle is nowhere to be found."
    description "Part of him thought this time he could trust her to get her things together and not get lost."
    description "Unfortunately, it seemed like he was needed once again to find the girl."
    description "The biggest mystery in this world..."
    description "is how she manages to find her way out of the front door every morning."
    dialogue :riley, "There isn't much around."
    description "The platform is practically empty, aside from a couple people who might be joining Riley and Elle on the train."
    description "Riley is early though, so it's doubtful he'd see te rest of his peers until he was on the train."
    description "Although Elle isn't at risk of missing the train, he knows Elle is going to cut it close for no reason."
    continue :phone_choice
  end

  scene :phone_choice do
    dialogue :riley, "I've still got some time to kill."
    choice "Look around some more", :look_around
    choice "Call Elle's phone", :call_elle
    choice "Play cookie clicker", :cookie_path
  end

  @count = 0
  scene :cookie_path do
    description do
      "Riley taps the screen, he has #{@count} cookies"
    end
    choice "Tap the cookie", :cookie_path do
      @count += 1
    end
    choice "Leave", :phone_choice
  end

  scene :look_around do
    description "Looking around, Riley can see three people in the station."
    description "There's a large burly dude with a letterman"
    description "There's a smaller girl with blue hair, wearing a bright yellow sweater,"
    description "she seems to be playing a game on a handheld gaming system Riley is familiar with."
    description "There's a lady standing in front of a small table with a bunch of pamphlets and informative imagery on a sign above it."
    dialogue :riley, "That's probably the tour guide."
    choice "Talk to the big guy", :big_guy_interact
    choice "Talk to the tour guide", :tour_guide_interact
    choice "Call Elle's phone", :call_elle
  end

  scene :big_guy_interact do
    dialogue :bigguy, "Yo not right now, I'm listening to my sports podcast."
    dialogue :riley, "Okay then."
    choice "Leave", :look_around
  end

  scene :tour_guide_interact do
    description "Moving closer to the info booth, the tour guide looks pleased as punch to have a chance to do her job."
    dialogue :guide, "Hello!"
    dialogue :guide, "Thank you so much for joining us on this trip!"
    dialogue :nay, "My name is Nay!"
    dialogue :nay, "I'd be happy to answer any questions you have regarding the train, or our destinations for the next 3 days."
    choice "Where are we going?", :destinations
  end

  scene :destinations do
    dialogue :nay, "Well first we're stopping off at the Midleton Distillery experience via a bus from the train's terminal."
    dialogue :nay, "Next, the recently established megarail will conect us to Wales where you'll be able to enjoy some of the scenery."
    dialogue :nay, "That's all we'll be able to cram into the first day."
    dialogue :riley, "Wow!"
    dialogue :nay, "The second day will be more dense with activities."
    dialogue :riley, "Sounds great, thanks!"
    dialogue :nay, "Any other questions?"
    choice "Nothing else for now.", :look_around
  end

  scene :call_elle do
    description "Dialing Elle's number, you get only one ring before you hear someone pick up the phone."
    dialogue :elle, "Hey! Hey! Hey! You will NOT believe all of the cute trinkets they have at the shop!"
    choice "Ask where she is", :elle_phone_reply_one
    choice "Ask what what's in the shop", :elle_phone_reply_two
  end

  scene :elle_phone_reply_one do
    dialogue :riley, "The shop? Isn't the shop before the bag check?"
    dialogue :riley, "Are you telling me you haven't even gone through security yet!"
    dialogue :elle, "Well..."
    dialogue :elle, "like..."
    dialogue :elle, "uh..."
    description "..."
    dialogue :riley, "Elle!"
    dialogue :elle, "Yeah okay, I'm not past security yet..."
    dialogue :elle, "I'll be there soon!"
    dialogue :riley, "*sigh*"
    dialogue :riley, "Alright, just hurry so we don't hold everyone up."
    dialogue :elle, "Okay, okay"
    dialogue :riley, "The train leaves in 30, don't miss it."
    description "As Riley hangs up the phone, he can hear some familiar blips and sounds coming from his right."
    description "He turns and sees the blue haired girl playing on a handheld console."
    description "Riley recognizes the sounds from a game he likes."
    continue :nerdy_girl_interact
  end

  scene :elle_phone_reply_two do
    dialogue :riley, "Oh yeah? What do they have?"
    dialogue :elle, "There's so much stuff!"
    dialogue :elle, "Minature train keychains, train UV lights, UV pens, and a super cute train plushie!"
    dialogue :elle, "I gonna buy it when we get back!"
    dialogue :riley, "Hey, not bad."
    dialogue :riley, "Not to rush you, but we have 30 minutes before the train leaves."
    dialogue :riley, "Make sure you have enough time to get through security."
    dialogue :elle, "Will do! See ya soon!"
    dialogue :tarnished, "I need to sleep."
    description "As Riley hangs up the phone, he can hear some familiar blips and sounds coming from his right."
    description "He turns and sees the blue haired girl playing on a handheld console."
    description "Riley recognizes the sounds from a game he likes."
  end

  scene :nerdy_girl_interact do
    description "Riley walks up to the girl,"
    description "The noise coming from the game, while quiet to most, was crystal clear to him."
    description "She was absolutley playing Monster Hunter, the sound unmistakable."
    dialogue :riley, "So, which weapon do you use?"
    description "The girl looks up at Riley, her eyes going wide."
    description "It's apparent that she wasn't expecting to be asked a topical question, or at least not one pertaining to the game."
    dialogue :nerdygirl, "T-The long sword..."
    dialogue :nerdygirl, "I take it you've played before?"
    dialogue :riley, "Oh yeah, I got it paired with my system."
    dialogue :riley, "I liked the game that came before, so I was excited to try this one out."
    dialogue :nerdygirl, "That's pretty cool."
    dialogue :aya, "I'm Aya"
    dialogue :riley, "Riley."
    dialogue :aya, "You a nature guy?"
    dialogue :riley, "Not really. Came here with a friend, but she's taking her sweet time getting through security."
    dialogue :aya, "I can relate, My friend booked this with me but canceled last second."
    dialogue :aya, "She INSISTED that I should still go, so in the spirit of not wasting money, here I am."
    dialogue :riley, "Well you're more than welcome to join me and Elle, assuming she even makes it on time."
    description "As if on cue, a bubbly girl darts through the entry gate, waving her hand wildly at Riley."
    continue :elle_arrives
  end

  scene :elle_arrives do
    dialogue :elle, "Hello! Sorry I took so long, I was seriously debating on whether or not it was
     responsible to buy the keychain."
    dialogue :rile, "You know what, good job, that shows some restraint."
    dialogue :elle, "It's too bad I'm not responsible."
    dialogue :riley, "i swear to god..."
    dialogue :aya, "Elle, I assume?"
    dialogue :elle, "Yup! do I know you?"
    dialogue :riley, "This is Aya, she'll be joining us."
    dialogue :elle, "Sweet! new friend!"
    description "As Riley, Elle, and Aya chat, a voice comes over the intercom, adivsing people who bought a ticket for the train to begin boarding."
    dialogue :riley, "As per usual, Elle, your timing is suspiciously perfect as ever."
    description "The three move to begin boarding the train."
    continue :boarding_the_train
  end

  scene :boarding_the_train do
    description "After getting their tickets punched, they boarded the train."
    dialogue :riley, "You have everything you need, right Elle?"
    dialogue :elle, "Yup yup! Quintuple checked! No accidents hopefully!"
    description "More and more people fill up the first train car, waiting to be seated."
    dialogue :nay, "Hello! My name is Nay, I'll be your guide for this trip."
    dialogue :nay, "I will be accompanied by two other members of staff for the remainder of the journey."
    dialogue :nay, "Those bieng Jack, our bartender for the refreshments car, and Loch, the conductor."
    dialogue :nay, "If you have any questions, feel free to ask me, or them about anything."
    dialogue :nay, "The train will begin moving shortly but a warning will be given for those who are standing so they aren't swept off their feet."
    description "Riley, Elle, and Aya find a couple seats, claiming them."
    description "Elle looks out the window, pouting as she realizes there isn't much to see looking out into the station since they haven't moved."
    description "Other people begin making their way to their seats, and not long after, the announcement plays throught he speakers."
    description "A loud, monotone voice delcares that the train will be moving in a few seconds, and to sit down if needed."
    continue :prologue_end
  end

  scene :prologue_end do
    description "Riley, Elle, and Aya begin to chat, before their conversation is interrupted by Elle."
    dialogue :elle, "Hey, Riley, let me squeeze by you, I gotta use the bathroom."
    description "Elle quickly shuffles off to shared bathroom."
    description "Aya and Riley begin talking abut their shared intrest in games."
    description "After a couple minutes, a scruffy-haired man walks by"
    dialogue :aya, "Are you the conductor?"
    dialogue :loch, "Oh, hello there, Yeah, that'd be me."
    dialogue :riley, "Is conducting a train hard?"
    dialogue :loch, "Usually, but this one is nearly autonomous."
    dialogue :loch, "She may look old on the outside, but she got the innards of a brand new bullet train."
    dialogue :riley, "Huh neat."
    dialogue :loch, "Quite. Don't mean to cut this short, but I'd rather not soi; myself on the first day here."
    description "Loch quickly shuffles away towards the bathroom."
    description "About 30 minutes pass. Riley notices that Elle hasn't come back yet, so he decides to check on her."
    description "Walking over to the bathroom, he notices the door is ajar."
    dialogue :riley, "Hello? Anyone in here? Being cautious as to not walk in on anyone naked"
    description "after a couple of long seconds without a response, Riley cracks the door open further."
    description "a putrid sight befalls him, as he notices Elle and Loch, both laying on the ground, similarly still."
    description "Riley hesitates, not sure whether to call our for help, or to drop to his knees and attempt first aid."
    description "Riley realizes that it might be pointless."
    description "The colour of their skin..."
    description "The stillness..."
    description "They were both dead."
  end
end