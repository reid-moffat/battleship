/**
 * Test cases for screenTemplate
 */

#include "../../include/screen/screenTemplate.h"
#include "../tests.h"

using screen::ScreenTemplate;

/**
 * Dummy base class to tests abstract class 'functionality'
 */
class DummyScreen : screen::ScreenTemplate {
public:
    int test;

    DummyScreen() {}

    void setT(int t) { test = t; }

    DummyScreen(const DummyScreen &other) = default;

    // Needed for dynamic memory
    ~DummyScreen() override = default;

    // Must be overridden
    void run(sf::RenderWindow &gui) override {}

    ScreenTemplate &operator=(const DummyScreen &rhs) {
        test = rhs.test;
        return *this;
    }
};


int main() {
    // These tests are mainly to understand base class implementation
    // and ensure the abstract class has a proper implementation
    DummyScreen testScreen;
    DummyScreen testScreen1;

    testScreen.setT(10);
    testScreen1.setT(20);

    ASSERT_OPERATION(testScreen.test, ==, 10);
    ASSERT_OPERATION(testScreen1.test, ==, 20);
    sf::RenderWindow rw;
    testScreen.run(rw);
    testScreen = testScreen1;
    ASSERT_OPERATION(testScreen.test, ==, 20);
    ASSERT_OPERATION(testScreen1.test, ==, 20);

    return 0;
}
