#include "gui/context_menu/launch_style.h"
#include "extern.h"
#include "gui/ui/root_ui.h"
#include "hid/display/numeric_driver.h"
#include "hid/led/indicator_leds.h"
#include "hid/matrix/matrix_driver.h"
#include "model/clip/clip.h"
#include <cstddef>

namespace deluge::gui::context_menu {

enum class LaunchStyle::Value {
	DEFAULT,
	FILL,
};
constexpr size_t kNumValues = 2;

LaunchStyle launchStyle{};

#if HAVE_OLED
char const* optionsls[] = {"Default", "Fill"};
#else
char const* optionsls[] = {"DEFA", "FILL"};
#endif

char const* LaunchStyle::getTitle() {
	static char const* title = "Launch Style";
	return title;
}

Sized<char const**> LaunchStyle::getOptions() {
	return {optionsls, kNumValues};
}

bool LaunchStyle::setupAndCheckAvailability() {
	Value valueOption = Value::DEFAULT;

	switch (clip->launchStyle) {
	case LAUNCH_STYLE_DEFAULT:
		valueOption = Value::DEFAULT;
		break;
	case LAUNCH_STYLE_FILL:
		valueOption = Value::FILL;
		break;
	default:
		valueOption = Value::DEFAULT;
	}
	currentUIMode = UI_MODE_NONE;

	currentOption = static_cast<int32_t>(valueOption);

#if HAVE_OLED
	scrollPos = currentOption;
#endif
	return true;
}

void LaunchStyle::selectEncoderAction(int8_t offset) {
	/* if (currentUIMode) return; */

	ContextMenu::selectEncoderAction(offset);

	auto valueOption = static_cast<Value>(currentOption);

	switch (valueOption) {
	case Value::DEFAULT:
		clip->launchStyle = LAUNCH_STYLE_DEFAULT;
		break;
	case Value::FILL:
		clip->launchStyle = LAUNCH_STYLE_FILL;
		break;

	default:
		clip->launchStyle = LAUNCH_STYLE_DEFAULT;
	}
}

} // namespace deluge::gui::context_menu
