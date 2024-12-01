# frozen_string_literal: true

require './scripts/core/core.rb'


class Story
  attr_reader :scenes, :characters
  attr_accessor :state

  def initialize(&block)
    @scenes = {}
    @characters = {}
    @current_scene = nil
    instance_eval(&block)
  end


  def scene(name, &block)
    @current_scene = name
    @scenes[name] = { choices: {}, timeline: [], continue: nil}
    instance_eval(&block)
  end

  def description(text = nil, &block)
    content = block_given? ? block : text
    @scenes[@current_scene][:timeline] << content
  end

  def choice(text, next_scene, &block)
    @scenes[@current_scene][:choices][text] = { next_scene: next_scene, action: block }
  end

  def continue(next_scene)
    @scenes[@current_scene][:continue] = next_scene
  end

  def character(name, display_name, color)
    @characters[name] = { name: display_name, color: color }
  end

  def dialogue(character, text = nil, &block)
    content = block_given? ? block : text
    @scenes[@current_scene][:timeline] << { character: character, text: content }
  end
end

def create_story(&block)
  Story.new(&block)
end

# Load the story file and store the created story in a global variable
def load_story(filename)
  story_content = File.read(filename)
  $story = eval(story_content)
end

def get_story
  $story
end
