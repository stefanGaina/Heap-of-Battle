#ifndef MULTIPLAYER_H_
#define MULTIPLAYER_H_

#include <mutex>

#include "Loop.hpp"
#include "Socket.hpp"

namespace Menu
{

class Multiplayer final : public Common::Loop
{
public:
	Multiplayer(void) noexcept;
	~Multiplayer(void) noexcept;

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

	void connectionDoneCallback(void) noexcept;

private:
	Utility::Socket::Callback callback;

	std::mutex callbackMutex;

}; /*< class Multiplayer */

} /*< namespace Menu */

#endif /*< MULTIPLAYER_H_ */
