#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class GameObject {
public:
    sf::Vector2f position;
    sf::Vector2f size;

    GameObject(float x, float y, float w, float h) : position(x, y), size(w, h) {}

    virtual void handleInput(sf::Time elapsed, unsigned int width) = 0;
    virtual void update(sf::Time elapsed, sf::FloatRect box, unsigned int width, unsigned int height, sf::Text& textL, sf::Text& textR, unsigned int& counterL, unsigned int& counterR) = 0;
    virtual void draw(sf::RenderWindow& window, sf::Text& textL, sf::Text& textR) = 0;
    virtual sf::FloatRect getBounds() = 0;
    virtual ~GameObject() {}
};

class Ball : public GameObject
{
public:
    sf::CircleShape ballshape;
    sf::Vector2f velocityOfBall;

    Ball(float x, float y, float speedX, float speedY, float radius, float facecount) : GameObject(x, y, radius, radius), velocityOfBall(speedX, speedY), ballshape(radius, facecount)
    {
        ballshape.setPosition(x, y);
    }

    void handleInput(sf::Time elapsed, unsigned int width) override
    {

    }

    void update(sf::Time elapsed, sf::FloatRect box, unsigned int width, unsigned int height, sf::Text& textL, sf::Text& textR, unsigned int& counterL, unsigned int& counterR) override
    {
        sf::FloatRect ballBox = ballshape.getGlobalBounds();
        ballshape.move(velocityOfBall * elapsed.asSeconds());


        if (ballshape.getPosition().y < 0 || ballshape.getPosition().y > 700)
        {
            velocityOfBall.y = -velocityOfBall.y;
            if (abs(velocityOfBall.y) < 1000 && abs(velocityOfBall.x) < 1000)
            {
                velocityOfBall.y = velocityOfBall.y * 1.01;
                velocityOfBall.x = velocityOfBall.x * 1.01;
            }
        }
        if (ballshape.getPosition().x < 0 || ballshape.getPosition().x > 1260)
        {
            if (ballshape.getPosition().x > 1260)
            {
                counterL++;
                textL.setString(std::to_string(counterL));
            }
            if (ballshape.getPosition().x < 0)
            {
                counterR++;
                textR.setString(std::to_string(counterR));
            }
            int randomNumber = (std::rand() % 2 == 0) ? -200 : 200;
            velocityOfBall.x = randomNumber;
            velocityOfBall.y = 0.f;
            ballshape.setPosition(float(width / 2.0), float(height / 2.0));
        }
        if (ballBox.intersects(box) && velocityOfBall.x > 0 && ballshape.getPosition().x > (width / 2))
        {
            velocityOfBall.x = -velocityOfBall.x;
            //std::cout << "colsion desni: " << box.getPosition().y << std::endl;
            if (abs(velocityOfBall.y) < abs(velocityOfBall.x))
            {
                if ((ballshape.getPosition().y - box.getPosition().y) <= 20)
                {
                    velocityOfBall.y = -abs(velocityOfBall.x / 3);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 40 && (ballshape.getPosition().y - box.getPosition().y) > 20)
                {
                    velocityOfBall.y = -abs(velocityOfBall.x / 7);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 60 && (ballshape.getPosition().y - box.getPosition().y) > 40)
                {
                    velocityOfBall.y = -abs(velocityOfBall.x / 20);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 80 && (ballshape.getPosition().y - box.getPosition().y) > 60)
                {
                    velocityOfBall.y = abs(velocityOfBall.x / 20);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 100 && (ballshape.getPosition().y - box.getPosition().y) > 80)
                {
                    velocityOfBall.y = abs(velocityOfBall.x / 7);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 120 && (ballshape.getPosition().y - box.getPosition().y) > 100)
                {
                    velocityOfBall.y = abs(velocityOfBall.x / 3);
                }
            }
        }
        else if (ballBox.intersects(box) && velocityOfBall.x < 0 && ballshape.getPosition().x < (width / 2))
        {
            velocityOfBall.x = -velocityOfBall.x;

            if (abs(velocityOfBall.y) < abs(velocityOfBall.x))
            {
                //std::cout << "KOLIZIJA CALC" << (ballshape.getPosition().y - box.getPosition().y) << std::endl;
                if ((ballshape.getPosition().y - box.getPosition().y) <= 20)
                {
                    velocityOfBall.y = -abs(velocityOfBall.x / 3);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 40 && (ballshape.getPosition().y - box.getPosition().y) > 20)
                {
                    velocityOfBall.y = -abs(velocityOfBall.x / 7);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 60 && (ballshape.getPosition().y - box.getPosition().y) > 40)
                {
                    velocityOfBall.y = -abs(velocityOfBall.x / 20);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 80 && (ballshape.getPosition().y - box.getPosition().y) > 60)
                {
                    velocityOfBall.y = abs(velocityOfBall.x / 20);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 100 && (ballshape.getPosition().y - box.getPosition().y) > 80)
                {
                    velocityOfBall.y = abs(velocityOfBall.x / 7);
                }
                else if ((ballshape.getPosition().y - box.getPosition().y) <= 120 && (ballshape.getPosition().y - box.getPosition().y) > 100)
                {
                    velocityOfBall.y = abs(velocityOfBall.x / 3);
                }
            }
            //std::cout << "KOLIZIJA KALK " << (ballshape.getPosition().y - box.getPosition().y) << std::endl;
            //std::cout << "colsion ljevi: " << box.getPosition().y << std::endl;
            //std::cout << "pozicija loptice: " << ballshape.getPosition().y << std::endl;
        }
        //std::cout << abs(velocityOfBall.x) << "   " << abs(velocityOfBall.y) << std::endl;
        //std::cout << box.getPosition().y << std::endl;
    }

    void draw(sf::RenderWindow& window, sf::Text& textL, sf::Text& textR) override
    {
        window.draw(ballshape);
        window.draw(textL);
        window.draw(textR);

    }

    sf::FloatRect getBounds() override
    {
        return ballshape.getGlobalBounds();
    }
};


class Paddle : public GameObject
{
public:
    sf::RectangleShape paddleShape;
    sf::Vector2f paddleSpeed;

    Paddle(float x, float y, float w, float h, float speedY) : GameObject(x, y, w, h), paddleSpeed(0.f, speedY), paddleShape(sf::Vector2f(w, h))
    {
        paddleShape.setPosition(x, y);
    }

    void handleInput(sf::Time elapsed, unsigned int width) override
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddleShape.getPosition().y > 0 && paddleShape.getPosition().x < (width / 2))
        {
            paddleShape.move(0, -600.f * elapsed.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddleShape.getPosition().y < 600 && paddleShape.getPosition().x < (width / 2))
        {
            paddleShape.move(0, 600.f * elapsed.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddleShape.getPosition().y > 0 && paddleShape.getPosition().x > (width / 2))
        {
            paddleShape.move(0, -600.f * elapsed.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddleShape.getPosition().y < 600 && paddleShape.getPosition().x >(width / 2))
        {
            paddleShape.move(0, 600.f * elapsed.asSeconds());
        }
    }

    void update(sf::Time elapsed, sf::FloatRect box, unsigned int width, unsigned int height, sf::Text& textL, sf::Text& textR, unsigned int& counterL, unsigned int& counterR) override
    {

    }

    void draw(sf::RenderWindow& window, sf::Text& textL, sf::Text& textR) override
    {
        window.draw(paddleShape);
    }

    sf::FloatRect getBounds() override
    {
        return paddleShape.getGlobalBounds();
    }
};


class Line : public GameObject
{
public:
    sf::RectangleShape lineShape;

    Line(float x, float y, float w, float h) : GameObject(x, y, w, h), lineShape(sf::Vector2f(w, h))
    {
        lineShape.setPosition(x, y);
    }

    void handleInput(sf::Time elapsed, unsigned int width) override
    {

    }

    void update(sf::Time elapsed, sf::FloatRect box, unsigned int width, unsigned int height, sf::Text& textL, sf::Text& textR, unsigned int& counterL, unsigned int& counterR) override
    {

    }

    void draw(sf::RenderWindow& window, sf::Text& textL, sf::Text& textR) override
    {
        window.draw(lineShape);
    }

    sf::FloatRect getBounds() override
    {
        return lineShape.getGlobalBounds();
    }
};

class SceneManager
{
private:
    std::vector<GameObject*> gameObjects;
public:
    void addObject(GameObject* obj)
    {
        gameObjects.push_back(obj);
    }

    void handleInput(sf::Time elapsed, unsigned int width)
    {
        for (auto obj : gameObjects)
        {
            obj->handleInput(elapsed, width);
        }
    }

    void update(sf::Time elapsed, unsigned int width, unsigned int height, sf::Text& textL, sf::Text& textR, unsigned int& counterL, unsigned int& counterR)
    {
        Ball* ball = dynamic_cast<Ball*>(gameObjects[0]);

        for (size_t i = 1; i < gameObjects.size() - 1; ++i)
        {
            GameObject* obj = gameObjects[i];
            sf::FloatRect otherBox = obj->getBounds();

            ball->update(elapsed, otherBox, width, height, textL, textR, counterL, counterR);
        }
    }

    void draw(sf::RenderWindow& window, sf::Text& textL, sf::Text& textR)
    {
        for (auto obj : gameObjects)
        {
            obj->draw(window, textL, textR);
        }
    }

    ~SceneManager()
    {
        for (auto obj : gameObjects) {
            delete obj;
        }
    }
};

class Game
{
public:
    SceneManager sceneManager;
    unsigned int width = 1280;
    unsigned int height = 720;
    void init()
    {

        std::srand(static_cast<unsigned int>(std::time(0)));
        float randomNumber = (std::rand() % 601) - 300;
        Ball* ball = new Ball(float(width / 2.0), float(height / 2.0), 300.f, randomNumber, 10.f, 64.f);
        Paddle* leftPaddle = new Paddle(float(width / 8.0), float(height / 2.0), 20.f, 120.f, 600.f);
        Paddle* rightPaddle = new Paddle(float(width / 1.2), float(height / 2.0), 20.f, 120.f, 600.f);
        Line* lineShape = new Line(float(width / 2.0), 0, 5.f, height);
        sceneManager.addObject(ball);
        sceneManager.addObject(leftPaddle);
        sceneManager.addObject(rightPaddle);
        sceneManager.addObject(lineShape);
        gameLoop();
    }
    void gameLoop()
    {
        sf::RenderWindow window(sf::VideoMode(width, height), "Pong");
        sf::Text textL;
        sf::Text textR;
        sf::Font font;
        unsigned int counterL = 0;
        unsigned int counterR = 0;
        font.loadFromFile("DS-DIGI.TTF");
        textL.setFont(font);
        textL.setString("0");
        textL.setCharacterSize(60);
        textL.setFillColor(sf::Color::White);
        textL.setPosition((width / 3), (height / 6));
        textR.setFont(font);
        textR.setString("0");
        textR.setCharacterSize(60);
        textR.setFillColor(sf::Color::White);
        textR.setPosition((width / 1.5), (height / 6));
        sf::Clock clock;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            sf::Time elapsed = clock.restart();
            sceneManager.handleInput(elapsed, width);
            sceneManager.update(elapsed, width, height, textL, textR, counterL, counterR);

            window.clear(sf::Color::Black);
            sceneManager.draw(window, textL, textR);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                break;
            }
        }
        endprogram();
    }
    void endprogram()
    {
        sceneManager.~SceneManager();
    }
};

int main()
{
    Game game;
    game.init();
    return 0;
}