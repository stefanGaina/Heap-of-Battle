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
 * @file hob_Units.cpp
 * @author Gaina Stefan
 * @date 14.02.2023
 * @brief This file implements the class defined in hob_Units.hpp.
 * @todo Implementation to be done.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <plog.h>

#include "hob_Units.hpp"
#include "hob_Faction.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Full file path of an image used by the timer.
 * @param name: The name of the image (without extension).
 * @return The full file path.
 *****************************************************************************************************/
#define TEXTURE_FILE_PATH(name) HOB_TEXTURES_FILE_PATH("units/" name)

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob
{

Units::Units(SDL_Renderer* const renderer) noexcept
	: TextureInitializer{ {
							  TEXTURE_FILE_PATH("alliance/infantry/figure"),				  /*< 0   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/death"),		  /*< 1   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/death1"),		  /*< 2   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down"),		  /*< 3   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down1"),		  /*< 4   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down2"),		  /*< 5   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down3"),		  /*< 6   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down_attack"),	  /*< 7   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down_attack2"),  /*< 8   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down_attack2"),  /*< 9   */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/down_attack3"),  /*< 10  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left"),		  /*< 11  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left1"),		  /*< 12  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left2"),		  /*< 13  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left3"),		  /*< 14  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left_attack"),	  /*< 15  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left_attack1"),  /*< 16  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left_attack2"),  /*< 17  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/left_attack3"),  /*< 18  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right"),		  /*< 19  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right1"),		  /*< 20  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right2"),		  /*< 21  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right3"),		  /*< 22  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right_attack"),  /*< 23  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right_attack1"), /*< 24  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right_attack2"), /*< 25  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/right_attack3"), /*< 26  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up"),			  /*< 27  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up1"),			  /*< 28  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up2"),			  /*< 29  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up3"),			  /*< 30  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up_attack"),	  /*< 31  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up_attack1"),	  /*< 32  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up_attack2"),	  /*< 33  */
							  TEXTURE_FILE_PATH("alliance/infantry/animation/up_attack3"),	  /*< 34  */
							  TEXTURE_FILE_PATH("alliance/ranged/figure"),					  /*< 35  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/death"),			  /*< 36  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/death1"),		  /*< 37  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/down"),			  /*< 38  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/down1"),			  /*< 39  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/down2"),			  /*< 40  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/down3"),			  /*< 41  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/down_attack"),	  /*< 42  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/down_attack2"),	  /*< 43  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/left"),			  /*< 44  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/left1"),			  /*< 45  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/left2"),			  /*< 46  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/left3"),			  /*< 47  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/left_attack"),	  /*< 48  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/left_attack1"),	  /*< 49  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/right"),			  /*< 50  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/right1"),		  /*< 51  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/right2"),		  /*< 52  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/right3"),		  /*< 53  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/right_attack"),	  /*< 54  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/right_attack1"),	  /*< 55  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/up"),			  /*< 56  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/up1"),			  /*< 57  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/up2"),			  /*< 58  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/up3"),			  /*< 59  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/up_attack"),		  /*< 60  */
							  TEXTURE_FILE_PATH("alliance/ranged/animation/up_attack1"),	  /*< 61  */
							  TEXTURE_FILE_PATH("alliance/cavalry/figure"),					  /*< 62  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/death"),		  /*< 63  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/death1"),		  /*< 64  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down"),			  /*< 65  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down1"),		  /*< 66  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down2"),		  /*< 67  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down3"),		  /*< 68  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down_attack"),	  /*< 69  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down_attack2"),	  /*< 70  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down_attack2"),	  /*< 71  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/down_attack3"),	  /*< 72  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left"),			  /*< 73  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left1"),		  /*< 74  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left2"),		  /*< 75  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left3"),		  /*< 76  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left_attack"),	  /*< 77  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left_attack1"),	  /*< 78  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left_attack2"),	  /*< 79  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/left_attack3"),	  /*< 80  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right"),		  /*< 81  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right1"),		  /*< 82  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right2"),		  /*< 83  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right3"),		  /*< 84  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right_attack"),	  /*< 85  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right_attack1"),  /*< 86  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right_attack2"),  /*< 87  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/right_attack3"),  /*< 88  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up"),			  /*< 89  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up1"),			  /*< 90  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up2"),			  /*< 91  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up3"),			  /*< 92  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up_attack"),	  /*< 93  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up_attack1"),	  /*< 94  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up_attack2"),	  /*< 95  */
							  TEXTURE_FILE_PATH("alliance/cavalry/animation/up_attack3"),	  /*< 96  */
							  TEXTURE_FILE_PATH("alliance/aircraft/figure"),				  /*< 97  */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/death"),		  /*< 98  */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/death1"),		  /*< 99  */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/down"),		  /*< 100 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/down1"),		  /*< 101 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/down2"),		  /*< 102 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/down_attack"),	  /*< 103 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/down_attack2"),  /*< 104 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/down_attack2"),  /*< 105 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/left"),		  /*< 106 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/left1"),		  /*< 107 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/left2"),		  /*< 108 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/left3"),		  /*< 109 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/left_attack"),	  /*< 110 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/left_attack1"),  /*< 111 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/left_attack2"),  /*< 112 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/right"),		  /*< 113 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/right1"),		  /*< 114 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/right2"),		  /*< 115 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/right3"),		  /*< 116 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/right_attack"),  /*< 117 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/right_attack1"), /*< 118 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/right_attack2"), /*< 119 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/up"),			  /*< 120 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/up1"),			  /*< 121 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/up2"),			  /*< 122 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/up3"),			  /*< 123 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/up_attack"),	  /*< 124 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/up_attack1"),	  /*< 125 */
							  TEXTURE_FILE_PATH("alliance/aircraft/animation/up_attack2"),	  /*< 126 */
							  TEXTURE_FILE_PATH("horde/infantry/figure"),					  /*< 127 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/death"),			  /*< 128 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/death1"),			  /*< 129 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down"),			  /*< 130 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down1"),			  /*< 131 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down2"),			  /*< 132 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down3"),			  /*< 133 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down_attack"),	  /*< 134 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down_attack2"),	  /*< 135 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down_attack2"),	  /*< 136 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/down_attack3"),	  /*< 137 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left"),			  /*< 138 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left1"),			  /*< 139 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left2"),			  /*< 140 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left3"),			  /*< 141 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left_attack"),	  /*< 142 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left_attack1"),	  /*< 143 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left_attack2"),	  /*< 144 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/left_attack3"),	  /*< 145 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right"),			  /*< 146 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right1"),			  /*< 147 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right2"),			  /*< 148 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right3"),			  /*< 149 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right_attack"),	  /*< 150 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right_attack1"),	  /*< 151 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right_attack2"),	  /*< 152 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/right_attack3"),	  /*< 153 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up"),				  /*< 154 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up1"),			  /*< 155 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up2"),			  /*< 156 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up3"),			  /*< 157 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up_attack"),		  /*< 158 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up_attack1"),		  /*< 159 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up_attack2"),		  /*< 160 */
							  TEXTURE_FILE_PATH("horde/infantry/animation/up_attack3"),		  /*< 161 */
							  TEXTURE_FILE_PATH("horde/ranged/figure"),						  /*< 162 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/death"),			  /*< 163 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/death1"),			  /*< 164 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down"),				  /*< 165 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down1"),			  /*< 166 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down2"),			  /*< 167 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down3"),			  /*< 168 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down_attack"),		  /*< 169 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down_attack2"),		  /*< 170 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down_attack2"),		  /*< 171 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/down_attack3"),		  /*< 172 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left"),				  /*< 173 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left1"),			  /*< 174 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left2"),			  /*< 175 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left3"),			  /*< 176 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left_attack"),		  /*< 177 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left_attack1"),		  /*< 178 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left_attack2"),		  /*< 179 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/left_attack3"),		  /*< 180 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right"),			  /*< 181 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right1"),			  /*< 182 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right2"),			  /*< 183 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right3"),			  /*< 184 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right_attack"),		  /*< 185 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right_attack1"),	  /*< 186 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right_attack2"),	  /*< 187 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/right_attack3"),	  /*< 188 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up"),				  /*< 189 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up1"),				  /*< 190 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up2"),				  /*< 191 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up3"),				  /*< 192 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up_attack"),		  /*< 193 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up_attack1"),		  /*< 194 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up_attack2"),		  /*< 195 */
							  TEXTURE_FILE_PATH("horde/ranged/animation/up_attack3"),		  /*< 196 */
							  TEXTURE_FILE_PATH("horde/cavalry/figure"),					  /*< 197 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/death"),			  /*< 198 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/death1"),			  /*< 199 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down"),			  /*< 201 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down1"),			  /*< 202 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down2"),			  /*< 203 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down3"),			  /*< 204 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down_attack"),		  /*< 205 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down_attack2"),	  /*< 206 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down_attack2"),	  /*< 207 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/down_attack3"),	  /*< 208 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left"),			  /*< 209 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left1"),			  /*< 210 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left2"),			  /*< 211 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left3"),			  /*< 212 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left_attack"),		  /*< 213 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left_attack1"),	  /*< 214 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left_attack2"),	  /*< 215 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/left_attack3"),	  /*< 216 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right"),			  /*< 217 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right1"),			  /*< 218 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right2"),			  /*< 219 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right3"),			  /*< 220 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right_attack"),	  /*< 221 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right_attack1"),	  /*< 222 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right_attack2"),	  /*< 223 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/right_attack3"),	  /*< 224 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up"),				  /*< 225 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up1"),				  /*< 226 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up2"),				  /*< 227 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up3"),				  /*< 228 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up_attack"),		  /*< 229 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up_attack1"),		  /*< 230 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up_attack2"),		  /*< 231 */
							  TEXTURE_FILE_PATH("horde/cavalry/animation/up_attack3")		  /*< 232 */
						  },
						  { /* No component is used. */ },
						  { /* No component is used. */ },
						  renderer }
	, components{}
{
}

void Units::draw(SDL_Renderer* const renderer) noexcept
{
	plog_verbose("Units are being drawn.");
	plog_assert(nullptr != renderer);

	for (auto component : components)
	{
		component.draw(renderer);
	}
}

void Units::add(const hobGame::Unit unit, const bool isAlliance) noexcept(false)
{
	Component component			 = {};
	size_t	  textureIndexOffset = 0UL;
	SDL_Rect  destination		 = { .x = 10 * HSCALE, .y = 14 * HSCALE, .w = 1 * HSCALE, .h = 1 * HSCALE };

	if (false == isAlliance)
	{
		textureIndexOffset = 135UL;
		destination		   = { .x = 10 * HSCALE, .y = 0 * HSCALE, .w = 1 * HSCALE, .h = 1 * HSCALE };
	}

	switch (unit)
	{
		case hobGame::Unit::NONE:
		{
			return;
		}
		case hobGame::Unit::INFANTRY:
		{
			component.updateTexture(textureContainer[0 + textureIndexOffset]);
			break;
		}
		case hobGame::Unit::RANGED:
		{
			break;
		}
		case hobGame::Unit::CAVALRY:
		{
			break;
		}
		case hobGame::Unit::AIRCRAFT:
		{
			break;
		}
		case hobGame::Unit::MAGE:
		{
			break;
		}
		default:
		{
			plog_error("Invalid unit! (unit: %" PRId32 ")", static_cast<int32_t>(unit));
			plog_assert(false);
			return;
		}
	}

	component.updatePosition(destination);
	try
	{
		components.push_back(component);
	}
	catch (const std::bad_alloc& exception)
	{
		plog_error("Failed to add unit into the component list!");
		throw exception;
	}
}

} /*< namespace hob */
