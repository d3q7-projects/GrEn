#pragma once

class Shape2D
{
	//TODO: (priority: 1) later in time we will change is so all shape are a post processing that will be able to use their depth value with the scene
	//					  this means that the draw function will be simplified to a boolean that says if the pixel is in the shape
	//					  preferably this will happen when we have a better defined multi-threaded rendering of post-processing effects
public:
	/// <summary>
	/// Draws on the frame and extras the shape if frame is defined correctly
	/// </summary>
	/// <param name="frame"> - pixels to draw on</param>
	/// <param name="frameExtras"> - extra data on the pixel</param>
	virtual void draw(void* frame, void* frameExtras, const int width, const int height) const= 0;
};

