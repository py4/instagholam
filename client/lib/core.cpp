#include "core.h"

Core* Core::core = NULL;

Core::Core()
{
	ClientHandler::init();
}

Core* Core::instance()
{
	if(core == NULL)
	{
		core = new Core;
		return core;
	}
	return core;
}
