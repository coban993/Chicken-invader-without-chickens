#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG
	return "assets/";
#else 
	return "C:/WithoutChickensInvader c++/WithoutChickensInvaderGame/assets/";
#endif
}
