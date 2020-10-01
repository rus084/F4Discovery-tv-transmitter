/*
 * invaders.c
 *
 *  Created on: 11 апр. 2019 г.
 */


// Clone of Space Invaders Game
#include "stdint.h"
#include "stdlib.h"
#include "fonts.h"
#include "st25_discovery_lcd.h"
#define MAX_X 240
#define MIN_X 10
#define DX 2
#define DY 4
#define PLAYER_Y 180
#define GAME_UPPER_EDGE 50

#define NUMOFLINES 6


void InvadersInit(void);

static const uint16_t TYPE1_1_SPRITE[8][16] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

static const uint16_t TYPE1_2_SPRITE[8][16] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000
};

static const uint16_t TYPE2_1_SPRITE[8][16] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

static const uint16_t TYPE2_2_SPRITE[8][16] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
};

static const uint16_t TYPE3_1_SPRITE[8][16] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
};

static const uint16_t TYPE3_2_SPRITE[8][16] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};

static const uint16_t PLAYER_SPRITE[8][16] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
	0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
	0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};

static const uint16_t RECT_SPRITE[8][3] = {
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0xFFFF, 0x0000,
};

static const uint16_t FLASH1_SPRITE[8][3] = {
	0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0xFFFF,
	0x0000, 0xFFFF, 0x0000,
	0xFFFF, 0x0000, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0x0000, 0xFFFF,
	0x0000, 0xFFFF, 0x0000,
	0xFFFF, 0x0000, 0x0000,
};

static const uint16_t FLASH2_SPRITE[8][3] = {
	0x0000, 0x0000, 0x0000,
	0xFFFF, 0x0000, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0x0000, 0xFFFF,
	0x0000, 0xFFFF, 0x0000,
	0xFFFF, 0x0000, 0x0000,
	0x0000, 0xFFFF, 0x0000,
	0x0000, 0x0000, 0xFFFF,
};


enum Enemy_type
{
	EMPTY_ENEMY,
	TARELKA,
	TYPE1_1,
	TYPE1_2,
	TYPE2_1,
	TYPE2_2,
	TYPE3_1,
	TYPE3_2,
	DEAD1,
	DEAD2,
	DEAD3,
	DEAD4,
	DEAD5,
	DEAD6
};

struct Coords
{
	uint16_t x;
	uint16_t y;
};

struct Enemy
{
	enum Enemy_type type;
	struct Coords cord;
};

enum Bullet_type
{
	EMPTY,
	RECT,
	FLASH1,
	FLASH2,
	TO_CLEAR
};

struct Bullet
{
	enum Bullet_type type;
	struct Coords cord;
};

typedef struct {

	struct Enemy alien[11 * NUMOFLINES + 1];
	struct Bullet ray[8];
	struct Bullet Player_ray;
	uint16_t Player_X;
	uint16_t curr_alien_move;
	uint16_t last_enemy_move;
	_Bool clear_pray;
	int clear_index;


	int last_scores;// = -1;
	int last_lives;// = -1;
	int last_max_score;// = -1;

	enum {
		RIGHT,
		LEFT,
		DOWN_LEFT,
		DOWN_RIGHT
	} direction;

	struct Buttons
	{
		unsigned fire : 1;
		unsigned left : 1;
		unsigned right : 1;
	} key;

	enum {
		NORM,
		COUNT,
		OVER
	} game_state;

	int scores;// = 0;
	int max_score;// = 0;
	int lives;// = 3;

	int counter;// = 0;

} InvadersVars_t;

//#define InvadersVars (*( (InvadersVars_t*)FrameVars ))

InvadersVars_t InvadersVars;

void animate_enemies(void)
{
	switch (InvadersVars.alien[InvadersVars.curr_alien_move].type)  // animate
	{
	case TYPE1_1:
		InvadersVars.alien[InvadersVars.curr_alien_move].type=TYPE1_2;
		break;
        case TYPE1_2:
			InvadersVars.alien[InvadersVars.curr_alien_move].type=TYPE1_1;
                break;
        case TYPE2_1:
			InvadersVars.alien[InvadersVars.curr_alien_move].type=TYPE2_2;
                break;
        case TYPE2_2:
			InvadersVars.alien[InvadersVars.curr_alien_move].type=TYPE2_1;
                break;
        case TYPE3_1:
			InvadersVars.alien[InvadersVars.curr_alien_move].type=TYPE3_2;
                break;
        case TYPE3_2:
			InvadersVars.alien[InvadersVars.curr_alien_move].type=TYPE3_1;
                break;
	default:
		break;
	}
}

void move_emeny()
{
	switch (InvadersVars.direction) // move enemies
	{
	case DOWN_RIGHT:
		InvadersVars.alien[InvadersVars.curr_alien_move].cord.y+=DY;
		break;
	case RIGHT:
		InvadersVars.alien[InvadersVars.curr_alien_move].cord.x+=DX;
		break;
	case DOWN_LEFT:
		InvadersVars.alien[InvadersVars.curr_alien_move].cord.y+=DY;
		break;
	case LEFT:
		InvadersVars.alien[InvadersVars.curr_alien_move].cord.x-=DX;
		break;
	default:
		break;
	}
}

void correct_enemy_index()
{

	unsigned righest=0;
	unsigned leftest=65;
	unsigned last_enemy=0;
	for (int i=0;i<11*NUMOFLINES;i++) // find left, right count
	{
		if (InvadersVars.alien[i].type!=EMPTY_ENEMY)
		{
			if ((i%11)>=(righest%11)) righest=i;
			if ((i%11)<=(leftest%11)) leftest=i;
			last_enemy=i;
		}
	}

	if (InvadersVars.curr_alien_move>=last_enemy)
	{
		InvadersVars.curr_alien_move=0;
		switch (InvadersVars.direction)
		{
		case DOWN_LEFT:
			InvadersVars.direction=LEFT;
			break;
		case DOWN_RIGHT:
			InvadersVars.direction=RIGHT;
			break;
		case LEFT:
			if (InvadersVars.alien[leftest].cord.x<=MIN_X) InvadersVars.direction=DOWN_RIGHT;
			break;
		case RIGHT:
			if (InvadersVars.alien[righest].cord.x>=MAX_X) InvadersVars.direction=DOWN_LEFT;
			break;
		default:
			InvadersVars.direction=RIGHT;
			break;
		}
	}
	else InvadersVars.curr_alien_move++;

	while(InvadersVars.alien[InvadersVars.curr_alien_move].type==EMPTY_ENEMY)
	{
		InvadersVars.curr_alien_move++;
	}
}

void check_round_win()
{
	unsigned alive_count=0;
	for (int i=0;i<11*NUMOFLINES;i++) // find left, right count
	{
		if (InvadersVars.alien[i].type!=EMPTY_ENEMY)
			alive_count++;
	}

	if (alive_count==0)
	{
		InvadersVars.lives++;
		InvadersInit();
		return;
	}
}

const uint16_t fire_probability[55] =
{
   20,  15,  10,  9,  9,  9,  9,  9,  9,  9,  9,
   7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
   7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
   7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
   6,  6,  6,  6,  5,  5,  4,  3,  3,  2,  0
};

void enemy_rays_process()
{
	unsigned alive_count=0;
	for (int i=0;i<11*NUMOFLINES;i++) // find left, right count
	{
		if (InvadersVars.alien[i].type!=EMPTY_ENEMY)
			alive_count++;
	}

	if (alive_count>11*NUMOFLINES) alive_count=11*NUMOFLINES;

	unsigned int probability=(11*NUMOFLINES-alive_count)/2; // 0 of 16384



	for (int i=0;i<11*NUMOFLINES;i++) // find left, right count
	{
		if (InvadersVars.alien[i].type!=EMPTY_ENEMY)
		{

			if ((rand()%16384)<probability)
			{
				for (int j=0;j<8;j++)
				{
					if (InvadersVars.ray[j].type==EMPTY)
					{
						switch (InvadersVars.alien[i].type)
						{
							case TYPE1_1:
							case TYPE1_2:
								InvadersVars.ray[j].type=RECT;
								break;
							case TYPE2_1:
							case TYPE2_2:
								InvadersVars.ray[j].type=(rand()&1)?RECT:FLASH1;
								break;
							case TYPE3_1:
							case TYPE3_2:
								InvadersVars.ray[j].type=FLASH1;
								break;
							default:
								break;
						}
						InvadersVars.ray[j].cord.x= InvadersVars.alien[i].cord.x+8;
						InvadersVars.ray[j].cord.y= InvadersVars.alien[i].cord.y+8;
						break;
					}
				}
			}
		}
	}

	for (int i=0;i<8;i++)
	{
		switch(InvadersVars.ray[i].type)
		{
		case FLASH1:
			InvadersVars.ray[i].type=FLASH2;
			InvadersVars.ray[i].cord.y+=3;
			break;
		case FLASH2:
			InvadersVars.ray[i].type=FLASH1;
			InvadersVars.ray[i].cord.y+=2;
			break;
		case RECT:
			InvadersVars.ray[i].cord.y+=2;
			break;
		default:
			break;
		}
		if ((InvadersVars.ray[i].type!=EMPTY)&&(InvadersVars.ray[i].cord.y>PLAYER_Y)) InvadersVars.ray[i].type=TO_CLEAR;
	}
}

void player_ray_process()
{
	unsigned last_enemy=0;
	for (int i=0;i<11*NUMOFLINES;i++) // find left, right count
	{
		if (InvadersVars.alien[i].type!=EMPTY_ENEMY)
			last_enemy=i;
	}


	if (InvadersVars.Player_ray.type!=EMPTY)
	{
		InvadersVars.Player_ray.cord.y-=2;
		if (((InvadersVars.alien[11*NUMOFLINES].type!=EMPTY)&&(InvadersVars.Player_ray.cord.y<=GAME_UPPER_EDGE-8))||
				((InvadersVars.alien[11*NUMOFLINES].type==EMPTY)&&(InvadersVars.Player_ray.cord.y<= InvadersVars.alien[last_enemy].cord.y-8)))
		{
			InvadersVars.Player_ray.type=EMPTY;
			InvadersVars.clear_pray=1;
			InvadersVars.clear_index=0xff;
		}
	}
	else
	{
		if (InvadersVars.key.fire)
		{
			InvadersVars.Player_ray.type=RECT;
			InvadersVars.Player_ray.cord.y=PLAYER_Y-8;
			InvadersVars.Player_ray.cord.x=InvadersVars.Player_X+7;
		}
	}
}

void Game_loop(void)
{
	if (InvadersVars.game_state==COUNT)
	{
		if (InvadersVars.counter>0)
		{
			InvadersVars.counter--;
			return;
		}
		else
		{
			InvadersVars.game_state=NORM;
		}
	}

	if (InvadersVars.game_state==OVER)
	{
		if (InvadersVars.counter>0)
		{
			InvadersVars.counter--;
			return;
		}
		InvadersInit();
		InvadersVars.lives=3;
		InvadersVars.game_state=NORM;
	}
	if (InvadersVars.game_state!=NORM) return;
	if (InvadersVars.alien[InvadersVars.curr_alien_move].cord.y>=PLAYER_Y-8) InvadersVars.game_state=OVER;

	InvadersVars.last_enemy_move= InvadersVars.curr_alien_move;


	enemy_rays_process();
	player_ray_process();
	if (InvadersVars.key.left) InvadersVars.Player_X--;
	if (InvadersVars.key.right) InvadersVars.Player_X++;
	if (InvadersVars.Player_X<MIN_X) InvadersVars.Player_X=MIN_X;
	if (InvadersVars.Player_X>MAX_X) InvadersVars.Player_X=MAX_X;

	check_round_win();
	animate_enemies();
	move_emeny();
	correct_enemy_index();

	//collisions
	if (InvadersVars.Player_ray.type!=EMPTY)
	{
		for (int i=0;i<11*NUMOFLINES+1;i++)
		{
			if (InvadersVars.alien[i].type!=EMPTY_ENEMY)
			{
				if ((InvadersVars.Player_ray.cord.y<= InvadersVars.alien[i].cord.y)&&(InvadersVars.Player_ray.cord.y>= InvadersVars.alien[i].cord.y-8))
				{
					int xmin=0;
					int xmax=0;
					switch (InvadersVars.alien[i].type)
					{
					case TYPE1_1:
					case TYPE1_2:
			 			xmin=2;
			 			xmax=12;
			            break;
			        case TYPE2_1:
			        case TYPE2_2:
			            xmin=4;
			            xmax=14;
			            break;
			        case TYPE3_1:
			        case TYPE3_2:
			            xmin=2;
			            xmax=13;
			            break;
			        default:
			         	break;
					}
					if ((InvadersVars.Player_ray.cord.x>= InvadersVars.alien[i].cord.x+xmin)&&(InvadersVars.Player_ray.cord.x<= InvadersVars.alien[i].cord.x+xmax))
					{
						switch(InvadersVars.alien[i].type)
						{
							case TYPE1_1:
							case TYPE1_2:
								InvadersVars.scores+=10;
								break;
							case TYPE2_1:
							case TYPE2_2:
								InvadersVars.scores+=15;
								break;
							case TYPE3_1:
							case TYPE3_2:
								InvadersVars.scores+=20;
								break;
							default:
								break;
						}
						InvadersVars.alien[i].type=EMPTY_ENEMY;
						InvadersVars.Player_ray.type=EMPTY;
						InvadersVars.clear_pray=1;
						InvadersVars.clear_index=i;
					}

				}
			}
		}
	}

	for (int i=0;i<8;i++)
	{
		if ((InvadersVars.ray[i].type!=EMPTY)&&(InvadersVars.ray[i].type!=TO_CLEAR))
		{
			if (InvadersVars.ray[i].cord.y>PLAYER_Y-8)
			{
				if ((InvadersVars.ray[i].cord.x>= InvadersVars.Player_X-1)&&(InvadersVars.ray[i].cord.x<= InvadersVars.Player_X+16))
				{
					InvadersVars.counter=50;
					InvadersVars.game_state=COUNT;
					InvadersVars.lives--;
					InvadersVars.ray[i].type=TO_CLEAR;
					if (InvadersVars.lives==0)
					{
						InvadersVars.counter=100;
						InvadersVars.game_state=OVER;
						if (InvadersVars.max_score < InvadersVars.scores) InvadersVars.max_score = InvadersVars.scores;
						InvadersVars.scores=0;
					}
				}
			}
		}
	}

}



void putPixeX(int x,int y,uint16_t color)
{
	writeFB( y, x, color);
}
void gr_putString(char* str,int x,int y)
{
	BSP_LCD_DisplayStringAt( x, y, str, LEFT_MODE);
}

void Frame_DRAW()
{
	//for (int y=0;y<240;y++)
	//{
	//	for (int x=0;x<320;x++)
	//	{
	//		putPixeX(x,y,0,0,0) ;
	//	}
	//}

	char buf[256];

if (InvadersVars.scores!= InvadersVars.last_scores)
{
	InvadersVars.last_scores= InvadersVars.scores;
        snprintf(buf,256,"SCORES: %d", InvadersVars.scores);
	gr_putString(buf,1,1);
}

if (InvadersVars.lives!= InvadersVars.last_lives)
{
	InvadersVars.last_lives= InvadersVars.lives;
	snprintf(buf,256,"LIVES: %d", InvadersVars.lives);
	gr_putString(buf,100,1);
}

if (InvadersVars.max_score!= InvadersVars.last_max_score)
{
	InvadersVars.last_max_score= InvadersVars.max_score;
	snprintf(buf,256,"MAX SCORES: %d", InvadersVars.max_score);
	gr_putString(buf,180,1);
}

	//for (int i=0;i<55;i++)
	{
    int i = InvadersVars.last_enemy_move;
		if (InvadersVars.alien[i].type!=EMPTY_ENEMY)
		{
			for (int x=0;x<16;x++)
			{
				if (InvadersVars.alien[i].cord.y>=DY)
				{
					for (int j=1;j<=DY;j++)
						putPixeX(InvadersVars.alien[i].cord.x+x, InvadersVars.alien[i].cord.y-j,0000) ;
				}

				for (int y=0;y<8;y++)
				{
					uint16_t color=0x0000;
					switch (InvadersVars.alien[i].type)
					{
						case TYPE1_1:
				 			color=TYPE1_1_SPRITE[y][x];
				            break;
						case TYPE1_2:
				 			color=TYPE1_2_SPRITE[y][x];
				            break;
				        case TYPE2_1:
				            color=TYPE2_1_SPRITE[y][x];
				            break;
				        case TYPE2_2:
				            color=TYPE2_2_SPRITE[y][x];
				            break;
				        case TYPE3_1:
				            color=TYPE3_1_SPRITE[y][x];
				            break;
				        case TYPE3_2:
				            color=TYPE3_2_SPRITE[y][x];
				            break;
				        default:
				         	break;
					}
					int xcord= InvadersVars.alien[i].cord.x+x;
					int ycord= InvadersVars.alien[i].cord.y+y;
					putPixeX(xcord,ycord,color) ;
				}
			}
		}
	}

	for (int x=0;x<16;x++)
	{
		for (int y=0;y<8;y++)
		{
			uint16_t color=PLAYER_SPRITE[y][x];

			int xcord= InvadersVars.Player_X+x;
			int ycord=PLAYER_Y+y;
			putPixeX(xcord,ycord,color) ;
		}
	}

	for (int i=0;i<8;i++)
	{
		if (InvadersVars.ray[i].type!=EMPTY)
		{
			for (int x=0;x<3;x++)
			{
				putPixeX(InvadersVars.ray[i].cord.x+x, InvadersVars.ray[i].cord.y-2,0000) ;
				putPixeX(InvadersVars.ray[i].cord.x+x, InvadersVars.ray[i].cord.y-1,0000) ;
				for (int y=0;y<8;y++)
				{
					uint16_t color=0x0000;
					switch (InvadersVars.ray[i].type)
					{
						case RECT:
				 			color=RECT_SPRITE[y][x];
				            break;
						case FLASH1:
				 			color=FLASH1_SPRITE[y][x];
				            break;
				        case FLASH2:
				            color=FLASH2_SPRITE[y][x];
				            break;
				        case TO_CLEAR:
				        	color=0x0000;
				        	break;
				        default:
				         	break;
					}
					int xcord= InvadersVars.ray[i].cord.x+x;
					int ycord= InvadersVars.ray[i].cord.y+y;
					putPixeX(xcord,ycord,color) ;
				}
			}
		}
		if (InvadersVars.ray[i].type==TO_CLEAR) InvadersVars.ray[i].type=EMPTY;
	}

	if (InvadersVars.Player_ray.type!=EMPTY)
	{
		for (int x=0;x<3;x++)
		{
			putPixeX(InvadersVars.Player_ray.cord.x+x, InvadersVars.Player_ray.cord.y+9,0000) ;
			putPixeX(InvadersVars.Player_ray.cord.x+x, InvadersVars.Player_ray.cord.y+8,0000) ;
			for (int y=0;y<8;y++)
			{
				uint16_t color=0x0000;
				switch (InvadersVars.Player_ray.type)
				{
					case RECT:
			 			color=RECT_SPRITE[y][x];
			            break;
					case FLASH1:
			 			color=FLASH1_SPRITE[y][x];
			            break;
			        case FLASH2:
			            color=FLASH2_SPRITE[y][x];
			        default:
			         	break;
				}
				int xcord= InvadersVars.Player_ray.cord.x+x;
				int ycord= InvadersVars.Player_ray.cord.y+y;
				putPixeX(xcord,ycord,color) ;
			}
		}
	}
	else if (InvadersVars.clear_pray)
	{
		InvadersVars.clear_pray=0;
		for (int x=0;x<3;x++)
		{
			for (int y=0;y<10;y++)
			{
				int xcord= InvadersVars.Player_ray.cord.x+x;
				int ycord= InvadersVars.Player_ray.cord.y+y;
				putPixeX(xcord,ycord,0000) ;
			}
		}
		if (InvadersVars.clear_index!=0xff)
			for (int x=0;x<16;x++)
			{
				for (int y=0;y<8;y++)
				{
					int xcord= InvadersVars.alien[InvadersVars.clear_index].cord.x+x;
					int ycord= InvadersVars.alien[InvadersVars.clear_index].cord.y+y;
					putPixeX(xcord,ycord,0000) ;
				}
			}
	}

}

void InvadersInit()
{
	memset(&InvadersVars, 0, sizeof(InvadersVars));
	InvadersVars.last_scores = -1;
	InvadersVars.last_lives = -1;
	InvadersVars.last_max_score = -1;
	InvadersVars.scores = 0;
	InvadersVars.max_score = 0;
	InvadersVars.lives = 3;




	BSP_LCD_SetFont(&Font8);


	for (int y=0;y<240;y++)
	{
		for (int x=0;x<320;x++)
		{
			putPixeX(x,y,0000) ;
		}
	}
/*
	for (int x=0;x<320;x++)
	{
		putPixeX(x,0,128<<8);
		putPixeX(x,239,128<<8);
	}

	for (int y=0;y<240;y++)
	{
		putPixeX(0,y,128<<8);
		putPixeX(319,y,128<<8);
	}
*/

	for (int i=0;i<11*NUMOFLINES;i++)
	{
		unsigned int x=i%11;
		unsigned int y=4-(i/11);
		switch (y) {
		case 0:
			InvadersVars.alien[i].type=TYPE3_1;
			break;
		case 1:
		case 2:
			InvadersVars.alien[i].type=TYPE2_1;
			break;
		case 3:
		case 4:
			InvadersVars.alien[i].type=TYPE1_1;
			break;
		default:
			InvadersVars.alien[i].type=(rand()%6)+2;
			break;
		}
		InvadersVars.alien[i].cord.x=(MAX_X+MIN_X)/2-96+16*x;
		InvadersVars.alien[i].cord.y=GAME_UPPER_EDGE+16+16*y;
	}

	InvadersVars.alien[11*NUMOFLINES].type=EMPTY_ENEMY;

	for (int i=0;i<8;i++)
		InvadersVars.ray[i].type=EMPTY;
	InvadersVars.Player_ray.type=EMPTY;
	InvadersVars.curr_alien_move=0;
	InvadersVars.direction=RIGHT;
	InvadersVars.Player_X=(MAX_X+MIN_X)/2;
        
        
        
      for (int i=0;i<66;i++)
      {
            Game_loop();
            Frame_DRAW();
      }
  

}
 void InvadersprocessGame()
{
	static uint32_t last_millis = 0;
	if (HAL_GetTick() <= (last_millis + 20))
		return;
	last_millis = HAL_GetTick();
/*
	if (key_events.keyLeft_pressed)
	{
		key_events.keyLeft_pressed = 0;
		InvadersVars.key.left = 1;
	}
	if (key_events.keyRight_pressed)
	{
		key_events.keyRight_pressed = 0;
		InvadersVars.key.right = 1;
	}
	if (key_events.keyUp_pressed)
	{
		key_events.keyUp_pressed = 0;
		InvadersVars.key.fire = 1;
	}

	if (key_events.keyLeft_released)
	{
		key_events.keyLeft_released = 0;
		InvadersVars.key.left = 0;
	}
	if (key_events.keyRight_released)
	{
		key_events.keyRight_released = 0;
		InvadersVars.key.right = 0;
	}
	if (key_events.keyUp_released)
	{
		key_events.keyUp_released = 0;
		InvadersVars.key.fire = 0;
	}

	if (key_events.keyDown_pressed)
	{
		key_events.keyDown_pressed = 0;
		FrameBack();
		return;
	}
*/
	Game_loop();
	Frame_DRAW();
}
