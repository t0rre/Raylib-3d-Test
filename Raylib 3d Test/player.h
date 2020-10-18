#pragma once
#include <raylib.h>
#include <ctime>
#include <math.h>
Vector3 toVector3(float x, float y, float z);
enum actions {
	jump,
	forward,
	backward,
	left,
	right,
	wireframe,
	none
};
class player
{
public: 
	Vector3 pos = toVector3(0.0f, 0.0f, 0.0f);
	Vector3 delta = toVector3(0.0f, 0.0f, 0.0f);
	Vector3 cameraPos;
	Vector3 cameraOffset = toVector3(0.0f, 10.0f, 10.0f);
	bool jumpX = false;
	bool jumpY = false;
	bool jumpZ = false;
	Color color = RED;
	float radius = 1.0f;
	int jumpStart = 0;
	int jumpDuration = 1;
	int jumpFinish = 0;
	bool wireFrame = false;
	int playerAngle = 0;
	

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
	void updateCamera()
	{
		float dx = 0 , dz = 0,xo = 0, zo = 0;
		
		dx = cos(deg2Rad(playerAngle)) * 10.0f;
		dz = sin(deg2Rad(playerAngle)) * 10.0f;
		if (dz < 0)
		{
			zo = -5.0f;
		}
		else 
		{
			zo = +5.0f;
		}
		if (dx < 0)
		{
			xo = -5.0f;
		}
		else
		{
			xo = +5.0f;
		}
		cameraPos = toVector3(pos.x + dx, pos.y+5.0f, pos.z + dz);
	}
	double deg2Rad(double deg)
	{
		return deg * PI/180;
	}
	void update(actions action)
	{
		switch (action)
		{
			case actions::forward:
				pos.x -= cos(deg2Rad(playerAngle)) * 0.1f;
				pos.z -= sin(deg2Rad(playerAngle)) * 0.1f;
				break;
			case actions::backward:
				pos.x += cos(deg2Rad(playerAngle)) * 0.1f;
				pos.z += sin(deg2Rad(playerAngle)) * 0.1f;
				break;
			case actions::left:
				playerAngle -= 1;
				break;
			case actions::right:
				playerAngle += 1;
				break;
			case actions::jump:
				if (!jumpY)
				{
					jumpStart = clock();
					jumpFinish = jumpStart + jumpDuration * CLOCKS_PER_SEC;
					jumpY = true;
				}
				break;
		}
		/*if (IsKeyDown(KEY_W))
		{
			pos.x -= cos(deg2Rad(playerAngle)) * 0.1f;
			pos.z -= sin(deg2Rad(playerAngle)) * 0.1f;
		}
		if (IsKeyDown(KEY_S))
		{
			pos.x += cos(deg2Rad(playerAngle)) * 0.1f;
			pos.z += sin(deg2Rad(playerAngle)) * 0.1f;
		}
		if (IsKeyDown(KEY_D))
		{
			playerAngle += 1;
		}
		if (IsKeyDown(KEY_A))
		{
			playerAngle -= 1;
		}*/
		if (playerAngle > 360)
		{
			playerAngle = 0;
		}
		else if (playerAngle < 0)
		{
			playerAngle = 360;
		}
		/*if (IsKeyDown(KEY_SPACE))
		{
			if (!jumpY)
			{
				jumpStart = clock();
				jumpFinish = jumpStart + jumpDuration * CLOCKS_PER_SEC;
				jumpY = true;
			}
		}*/
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

