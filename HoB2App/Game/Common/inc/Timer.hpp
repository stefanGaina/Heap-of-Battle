#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

#include "IDrawable.hpp"
#include "TextureInitializer.hpp"

namespace Game
{

class Timer : public Common::TextureInitializer<22ULL, 4ULL>
{
public:
	/**
	 * @brief TODO
	*/
	using CallbackFunction = std::function<void(void)>;

	/**
	 * @brief TODO
	*/
	using Callback = std::shared_ptr<CallbackFunction>;

	/**
	 * @brief TODO
	 * @param void
	*/
	Timer(void) noexcept;

	/**
	 * @brief TODO
	 * @param void
	*/
	~Timer(void) noexcept;

	/**
	 * @brief TODO
	 * @param seconds 
	 * @return void
	*/
	void updateEnemyTime(uint16_t seconds) noexcept;

	/**
	 * @brief TODO
	 * @param seconds 
	 * @param callback 
	 * @return void
	*/
	void start(uint16_t seconds, Callback callback = nullptr) noexcept;

	/**
	 * @brief TODO
	 * @param  
	 * @return void
	*/
	void stop(void) noexcept;

	/**
	 * @brief TODO
	 * @param isAlliance 
	 * @return void
	*/
	static void setTextures(bool isAlliance) noexcept;

private:
	/**
	 * @brief TODO
	 * @param callback 
	 * @return void
	*/
	void countingFunction(Callback callback) noexcept;

	/**
	 * @brief TODO
	 * @param void
	 * @return void
	*/
	void updateTextures(void) noexcept;

private:
	/**
	 * @brief TODO
	*/
	static std::array<std::string, 22ULL> s_filePaths;

	/**
	 * @brief TODO
	*/
	static bool s_interruptWait;

	/**
	 * @brief TODO
	*/
	uint16_t m_timeLeft;

	/**
	 * @brief TODO
	*/
	std::mutex m_mutex;

	/**
	 * @brief TODO
	*/
	std::thread m_countingThread;

	/**
	 * @brief TODO
	*/
	std::mutex m_waitMutex;

	/**
	 * @brief TODO
	*/
	std::condition_variable m_waitTime;
}; /*< class Timer */

} /*< namespace Game */

#endif /*< TIMER_HPP_ */
