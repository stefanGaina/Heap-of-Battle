/******************************************************************************************************
 * @file hob_Main.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file provides an entry point for the Heap-of-Battle game.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#define SDL_MAIN_HANDLED
#include <iostream>
#include <plog.h>

#include "hob_Game.hpp"

/******************************************************************************************************
 * ENTRY POINT                                                                                        *
 *****************************************************************************************************/

int main(int argc, char* argv[])
{
	if (1L < argc)
	{
		std::cout << "Parameters are ignored!" << std::endl;
	}

	try
	{
		hob::Game::run();
	}
	catch (const std::exception& exception)
	{
		plog_fatal("Game failed to start!");
		return EXIT_FAILURE;
	}

	plog_info("Thank you for playing!");
	return EXIT_SUCCESS;
}
