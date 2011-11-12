#include "Resource.h"

Resource::Resource()
{
}

Resource::Resource(std::string _type, float _probability)
{
	type = _type;
	probability = _probability;
}