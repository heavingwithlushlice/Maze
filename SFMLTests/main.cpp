#include <sfml\Graphics.hpp>
#include <iostream>
#include <cmath>

double pi = (2 * acos(0.0));
bool currentpillarvisible = 0;

int screenWidth = 1920;
int screenHeight = 1080;

float playerx = screenWidth / 2;
float playery = screenHeight;

float movey = 0;
float movex = 0;

const int levelwidth = 20;
const int levelheight = 20;
const int noOfFloors = 3;
float elevation = 1;

double getyPosOfPillar(double heightOfPillar, double elevation, int upperorlower) //0 = upper, 1 = lower
{
	if (upperorlower == 0)
	{
		return ((screenHeight / 2) - (heightOfPillar) / 2) - ((heightOfPillar)*(elevation - 1));
	}
	if (upperorlower == 1)
	{
		return ((screenHeight / 2) + (heightOfPillar) / 2) - ((heightOfPillar)*(elevation - 1));
	}

}

double narrow(double x, double y, double z)
{
	//x = x * (2000 / sqrt((y*y)+(x*x)));

	//x = x * (200000 / ((y*y) + (x*x)));

	//y = -sqrt((y*y) + (z*z)); //turn y into "distance" incorporating the z value too 

	x = x * -(2000 / y);

	return x;
}

double distancetolength(double distance)
{

	if (distance*distance == 0)
	{

		distance = 0.01; //prevent dividing by 0 to ensure distance is nonzero
	}

	//distance = 5 + (150000 / (distance*distance)); //convert a linear distance between the point and the player into a distance-scaled length
	
	distance = 5 + (150000 / (distance));;

	return distance;
}

double xytodistance(double x, double y, double z)
{

	//double distance = sqrt((x*x+y*y));

	double distance = y;

	return distance;
}

double arrayPosToCoord(double arraypos, double screenwidth, int arraywidth)
{

	double coord = (arraypos*(screenwidth / arraywidth));
	return coord;

}

int coordToarrayPos(double coord, double screenwidth, float arraywidth)
{

	int arraypos = coord / (screenwidth / arraywidth);
	return arraypos;

}

double calculatePillarCoords(int height, int width, float elevation, double angle, int switcher)
{

	double x = arrayPosToCoord(height, screenWidth, levelwidth);
	double y = arrayPosToCoord(width, screenHeight, levelheight);
	//double z = arrayPosToCoord(elevation, screenHeight, noOfFloors) - arrayPosToCoord(1, screenHeight, noOfFloors); //subtract the value of 1 converted into coords such that the ground level = 0 px in coords. 
	double z = (elevation - 1) * 100;


	x = x - playerx + movex; //shift the map to make the player the origin point
	y = y - (playery - movey);

	double newx = ((x)* cos(angle)) - (y)* sin(angle);
	double newy = ((y)* cos(angle) + (x)* sin(angle)); //rotate around the mouse position

	double distanceFromPlayer = xytodistance(newx, newy, z); //calculate the distance between the player located at origin and the point (to create distance scaling of heights)
	//distanceFromPlayer = sqrt((distanceFromPlayer*distanceFromPlayer) + z*z); //apply the trigonometry to the floor level (ie, if it's on ah igher or lower floor, treat it as further away

	newx = narrow(newx, newy, z); //artificially narrow x based on its y positioning (to get narrow as it gets furhter away)

	x = newx + playerx;
	y = newy + (playery); //reset the player away from the origin back to the player's location 

	distanceFromPlayer = distancetolength(distanceFromPlayer); //convert the distance from the player to a vertical "length" of pillar

	if (switcher == 0)
	{
		return x;
	}
	if (switcher == 1)
	{
		return y;
	}
	if (switcher == 2)
	{
		return distanceFromPlayer;
	}
}

int main()
{

    sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML", sf::Style::Close | sf::Style::Resize, settings);
	sf::RectangleShape player(sf::Vector2f(5.0f, 5.0f));
	player.setFillColor(sf::Color::Red);
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);



	int level[levelwidth][levelheight] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,0},
		{1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,0},
		{1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0},
		{1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0},
		{1,1,0,1,0,0,0,1,0,0,0,0,1,1,1,1,0,0,1,0},
		{1,0,0,1,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
		{1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	while (window.isOpen())
	{
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			
			}
		}
	
		sf::Vector2i currentMouse = sf::Mouse::getPosition(window);

		double angle = -((currentMouse.x - mousePos.x) / 10)*(2 * acos(0.0) / 180);
		double angle2 = -((currentMouse.y - mousePos.y))*(2 * acos(0.0) / 180);
		elevation = elevation + (angle2 / 100);


		if (angle != -((currentMouse.x - mousePos.x) / 10)*(2 * acos(0.0) / 180))
		{
			//window.clear();
			//printf("%f \n", angle);

			sf::Mouse::setPosition(sf::Vector2i(10, 50));
		}


		window.clear();
		
		
		int i = 1;

		for (int i = 1; i <= levelwidth; i++)
			
		{

			int width = i;

			for (int j = 1; j <= levelheight; j++)
			{
				
				int height = j;
				
				//sf::Vertex point(sf::Vector2f(height, width), sf::Color::White);


				if (level[width-1][height-1] == 1)
				{

					double x = calculatePillarCoords(height, width, elevation,  angle, 0);
					double y = calculatePillarCoords(height, width, elevation, angle, 1);
					double heightOfPillar = calculatePillarCoords(height, width, elevation, angle, 2);

					player.setSize(sf::Vector2f(5.0f, heightOfPillar));

					player.setPosition((float)x, (float)(getyPosOfPillar(heightOfPillar, elevation, 0))); //place the vertical pillar in the middle of the screen
			
					currentpillarvisible = 0; //presume it is not visible until it is (this is a global variable)

					if (playery > (y))
					{
						window.draw(player); //draw the new line 
						//printf("player drawn at %i %i", height, width);
						currentpillarvisible = 1; //declare that it is visible! 
					}

					//time to draw the roof and floor parts.... 

					double currentx = x;
					double currenty = getyPosOfPillar(heightOfPillar, elevation, 0);
					double currentHeight = heightOfPillar; //parameters for the current pillar that has just been drawn
					
					if (level[width][height - 1] == 1) //if there is one to the right... 

					{

						double x = calculatePillarCoords(height, width+1, elevation, angle, 0); //calculate values for the pillar to the right 
						double y = calculatePillarCoords(height, width+1, elevation, angle, 1);
						double heightOfPillar = calculatePillarCoords(height, width+1, elevation, angle, 2);
												
						sf::Vertex line[] =
						{
							sf::Vertex(sf::Vector2f(currentx, currenty)),
							sf::Vertex(sf::Vector2f(x,  getyPosOfPillar(heightOfPillar, elevation, 0)))
						};

						float linelength = x - currentx; //work out how long the convex shape is to prevent super long shapes going across the screen

						sf::ConvexShape convex;
						sf::ConvexShape convex2;

						convex.setPointCount(4);
						convex2.setPointCount(4);

						double NewMidy = getyPosOfPillar(heightOfPillar, elevation, 0) + (heightOfPillar / 2);
						double currentMidy = getyPosOfPillar(currentHeight, elevation, 0) + (currentHeight / 2);

						convex.setPoint(0, sf::Vector2f(currentx, currenty + currentHeight));
						convex.setPoint(1, sf::Vector2f(x, getyPosOfPillar(heightOfPillar, elevation, 1)));
						convex.setPoint(2, sf::Vector2f(x, NewMidy));
						convex.setPoint(3, sf::Vector2f(currentx, currentMidy));

						convex2.setPoint(0, sf::Vector2f(currentx, currenty));
						convex2.setPoint(1, sf::Vector2f(x, getyPosOfPillar(heightOfPillar, elevation, 0)));
						convex2.setPoint(2, sf::Vector2f(x, NewMidy));
						convex2.setPoint(3, sf::Vector2f(currentx, currentMidy));

						if (currentpillarvisible == 1)
						{

							if (fabs(linelength) < (screenWidth))
							{
								window.draw(convex2);
								window.draw(convex);
							}
							else
							{
								//printf("%f", linelength);

							}
						}

					}
					if (level[width-1][height] == 1) //if there is one below... 
					{

						double x = calculatePillarCoords(height+1, width, 1, angle, 0); //calculate values for the pillar to the right 
						double y = calculatePillarCoords(height+1, width, 1, angle, 1);
						double heightOfPillar = calculatePillarCoords(height+1, width, 1, angle, 2);

						float linelength = x - currentx; //work out how long the convex shape is to prevent super long shapes going across the screen

						sf::ConvexShape convex;
						sf::ConvexShape convex2;

						convex.setPointCount(4);
						convex2.setPointCount(4);

						double NewMidy = getyPosOfPillar(heightOfPillar, elevation, 0) + (heightOfPillar / 2);
						double currentMidy = getyPosOfPillar(currentHeight, elevation, 0) + (currentHeight / 2);


						convex.setPoint(0, sf::Vector2f(currentx, currenty + currentHeight));
						convex.setPoint(1, sf::Vector2f(x, getyPosOfPillar(heightOfPillar, elevation, 1)));
						convex.setPoint(2, sf::Vector2f(x, NewMidy));
						convex.setPoint(3, sf::Vector2f(currentx, NewMidy));

						convex2.setPoint(0, sf::Vector2f(currentx, currenty));
						convex2.setPoint(1, sf::Vector2f(x, getyPosOfPillar(heightOfPillar, elevation, 0)));
						convex2.setPoint(2, sf::Vector2f(x, NewMidy));
						convex2.setPoint(3, sf::Vector2f(currentx, NewMidy));

						if (playery > (y) || currentpillarvisible == 1)

						{

							if (fabs(linelength) < (screenWidth))
							{
								window.draw(convex2);
								window.draw(convex);

							}
						}


					}

				}

			}

		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			
			
			{

				movex = movex + sin(angle);
				movey = movey + cos(angle);

			}		

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			
			{

				movex = movex - sin(angle);
				movey = movey - cos(angle);

			}
		
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
						
			{

				movex = movex + sin(angle + (pi / 2));
				movey = movey + cos(angle + (pi / 2));

			}
						
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			
				movex = movex + sin(angle - (pi / 2));
				movey = movey + cos(angle - (pi / 2));
				
		}

	
		if (sf::Mouse::getPosition(window) != mousePos)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		}

		window.display();
	
	}

	return 0;
}


