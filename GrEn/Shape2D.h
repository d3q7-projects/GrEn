#pragma once

class Shape2D
{
public:
	/// <summary>
	/// Draws on the frame and extras the shape if frame is defined correctly
	/// </summary>
	/// <param name="frame"> - pixels to draw on</param>
	/// <param name="frameExtras"> - extra data on the pixel</param>
	virtual void draw(void* frame, void* frameExtras) const= 0;
};

