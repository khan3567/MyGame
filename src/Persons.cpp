#include "Persons.h"


PLAYER::PLAYER(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health) {
	isAlive = true;
	x = X;
	y = Y;
	dx = DeltaX;
	dy = DeltaY;
	w = W;
	h = H;
	onGround = true;
	STATE = stay;
	sprite.setTextureRect(sf::IntRect(0, 187, 42, 52));
	dir = 0;
	health = Health;
	crystals = 0;
	hit = gothit = false;
	shield = 0;
	win = false;
}

void PLAYER::KeyCheck() {
	if (onGround) {
		if (key["L"]) {
			dir = 1;
			if (STATE != duck) dx = -0.17;
			if (STATE == stay) STATE = walk;
		}
		if (key["R"]) {
			dir = 0;
			if (STATE != duck) dx = 0.17;
			if (STATE == stay) STATE = walk;

		}
		if (key["Up"]) {
			if (STATE != jump) {
				dy = -0.36;
				STATE = jump;
				onGround = false;
			}
		}
		if (key["Down"]) {
			dx = 0;
			STATE = duck;
		}

		// обработка отпускания клавишь
		if (!key["R"] and !key["L"] and !key["Down"] and !key["Up"]) {
			dx = 0;
			dy = 0;
			STATE = stay;
		}
	}
	else {
		if (key["L"]) {
			dir = 1;
			dx = -0.17;

		}
		if (key["R"]) {
			dir = 0;
			dx = 0.17;

		}
		if (key["Down"]) {
			dy = 0.25;
			STATE = duck;
		}

		// обработка отпускания клавишь
		if (!(key["R"] || key["L"])) {
			dx = 0;
			if (STATE == walk) STATE = stay;
		}


	}

}

void PLAYER::update(float time) {

	if (health <= 0) {
		isAlive = false;
		animman.set("dead");
		dx = dy = 0;
		animman.tick(time);
	}

	if (isAlive) {
		KeyCheck();

		if (shield) {
			shield -= time;
			if (shield < 0) {
				shield = 0;
			}
		}

		if (STATE == stay) animman.set("stay");
		if (STATE == walk) animman.set("walk");
		if (STATE == jump) animman.set("jump");
		if (STATE == duck) animman.set("duck");

		if (hit) {
			set_hit();
		}
		if (gothit) {
			set_gothit();
		}


		if (dir) animman.flip();

		onGround = false;

		x += dx * time;
		Collision(0);

		dy += 0.0005 * time;
		y += dy * time;
		Collision(1);

		animman.tick(time);

		//w = animman.wh.first;

		currentFrameRect = sf::FloatRect(x, y, w, h);


		key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] = false;
	}

}

void PLAYER::set_hit() {
	dy = -0.25;
	animman.set("jump");
	hit = false;
	STATE = jump;
}

void PLAYER::set_gothit() {
	dy = -0.5;
	health -= 1;
	gothit = false;
	shield = 6000;
	STATE = duck;
}

void PLAYER::Collision(int dir) {
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == 'b')
			{
				if ((dx > 0) && (dir == 0)) x = j * 32 - w;
				if ((dx < 0) && (dir == 0)) x = j * 32 + 32;
				if ((dy > 0) && (dir == 1)) { y = i * 32 - h;  dy = 0;   onGround = true; STATE = stay; }
				if ((dy < 0) && (dir == 1)) { y = i * 32 + 32;   dy = 0; }
			}
			if (TileMap[i][j] == '0')
			{
				if ((dx > 0) && (dir == 0)) x = j * 32 - w;
				if ((dx < 0) && (dir == 0)) x = j * 32 + 32;
				if ((dy > 0) && (dir == 1)) { y = i * 32 - h;  dy = 0;   onGround = true; STATE = stay; }
				if ((dy < 0) && (dir == 1)) { y = i * 32 + 32;   dy = 0; }
				health -= 1;
			}
			if (TileMap[i][j] == 'c')
			{
				crystals += 1;
				TileMap[i][j] = ' ';
			}
			if (TileMap[i][j] == 'f' or TileMap[i][j] == 'F')
			{
				win = true;
			}

		}
}


Enemy::Enemy() {};

Enemy::Enemy(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health) {
	isAlive = true;
	x = X;
	y = Y;
	dx = DeltaX;
	dy = DeltaY;
	w = W;
	h = H;
	STATE = walk;
	sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
	dir = 1;
}

void Enemy::update(float time) {
	if (isAlive) {

		if (STATE == walk) animman.set("walk");
		if (STATE == dead) animman.set("dead");


		x += dx * time;


		if (dir) animman.flip();
		Collision(0);
		dy += 0.0005 * time;
		y += dy * time;
		Collision(1);

		w = animman.wh.first;

		animman.tick(time);


		currentFrameRect = sf::FloatRect(x, y, w, h);
	}
	else {
		dx = 0;
		dy = 0;
		animman.set("dead");
		animman.tick(time);
	}

}

void Enemy::Collision(int dirxy) {
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0' or TileMap[i][j] == 'b')
			{
				float check = dir;
				if ((dx > 0) && (dirxy == 0)) { x = j * 32 - w; dir = std::abs(dir - 1); dx *= -1; }
				else if ((dx < 0) && (dirxy == 0)) { x = j * 32 + 32; dir = std::abs(dir - 1); dx *= -1; }
				if ((dy > 0) && (dirxy == 1)) { y = i * 32 - h;  dy = 0; }
				if ((dy < 0) && (dirxy == 1)) { y = i * 32 + 32;   dy = 0; }

			}

		}

}


Mashroom::Mashroom(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health) {
	marshmallow_texture_walk.loadFromFile("../assets/images/Walk.png");
	marshmallow_texture_dead.loadFromFile("../assets/images/RIP1.png");
	animman.create("walk", marshmallow_texture_walk, 40, 59, 33, 70, 8, 0.0035, 128);
	animman.create("dead", marshmallow_texture_dead, 64, 0, -64, 64, 1, 0.01, 0);
	isAlive = true;
	x = X;
	y = Y;
	dx = 0.035;
	dy = DeltaY;
	w = W;
	h = H;
	STATE = walk;
	sprite.setTextureRect(sf::IntRect(0, 0, 33, 70));
	dir = 1;
	health = Health;
}



Turtle::Turtle(int X, int Y, float W, float H, int DeltaX, int DeltaY, int Health) {
	turtle_texture_walk.loadFromFile("../assets/images/spritesheet (1).png");
	turtle_texture_dead.loadFromFile("../assets/images/RIP1.png");
	animman.create("walk", turtle_texture_walk, 0, 0, 64, 62, 30, 0.03, 64);
	animman.create("dead", turtle_texture_dead, 64, 0, -64, 64, 1, 0.01, 0);
	isAlive = true;
	x = X;
	y = Y;
	dx = 0.02;
	dy = 0;
	w = W;
	h = H;
	STATE = walk;
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 31));
	dir = 1;
	health = Health;
}