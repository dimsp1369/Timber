#include <SFML/Graphics.hpp>

using namespace sf;

#include <iostream>

// This is where out game starts from
int main()
{
	// Create vidoe mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);


	// ****** Backgound *******
	// Create the texture to hold a graphic on the GPU
	Texture textureBG;
	textureBG.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBG;
	spriteBG.setTexture(textureBG);

	// Set the spriteBG to cover the screen
	spriteBG.setPosition(0, 0);


	// ****** Make a tree sprite ****** 
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// ******* Make a Bee sprite *******
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	// Is the bee moving?
	bool beeIsActive = false;
	// How bee is fast
	float beeSpeed = 0.0f;

	// ******* Make a Cloud sprite ******
	Texture textureCloud;
	// Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");
	// 3 New sprites with the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	// Position the clouds on the left of the screen
	// at different heights
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variable to control time
	Clock clock;


	while (window.isOpen()) {
		// Handle the player input

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// Update the screen
		// measure time
		Time dt = clock.restart();

		// Setup the bee
		if (!beeIsActive) {
			// How fast
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;
			// How High
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);
			beeIsActive = true;
		} else { 
			spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
			// Has the bee reached the left-hand edge of the screen?
			if (spriteBee.getPosition().x < -100) {
				// Set it up ready to be a whole new bee next frame
				beeIsActive = false;
			}
		}

		// Manage the clouds
		// Cloud 1
		if (!cloud1Active) {
			// How fast is the cloud
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);
			// How high is the cloud
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;
		} else {
			spriteCloud1.setPosition(
				spriteCloud1.getPosition().x +
				(cloud1Speed * dt.asSeconds()),
				spriteCloud1.getPosition().y);
			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud1.getPosition().x > 1920) {
				// Set it up ready to be a whole new cloud next frame
				cloud1Active = false;
			}
		}

		// Cloud 2
		if (!cloud2Active) {
			// How fast is the cloud
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);
			// How high is the cloud
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(-200, height);
			cloud2Active = true;
		} else {
			spriteCloud2.setPosition(
				spriteCloud2.getPosition().x +
				(cloud2Speed * dt.asSeconds()),
				spriteCloud2.getPosition().y);
			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud2.getPosition().x > 1920) {
				// Set it up ready to be a whole new cloud next frame
				cloud2Active = false;
			}
		}

		if (!cloud3Active) {
			// How fast is the cloud
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);
			// How high is the cloud
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(-200, height);
			cloud3Active = true;
		} else {
			spriteCloud3.setPosition(
				spriteCloud3.getPosition().x +
				(cloud3Speed * dt.asSeconds()),
				spriteCloud3.getPosition().y);
			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud3.getPosition().x > 1920) {
				// Set it up ready to be a whole new cloud next frame
				cloud3Active = false;
			}
		}

		// Draw the screen

		// Clear from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBG);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);
		// Show everything we just drew
		window.display();
	}

	return 0;
}
