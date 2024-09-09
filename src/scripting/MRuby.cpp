//
// Created by novel on 2024-09-08.
//

#include <iostream>
#include <fstream>
#include "MRuby.h"
#include "../core/Debug.h"
#include "mruby/compile.h"
#include "mruby/hash.h"
#include "mruby/string.h"
#include "mruby/array.h"

namespace MRB {
    MRuby::MRuby() {
        mrb = mrb_open();
        if (!mrb) {
            std::cerr << "Error opening mruby state" << std::endl;
            exit(1);
        }
    }

    MRuby::~MRuby() {
        mrb_close(mrb);
    }

    std::string MRuby::readFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            Debug::FatalError("No File:", __FILE__, __LINE__);
            exit(1);
        }
        return std::string{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    }

    void MRuby::LoadFile(const std::string &filename) {

    }

    RClass *MRuby::GetClass(const std::string &filename) {
        return mrb_class_get(mrb, filename.c_str());
    }

    rb MRuby::Instantiate(RClass *rClass, int argc = 0, rb *argv = nullptr) {
        return mrb_obj_new(mrb, rClass, argc, argv);
    }

    rb MRuby::CallFunction(rb object, const char *name, int argc = 0, rb *argv = nullptr) {
        return mrb_funcall(mrb, object, name, argc, argv);
    }

    rb MRuby::SymbolValue(const char *sym) {
        return mrb_symbol_value(mrb_intern_cstr(mrb, sym));
    }

    rb MRuby::SymbolValue(mrb_state* mrb, const char *sym) {
        return mrb_symbol_value(mrb_intern_cstr(mrb, sym));
    }

    const char *MRuby::CString(rb str) {
        return mrb_str_to_cstr(mrb, str);
    }

    bool MRuby::IsNil(rb val) {
        return mrb_nil_p(val);
    }

    bool MRuby::IsTrue(rb val) {
        return mrb_true_p(val);
    }

    bool MRuby::IsFalse(rb val) {
        return mrb_false_p(val);
    }


    rb MRuby::NewHash() {
        return mrb_hash_new(mrb);
    }

    rb MRuby::GetHashValue(mrb_value hash, const char *key) {
        return GetHashValue(hash, SymbolValue(key));
    }

    rb MRuby::GetHashValue(mrb_value hash, rb key) {
        return mrb_hash_get(mrb, hash, key);
    }

    rb MRuby::GetHashKeys(rb hash) {
        return mrb_hash_keys(mrb, hash);
    }

    bool MRuby::IsHashEmpty(rb hash) {
        return mrb_hash_empty_p(mrb, hash);
    }

    rb MRuby::HashFetch(rb hash, rb key, rb default_value) {
        return mrb_hash_fetch(mrb, hash, key, default_value);
    }

    rb MRuby::HashDeleteKey(rb hash, rb key) {
        return mrb_hash_delete_key(mrb, hash, key);
    }

    bool MRuby::HashHasKey(rb hash, rb key) {
        return mrb_hash_key_p(mrb, hash, key);
    }

    rb MRuby::GetHashValues(rb hash) {
        return mrb_hash_values(mrb, hash);
    }

    void MRuby::HashClear(rb hash) {
        mrb_hash_clear(mrb, hash);
    }

    size_t MRuby::HashSize(rb hash) {
        return mrb_hash_size(mrb, hash);
    }

    size_t MRuby::ArrayLength(rb array) {
        return RARRAY_LEN(array);
    }

    rb MRuby::ArrayEntry(rb array, size_t index) {
        return mrb_ary_entry(array, index);
    }

    rb MRuby::NewArray() {
        return mrb_ary_new(mrb);
    }

    void MRuby::ArrayPush(rb array, rb value) {
        mrb_ary_push(mrb, array, value);
    }

    rb MRuby::ArrayPop(rb array) {
        return mrb_ary_pop(mrb, array);
    }

    void MRuby::ArrayClear(rb array) {
        mrb_ary_clear(mrb, array);
    }

    void MRuby::SetHashValue(rb hash, rb key, rb val) {
        mrb_hash_set(mrb, hash, key, val);
    }


    const char *MRuby::TypeString(rb val) {
        mrb_vtype type = mrb_type(val);
        switch (type) {
            case MRB_TT_FALSE:
                return "MRB_TT_FALSE";
            case MRB_TT_TRUE:
                return "MRB_TT_TRUE";
            case MRB_TT_FLOAT:
                return "MRB_TT_FLOAT";
            case MRB_TT_INTEGER:
                return "MRB_TT_INTEGER";
            case MRB_TT_SYMBOL:
                return "MRB_TT_SYMBOL";
            case MRB_TT_UNDEF:
                return "MRB_TT_UNDEF";
            case MRB_TT_CPTR:
                return "MRB_TT_CPTR";
            case MRB_TT_FREE:
                return "MRB_TT_FREE";
            case MRB_TT_OBJECT:
                return "MRB_TT_OBJECT";
            case MRB_TT_CLASS:
                return "MRB_TT_CLASS";
            case MRB_TT_MODULE:
                return "MRB_TT_MODULE";
            case MRB_TT_ICLASS:
                return "MRB_TT_ICLASS";
            case MRB_TT_SCLASS:
                return "MRB_TT_SCLASS";
            case MRB_TT_PROC:
                return "MRB_TT_PROC";
            case MRB_TT_ARRAY:
                return "MRB_TT_ARRAY";
            case MRB_TT_HASH:
                return "MRB_TT_HASH";
            case MRB_TT_STRING:
                return "MRB_TT_STRING";
            case MRB_TT_RANGE:
                return "MRB_TT_RANGE";
            case MRB_TT_EXCEPTION:
                return "MRB_TT_EXCEPTION";
            case MRB_TT_ENV:
                return "MRB_TT_ENV";
            case MRB_TT_DATA:
                return "MRB_TT_DATA";
            case MRB_TT_FIBER:
                return "MRB_TT_FIBER";
            case MRB_TT_ISTRUCT:
                return "MRB_TT_ISTRUCT";
            case MRB_TT_BREAK:
                return "MRB_TT_BREAK";
            case MRB_TT_COMPLEX:
                return "MRB_TT_COMPLEX";
            case MRB_TT_RATIONAL:
                return "MRB_TT_RATIONAL";
            case MRB_TT_BIGINT:
                return "MRB_TT_BIGINT";
            default:
                return "Unknown Type";
        }
    }

    void MRuby::PrintError() {
        mrb_print_error(mrb);
    }

    void MRuby::PrintBacktrace() {
        mrb_print_backtrace(mrb);
    }


    mrb_state *MRuby::MRuby::GetMrb() {
        return mrb;
    }
}
