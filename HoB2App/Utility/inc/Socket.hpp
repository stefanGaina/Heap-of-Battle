#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <thread>
#include <functional>
#include <winsock2.h>

#include "Types.hpp"

namespace Utility
{

/**
 * @brief TODO
*/
enum class MessageType
{
	END_COMMUNICATION = 0,
	VERSION           = 1,
	TEXT              = 2,
	END_TURN          = 3,
	TIME              = 4,
};

/**
 * @brief TODO
*/
union MessagePayload
{
	char     text[80];
	char     version[VERSION_STRING_SIZE];
	uint16_t timeLeft;
};

/**
 * @brief TODO
*/
struct Message
{
	MessageType    type;
	MessagePayload payload;
};

/**
 * @brief TODO
*/
class Socket final
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
	 * @brief Singleton way to get access to the socket object.
	 * @param void
	 * @return Reference to the socket instance.
	*/
	static Socket& getInstance(void) noexcept;

	/**
	 * @brief TODO
	 * @param callback 
	 * @return 
	*/
	bool createServer(Callback callback = nullptr) noexcept;

	/**
	 * @brief TODO
	 * @param ipAddress 
	 * @return 
	*/
	bool createClient(std::string ipAddress) noexcept;

	/**
	 * @brief TODO
	 * @param  
	 * @return 
	*/
	void clean(void) noexcept;

	/**
	 * @brief TODO
	 * @param updateMessage 
	 * @return 
	*/
	void receiveUpdates(Message& updateMessage) const noexcept;

	/**
	 * @brief TODO
	 * @param updateMessage 
	 * @return 
	*/
	void sendUpdate(const Message& updateMessage) const noexcept;

	/**
	 * @brief Prevents the creation of another object.
	 * @param otherSocket: instance to be copied.
	*/
	Socket(Socket& otherSocket) = delete;

	/**
	 * @brief Prevents the creation of another object.
	 * @param socket: instance to be copied.
	*/
	void operator=(const Socket& socket) = delete;

private:
	/**
	 * @brief Initializes the Windows Socket API, but does not create the socket implicitly.
	 * @param void
	*/
	Socket(void) noexcept;

	/**
	 * @brief Deinitializes the Windows Socket API and cleans the sockets if it was not already.
	 * @param void
	*/
	~Socket(void) noexcept;

	/**
	 * @brief TODO
	 * @param callback 
	 * @return 
	*/
	void waitConnectionFunction(Callback callback) noexcept;

	/**
	 * @brief TODO
	 * @param void
	 * @return void
	*/
	void closeServer(void) noexcept;

	/**
	 * @brief TODO
	 * @param void
	 * @return void
	*/
	void closeClient(void) noexcept;

private:
	/**
	 * @brief TODO
	*/
	SOCKET m_serverSocket;

	/**
	 * @brief TODO
	*/
	SOCKET m_clientSocket;

	/**
	 * @brief TODO
	*/
	std::thread m_waitConnectionThread;
}; /*< class Socket */

} /*< namespace Utility */

#endif /*< SOCKET_H_ */
