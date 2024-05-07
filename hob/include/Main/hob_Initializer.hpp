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
 * @file hob_Initializer.hpp
 * @author Gaina Stefan
 * @date 28.03.2024
 * @brief This file defines the class and method prototypes of the initializer.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_INITIALIZER_HPP_
#define HOB_INITIALIZER_HPP_

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

/** ***************************************************************************************************
 * @brief Class used to control the intialization of subsystems.
 * @details The initialization is done through constructor and deinitialization is done through
 * destructor. The object should be instantiated before everything else ensuring it will be the last
 * to do the clean-up.
 *****************************************************************************************************/
class Initializer final
{
public:
	/** ***********************************************************************************************
	 * @brief Checks for loaded libraries versions and initializes SDL, SDL image, SDL mixer, SDL ttf,
	 * and Plog in case of development builds.
	 * @param void
	 * @throws std::exception If the initialization of any of the subsystems fails.
	 *************************************************************************************************/
	Initializer(void) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Deinitializes SDL, SDL image, SDL mixer, SDL ttff and deinitializes Plog in case of
	 * development builds.
	 * @param void
	 *************************************************************************************************/
	~Initializer(void) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_INITIALIZER_HPP_ */
