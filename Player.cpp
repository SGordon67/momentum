#include "Player.h"
#include "SFML/Graphics/Shader.hpp"

extern sf::Glsl::Mat3 multiply(const sf::Glsl::Mat3& a, const sf::Glsl::Mat3& b);

Player::Player(InputSystem* input, sf::Texture* texture)
    : Entity(d_playerPosition, d_playerSize, d_playerAngle, RenderLayer::Main, texture, 
             d_playerMaxVelocity, d_playerAcceleration, d_playerAngularAcceleration, d_playerMaxHP, d_playerMass, d_playerRadius, d_playerDrag),
    m_input(input)
{
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(sf::IntRect({0, 0}, {
        static_cast<int>(m_texture->getSize().x),
        static_cast<int>(m_texture->getSize().y)
    }));
    m_sprite.setScale({ static_cast<float>(m_texture->getSize().y) / static_cast<float>(m_texture->getSize().x), 1.f });
    m_sprite.setOrigin({m_texture->getSize().x / 2.f, m_texture->getSize().y / 2.f});
    m_sprite.setPosition(d_playerPosition);
    if(!m_shader.loadFromFile("./art/ball.frag", sf::Shader::Type::Fragment))
        std::cout << "Shader not loaded :(" << std::endl;
}
Player::Player(InputSystem* input, sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture,
               float maxVelocity, float acceleration, sf::Angle angularVelocity, int maxHP,
               float mass, float radius, float drag)
    : Entity(position, size, rotation, renderLayer, texture, maxVelocity, acceleration, angularVelocity, maxHP, mass, radius, drag),
    m_input(input)
{
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(m_texture->getSize().x), static_cast<int>(m_texture->getSize().y)}));
    m_sprite.setScale({1.f, 1.f});
    if(!m_shader.loadFromFile("./art/ball.frag", sf::Shader::Type::Fragment))
        std::cout << "Sprite not loaded :(" << std::endl;
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
        angle = sf::degrees(270);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(90);
    }else if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(180);
    }else if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    } // two buttons pushed
    else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    }else if(input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(225);
    }else if(input->isPressed(Button::Up) && !input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(315);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(135);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(45);
    }else if(!input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    } // three buttons pushed
    else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && input->isPressed(Button::Left) && !input->isPressed(Button::Right)){
        angle = sf::degrees(180);
    }else if(input->isPressed(Button::Up) && input->isPressed(Button::Down) && !input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(0);
    }else if(input->isPressed(Button::Up) && !input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(270);
    }else if(!input->isPressed(Button::Up) && input->isPressed(Button::Down) && input->isPressed(Button::Left) && input->isPressed(Button::Right)){
        angle = sf::degrees(90);
    } // all four pushed
    else{
        angle = sf::degrees(0);
    }
    return angle;
}
void Player::updateRotation(float dt){
    sf::Vector2f v = getVelocity();
    float speed = std::sqrt(v.x * v.x + v.y * v.y);
    if(speed < 0.01f) return;

    float radius = m_sprite.getGlobalBounds().size.x / 2.f;

    // custom rotation speed
    float effectiveSpeed = std::min(speed, m_maxVelocity * 0.8f);
    float speedAdjust = 0.7f;
    float deltaAngle = -(effectiveSpeed / radius * dt * speedAdjust);
    // raw rotation speed
    // float deltaAngle = -(speed / radius * dt);

    sf::Vector3f axis(v.y, 0.f, -v.x);
    float len = std::sqrt(axis.x*axis.x + axis.z*axis.z);
    if(len > 0.0001f) axis /= len;

    float s = sin(deltaAngle);
    float c = cos(deltaAngle);
    float t = 1.f - c;
    auto& a = axis;
    sf::Glsl::Mat3 delta({
        t*a.x*a.x + c,       t*a.x*a.y - s*a.z,  t*a.x*a.z + s*a.y,
        t*a.x*a.y + s*a.z,   t*a.y*a.y + c,       t*a.y*a.z - s*a.x,
        t*a.x*a.z - s*a.y,   t*a.y*a.z + s*a.x,   t*a.z*a.z + c
    });
    m_rotationMatrix = multiply(m_rotationMatrix, delta);
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
    updateRotation(dt);
}
void Player::render(sf::RenderWindow& window){
    m_shader.setUniform("texture", sf::Shader::CurrentTexture);
    m_shader.setUniform("rotationMatrix", m_rotationMatrix);
    window.draw(m_sprite, &m_shader);
}
