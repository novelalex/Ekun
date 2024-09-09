//
// Created by novel on 2024-09-09.
//

#ifndef EKUN_HASH_H
#define EKUN_HASH_H

#include "MRuby.h"

namespace MRuby {
    class Hash {
    private:
        mrb_state *mrb;
        rb val;
    public:
        explicit Hash(mrb_state mrb);
        rb Self();
        mrb_state *GetMrb();
    };
}


#endif //EKUN_HASH_H
