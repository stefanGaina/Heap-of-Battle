/******************************************************************************************************
 * @file hob_Server.cpp                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 29.08.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hob_Server.hpp.                                 *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Server.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Server& Server::getInstance(void) noexcept
{
	static Server serverInstance = {};

	plog_verbose("Server instance is being got.");

	return serverInstance;
}

Server::Server(void) noexcept
	: m_server{ nullptr }
{
	plog_trace("Server is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ")", sizeof(*this), sizeof(m_server));
}

Server::~Server(void) noexcept
{
	plog_trace("Socket is being destructed.");
	close();
}

void Server::create(void) noexcept(false)
{
	plog_debug("Server is being created.");
	if (nullptr != m_server)
	{
		plog_warn("Server is already created!");
		return;
	}

	try
	{
		m_server = std::make_unique<hobServer::Server>();
	}
	catch (const std::bad_alloc& exception)
	{
		plog_error("Unable to allocate memory for server! (bytes: %" PRIu64 ")", sizeof(hobServer::Server));
		throw std::exception();
	}

	m_server->runAsync(8787U);
	plog_info("Server successfully created!");
}

void Server::close(void) noexcept
{
	plog_debug("Server is being closed.");
	if (nullptr == m_server)
	{
		plog_warn("Server has not been created!");
		return;
	}

	m_server->stop();
	m_server = nullptr;
	plog_info("Server closed successfully!");
}

} /*< namespace hob */
