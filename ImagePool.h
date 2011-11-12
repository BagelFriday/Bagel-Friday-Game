#ifndef IMAGEPOOL
#define IMAGEPOOL

#include <map>
#include <SFML/Graphics.hpp>

class ImagePool
{
private:
	std::map< std::string, sf::Image* > pool;
public:
	ImagePool();

	sf::Image* loadWithPool(std::string filename);

	~ImagePool();
};

#endif // IMAGEPOOL