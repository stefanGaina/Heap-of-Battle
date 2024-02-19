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
 * @file hob_LocalMenu.hpp
 * @author Gaina Stefan
 * @date 29.09.2023
 * @brief This file defines the class and method prototypes of the LAN menu scene.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_LOCAL_MENU_HPP_
#define HOB_LOCAL_MENU_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "hob_Loop.hpp"
#include "hob_TextureInitializer.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_AsyncQueue.hpp"
#include "hob_Music.hpp"
#include "hob_Faction.hpp"
#include "hobServer_Server.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Enumerates local menu's textures index.
 *****************************************************************************************************/
enum LocalMenuTextureIndex
{
	LOCAL_MENU_TEXTURE_INDEX_BACKGROUND		 = 0, /**< Index to the local menu's background texture.           */
	LOCAL_MENU_TEXTURE_INDEX_BUTTON_IDLE	 = 1, /**< Index to the local menu's idle button texture.          */
	LOCAL_MENU_TEXTURE_INDEX_BUTTON_ACTIVE	 = 2, /**< Index to the local menu's active button texture.        */
	LOCAL_MENU_TEXTURE_INDEX_BUTTON_PRESSED	 = 3, /**< Index to the local menu's pressed button texture.       */
	LOCAL_MENU_TEXTURE_INDEX_HOST_GAME_TEXT	 = 4, /**< Index to the local menu's "HOST GAME" text texture.     */
	LOCAL_MENU_TEXTURE_INDEX_CONNECT_TEXT	 = 5, /**< Index to the local menu's "CONNECT" text texture.       */
	LOCAL_MENU_TEXTURE_INDEX_BACK_TEXT		 = 6, /**< Index to the local menu's "BACK" text texture.          */
	LOCAL_MENU_TEXTURE_INDEX_WAITING_TEXT	 = 7, /**< Index to the local menu's "WAITING..." text texture.    */
	LOCAL_MENU_TEXTURE_INDEX_CONNECTING_TEXT = 8, /**< Index to the local menu's "CONNECTING..." text texture. */
	LOCAL_MENU_TEXTURES_COUNT				 = 9  /**< How many textures local menu loads.                     */
};

/** ***************************************************************************************************
 * @brief Enumerates local menu's changeable components index.
 *****************************************************************************************************/
enum LocalMenuComponentIndex
{
	LOCAL_MENU_COMPONENT_INDEX_BUTTON_HOST_GAME = 1, /**< Index to the local menu's host game button component. */
	LOCAL_MENU_COMPONENT_INDEX_BUTTON_CONNECT	= 2, /**< Index to the local menu's connect button component.   */
	LOCAL_MENU_COMPONENT_INDEX_BUTTON_BACK		= 3, /**< Index to the local menu's back button component.      */
	LOCAL_MENU_COMPONENT_INDEX_HOST_GAME_TEXT	= 4, /**< Index to the local menu's host game text component.   */
	LOCAL_MENU_COMPONENT_INDEX_CONNECT_TEXT		= 5, /**< Index to the local menu's connect text component.     */
	LOCAL_MENU_COMPONENTS_COUNT					= 7	 /**< How many components the local menu uses.              */
};

/** ***************************************************************************************************
 * @brief Enumerates local menu's sounds index.
 *****************************************************************************************************/
enum LocalMenuSoundIndex
{
	LOCAL_MENU_SOUND_INDEX_CLICK = 0, /**< Index to the local menu's click sound. */
	LOCAL_MENU_SOUND_INDEX_ERROR = 1, /**< Index to the local menu's error sound. */
	LOCAL_MENU_SOUNDS_COUNT		 = 2  /**< How many sounds the local menu loads.  */
};

/** ***************************************************************************************************
 * @brief Enumerates the connection status of the client socket.
 *****************************************************************************************************/
enum class ConnectionStatus
{
	SUCCESS = 0, /**< The connection has been established successfully.    */
	FAILED	= 1, /**< The connection/creation of the client socket failed. */
	ABORTED = 2	 /**< The connection has been established, but lost.       */
};

/** ***************************************************************************************************
 * @brief LAN scene.
 *****************************************************************************************************/
class LocalMenu final
	: public Loop,
	  public TextureInitializer<LOCAL_MENU_TEXTURES_COUNT, LOCAL_MENU_COMPONENTS_COUNT>,
	  private SoundInitializer<LOCAL_MENU_SOUNDS_COUNT>
{
public:
	/** ***********************************************************************************************
	 * @brief Loads the textures and sounds needed for this scene.
	 * @param renderer: Rendering context of the window.
	 * @param cursor: Reference to the cursor object.
	 * @param ping: Reference to the ping object.
	 * @param music: Reference to the music object.
	 * @param faction: Reference to the faction object.
	 * @param server: Reference to the server object.
	 * @param socket: Reference to the socket object.
	 *************************************************************************************************/
	LocalMenu(SDL_Renderer* renderer, Cursor& cursor, Ping* ping, Music& music, Faction& faction, hobServer::Server& server, Socket& socket) noexcept;

	/** ***********************************************************************************************
	 * @brief Destroys the loaded textures and sound needed for this scene.
	 * @param void
	 *************************************************************************************************/
	~LocalMenu(void) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Handles an event.
	 * @param event: Event to be handled.
	 * @return void
	 *************************************************************************************************/
	void handleEvent(const SDL_Event& event) noexcept override;

	/** ***********************************************************************************************
	 * @brief Method implementation for drawing scene updates.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void draw(void) noexcept override;

	/** ***********************************************************************************************
	 * @brief Handles a button down event.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void handleButtonDown(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles a button up event.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void handleButtonUp(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles a mouse motion event.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void handleMouseMotion(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles a quit event.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void handleQuit(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Handles the updates present in queue.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void handleQueue(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Joins the receiving thread (only if it is joinable).
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void joinReceivingThread(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Joins the wait connection thread (only if it is joinable).
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void joinWaitConnectionThread(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Receives updates from the server.
	 * @param void
	 * @return void
	 *************************************************************************************************/
	void receivingFunction(void) noexcept;

	/** ***********************************************************************************************
	 * @brief Creates client socket and waits for connection to be established.
	 * @param ipAddress: The IP address of the server.
	 * @return void
	 *************************************************************************************************/
	void waitConnectionFunction(std::string ipAddress) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief Thread safe queue for buffering connection statuses.
	 *************************************************************************************************/
	AsyncQueue<ConnectionStatus> queue;

	/** ***********************************************************************************************
	 * @brief The thread that will be created if the waiting of connections is be done asynchronically.
	 *************************************************************************************************/
	std::thread waitConnectionThread;

	/** ***********************************************************************************************
	 * @brief Thread for receiving updates from the server.
	 *************************************************************************************************/
	std::thread receivingThread;

	/** ***********************************************************************************************
	 * @brief Flag indicating if the receiving thread should still execute.
	 *************************************************************************************************/
	std::atomic<bool> receivingUpdates;

	/** ***********************************************************************************************
	 * @brief Holds the index of the component that was previously pressed.
	 *************************************************************************************************/
	size_t clickDownIndex;

	/** ***********************************************************************************************
	 * @brief Reference to the music object.
	 *************************************************************************************************/
	Music& music;

	/** ***********************************************************************************************
	 * @brief Reference to the faction object.
	 *************************************************************************************************/
	Faction& faction;

	/** ***********************************************************************************************
	 * @brief Reference to the server object.
	 *************************************************************************************************/
	hobServer::Server& server;

	/** ***********************************************************************************************
	 * @brief Reference to the socket object.
	 *************************************************************************************************/
	Socket& socket;
};

} /*< namespace hob */

#endif /*< HOB_LOCAL_MENU_HPP_ */
