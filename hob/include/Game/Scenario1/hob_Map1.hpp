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
// #include "hob_Menu.hpp"
// #include "hob_Chat.hpp"
// #include "hob_Tiles1.hpp"
// #include "hob_Buildings1.hpp"
#include "hob_Grid1.hpp"
#include "hob_Timer.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

namespace hob
{

class Map1 final : public Loop
{
public:
	/**
	 * @brief
	 * @param void
	*/
	Map1(void);

	/**
	 * @brief
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
	 * @brief
	 * @param void
	 * @return void
	*/
	void receivingFunction(void) noexcept;

	// /**
	//  * @brief
	//  * @param void
	//  * @return void
	// */
	// void onTimesUp(void) noexcept;

private:
	// /**
	//  * @brief
	// */
	// Menu menu;

	// /**
	//  * @brief
	// */
	// Chat chat;

	// /**
	//  * @brief
	// */
	// Tiles1 tiles;

	// /**
	//  * @brief
	// */
	// Buildings1 m_buildings;

	/**
	 * @brief
	*/
	Grid1 m_grid;

	/**
	 * @brief
	*/
	Timer m_timer;

	/**
	 * @brief
	*/
	std::thread receivingThread;

	/**
	 * @brief
	*/
	bool receivingUpdates;
};

} /*< namespace hob */

#endif /*< HOB_MAP1_H_ */
