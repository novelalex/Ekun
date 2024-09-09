#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>

#include <string>
#include <memory>
#include "core/Debug.h"
#include "core/GameManager.h"

int main(int argc, char *args[]) {
    _CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    static_assert(sizeof(void *) == 8, "This program is not ready for 32-bit build");

    Debug::DebugInit("EkunLog.txt");

    auto gm = std::make_unique<GameManager>();
    if (gm->Initialize("Ekun (Name subject to change)", 1280, 720)) {
        gm->Run();
    } else {
        printf("Init Failed\n");
    }

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    return 0;
}
