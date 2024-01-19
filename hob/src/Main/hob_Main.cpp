/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024                                                                  *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file hob_Main.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 22.12.2023  Gaina Stefan               Ported to Linux.                                            *
 * 19.01.2024  Gaina Stefan               Fix extra compiler warning.                                 *
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
	(void)argv;
	if (1 < argc)
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
