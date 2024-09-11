//
// Created by novel on 2024-09-10.
//

#ifndef EKUN_SCRIPT_H
#define EKUN_SCRIPT_H

#include "MRuby.h"

class Script {

public:
    Script();
    Script(mrb_state* mrb, const std::string& filename);

    static void LoadScript(mrb_state* mrb, const std::string& filename);

    MRB::rb args{}; // Hash that gets passed in to every function, I think that's how DragonRuby does it
    MRB::rb load{};
    MRB::rb output{};
    MRB::rb input{};
    MRB::rb config{};
    MRB::rb state{};

    void CreateArgs(mrb_state *mrb);
};


#endif //EKUN_SCRIPT_H
