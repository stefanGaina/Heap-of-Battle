#include <plog.h>

#include "StartGame.hpp"
#include "Cursor.hpp"

namespace Menu
{

StartGame::StartGame(void)
	: Loop{}
{
	plog_trace("Start game is being constructed.");
}

StartGame::~StartGame(void)
{
	plog_trace("Start game is being deconstructed.");
}

void StartGame::draw(void) noexcept
{
	plog_verbose("Start game is being drawn.");
	//TextureInitializer::draw();
}

void StartGame::handleEvent(const SDL_Event& event) noexcept
{
	static size_t clickDownIndex = 0ULL;

	Coordinate click      = { 0 };
	uint32_t   mouseState = 0UL;
	size_t     index      = 0ULL;

	plog_verbose("Events is being handled.");

	switch (event.type)
	{
		//case SDL_MOUSEBUTTONDOWN:
		//{
		//	mouseState = SDL_GetMouseState(&click.x, &click.y);
		//	plog_trace("Mouse (%" PRIu32 ") was clicked. (%" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

		//	if (LEFT_CLICK != SDL_BUTTON(mouseState))
		//	{
		//		plog_trace("Mouse click is not left click.");
		//		return;
		//	}

		//	for (index = MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME; index <= MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT; ++index)
		//	{
		//		if (componentContainer[index].isMouseInside(click, bar_corrections))
		//		{
		//			plog_verbose("Bar is pressed. (%" PRIu64 ")", index);
		//			componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_PRESSED].getData());
		//			soundContainer[MAIN_MENU_SOUND_INDEX_CLICK].play();
		//			clickDownIndex = index;
		//			return;
		//		}
		//		componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE].getData());
		//	}
		//	break;
		//}
		//case SDL_MOUSEBUTTONUP:
		//{
		//	mouseState = SDL_GetMouseState(&click.x, &click.y);
		//	plog_trace("Mouse (%" PRIu32 ") was released. (%" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

		//	if (0ULL != clickDownIndex && componentContainer[clickDownIndex].isMouseInside(click, bar_corrections))
		//	{
		//		switch (clickDownIndex)
		//		{
		//			case MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME:
		//			{
		//				plog_debug("Start game bar was selected, clicked and released.");
		//				stopLoop(Scene::GAME);
		//				break;
		//			}
		//			case MAIN_MENU_COMPONENT_INDEX_BUTTON_SETTINGS:
		//			{
		//				plog_debug("Settings bar was selected, clicked and released.");
		//				stopLoop(Scene::SETTINGS);
		//				break;
		//			}
		//			case MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT:
		//			{
		//				plog_debug("Exit bar was selected, clicked and released.");
		//				stopLoop(Scene::QUIT);
		//				break;
		//			}
		//		}
		//	}
		//	clickDownIndex = 0ULL;
		//	//break; <- commented so buttons get reselected appropriately.
		//}
		//case SDL_MOUSEMOTION:
		//{
		//	mouseState = SDL_GetMouseState(&click.x, &click.y);
		//	plog_verbose("Mouse (%" PRIu32 ") was moved. (%" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

		//	Utility::Cursor::getInstance().updatePosition(click);

		//	if (LEFT_CLICK == SDL_BUTTON(mouseState))
		//	{
		//		plog_verbose("Mouse left click is pressed.");
		//		return;
		//	}

		//	for (index = MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME; index <= MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT; ++index)
		//	{
		//		if (componentContainer[index].isMouseInside(click, bar_corrections))
		//		{
		//			plog_verbose("Bar is selected. (%" PRIu64 ")", index);
		//			componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_ACTIVE].getData());
		//			return;
		//		}
		//		componentContainer[index].updateTexture(textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE].getData());
		//	}
		//	break;
		//}
		case SDL_QUIT:
		{
			plog_info("Command to quit game was given!");
			stopLoop(Scene::QUIT);
			break;
		}
		default:
		{
			plog_verbose("Event received but not handled.");
			break;
		}
	}
}

} /*< namespace Menu */
