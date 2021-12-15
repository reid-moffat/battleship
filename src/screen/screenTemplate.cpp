/**
 * ScreenTemplate abstract class implementation
 */

#include "../../include/screen/screenTemplate.hpp"

using screen::ScreenTemplate;

ScreenTemplate::ScreenTemplate() = default;

// Big three
ScreenTemplate::ScreenTemplate(const ScreenTemplate &other) = default;
ScreenTemplate::~ScreenTemplate() = default;
ScreenTemplate &screen::ScreenTemplate::operator=(const ScreenTemplate &rhs) = default;
