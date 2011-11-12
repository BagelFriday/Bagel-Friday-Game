#ifndef RESOURCE
#define RESOURCE

#include "Entity.h"

class Resource: public Entity
{
private:
public:
	std::string type;

	float probability;

	Resource();

	Resource(std::string _type, float _probability);
};

#endif // RESOURCE