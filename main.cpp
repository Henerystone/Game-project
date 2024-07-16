#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Define the size of the window
const int windowWidth = 800;
const int windowHeight = 600;

// Define the size and speed of the paddles
const int paddleWidth = 10;
const int paddleHeight = 100;
const float paddleSpeed = 0.6f;

// Define the size and speed of the ball
const float ballRadius = 10.0f;
const float ballSpeed = 0.4f;

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Ping Pong Game");

    // Create the paddles
    sf::RectangleShape leftPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    leftPaddle.setPosition(50, (windowHeight / 2) - (paddleHeight / 2));
    leftPaddle.setFillColor(sf::Color::Green);

    sf::RectangleShape rightPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    rightPaddle.setPosition(windowWidth - 50 - paddleWidth, (windowHeight / 2) - (paddleHeight / 2));
    rightPaddle.setFillColor(sf::Color::Red);

    // Create the ball
    sf::CircleShape ball(ballRadius);
    ball.setPosition((windowWidth / 2) - ballRadius, (windowHeight / 2) - ballRadius);
    ball.setFillColor(sf::Color::White);

    // Ball velocity
    sf::Vector2f ballVelocity(ballSpeed, ballSpeed);

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Move the left paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0) {
            leftPaddle.move(0, -paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y < windowHeight - paddleHeight) {
            leftPaddle.move(0, paddleSpeed);
        }

        // Move the right paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0) {
            rightPaddle.move(0, -paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y < windowHeight - paddleHeight) {
            rightPaddle.move(0, paddleSpeed);
        }

        // Move the ball
        ball.move(ballVelocity);

        // Check collisions with the top and bottom of the window
        if (ball.getPosition().y <= 0 || ball.getPosition().y >= windowHeight - ballRadius * 2) {
            ballVelocity.y = -ballVelocity.y;
        }

        // Check collisions with the paddles
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballVelocity.x = -ballVelocity.x;
        }

        // Check if the ball is out of the left or right side
        if (ball.getPosition().x <= 0 || ball.getPosition().x >= windowWidth - ballRadius * 2) {
            ball.setPosition((windowWidth / 2) - ballRadius, (windowHeight / 2) - ballRadius);
            ballVelocity.x = ballSpeed;
            ballVelocity.y = ballSpeed;
        }

        // Clear the window
        window.clear();

        // Draw the paddles and the ball
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
