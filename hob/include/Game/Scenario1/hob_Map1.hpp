/******************************************************************************************************
 * @file hob_Map1.hpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 27.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the class and method prototypes of the map of the first scenario.       *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef HOB_MAP1_H_
#define HOB_MAP1_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <thread>

#include "hob_Loop.hpp"
#include "hob_Menu.hpp"
// #include "hob_Chat.hpp"
#include "hob_Tiles1.hpp"
#include "hob_Buildings1.hpp"
#include "hob_Grid1.hpp"
#include "hob_Timer.hpp"

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
	 * @param void
	*/
	Map1(void);

	/**
	 * @brief Closes the socket and resets the cursor.
	 * @param void
	*/
	~Map1(void);

private:
	/**
	 * @brief Handles an event.
	 * @param event: event to be handled.
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
	 * @brief Menu background.
	*/
	Menu m_menu;

	// /**
	//  * @brief
	// */
	// Chat chat;

	/**
	 * @brief Playing board background.
	*/
	Tiles1 m_tiles;

	/**
	 * @brief Graphical representation of the buildings.
	*/
	Buildings1 m_buildings;

	/**
	 * @brief Lines between tiles and buildings.
	*/
	Grid1 m_grid;

	/**
	 * @brief Graphical representation of the time left.
	*/
	Timer m_timer;

	/**
	 * @brief Thread for receiving updates from the server.
	*/
	std::thread receivingThread;

	/**
	 * @brief Flag indicating if the receiving thread should still execute.
	*/
	bool receivingUpdates;
};

} /*< namespace hob */

#endif /*< HOB_MAP1_H_ */
