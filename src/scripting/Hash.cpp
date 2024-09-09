//
// Created by novel on 2024-09-09.
//

#include "Hash.h"

MRB::Hash::Hash(mrb_state mrb) {
 // TODO
}

mrb_state *MRB::Hash::GetMrb() {
    return mrb;
}

MRB::rb MRB::Hash::Self() {
    return val;
}

