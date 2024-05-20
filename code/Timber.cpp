#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

// Functions declaration

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
// Where is the player/branch?
// Left ot right
enum class side {
    LEFT, RIGHT, NONE
};
side branchPositions[NUM_BRANCHES];

// This is where out game starts from
int main() {
    // Create video mode object
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

    // ****** Player ********
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    // the player starts on the LEFT side
    side playerSide = side::LEFT;

    // prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");

    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);
    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // preparing the flying log
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");

    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // Control the player input
    bool acceptInput = false;

    // ****** Player END ********

    // ****** Sound *******

    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    // ****** Sound END*******

    // Time control
    // Variable to control time
    Clock clock;
    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Track whether the game is running
    bool paused = true;

    // ***** Draw some text *****
    int score = 0;
    Text messageText;
    Text scoreText;
    // We need to choose a font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    messageText.setFont(font);
    scoreText.setFont(font);

    // Set the message content
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");
    // Set the number of characters
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    // Choose the text color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // Set Text Position
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    // ***** Make  Branches Sprite *****
    // Prepare 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    // Set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        // Set the sprite's origin to dead centre
        // We can then spin it round without changing its position
        branches[i].setOrigin(220, 20);
    }


    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);

    while (window.isOpen()) {
        // Handle the player input

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                //Listen for key press again
                acceptInput = true;
                // hide the axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Start the game
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            // Reset the time and the score
            score = 0;
            timeRemaining = 6;

            // Make all branches disappear
            for (int i = 1; i < NUM_BRANCHES; i++) {
                branchPositions[i] = side::NONE;
            }

            // hide the gravestone
            spriteRIP.setPosition(675, 2000);

            // MOve the player into position
            spritePlayer.setPosition(580, 720);
            acceptInput = true;
        }

        // Listen the player control
        if (acceptInput) {
            if (Keyboard::isKeyPressed((Keyboard::Right))) {
                playerSide = side::RIGHT;
                score++;
                // Add the amout of time remaining
                timeRemaining += (2 / score) + 0.15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);
                // Update the branches
                updateBranches(score);

                // Set the log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
                chop.play();
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                // Make sure the player is on the left
                playerSide = side::LEFT;
                score++;
                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT,
                                      spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);
                // update the branches
                updateBranches(score);
                // set the log flying
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logActive = true;
                acceptInput = false;
                chop.play();
            }
        }

        // Update the screen

        if (!paused) {
            // measure time
            Time dt = clock.restart();
            // Subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();
            // size up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {

                // Pause the game
                paused = true;
                // Change the message shown to the player
                messageText.setString("Out of time!!");
                //Reposition the text based on its new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left +
                                      textRect.width / 2.0f,
                                      textRect.top +
                                      textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                outOfTime.play();
            }

            // Setup the bee
            if (!beeIsActive) {
                // How fast
                srand((int) time(0));
                beeSpeed = (rand() % 200) + 200;
                // How High
                srand((int) time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeIsActive = true;
            } else {
                spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                                      spriteBee.getPosition().y);
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
                srand((int) time(0) * 10);
                cloud1Speed = (rand() % 200);
                // How high is the cloud
                srand((int) time(0) * 10);
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
                srand((int) time(0) * 20);
                cloud2Speed = (rand() % 200);
                // How high is the cloud
                srand((int) time(0) * 20);
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
                srand((int) time(0) * 30);
                cloud3Speed = (rand() % 200);
                // How high is the cloud
                srand((int) time(0) * 30);
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
            // Update the score text
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            // update the branch sprites
            for (int i = 0; i < NUM_BRANCHES; i++) {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT) {
                    // Move the sprite to the left side
                    branches[i].setPosition(610, height);
                    // Flip the sprite round the other way
                    branches[i].setRotation(180);
                } else if (branchPositions[i] == side::RIGHT) {
                    // Move the sprite to the right side
                    branches[i].setPosition(1330, height);
                    // Set the sprite rotation to normal
                    branches[i].setRotation(0);
                } else {
                    // Hide the branch
                    branches[i].setPosition(3000, height);
                }
            }

            // Handling a flying log
            if (logActive) {
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                                      spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                // Has the log reached the right hand edge?
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }

            // has the player been squished byt a branch
            if (branchPositions[5] == playerSide) {
                // death
                paused = true;
                acceptInput = false;

                // Draw the gravestone
                spriteRIP.setPosition(525, 760);
                // hide player
                spritePlayer.setPosition(2000, 660);
                //Change the text of the message
                messageText.setString("SQUISHED!!");
                // Center it on the screen
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                      textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                death.play();
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
        // Draw the branches
        for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }
        window.draw(spriteTree);
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);
        window.draw(spriteBee);
        // Draw the score
        window.draw(scoreText);
        // Draw the timebar
        window.draw(timeBar);
        if (paused) {
            // Draw our message
            window.draw(messageText);
        }
        // Show everything we just drew
        window.display();
    }

    return 0;
}

// Funstions Definitions

void updateBranches(int seed) {
    // Move all the branches down one place
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    // Spawn a new branch at position 0
    // LEFT, RIGHT or NONE
    srand((int) time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}
