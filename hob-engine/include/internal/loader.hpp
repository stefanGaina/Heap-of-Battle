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
 * @file loader.hpp
 * @author Gaina Stefan
 * @date 18.12.2024
 * @brief This header defines the loader class.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef HOB_ENGINE_INTERNAL_LOADER_HPP_
#define HOB_ENGINE_INTERNAL_LOADER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include "details/visibility.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

/** ***************************************************************************************************
 * @brief This static class abstracts loading resources with throwing exceptions in case of failure.
 *****************************************************************************************************/
class HOB_ENGINE_LOCAL loader final
{
public:
	/** ***********************************************************************************************
	 * @brief Loads a texture from an image file on disk.
	 * @details The supported image formats are: bmp, png, tga, jpg, gif, psd, hdr and pic. Some format
	 * options are not supported, like progressive jpeg. For more details check sf::Texture's
	 * documentation. It is thread-safe.
	 * @param file_path: The path of the image file to load.
	 * @param x: The left coordinate of the rectangle to load from the image.
	 * @param y: The top coordinate of the rectangle to load from the image.
	 * @param width: The width of the rectangle to load from the image.
	 * @param height: The height of the rectangle to load from the image.
	 * @returns The successfully loaded texture.
	 * @throws std::runtime_error: If loading the texture fails.
	 *************************************************************************************************/
	[[nodiscard]] static sf::Texture
	load_texture(const std::string& file_path, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Loads a font from a file on disk.
	 * @details The supported font formats are: TrueType, Type 1, CFF, OpenType, SFNT, X11 PCF, Windows
	 * FNT, BDF, PFR and Type 42. For more details check sf::Font's documentation. It is thread-safe.
	 * @param file_path: The path of the font file to load.
	 * @returns The successfully loaded font.
	 * @throws std::runtime_error: If loading the font fails.
	 *************************************************************************************************/
	[[nodiscard]] static sf::Font load_font(const std::string& file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Creates a sprite from a loaded texture and configures it.
	 * @details For more details check sf::Sprite's documentation. It is thread-safe.
	 * @param textures: Container with all the loaded textures.
	 * @param texture_index: The index coresponding to the sprite's to be created source texture.
	 * @param x: The horizontal position on the screen of the sprite to be created.
	 * @param y: The vertical position on the screen of the sprite to be created.
	 * @param width: The width of the sprite to be created.
	 * @param height The height of the sprite to be created.
	 * @returns The successfully created sprite.
	 * @throws std::out_of_range: If the texture's index is invalid.
	 * @throws std::bad_alloc: If allocating memory for the sprite fails.
	 *************************************************************************************************/
	[[nodiscard]] static std::shared_ptr<sf::Sprite>
	load_sprite(const std::vector<sf::Texture>& textures, std::size_t texture_index, float x, float y, float width, float height) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Creates a text from a loaded font and configures it.
	 * @details For more details check sf::Text's documentation. It is thread-safe.
	 * @param fonts: Container with all the loaded fonts.
	 * @param font_index: The index coresponding to the text's to be created source font.
	 * @param string: The to be created text's string.
	 * @param color: The fill color of the text to be created.
	 * @param position: The position on the screen of the text to be created.
	 * @param character_size: The character size (in pixels) of the text to be created.
	 * @returns The successfully created text.
	 * @throws std::out_of_range: If the font's index is invalid.
	 * @throws std::bad_alloc: If allocating memory for the text fails.
	 *************************************************************************************************/
	[[nodiscard]] static std::shared_ptr<sf::Text>
	load_text(const std::vector<sf::Font>& fonts,
			  std::size_t				   font_index,
			  const std::string&		   string,
			  const sf::Color&			   color,
			  const sf::Vector2f&		   position,
			  std::uint32_t				   character_size) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Opens a music from an audio file.
	 * @details The supported audio formats are: WAV (PCM only), OGG/Vorbis, FLAC. For more details
	 * check sf::Music's documentation. It is thread-safe.
	 * @param music: The object that will open the audio file. The loop is enabled by default.
	 * @param file_path: The path of the music file to open.
	 * @returns void
	 * @throws std::runtime_error: If opening the music fails.
	 *************************************************************************************************/
	static void load_music(sf::Music& music, const std::string& file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Loads a sound buffer from a file.
	 * @details The supported audio formats are: WAV (PCM only), OGG/Vorbis, FLAC. For more details
	 * check sf::SoundBuffer's documentation. It is thread-safe.
	 * @param file_path: The path of the sound file to load.
	 * @returns The successfully loaded sound buffer.
	 * @throws std::runtime_error: If loading the sound buffer fails.
	 *************************************************************************************************/
	[[nodiscard]] static sf::SoundBuffer load_sound_buffer(const std::string& file_path) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Creates a sound from a loaded sound buffer.
	 * @details For more details check sf::Sound's documentation. It is thread-safe.
	 * @param sound_buffers: Container with all the loaded sound buffers.
	 * @param buffer_index The index coresponding to the sound's to be created source buffer.
	 * @returns The successfully created sound.
	 * @throws std::out_of_range: If the sound buffer's index is invalid.
	 *************************************************************************************************/
	[[nodiscard]] static sf::Sound load_sound(const std::vector<sf::SoundBuffer>& sound_buffers, std::size_t buffer_index) noexcept(false);
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_INTERNAL_LOADER_HPP_ */
