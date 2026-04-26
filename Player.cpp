#include "Player.h"

Player::Player(InputSystem* input, sf::Texture* texture)
    : Entity(d_playerPosition, d_playerSize, d_playerAngle, RenderLayer::Main, texture, 
             d_playerMaxVelocity, d_playerAcceleration, d_playerAngularAcceleration, d_playerMaxHP),
    m_input(input)
{
}
Player::Player(InputSystem* input, sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture,
               float maxVelocity, float acceleration, sf::Angle angularVelocity, int maxHP)
    : Entity(position, size, rotation, renderLayer, texture, maxVelocity, acceleration, angularVelocity, maxHP),
    m_input(input){
}
float Player::determineAcceleration(InputSystem* input){
    float accel = m_acceleration;
    // one button pushed, keep same
    // three buttons pushed, keep same

    if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        // zero buttons pushed
        accel = 0;
    } else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        // up/down pushed
        accel = 0;
    }else if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        // left/right pushed
        accel = 0;
    }else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        // up/down/left/right pushed
        accel = 0;
    }
    return accel;
}
sf::Angle Player::determineDirection(InputSystem* input){
    sf::Angle angle = sf::degrees(0);
    // no buttons pushed
    if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    } // one button pushed
    else if(input->isPressed(Button::Up) && !input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(90);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(270);
    }else if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    }else if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(180);
    } // two buttons pushed
    else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    }else if(input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(45);
    }else if(input->isPressed(Button::Up) && !input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(135);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(315);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(225);
    }else if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    } // three buttons pushed
    else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    }else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(180);
    }else if(input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(90);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(270);
    } // all four pushed
    else{
        angle = sf::degrees(0);
    }
    return angle;
}

void Player::updateVelocity(sf::Angle dir, float acceleration, float dt){
    // zero out the velocity if its small enough
    if(getVelocity().x < 0.5 && getVelocity().x > -0.5) setVelocity({0, getVelocity().y});
    if(getVelocity().y < 0.5 && getVelocity().y > -0.5) setVelocity({getVelocity().x, 0});

    addDragForce(m_velocity, getMass(), dt);
    addAccelerationForce(m_velocity, acceleration, dir, getMaxVelocity(), getMass(), dt);
}
void Player::update(float dt){
    if(m_input->isNewlyPressed(Button::Interact)){
        std::cout << "Player interacting with nothing O.O" << std::endl;
    }

    float accel = determineAcceleration(m_input);
    sf::Angle angle = determineDirection(m_input);
    updateVelocity(angle, accel, dt);
    updatePosition(dt);
}
void Player::render(sf::RenderWindow& window){
    window.draw(m_sprite);
}
