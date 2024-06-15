#pragma once
#ifndef ANIM_H
#define ANIM_H



#include <SFML/Graphics.hpp>
#include <iostream>


class Animation {
public:
	std::vector<sf::IntRect> frames, frames_flip; // массивы кадров
	float currentFrame, speed;
	bool flip, isPlaying;
	sf::Sprite sprite;
	std::pair<int, int> currentFrameParam;

	Animation();


	Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed, int step);
	

	std::pair<int, int> tick(float time);

};



class AnimationManager {
public:
	sf::String currentAnim; // имя текущей анимации
	std::map<sf::String, Animation> animList; // список анимаций с их именами
	std::pair<int, int> wh;

	AnimationManager();

	void create(std::string name, sf::Texture& t, int x, int y, int w, int h, int count, float speed, int step = 0, bool Loop = true);

	void draw(sf::RenderWindow& window, int x = 0, int y = 0);

	void set(std::string name);

	void flip(bool b = 1);

	void tick(float time);

};



#endif // !ANIM_H

