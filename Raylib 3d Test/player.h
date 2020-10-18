#pragma once
#include <raylib.h>
#include <ctime>
#include <math.h>
Vector3 toVector3(float x, float y, float z);
class player
{
public: 
	Vector3 pos = toVector3(0.0f, 0.0f, 0.0f);
	Vector3 delta = toVector3(0.0f, 0.0f, 0.0f);
	bool jumpX = false;
	bool jumpY = false;
	bool jumpZ = false;
	Color color = RED;
	float radius = 1.0f;
	int jumpStart = 0;
	int jumpDuration = 1;
	int jumpFinish = 0;
	bool wireFrame = false;

	Vector3 toVector3(float x, float y, float z)
	{
		return { x,y,z };
	}
public:
	void drawPlayer()
	{
		if (wireFrame)
		{
			DrawSphereWires(toVector3(pos.x, pos.y + radius, pos.z), radius, 20, 20, WHITE);
		}
		else
		{
			DrawSphere(toVector3(pos.x, pos.y + radius, pos.z), radius, color);
		}
		
	}
	void update()
	{
		if (IsKeyDown(KEY_W))
		{
			pos.x -= 0.1f;
		}
		if (IsKeyDown(KEY_S))
		{
			pos.x += 0.1f;
		}
		if (IsKeyDown(KEY_D))
		{
			pos.z -= 0.1f;
		}
		if (IsKeyDown(KEY_A))
		{
			pos.z += 0.1f;
		}
		if (IsKeyDown(KEY_SPACE))
		{
			if (!jumpY)
			{
				jumpStart = clock();
				jumpFinish = jumpStart + jumpDuration * CLOCKS_PER_SEC;
				jumpY = true;
			}
		}
		if (jumpY)
		{
			
			//When jumping motion is active
			int x = clock() - jumpStart;
			pos.y = -0.001f * (x * (x - (jumpFinish-jumpStart)))*GetFrameTime();
			if (pos.y < 0)
			{
				jumpY = false;
				pos.y = 0;
			}
			
			pos.x += delta.x;
			pos.y += delta.y;
			pos.z += delta.z;
		}
		
	}
};

