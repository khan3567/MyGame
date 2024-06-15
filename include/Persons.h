#pragma once
#ifndef PERSONS_H
#define PERSONS_H

#include "anim.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class PLAYER {
public:
	sf::FloatRect currentFrameRect;

	float x, y, dx, dy, w, h;
	AnimationManager animman;
	bool onGround;
	bool isAlive;
	int health;
	int crystals;
	int dir;
	sf::Sprite sprite;

	sf::Texture texture;

	bool hit, gothit, win;
	int shield;

	enum {stay, walk, duck, jump, dead} STATE;
	std::map<std::string, bool> key; // информация о нажатии клавишь

	PLAYER(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health = 3);

	void KeyCheck(); 

	void update(float time); 

	void set_hit();

	void set_gothit();

	void Collision(int dir);



};




class Enemy {
public:
	sf::FloatRect currentFrameRect;

	float x, y, dx, dy, w, h;
	AnimationManager animman;
	bool isAlive;
	int health;
	int dir;
	sf::Sprite sprite;

	sf::Texture texture;

	enum { walk, dead } STATE;

	Enemy();

	Enemy(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health = 1);

	void update(float time);

	void Collision(int dirxy);



};



class Mashroom: public Enemy {
public:
	sf::Texture marshmallow_texture_walk;
	sf::Texture marshmallow_texture_dead;

	Mashroom(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health = 1);

};


class Turtle : public Enemy {
public:
	sf::Texture turtle_texture_walk;
	sf::Texture turtle_texture_dead;

	Turtle(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health = 1);

};


#endif //!PERSONS_H
