#include "raycast.h"

// Constructor for a group of n objects.
Group::Group(int n) {

  this->_object = new Object3D*[n];
  this->_count  = n;
  for(int i = 0; i < n; i++) {
    this->_object[i] = NULL;
  }
}

// Destructor.
Group::~Group() {

  if (this->_object == NULL) {
    return;
  }

  for (int i = 0; i < this->_count; i++) {
    if (this->_object[i] != NULL) {
      delete this->_object[i];
    }
  }
  delete[] this->_object;
}

// Insert an object into the array.
void Group::addObject(int index, Object3D *obj) {

  this->_object[index] = obj;

}

bool Group::intersect(const Ray &r, Hit &h)
{

	bool success = false;

	//Create vars for empty hit object
	float t = INFINITY;
	Vec3f col;
	Hit hTemp(t, col);
	
	//For all objects in scene
	for(int i = 0; i < this->_count; i++)
	{
		//If there is an intersection
		bool test = this->_object[i]->intersect(r,hTemp);
		if(test)
		{
			success = true;
			if(hTemp.getT() < t)
			{
				//Fetch depth and object colour
				t = hTemp.getT();
				col = hTemp.getColor();
			};
		};
	};
	
	//If an intersection occurs
	if(success)
		//Update hit object
		h.set(t, col);

	return success;
}
