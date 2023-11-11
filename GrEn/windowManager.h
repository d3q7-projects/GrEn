#pragma once
#include <map>
#include "Window.h"

class windowManager
{
public:
	windowManager() = delete;
	windowManager(windowManager&) = delete;
	static void addWindow(void* , Window*);
	static Window* getWindow(void*);

private:
	static std::map<void*, Window*> windowAssociation; //internal use
};

