/******************************************************************************************************
 * Copyright (C) 2024 Gaina Stefan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file visibility.hpp
 * @author Gaina Stefan
 * @date 17.12.2024
 * @brief This header defines the visibility attribute when compiling hob-engine.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENGINE_DETAILS_VISIBILITY_HPP_
#define HOB_ENGINE_DETAILS_VISIBILITY_HPP_

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

#ifdef HOB_ENGINE_BUILD

#ifdef __GNUC__

/** ***************************************************************************************************
 * @brief Defines the visibility attribute for exported symbols.
 *****************************************************************************************************/
#define HOB_ENGINE_API __attribute__((visibility("default")))

/** ***************************************************************************************************
 * @brief Defines the visibility attribute for hidden symbols.
 *****************************************************************************************************/
#define HOB_ENGINE_LOCAL __attribute__((visibility("hidden")))

#else

#error "hob-engine requires g++ to be compiled."

#endif /*< __GNUC__ */

#else

/** ***************************************************************************************************
 * @brief The engine is not being built.
 *****************************************************************************************************/
#define HOB_ENGINE_API

/** ***************************************************************************************************
 * @brief The engine is not being built.
 *****************************************************************************************************/
#define HOB_ENGINE_LOCAL

#endif /*< HOB_ENGINE_BUILD */

#endif /*< HOB_ENGINE_DETAILS_VISIBILITY_HPP_ */
