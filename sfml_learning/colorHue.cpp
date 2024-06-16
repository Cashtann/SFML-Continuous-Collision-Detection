#include "colorHue.h"
#include <iostream>

void CustomHueRotation::ColorHueRotation::updateHue()
{
    // This is converting Hue (0-360 deg) value into RGB (full brightness and saturation)
    // Based on a diagram

    // Setting R value
    if      ((mHueAngle >= 300) ||  (mHueAngle <= 60))              { colorRGB.x = 255; }
    else if ((mHueAngle >= 120) &&  (mHueAngle <= 240))             { colorRGB.x = 0; }
    else if ((mHueAngle > 60) &&    (mHueAngle < 120))              { colorRGB.x = (float)(((60-(mHueAngle - 60)) / 60) * 255); }
    else if ((mHueAngle > 240) &&   (mHueAngle < 300))              { colorRGB.x = (float)(((mHueAngle - 240) / 60) * 255); }
    else                                                            { colorRGB.x = 0; }

    // Setting G value
    if      ((mHueAngle >= 60) &&   (mHueAngle <= 180))             { colorRGB.y = 255; }
    else if ((mHueAngle >= 240) ||  (mHueAngle == 0))               { colorRGB.y = 0; }
    else if (mHueAngle < 60)                                        { colorRGB.y = (float)((mHueAngle / 60) * 255); }
    else if ((mHueAngle > 180) &&   (mHueAngle < 240))              { colorRGB.y = (float)(((60-(mHueAngle - 180)) / 60) * 255); }
    else                                                            { colorRGB.y = 0; }

    // Setting B value
    if      ((mHueAngle >= 180) &&  (mHueAngle <= 300))             { colorRGB.z = 255; }
    else if ((mHueAngle <= 120) ||  (mHueAngle == 0))               { colorRGB.z = 0; }
    else if ((mHueAngle > 120) &&   (mHueAngle < 180))              { colorRGB.z = (float)(((mHueAngle - 120) / 60) * 255); }
    else if (mHueAngle > 300)                                       { colorRGB.z = (float)(((60-(mHueAngle - 300)) / 60) * 255); }
    else                                                            { colorRGB.z = 0; }
}

CustomHueRotation::ColorHueRotation::ColorHueRotation(float startingHue)
{
    mHueAngle = (float)((int)startingHue % 360);
    mHueAngleReal = mHueAngle;
    updateHue();
}

void CustomHueRotation::ColorHueRotation::rotateHue(float amount)
{
    mHueAngleReal = mHueAngleReal += amount;
    if (mHueAngleReal > 360) { mHueAngleReal = 0.0f; }
    mHueAngle = (float)((int)(mHueAngleReal + amount) % 360);
    updateHue();
}
