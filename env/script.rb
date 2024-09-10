# frozen_string_literal: true

def init(args)
    args[:state][:x] = 1
end

def update(args)
    args[:state][:x] += 1
    puts args[:state][:x]
end

def render(args)
end

