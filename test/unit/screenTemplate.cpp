/**
 * Test cases for screenTemplate
 */

#include "../../src/controllers/screenTemplate.hpp"
#include "../assertions.hpp"
#include <gtest/gtest.h>

using screen::ScreenTemplate;

/**
 * Dummy base class to test abstract class 'functionality'
 */
class DummyScreen : screen::ScreenTemplate {
private:
    int test{};

public:
    DummyScreen() = default;

    // Dummy methods
    void setT(int t) { test = t; }
    [[nodiscard]] int getT() const { return test; };
    void run(sf::RenderWindow &gui) override {}

    // Needed for dynamic memory
    DummyScreen(const DummyScreen &other) = default;
    ~DummyScreen() override = default;
    DummyScreen &operator=(const DummyScreen &rhs) {
        test = rhs.test;
        return *this;
    }
};

TEST(unit, screenTemplate) {
    // These test are mainly to understand base class implementation
    // and ensure the abstract class has a proper implementation
    DummyScreen testScreen;
    DummyScreen testScreen1;

    testScreen.setT(10);
    testScreen1.setT(20);

    ASSERT_OPERATION(testScreen.getT(), ==, 10);
    ASSERT_OPERATION(testScreen1.getT(), ==, 20);
    sf::RenderWindow rw;
    testScreen.run(rw);
    testScreen = testScreen1;
    ASSERT_OPERATION(testScreen.getT(), ==, 20);
    ASSERT_OPERATION(testScreen1.getT(), ==, 20);
}
