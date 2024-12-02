//
// Created by novel on 11/30/2024.
//

#ifndef EKUN_STORYPLAYER_H
#define EKUN_STORYPLAYER_H

#include "../scripting/MRubyUtils.h"
#include <string>
#include <unordered_map>

#define MRB_GC_BEGIN int arena_index = mrb_gc_arena_save(mrb)
#define MRB_GC_END

class StoryPlayer {
private:
    MRubyUtils mrb_utils;
    mrb_value story;
    mrb_value scenes;
    mrb_value characters;
    std::string current_scene;
    int current_timeline_index = 0;

    bool has_more_entries();
    void handle_current_entry();
    void PostTimeline();
    bool handle_continue(mrb_value scene);
    void handle_choices(mrb_value scene);

public:
    std::unordered_map<std::string, std::string> currentDisplay{};
    bool shouldContinue;

    StoryPlayer(mrb_state* mrb, mrb_value story);
    bool play();
    void set_scene(std::string new_scene);
    bool update();

};


#endif //EKUN_STORYPLAYER_H
