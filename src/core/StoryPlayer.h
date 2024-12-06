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

struct ChoiceData {
    mrb_value choice_keys;
    mrb_value choices;
};

class StoryPlayer {
private:
    MRubyUtils mrb_utils;
    mrb_value story;
    mrb_value scenes;
    mrb_value characters;
    std::string current_scene;
    int current_timeline_index = 0;
    ChoiceData current_choice_data;

    bool has_more_entries();
    void handle_current_entry();
    void PostTimeline();
    bool handle_continue(mrb_value scene);
    void handle_choices(mrb_value scene);


public:
    std::unordered_map<std::string, std::string> currentDisplay{};
    std::vector<std::string> currentChoices{};
    bool shouldContinue;

    StoryPlayer(mrb_state* mrb, mrb_value story);
    bool play();
    void set_scene(std::string new_scene);
    bool update();
    void post_choice(int choice);


};


#endif //EKUN_STORYPLAYER_H
