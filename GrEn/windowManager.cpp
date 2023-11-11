#include "windowManager.h"

std::map<void*, Window*> windowManager::windowAssociation;


void windowManager::addWindow(void* sdlP, Window* grenP)
{
	windowManager::windowAssociation[sdlP] = grenP;
}

Window* windowManager::getWindow(void* sdlP)
{
	return windowManager::windowAssociation[sdlP];
}
