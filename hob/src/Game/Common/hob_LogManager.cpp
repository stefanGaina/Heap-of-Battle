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
 * @file hob_LogManager.cpp
 * @author Gaina Stefan
 * @date 09.02.2024
 * @brief This file implements the class defined in hob_LogManager.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <plog.h>

#include "hob_LogManager.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

#ifndef PLOG_STRIP_ALL

void LogManager::handleCommand(const char* const command) noexcept
{
	plog_verbose("Log command is being handled. (command: %s)", command);
	plog_assert(nullptr != command);

	if ('s' == command[0])
	{
		handleSetCommand(command + 1);
		return;
	}

	if ('g' == command[0])
	{
		handleGetCommand(command + 1);
		return;
	}

	plog_warn("Invalid command! (command: %s)", command);
}

void LogManager::handleSetCommand(const char* command) noexcept
{
	plog_assert(nullptr != command);
	plog_verbose("Log set commands is being handled. (command: %s)", command);

	if (true == isCommandSeverityLevel(command))
	{
		plog_set_severity_level(static_cast<guint8>(atoi(command + 3)));
		return;
	}

	if (true == isCommandFileSize(command))
	{
		plog_set_file_size(atoll(command + 3));
		return;
	}

	if (true == isCommandFileCount(command))
	{
		plog_set_file_count(static_cast<guint8>(atoi(command + 3)));
		return;
	}

	if (true == isCommandTerminalMode(command))
	{
		plog_set_terminal_mode(static_cast<gboolean>(atoi(command + 3)));
		return;
	}

	if (true == isCommandBufferMode(command))
	{
		if (FALSE == plog_set_buffer_mode(atoi(command + 3)))
		{
			plog_error("Failed to set log buffer mode!");
		}
		return;
	}

	plog_warn("Invalid set command! (command: %s)", command);
}

void LogManager::handleGetCommand(const char* const command) noexcept
{
	plog_assert(nullptr != command);
	plog_verbose("Log get commands is being handled. (command: %s)", command);

	if (true == isCommandSeverityLevel(command))
	{
		plog_info("Log severity level: %" PRIu8 "!", plog_get_severity_level());
		return;
	}

	if (true == isCommandFileSize(command))
	{
		plog_info("Log file size: %" PRIu64 "!", plog_get_file_size());
		return;
	}

	if (true == isCommandFileCount(command))
	{
		plog_info("Log file count: %" PRIu64 "!", plog_get_file_count());
		return;
	}

	if (true == isCommandTerminalMode(command))
	{
		plog_info("Log terminal mode: %" PRId32 "!", plog_get_terminal_mode());
		return;
	}

	if (true == isCommandBufferMode(command))
	{
		plog_info("Log buffer mode: %" PRId32 "!", plog_get_buffer_mode());
		return;
	}

	plog_warn("Invalid get command! (command: %s)", command);
}

bool LogManager::isCommandSeverityLevel(const char* const command) noexcept
{
	plog_assert(nullptr != command);
	return isCommand(command, "sl");
}

bool LogManager::isCommandFileSize(const char* const command) noexcept
{
	plog_assert(nullptr != command);
	return isCommand(command, "fs");
}

bool LogManager::isCommandFileCount(const char* const command) noexcept
{
	plog_assert(nullptr != command);
	return isCommand(command, "fc");
}

bool LogManager::isCommandTerminalMode(const char* const command) noexcept
{
	plog_assert(nullptr != command);
	return isCommand(command, "tm");
}

bool LogManager::isCommandBufferMode(const char* const command) noexcept
{
	plog_assert(nullptr != command);
	return isCommand(command, "bm");
}

bool LogManager::isCommand(const char* const command, const char* const identifier) noexcept
{
	plog_assert(nullptr != command);
	plog_assert(nullptr != identifier);

	return 0 == strncmp(command, identifier, strlen(identifier));
}

#endif /*< PLOG_STRIP_ALL */

} /*< namespace hob */
