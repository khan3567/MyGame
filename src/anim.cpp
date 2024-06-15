#include "anim.h"



Animation::Animation() {

}


Animation::Animation(sf::Texture& t, int x, int y, int w, int h, int count, float Speed, int step) {
	speed = Speed;
	sprite.setTexture(t);

	currentFrame = 0;
	isPlaying = true;
	flip = false;

	for (int i = 0; i < count; i++) {
		frames_flip.push_back(sf::IntRect(x + i * step, y, w, h));
		frames.push_back(sf::IntRect(x + i * step + w, y, -w, h));

	}

}

std::pair<int, int> Animation::tick(float time) {
	currentFrame += speed * time;

	if (currentFrame > frames.size()) {
		currentFrame -= frames.size();
	}

	int i = currentFrame;
	sprite.setTextureRect(frames[i]);
	if (flip) sprite.setTextureRect(frames_flip[i]);

	currentFrameParam = { frames_flip[i].width, frames[i].height };

	return currentFrameParam;
}


AnimationManager::AnimationManager()
{

}

void AnimationManager::create(std::string name, sf::Texture& t, int x, int y, int w, int h, int count, float speed, int step, bool Loop)
{
	animList[name] = Animation(t, x, y, w, h, count, speed, step); // добавление в список новой анимации
	currentAnim = name;

}

void AnimationManager::draw(sf::RenderWindow& window, int x, int y) {
	animList[currentAnim].sprite.setPosition(x, y);
	window.draw(animList[currentAnim].sprite);
}

void AnimationManager::set(std::string name)
{
	currentAnim = name;
	animList[currentAnim].flip = 0;
}

void AnimationManager::flip(bool b) { animList[currentAnim].flip = b; }

void AnimationManager::tick(float time) {
	wh = animList[currentAnim].tick(time);
}


