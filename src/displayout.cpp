#include "displayout.h"


displayout::displayout() {
    // Init the display thread

    ThreadDisplay = std::thread(&displayout::Threaded_Display, this);


}

displayout::~displayout() {
    // Join the main thread from here
    SetToQuit = true;

    // if it takes too long for the thread to join then we can hang here
    /// TODO fix this hang
    while (ThreadDisplay.joinable()) {
        ThreadDisplay.join();
    }
 
}

void displayout::out(int enumTypeColor, std::string ToDisplay) {


    D_COLOR::ColorM::Modifier ModColor[] = { D_COLOR::defM, D_COLOR::blueM, D_COLOR::greenM, D_COLOR::redM, D_COLOR::redM, D_COLOR::magentaM, D_COLOR::yellowM };

    D_COLOR::__OBJSTRING ColorBack = { ToDisplay, D_COLOR::debugstring[enumTypeColor], ModColor[enumTypeColor]};

    PreDisplayControl.push_back(ColorBack);

    
}

void displayout::Threaded_Display() {
    // Start the init for the display thread that will be displaying all content from a thread(s)
    while (!SetToQuit) {
        usleep(66);
        

        if (!__IsDisplaying) {
        auto ThreadPart = PreDisplayControl;
        PreDisplayControl.clear();

            if (ThreadPart.size() > 0) {
                __IsDisplaying = true;

                for (auto i : ThreadPart) {
                    if (i.Message.size() > 0) {
                        std::cout << i.DebugType << "[" << i.Prompt << "]: " << i.Message << D_COLOR::defM << std::endl;
                        AllLog.push_back(i.Message);
                    }
                }
                __IsDisplaying = false;
            }
        }

    }

}