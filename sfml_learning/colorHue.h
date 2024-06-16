#pragma once
#include <SFML/Graphics.hpp>
#include "colorHue.h"

namespace CustomHueRotation {

	class ColorHueRotation 
	{
	private:
		float mHueAngle;
		float mHueAngleReal;

	public:
		sf::Vector3i colorRGB;
		void updateHue();
		ColorHueRotation(float startHueAngle);
		void rotateHue(float amount);
	};

}