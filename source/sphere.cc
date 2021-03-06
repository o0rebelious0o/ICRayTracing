#include "raycast.h"

// Add any code you need here and in the corresponding header
// file.


Sphere::Sphere()
{
	//Instantiate Basic Sphere
	this->_color = {0.0, 0.0, 0.0};
	this->centre = {0.0, 0.0, 0.0};
	this->radius = 0.0;
}



Sphere::Sphere(Vec3f centre, float radius, Vec3f color)
{
	//Create Sphere with Values
	this->centre = centre;
	this->radius = radius;
	this->_color = color;
}


bool Sphere::intersect(const Ray &r, Hit &h)
{
	float aCoeff, bCoeff, cCoeff, det, intersect1, intersect2;
	
	//The following as calculated using the information in the formula given in Lecture 10, slide 12
	Vec3f deltaChange = r.getOrigin()-centre;

	aCoeff = 1.0;
	bCoeff = r.getDirection().Dot3( deltaChange );
	cCoeff = deltaChange.Length() * deltaChange.Length() - radius * radius;
	
	det = bCoeff*bCoeff-cCoeff;

	//Imaginary Intercepts
	if(det < 0)
		return false;

	intersect1 = (-aCoeff * bCoeff + sqrt(det));
	intersect2 = (-aCoeff * bCoeff - sqrt(det));

	//Not in field of view
	if (intersect1 < 0) intersect1 = INFINITY;
	if (intersect2 < 0) intersect2 = INFINITY;

	//Neither intersect visible
	if (intersect1 == INFINITY && intersect2 == INFINITY)
		return false;

	//If intersect one is in view and closer
	if(intersect1 < intersect2)
	{
		if(intersect1 < h.getT())
			h.set(intersect1, _color);
	}
	else
	{
		if(intersect2 < h.getT())
			h.set(intersect2, _color);
	};

	return true;
}
