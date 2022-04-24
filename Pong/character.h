#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>
#include <chrono>

class Animation {
public:
    Animation() = default;
    Animation(int x, int y, int width, int height) {
        texture.loadFromFile("Textures/professor_walk_cycle_no_hat.png");
        for (int i = 0; i < nFrames; i++) {
            frames[i] = { x + i * width, y,width, height };
        }
    }



    void ApplyToSprite(sf::Sprite& s) const {
        s.setTexture(texture);
        s.setTextureRect(frames[iFrame]);
    }

    void update(float dt) {
        time += dt;
        while (time >= holdTime) {
            time -= holdTime;
            Advance();
        }
    }
private:
    void Advance() {
        if (++iFrame >= nFrames) {
            iFrame = 0;
        }
    }
private:
    static constexpr int nFrames = 8;
    static constexpr float holdTime = 0.1;
    sf::Texture texture;
    sf::IntRect frames[nFrames];
    int iFrame = 0;
    float time = 0.0;


};


class Character {
private:
    enum class AnimationIndex {
        WalkingUp,
        WalkingDown,
        WalkingLeft,
        WalkingRight,
        Count
    };
public:
    Character(const sf::Vector2f& newPos)
    {
        pos = newPos;
        sprite.setTextureRect({ 0,0,64,64 });
        animations[int(AnimationIndex::WalkingUp)] = Animation(64, 0, 64, 64);
        animations[int(AnimationIndex::WalkingDown)] = Animation(64, 128, 64, 64);
        animations[int(AnimationIndex::WalkingLeft)] = Animation(64, 64, 64, 64);
        animations[int(AnimationIndex::WalkingRight)] = Animation(64, 192, 64, 64);
    }

    void setPos(const sf::Vector2f& newPos) {
        pos = newPos;
    }

    void draw(sf::RenderTarget& rt) const {

        rt.draw(sprite);
    }

    void setDirection(const sf::Vector2f& dir) {

        vel = dir * speed;
        if (dir.x > 0.0) {
            curAnimation = AnimationIndex::WalkingRight;
        }
        else if (dir.x < 0.0) {
            curAnimation = AnimationIndex::WalkingLeft;
        }
        else if (dir.y < 0.0) {
            curAnimation = AnimationIndex::WalkingUp;
        }
        else if (dir.y > 0.0) {
            curAnimation = AnimationIndex::WalkingDown;
        }
    }

    void update(float dt) {
        // sf::Vector2f prevPos = pos;  
         //pos += vel * dt;



        animations[int(curAnimation)].update(dt);
        animations[int(curAnimation)].ApplyToSprite(sprite);

        sprite.setPosition(pos);
    }
private:
    static constexpr float speed = 100.0;
    sf::Vector2f pos;
    sf::Vector2f vel = { 0.0, 0.0 };
    sf::Sprite sprite;
    Animation animations[int(AnimationIndex::Count)];
    AnimationIndex curAnimation = AnimationIndex::WalkingDown;
};