#include "ox/oxygine.hpp"
#include "ox/Stage.hpp"
#include "ox/DebugActor.hpp"

#include "../Header/ChessView.h"
#include "../Header/ChessModel.h"

#include <memory>

using namespace oxygine;
using namespace Game;

// This function is called each frame
int mainloop()
{
    // Update engine-internal components
    // If input events are available, they are passed to Stage::instance.handleEvent
    // If the function returns true, it means that the user requested the application to terminate
    bool done = core::update();

    // Update our stage
    // Update all actors. Actor::update will also be called for all its children
    getStage()->update();

    if (core::beginRendering())
    {
        Color clearColor(32, 32, 32, 255);
        Rect viewport(Point(0, 0), core::getDisplaySize());
        // Render all actors inside the stage. Actor::render will also be called for all its children
        getStage()->render(clearColor, viewport);

        core::swapDisplayBuffers();
    }

    return done ? 1 : 0;
}

// Application entry point
void run()
{
    ObjectBase::__startTracingLeaks();

    // Initialize Oxygine's internal stuff
    core::init_desc desc;
    desc.title = "Chedd";

    // The initial window size can be set up here on SDL builds, ignored on Mobile devices
    desc.w = 1000;
    desc.h = 1000;

    core::init(&desc);


    // Create the stage. Stage is a root node for all updateable and drawable objects
    Stage::instance = new Stage();
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    auto chessView = new Game::ChessView(100, 100, 100);
    getStage()->addChild(chessView);
    chessView->setModel(std::make_unique<Game::ChessModel>(100));

    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
    DebugActor::show();

    while (1)
    {
        int done = mainloop();
        if (done)
            break;
    }
    /*
     If we get here, the user has requested the Application to terminate.
     We dump and log all our created objects that have not been freed yet
    */
    ObjectBase::dumpCreatedObjects();

    // Releases all internal components and the stage
    core::release();

    // The dump list should be empty by now,
    // we want to make sure that there aren't any memory leaks, so we call it again.
    ObjectBase::dumpCreatedObjects();

    ObjectBase::__stopTracingLeaks();
    //end
}

#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C"
{
    void one(void* param) { mainloop(); }
    void oneEmsc() { mainloop(); }

    int main(int argc, char* argv[])
    {

        run();

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
        // If parameter 2 is set to 1, refresh rate will be 60 fps, 2 - 30 fps, 3 - 15 fps.
        //SDL_iPhoneSetAnimationCallback(core::getWindow(), 1, one, nullptr);
#endif

#if EMSCRIPTEN
        emscripten_set_main_loop(oneEmsc, 0, 0);
#endif

        return 0;
    }
};
#endif