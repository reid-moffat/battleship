/**
 * ScreenTemplate abstract class implementation
 */

#include "screenTemplate.hpp"

using screen::ScreenTemplate;

ScreenTemplate::ScreenTemplate() : resources("", {}, {}, {}) {}

void screen::ScreenTemplate::run() {
    this->update();
    this->poll();
    this->render();
}
