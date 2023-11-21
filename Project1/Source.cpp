#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

//Checks for collision along the X-axis
int x_collision(float radius, float width, float x)
{
    if (x >= width - radius || x <= radius)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Checks for collision on the Y-axis
int y_collision(float radius, float height, float y)
{
    if (y >= height - radius  || y <= radius)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Defines a ball object for the simulation
struct Ball
{
    //Instantiates object variables
    float ball_radius, y_Velocity, x_Velocity, y_Position, x_Position, gravity, time_Step, co_Restitution, collision_Offset;
    Ball()
    {
        ball_radius = 3;
        x_Position = 20;
        y_Position = 400;
        y_Velocity = 50;
        x_Velocity = 50;
        gravity = -9.81;
        time_Step = 0.1;
        co_Restitution = 0.8;
        collision_Offset = 0;
    }

    //Updates next X position
    float delta_x()
    {
        x_Position = x_Position + (x_Velocity * time_Step);
        return x_Position;
    }

    //Updates next Y position
    float delta_y(float height)
    {
        y_Position = y_Position + (y_Velocity * time_Step) + (0.5 * gravity * time_Step * time_Step);
        y_Velocity = y_Velocity + (gravity * time_Step);
        return height - y_Position;
    }

    //Returns X position
    float get_x()
    {
        return x_Position;
    }

    //Returns Y position
    float get_y(float height)
    {
        return height - y_Position;
    }

    //Returns radius of ball
    float get_radius()
    {
        return ball_radius;
    }

    //Changes Y-velocity upon vertical collision
    void y_collision_change(float height)
    {
        y_Velocity = -co_Restitution * y_Velocity;
        if (get_y(height) < height / 2) 
        {
            y_Position = height - ball_radius - collision_Offset;
        }
        else 
        {
            y_Position = ball_radius + collision_Offset;
        }
    } 

    //Changes X-velocity upon horizontal collision
    void x_collision_change(float width)
    {
        x_Velocity = -co_Restitution * x_Velocity;
        if (get_x() > width / 2)
        {
            x_Position = width - ball_radius - collision_Offset;
        }
        else
        {
            x_Position = ball_radius + collision_Offset;
        }
    }
};

int main() {

    //Creates ball object and set space size
    Ball ball;
    float width = 500;
    float height = 500;
    
    //Sets up the window for rendering the ball
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball Physics");
    sf::CircleShape point(ball.get_radius());
    point.setFillColor(sf::Color::Red);
    point.setPosition(ball.get_x(), ball.get_y(height));
   
    //Renders each frame
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        //Checks for collision and runs collision methods if true
        if (y_collision(ball.get_radius(), height, ball.get_y(height)))
        {
            ball.y_collision_change(height);
        }
        else if (x_collision(ball.get_radius(), width, ball.get_x()))
        {
            ball.x_collision_change(width);
        }
        
        //Render ball
        point.setPosition(ball.delta_x(), ball.delta_y(height));
        
        //Clear window for new frame
        window.clear();
        window.draw(point);
        window.display();
    }

    return 0;
}


