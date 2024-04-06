/******************************************************************************************************
 * Heap of Battle Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file hob_Main.hpp
 * @author Gaina Stefan
 * @date 23.07.2023
 * @brief This file provides an entry point for the Heap-of-Battle game.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Game.hpp"
#include "hob_Test.hpp"

/******************************************************************************************************
 * ENTRY POINT
 *****************************************************************************************************/

int main(const int argc, char** const argv)
{
	int32_t					   exitCode = EXIT_SUCCESS;
	std::unique_ptr<hob::Game> game		= nullptr;

	handle_arguments(argc, argv);
	try
	{
		game = std::make_unique<hob::Game>();
		game->run();
	}
	catch (...)
	{
		plog_fatal("Game failed to be initialized!");
		exitCode = EXIT_FAILURE;
	}

	plog_info("Thank you for playing! (exit code: %" PRId32 ")", exitCode);
	test_deinit();

	return exitCode;
}
