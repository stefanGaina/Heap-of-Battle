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
 * @file hob_Map1.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * 26.08.2023  Gaina Stefan               Added chat.                                                 *
 * 29.08.2023  Gaina Stefan               Fixed comment.                                              *
 * 16.01.2024  Gaina Stefan               Added faction member.                                       *
 * @details This file defines the class and method prototypes of the map of the first scenario.       *
 * @todo Fix doxygen comments.                                                                        *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_MAP1_H_
#define HOB_MAP1_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <thread>
#include <atomic>

#include "hob_Loop.hpp"
#include "hob_Music.hpp"
#include "hob_Faction.hpp"
#include "hob_Menu.hpp"
#include "hob_Chat.hpp"
#include "hob_Tiles1.hpp"
#include "hob_Buildings1.hpp"
#include "hob_Grid1.hpp"
#include "hob_Units.hpp"
#include "hobGame_Game.hpp"
#include "hobServer_Server.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

/**
 * @brief Main class of the scenario 1.
*/
class Map1 final : public Loop
{
public:
	/**
	 * @brief Creates the receiving thread and changes the cursor.
	 * @param renderer: Rendering context of the window.
	 * @param cursor: Reference to the cursor object.
	 * @param ping: TODO
	 * @param music: Reference to the music object.
	 * @param faction: TODO
	 * @param server: TODO
	 * @param socket: TODO
	*/
	Map1(SDL_Renderer* renderer, Cursor& cursor, Ping* ping, Music& music, const Faction& faction, hobServer::Server& server, Socket& socket) noexcept;

	/**
	 * @brief Closes the socket and resets the cursor.
	 * @param void
	*/
	~Map1(void) noexcept;

private:
	/**
	 * @brief Handles an event.
	 * @param event: Event to be handled.
	 * @return void
	*/
	void handleEvent(const SDL_Event& event) noexcept override;

	/**
	 * @brief Draws scene specific stuff to the screen.
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief Receives updates from the server.
	 * @param void
	 * @return void
	*/
	void receivingFunction(void) noexcept;

private:
	/**
	 * @brief TODO
	*/
	hobGame::Game game;

	/**
	 * @brief Playing board background.
	*/
	Tiles1 tiles;

	/**
	 * @brief Menu background.
	*/
	Menu menu;

	/**
	 * @brief Graphical representation of the buildings.
	*/
	Buildings1 buildings;

	/**
	 * @brief Visual representation of chat box and messages.
	*/
	Chat chat;

	/**
	 * @brief Lines between tiles and buildings.
	*/
	Grid1 grid;

	/**
	 * @brief TODO
	*/
	Units units;

	/**
	 * @brief Thread for receiving updates from the server.
	*/
	std::thread receivingThread;

	/**
	 * @brief Flag indicating if the receiving thread should still execute.
	*/
	std::atomic<bool> receivingUpdates;

	/**
	 * @brief TODO
	*/
	Music& music;

	/**
	 * @brief TODO
	*/
	const Faction& faction;

	/**
	 * @brief TODO
	*/
	hobServer::Server& server;

	/**
	 * @brief TODO
	*/
	Socket& socket;
};

} /*< namespace hob */

#endif /*< HOB_MAP1_H_ */
