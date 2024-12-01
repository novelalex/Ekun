//
// Created by novel on 11/30/2024.
//

#ifndef EKUN_MRUBYUTILS_H
#define EKUN_MRUBYUTILS_H

#include <mruby.h>
#include <string>
class MRubyUtils {
private:
    mrb_state* mrb;

public:
    MRubyUtils(mrb_state* mrb);

    std::string get_string(mrb_value value);

    mrb_value get_hash_value(mrb_value hash, const char* key);
    mrb_value get_hash_value(mrb_value hash, mrb_value key);


    bool hash_empty(mrb_value hash);
    mrb_value hash_keys(mrb_value hash);

    mrb_value call_method(mrb_value obj, const char* method, int argc = 0, mrb_value* argv = nullptr);

    int array_length(mrb_value array);
    mrb_value array_entry(mrb_value array, int index);

    bool is_nil(mrb_value value);

    const char* symbol_name(mrb_value symbol);

    std::string mrb_vtype_to_string(mrb_vtype type);

    void print_mrb_value_type(mrb_value value);

    void print_error();
    void print_backtrace();

    int gc_arena_save();
    void gc_arena_restore(int idx);

};


#endif //EKUN_MRUBYUTILS_H
