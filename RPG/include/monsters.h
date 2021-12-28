#pragma once

#include "sprites.h"
#include "combat.h"

#include "raylib.h"

#include <string>

class MOB
{
public:
	int Id = -1;

	std::string Name;
	int Sprite = -1;

	int Health = 1;
	DefenseInfo Defense;
	AttackInfo Attack;

	float DetectionRadius = 200;
	float Speed = 50;

	std::string lootTable = "mob_loot";
};

// Mob Database
MOB* AddMob(const char* name, int sprite, int health = 1);
MOB* GetMob(int id);

void SetupDefaultMobs();

// monster constants
constexpr int RatMob = 0;
constexpr int SnakeMob = 1;
constexpr int GhostMob = 2;
constexpr int TrollMob = 3;
constexpr int TurtleMob = 4;
constexpr int BlobMob = 5;
constexpr int OgreMob = 6;
constexpr int MonkMob = 7;
constexpr int BeholderMob = 8;
