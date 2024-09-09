//
// Created by novel on 2024-09-08.
//

#ifndef EKUN_MRUBY_H
#define EKUN_MRUBY_H

#include <mruby.h>
#include <string>

namespace MRuby {

    typedef mrb_value rb;

    // I'm filling out these functions as I need them, this is not a full wrapper around mruby
    class MRuby {
    private:
        mrb_state *mrb;
    public:
        mrb_state *GetMrb();

    public:
        MRuby();

        ~MRuby();



        void LoadFile(const std::string &filename);

        RClass *GetClass(const std::string &filename); // Returns a class

        rb Instantiate(RClass *rClass, int argc, rb *argv); // Returns an object

        rb CallFunction(rb object, const char *name, int argc, rb *argv); // Returns whatever the function returns


        bool IsNil(rb val);

        bool IsTrue(rb val);

        bool IsFalse(rb val);

        rb SymbolValue(const char *sym);

        // TODO: Refactor into a separate object
        rb NewHash();

        rb GetHashValue(rb hash, const char *key);

        rb GetHashValue(rb hash, rb key);

        void SetHashValue(rb hash, rb key, rb val);

        rb GetHashKeys(rb hash);

        bool IsHashEmpty(rb hash);

        rb HashFetch(rb hash, rb key, rb default_value);

        rb HashDeleteKey(rb hash, rb key);

        bool HashHasKey(rb hash, rb key);

        rb GetHashValues(rb hash);

        void HashClear(rb hash);

        mrb_int HashSize(rb hash);

        // TODO: Refactor into a separate object
        int ArrayLength(rb array);

        rb ArrayEntry(rb array, int index);

        rb NewArray();

        void ArrayClear(rb array);

        rb ArrayPop(rb array);

        void ArrayPush(rb array, rb value);

        const char *TypeString(rb val);

        const char *CString(rb str);

        void PrintError();

        void PrintBacktrace();


    private:
        static std::string readFile(const std::string &filename);

    };
}


#endif //EKUN_MRUBY_H
