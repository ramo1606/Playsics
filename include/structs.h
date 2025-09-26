#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Engine Engine;
typedef struct Renderer Renderer;

struct Engine
{
	bool debug;

	Renderer* renderer;
};

struct Renderer
{
	LCDFont* font;
	bool initialized;
};

typedef struct
{
	float x;
	float y;
} Vector2;

typedef struct
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct 
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	float mass;
} Particle;

#endif // !STRUCTS_H
