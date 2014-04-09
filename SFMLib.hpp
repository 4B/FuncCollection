#ifndef SFMLIB_H
#define SFMLIB_H

#include <SFML/Graphics.hpp>
#include <random>

namespace Func
{
	namespace Mouse
	{
		/*Returns the x world-coordinate of your mouse as int*/
		int x(){ return sf::Mouse::getPosition().x; };
		/*Returns the y world-coordinate of your mouse as int*/
		int y(){ return sf::Mouse::getPosition().y; };
		/*Returns the x window-coordinate of your mouse as int*/
		int x(const sf::RenderWindow &window){ return sf::Mouse::getPosition(window).x; };
		/*Returns the y window-coordinate of your mouse as int*/
		int y(const sf::RenderWindow &window){ return sf::Mouse::getPosition(window).y; };
	}

	namespace Shape
	{
		/*Returns a rectangleshape with specified parameters*/
		const sf::RectangleShape rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color)
		{
			sf::RectangleShape rectangle(size);
			rectangle.setPosition(position.x, position.y);
			rectangle.setFillColor(color);

			return rectangle;
		}

		/*Returns a circleshape with specified parameters*/
		const sf::CircleShape circle(sf::Vector2f position, float radius, sf::Color color)
		{
			sf::CircleShape circle(radius);
			circle.setPosition(position.x, position.y);
			circle.setFillColor(color);

			return circle;
		}

		/*Returns a triangle with specified parameters*/
		const sf::VertexArray triangle(sf::Vector2f pointOne, sf::Vector2f pointTwo, sf::Vector2f pointThree, sf::Color color)
		{
			sf::VertexArray triangle(sf::Triangles, 3);
			triangle[0] = pointOne;
			triangle[1] = pointTwo;
			triangle[2] = pointThree;

			triangle[0].color = color;
			triangle[1].color = color;
			triangle[2].color = color;

			return triangle;
		}
	}

	namespace Collision
	{
		/*Returns true if the rectangles collide*/
		bool intersect(const sf::RectangleShape &first, const sf::RectangleShape &second)
		{ 
			return first.getGlobalBounds().intersects(second.getGlobalBounds());
		}
		/*Returns true if the circles collide*/
		bool intersect(const sf::CircleShape &first, const sf::CircleShape &second)
		{
			sf::Vector2f mOne(first.getPosition().x + first.getRadius() / 2, first.getPosition().y + first.getRadius() / 2);
			sf::Vector2f mTwo(second.getPosition().x + second.getRadius() / 2, second.getPosition().y + second.getRadius() / 2);
			float distance = sqrt((mOne.x - mTwo.x) * (mOne.x - mTwo.x) + (mOne.y - mTwo.y) * (mOne.y - mTwo.y));
			if (first.getRadius() + second.getRadius() >= distance)
				return true;
			else
				return false;
		}
	}

	namespace Random
	{
		/*Internal stuff, there aren't any relevant functions for you*/
		namespace Detail
		{
			std::mt19937 rnd;
			bool i;
			void checkInit()
			{
				if (!i)
				{
					rnd.seed((unsigned)time(NULL));
					i = true;
				}
			};
		}

		/*Returns an integer in the range of min to max*/
		int getInt(int min, int max)
		{
			Detail::checkInit();
			std::uniform_int_distribution<int> uniform_dist(min, max);
			return uniform_dist(Detail::rnd);
		}
		/*Returns a double in the range of min to max*/
		double getDouble(double min, double max)
		{
			Detail::checkInit();
			std::uniform_real_distribution<double> uniform_dist(min, max);
			return uniform_dist(Detail::rnd);
		}
	}

	namespace Framerate
	{
		sf::Clock clock;
		/*Returns the FPS as int*/
		const int fps()
		{
			float currentTime = clock.restart().asSeconds();
			float f = 1.f / (currentTime);

			return static_cast<int>(f);
		}
	}
}

#endif
