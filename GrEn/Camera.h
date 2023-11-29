#pragma once
#include "Window.h"
#include "GrEnDefinitions.h"
#include "GeometryGroup.h"
#include "Geometry.h"
#include "GrEnException.h"

#define GEOMETRY_GROUPS_PER_FRAME 128
#define GEOMETRIES_PER_FRAME 512
#define FAR_PLANE 1000.0f
#define NEAR_PLANE 0.1f

enum class Projection
{
	Perspective,
	Orthographic,
};

class Window;
class Camera
{
public:
	Camera(const int w, const int h, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p);
	Camera(Window& window, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p);

	GrEn::vec3<float> getPos() const;
	GrEn::vec3<float> getDir() const;
	float getFov() const;
	int getWidth() const;
	int getHeight() const;

	void setPos(const GrEn::vec3<float>& position);
	void setDir(const GrEn::vec3<float>& direction);
	void setFov(const float& fov);
	void setWidth(const int& width);
	void setHeight(const int& height);
	
	void getInversePointAtMat(GrEn::mat4<float>& mat);
	void getObjectToScreenMat(GrEn::mat4<float>& mat);

	void addGeometry(Geometry* mesh); //might change from const when we add vertex shaders
	void addGeometryGroup(GeometryGroup* mesh); //same as above

	void render();

private:
	void calcInversePointAtMat();
	void calcObjectToScreenMat();
	void updateFields();
	void* outputColor;
	struct frameExtra* pixelExtras;
	
	GrEn::vec3<float> worldPosition;
	GrEn::vec3<float> direction;
	float fov;
	int width;
	int height;
	Projection projection;

	GrEn::mat4<float> inversePointtAtMat;
	GrEn::mat4<float> objectToScreenMat;
	
	GeometryGroup** meshGroups;
	Geometry** meshes;
	
	Window* attachedWindow;

	int meshGroupsBound;
	int meshesBound;

};

