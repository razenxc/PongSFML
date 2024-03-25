#include "fonts.h"

namespace Fonts
{
	std::string fontsPath = R"(resources/fonts/)";
	
	Fonts::Fonts()
	{
		madimiOne.loadFromFile(fontsPath + "MadimiOne-Regular.ttf");
		robotoMedium.loadFromFile(fontsPath + "Roboto-Medium.ttf");
	}
}