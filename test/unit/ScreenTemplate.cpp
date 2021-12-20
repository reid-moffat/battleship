/**
* Test cases for screenTemplate
*/

#include "../../src/controllers/screenTemplate.hpp"
#include <gtest/gtest.h>

using screen::ScreenTemplate;

/**
* Dummy base class to test abstract class 'functionality'
*/
class DummyScreen : screen::ScreenTemplate {
public:
    static DummyScreen &getInstance() {
        if (instance == nullptr) {
            instance = new DummyScreen();
        }
        return *instance;
    }

    // Dummy methods
    void run() override {}

    // Needed for dynamic memory
    DummyScreen(const DummyScreen &other) = delete;
    DummyScreen &operator=(const DummyScreen &rhs) = delete;

private:
    DummyScreen() = default;
    static DummyScreen *instance;
};

DummyScreen *DummyScreen::instance = nullptr;

TEST(unit, screenTemplate) {
    // These test are mainly to understand base class implementation
    // and ensure the abstract class has a proper implementation
    DummyScreen &testScreen = DummyScreen::getInstance();
}
