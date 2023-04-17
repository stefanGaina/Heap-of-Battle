#ifndef MAP1_H_
#define MAP1_H_

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <thread>

#include "Loop.hpp"
#include "Menu.hpp"
#include "Chat.hpp"
#include "Tiles1.hpp"
#include "Buildings1.hpp"
#include "Grid1.hpp"
#include "Timer.hpp"

namespace Game
{

class Map1 final : public Common::Loop
{
public:
	Map1(void);
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

private:
	void receivingFunction(void) noexcept;

	void onTimesUp(void) noexcept;

private:
	Menu menu;
	Chat chat;

	Tiles1 tiles;
	Buildings1 m_buildings;
	Grid1 grid;
	Timer timer;

	std::thread receivingThread;

	bool receivingUpdates;
}; /*< class Map1 */

} /*< namespace Game */

#endif /*< MAP1_H_ */
