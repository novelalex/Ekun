//
// Created by novel on 11/30/2024.
//

#include "StoryPlayer.h"

#include <iostream>
#include <map>

#define MRUBY_GC_START //int mruby_gc_arena_index = mrb_utils.gc_arena_save();
#define MRUBY_GC_STOP //mrb_utils.gc_arena_restore(mruby_gc_arena_index)

StoryPlayer::StoryPlayer(mrb_state *mrb, mrb_value story) : mrb_utils(mrb), story(story), shouldContinue(false) {
    scenes = mrb_utils.call_method(story, "scenes");
    characters = mrb_utils.call_method(story, "characters");
    current_scene = "start";
    currentDisplay["type"] = "none";
}

void StoryPlayer::set_scene(std::string new_scene) {
    current_scene = new_scene;
    current_timeline_index = 0;
}

bool StoryPlayer::handle_continue(mrb_value scene) {
    mrb_value cont = mrb_utils.get_hash_value(scene, "continue");
    if (!mrb_utils.is_nil(cont)) {

        set_scene(mrb_utils.symbol_name(cont));
        return true;
    }
    return false;
}

void StoryPlayer::handle_choices(mrb_value scene) {
    mrb_value choices = mrb_utils.get_hash_value(scene, "choices");
    mrb_value choice_keys = mrb_utils.hash_keys(choices);
    int choices_len = mrb_utils.array_length(choice_keys);

    for (int i = 0; i < choices_len; i++) {
        mrb_value choice = mrb_utils.array_entry(choice_keys, i);
        std::cout << i + 1 << ". " << mrb_utils.get_string(choice) << std::endl;
    }

    int choice;
    do {
        std::cout << "Choose your action (1-" << choices_len << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > choices_len);

    mrb_value chosen_key = mrb_utils.array_entry(choice_keys, choice - 1);
    mrb_value choice_map = mrb_utils.get_hash_value(choices, chosen_key);

    mrb_value choice_block = mrb_utils.get_hash_value(choice_map, "action");
    if (!mrb_utils.is_nil(choice_block)) {
        mrb_utils.call_method(choice_block, "call", 0);
        mrb_utils.print_error();
    }
    set_scene(mrb_utils.symbol_name(mrb_utils.get_hash_value(choice_map, "next_scene")));
}

bool StoryPlayer::play() {

    //clear_screen();
    //mrb_utils.print_mrb_value_type(scenes);
    mrb_utils.print_error();
    mrb_utils.print_backtrace();

    mrb_value scene = mrb_utils.get_hash_value(scenes, current_scene.c_str());
    if (mrb_type(scene) == MRB_TT_FALSE) {
        std::cout << "[ERROR] :" << current_scene << " is not defined as a scene.\n";
    }
    mrb_utils.print_error();
    mrb_utils.print_backtrace();
    // print_description(scene);
    bool result = update();

    mrb_value choices = mrb_utils.get_hash_value(scene, "choices");
    mrb_value cont = mrb_utils.get_hash_value(scene, "continue");

    mrb_utils.print_error();
    mrb_utils.print_backtrace();
    if (mrb_utils.hash_empty(choices) && mrb_utils.is_nil(cont)) {
        std::cout << "The End." << std::endl;
        return result;
    }

    mrb_utils.print_error();
    mrb_utils.print_backtrace();
    if (handle_continue(scene)) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return result;
    }
    mrb_utils.print_error();
    mrb_utils.print_backtrace();
    handle_choices(scene);
    return result;
}


bool StoryPlayer::has_more_entries() {
    MRUBY_GC_START;
    mrb_value scene = mrb_utils.get_hash_value(scenes, current_scene.c_str());
    mrb_value timeline = mrb_utils.get_hash_value(scene, "timeline");
    size_t timeline_len = mrb_utils.array_length(timeline);
    MRUBY_GC_STOP;
    return current_timeline_index < timeline_len;
}

void StoryPlayer::handle_current_entry() {
    mrb_utils.print_error();
    mrb_utils.print_backtrace();
    MRUBY_GC_START;
    mrb_value scene = mrb_utils.get_hash_value(scenes, current_scene.c_str());
    mrb_value timeline = mrb_utils.get_hash_value(scene, "timeline");
    mrb_value line = mrb_utils.array_entry(timeline, current_timeline_index);

    if (mrb_type(line) == MRB_TT_STRING) {
        //std::cout << mrb_utils.get_string(line) << std::endl;
        currentDisplay.clear();
        currentDisplay["type"] = "description";
        currentDisplay["text"] = mrb_utils.get_string(line);
        MRUBY_GC_STOP;
        return;
    }

    if (mrb_type(line) == MRB_TT_PROC) {
        mrb_value display_str = mrb_utils.call_method(line, "call");
        //std::cout << mrb_utils.get_string(display_str) << std::endl;
        // TODO: Build the currentDisplay Map for dynamic text
        currentDisplay.clear();
        currentDisplay["type"] = "description";
        currentDisplay["text"] = mrb_utils.get_string(display_str);
        MRUBY_GC_STOP;
        return;
    }

    mrb_value character_sym = mrb_utils.get_hash_value(line, "character");
    mrb_value text = mrb_utils.get_hash_value(line, "text");

    if (mrb_type(text) == MRB_TT_PROC) {
        text = mrb_utils.call_method(text, "call");
    }
    mrb_value character = mrb_utils.get_hash_value(characters, character_sym);
    mrb_value char_name = mrb_utils.get_hash_value(character, "name");
    mrb_value char_color = mrb_utils.get_hash_value(character, "color");

    /*std::string colored_text = color_text(
            mrb_utils.get_string(char_name) + ": \"" + mrb_utils.get_string(text) + "\"",
            mrb_utils.get_string(mrb_utils.call_method(char_color, "to_s"))
    );
    std::cout << colored_text << std::endl;
     */
    // TODO: Figure out a new way to color text
    currentDisplay.clear();
    currentDisplay["type"] = "dialogue";
    currentDisplay["character"] = mrb_utils.get_string(char_name);
    currentDisplay["text"] = mrb_utils.get_string(text);
    MRUBY_GC_STOP;
}

bool StoryPlayer::update() {
    if (!has_more_entries()) return false;

    handle_current_entry();
    current_timeline_index++;
    return true;
}

