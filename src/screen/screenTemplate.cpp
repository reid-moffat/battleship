/**
* ScreenTemplate "interface" implementation
*/

#include "../../include/screen/screenTemplate.h"

using screen::ScreenTemplate;

ScreenTemplate::ScreenTemplate() = default;

ScreenTemplate::ScreenTemplate(const ScreenTemplate &other) = default;

ScreenTemplate::~ScreenTemplate() = default;// I know this doesn't make sense, but it works

ScreenTemplate &screen::ScreenTemplate::operator=(const ScreenTemplate &rhs) = default;