/** @file Main.cpp
 *  @brief Provides the entry point of the  application.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#define SDL_MAIN_HANDLED /*< Initialization and deinitialization will be done manually. */
#define DEBUG_MODE       /*< Comment this for release mode builds.                      */

#include <stdlib.h>
#include <plog.h>
#include <pers_config.h>

#include "Window.hpp"
#include "MainMenu.hpp"
#include "Settings.hpp"
#include "Multiplayer.hpp"
#include "Map1.hpp"
#include "Music.hpp"

/***********************************************************************************************************************
 * ENTRY POINT                                                                                                         *
 **********************************************************************************************************************/

int main(int argc, char* argv[])
{
#ifdef DEBUG_MODE
	(void)ShowWindow(GetConsoleWindow(), SW_SHOW);
	plog_init(NULL); /*< Called here for logs in constructors to appear in file. */
#else
	(void)ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	plog_info("Starting game! (version: %s)", VERSION_STRING);

	Window::Window                window        = {};
	Scene                         scene         = Scene::MAIN_MENU;
	Scene                         previousScene = Scene::MAIN_MENU;
	std::shared_ptr<Common::Loop> sceneLoop     = nullptr;

	pers_config_read();

RESET:

	try
	{
		window.create(static_cast<bool>(pers_config_get_is_fullscreen()));
	}
	catch (std::exception& exception)
	{
		plog_fatal("Window failed to be created! (exception message: %s)", exception.what());
		return EXIT_FAILURE;
	}

	while (Scene::QUIT != scene && Scene::RESET != scene)
	{
		previousScene = scene;
		switch (scene)
		{
			/* Scene loops are on the heap so main function does not use too much stack. */
			case Scene::MAIN_MENU:
			{
				try
				{
					sceneLoop = std::make_shared<Menu::MainMenu>();
				}
				catch (std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for main menu scene! (exception message: %s)", exception.what());
					scene = Scene::RESET;
					break;
				}
				scene = sceneLoop->startLoop();
				break;
			}
			case Scene::SETTINGS:
			{
				try
				{
					sceneLoop = std::make_shared<Menu::Settings>();
				}
				catch (std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for settings scene! (exception message: %s)", exception.what());
					scene = Scene::RESET;
					break;
				}
				scene = sceneLoop->startLoop();
				break;
			}
			case Scene::MULTIPLAYER:
			{
				try
				{
					sceneLoop = std::make_shared<Menu::Multiplayer>();
				}
				catch (std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for multiplayer scene! (exception message: %s)", exception.what());
					scene = Scene::RESET;
					break;
				}
				scene = sceneLoop->startLoop();
				break;
			}
			case Scene::GAME:
			{
				try
				{
					sceneLoop = std::make_shared<Game::Map1>();
				}
				catch (std::bad_alloc& exception)
				{
					plog_fatal("Unable to allocate memory for map1 scene! (exception message: %s)", exception.what());
					scene = Scene::RESET;
					break;
				}
				scene = sceneLoop->startLoop();
				break;
			}
			default:
			{
				plog_fatal("Invalid scene! (scene: %" PRId32 ")", static_cast<int32_t>(scene));
				scene = Scene::QUIT;
				break;
			}
		}
		sceneLoop = nullptr;
	}

	if (Scene::RESET == scene)
	{
		// TODO: destroying window means deinitializing SDL but music and cursor are still loaded.
		// Check if that is a problem or not when implementing runtime configuration of fullscreen.
		scene = previousScene;
		window.destroy();

		goto RESET;
	}

	pers_config_write();

	Utility::Music::getInstance().stop();

	plog_info("Thank you for playing!");
	//plog_deinit(); <- Calling this is optional, commented for logs in destructors to appear in file.

	return EXIT_SUCCESS;
}
