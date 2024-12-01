//
// Created by novel on 11/30/2024.
//

#include "MRubyUtils.h"

#include <mruby/string.h>
#include <mruby/hash.h>
#include <mruby/array.h>
#include <iostream>

MRubyUtils::MRubyUtils(mrb_state* mrb) : mrb(mrb) {}

std::string MRubyUtils::get_string(mrb_value value) {
    return mrb_str_to_cstr(mrb, value);
}

mrb_value MRubyUtils::call_method(mrb_value obj, const char* method, int argc, mrb_value* argv) {
    return mrb_funcall_argv(mrb, obj, mrb_intern_cstr(mrb, method), argc, argv);
}

int MRubyUtils::array_length(mrb_value array) {
    return RARRAY_LEN(array);
}

mrb_value MRubyUtils::array_entry(mrb_value array, int index) {
    return mrb_ary_entry(array, index);
}

mrb_value MRubyUtils::get_hash_value(mrb_value hash, const char* key) {
    return mrb_hash_get(mrb, hash, mrb_symbol_value(mrb_intern_cstr(mrb, key)));
}

mrb_value MRubyUtils::get_hash_value(mrb_value hash, mrb_value key)
{
    return mrb_hash_get(mrb, hash, key);
}

mrb_value MRubyUtils::hash_keys(mrb_value hash) {
    return mrb_hash_keys(mrb, hash);
}

bool MRubyUtils::hash_empty(mrb_value hash) {
    return mrb_hash_empty_p(mrb, hash);
}

bool MRubyUtils::is_nil(mrb_value value) {
    return mrb_nil_p(value);
}

const char* MRubyUtils::symbol_name(mrb_value symbol) {
    return mrb_sym_name(mrb, mrb_symbol(symbol));
}

std::string MRubyUtils::mrb_vtype_to_string(mrb_vtype type) {
    switch (type) {
        case MRB_TT_FALSE: return "MRB_TT_FALSE";
        case MRB_TT_TRUE: return "MRB_TT_TRUE";
        case MRB_TT_FLOAT: return "MRB_TT_FLOAT";
        case MRB_TT_INTEGER: return "MRB_TT_INTEGER";
        case MRB_TT_SYMBOL: return "MRB_TT_SYMBOL";
        case MRB_TT_UNDEF: return "MRB_TT_UNDEF";
        case MRB_TT_CPTR: return "MRB_TT_CPTR";
        case MRB_TT_FREE: return "MRB_TT_FREE";
        case MRB_TT_OBJECT: return "MRB_TT_OBJECT";
        case MRB_TT_CLASS: return "MRB_TT_CLASS";
        case MRB_TT_MODULE: return "MRB_TT_MODULE";
        case MRB_TT_ICLASS: return "MRB_TT_ICLASS";
        case MRB_TT_SCLASS: return "MRB_TT_SCLASS";
        case MRB_TT_PROC: return "MRB_TT_PROC";
        case MRB_TT_ARRAY: return "MRB_TT_ARRAY";
        case MRB_TT_HASH: return "MRB_TT_HASH";
        case MRB_TT_STRING: return "MRB_TT_STRING";
        case MRB_TT_RANGE: return "MRB_TT_RANGE";
        case MRB_TT_EXCEPTION: return "MRB_TT_EXCEPTION";
        case MRB_TT_ENV: return "MRB_TT_ENV";
        case MRB_TT_DATA: return "MRB_TT_DATA";
        case MRB_TT_FIBER: return "MRB_TT_FIBER";
        case MRB_TT_ISTRUCT: return "MRB_TT_ISTRUCT";
        case MRB_TT_BREAK: return "MRB_TT_BREAK";
        case MRB_TT_COMPLEX: return "MRB_TT_COMPLEX";
        case MRB_TT_RATIONAL: return "MRB_TT_RATIONAL";
        case MRB_TT_BIGINT: return "MRB_TT_BIGINT";
        default: return "Unknown Type";
    }
}

void MRubyUtils::print_mrb_value_type(mrb_value value) {
    mrb_vtype type = mrb_type(value);
    std::cout << "Value type: " << mrb_vtype_to_string(type) << std::endl;
}

void MRubyUtils::print_error()
{
    mrb_print_error(mrb);
}

void MRubyUtils::print_backtrace()
{
    mrb_print_backtrace(mrb);
}

int MRubyUtils::gc_arena_save() {
    return mrb_gc_arena_save(mrb);
}

void MRubyUtils::gc_arena_restore(int idx) {
    mrb_gc_arena_restore(mrb, idx);
}
