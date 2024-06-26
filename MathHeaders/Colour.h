#pragma once

#include <cstdint>

namespace MathClasses
{
	struct Colour
	{
		std::uint32_t colour;

		Colour() {
			SetRed(0);
			SetGreen(0);
			SetBlue(0);
			SetAlpha(255);
		}

		Colour(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
		{
			SetRed(red);
			SetGreen(green);
			SetBlue(blue);
			SetAlpha(alpha);
		}

		bool operator == (Colour other)
		{
			if (this->colour == other.colour)
			{
				return true;
			}
			return false;
		}

		//returning unsigned char only returns last 8 bits
		unsigned char GetRed() const
		{
			return colour >> 24;
		}

		unsigned char GetGreen() const
		{
			return colour >> 16;
		}

		unsigned char GetBlue() const
		{
			return colour >> 8;
		}

		unsigned char GetAlpha() const
		{
			return colour;
		}

		void SetRed(unsigned char red)
		{
			//Push red bits into correct pos
			unsigned int v = (unsigned int)red << 24;
			//clear current red values
			colour = colour & 0x00ffffff;
			//put new red vals into place
			colour = colour | v;
		}

		void SetGreen(unsigned char green)
		{
			unsigned int v = (unsigned int)green << 16;
			colour = colour & 0xff00ffff;
			//pipe copies a bit to the evaluated result if it exists in any of the operand
			colour = colour | v;
		}

		void SetBlue(unsigned char blue)
		{
			unsigned int v = (unsigned int)blue << 8;
			colour = colour & 0xffff00ff;
			colour = colour | v;
		}

		void SetAlpha(unsigned char Alpha)
		{
			unsigned int v = (unsigned int)Alpha;
			colour = colour & 0xffffff00;
			colour = colour | v;
		}

	};
}