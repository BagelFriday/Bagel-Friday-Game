#include "ImagePool.h"

ImagePool::ImagePool()
{
}

sf::Image* ImagePool::loadWithPool(std::string filename)
{
	if (pool.count(filename) == 0)
	{
		// Image never added before, add it
		pool[filename] = new sf::Image();
		pool[filename]->LoadFromFile(filename);
		pool[filename]->SetSmooth(false);
	}

	return pool[filename];
}

ImagePool::~ImagePool()
{
	for (std::map< std::string, sf::Image* >::iterator it = pool.begin(); it != pool.end(); it++)
	{
		delete (*it).second;
	}
}