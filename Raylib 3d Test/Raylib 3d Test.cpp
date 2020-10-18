#include <raylib.h>
#include "player.h"
#include <string>
constexpr auto PLAYER_RADIUS = 1.0f;
void draw(), update();
Camera3D camera = { 0 };
Vector3 toVector3(float x, float y, float z);
Vector3 playerPos = toVector3(0.0f, 0.0f, 0.0f);
player* players = new player{1};
int currentPlayer = 0;
bool cameraStatic = false;
int main()
{
    InitWindow(540,480, "Raylib 3D Test");
    camera.position = toVector3(10.0f, 10.0f, 10.0f);
    camera.target = toVector3(0.0f, 0.0f, 0.0f);
    camera.up = toVector3(0.0f, 1.0f, 0.0f);
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;
    players[1].color = GREEN;
    players[2].color = YELLOW;
    players[3].color = PINK;
    players[4].color = ORANGE;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        update();
        draw();
    }
}
void update()
{
    for (int i = 0; i < 5; i++)
    {
        players[i].updated = false;
    }
    //Key press code here
    if (IsKeyDown(KEY_LEFT))
    {
        players[currentPlayer].cameraOffset.x -= 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        players[currentPlayer].cameraOffset.x += 0.1f;
    }
    if (IsKeyDown(KEY_UP))
    {
        players[currentPlayer].cameraOffset.z -= 0.1f;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        players[currentPlayer].cameraOffset.z += 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT_SHIFT))
    {
        players[currentPlayer].cameraOffset.y += 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT_CONTROL))
    {
        players[currentPlayer].cameraOffset.y -= 0.1f;
    }
    if (IsKeyPressed(KEY_H))
    {
        cameraStatic = !cameraStatic;
    }
    if (IsKeyPressed(KEY_K))
    {
        players[currentPlayer].wireFrame = !players[currentPlayer].wireFrame;
    }
    if (IsKeyPressed(KEY_F))
    {
        ToggleFullscreen();
    }
    //player 1 controls
    if (IsKeyDown(KEY_W))
    {
        players[currentPlayer].update(actions::forward);
        players[currentPlayer].updated = true;
    }
    if (IsKeyDown(KEY_S))
    {
        players[currentPlayer].update(actions::backward);
        players[currentPlayer].updated = true;
    }
    if (IsKeyDown(KEY_D))
    {
        players[currentPlayer].update(actions::right);
        players[currentPlayer].updated = true;
    }
    if (IsKeyDown(KEY_A))
    {
        players[currentPlayer].update(actions::left);
        players[currentPlayer].updated = true;
    }
    if (IsKeyDown(KEY_SPACE))
    {
        players[currentPlayer].update(actions::jump);
        players[currentPlayer].updated = true;
    }
    for (int i = 0; i < 5; i++)
    {
        if (players[i].updated == false)
        {
            players[i].update(actions::none);
        }
    }
    if (cameraStatic)
    {
        camera.position = players[currentPlayer].cameraOffset;
    }
    else
    {
        players[currentPlayer].updateCamera();
        camera.position = players[currentPlayer].cameraPos;
    }
    camera.target = players[currentPlayer].pos;
    //change current player
    if (IsKeyPressed(KEY_KP_0))
    {
        currentPlayer = 0;
    }
    if (IsKeyPressed(KEY_KP_1))
    {
        currentPlayer = 1;
    }
    if (IsKeyPressed(KEY_KP_2))
    {
        currentPlayer = 2;
    }
    if (IsKeyPressed(KEY_KP_3))
    {
        currentPlayer = 3;
    }
    if (IsKeyPressed(KEY_KP_4))
    {
        currentPlayer = 4;
    }
}
void draw()
{
    UpdateCamera(&camera);
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(camera);
    DrawCube(toVector3(-5.0f, -5.0f, -5.0f), 10.0f, 10.0f, 10.0f, BLUE);
    DrawCubeWires(toVector3(-5.0f, -5.0f, -5.0f), 10.0f, 10.0f, 10.0f, YELLOW);
    DrawGrid(20,1.0f);
    //Draw player;
    for (int i = 0; i < 5; i++)
    {
        players[i].drawPlayer();
    }
    EndMode3D();
    std::string message = "Jumpstart: " + std::to_string(players[currentPlayer].jumpStart)+"\nJumpfinish: " + std::to_string(players[currentPlayer].jumpFinish)+"\ndeltaY: "+ std::to_string(players[currentPlayer].delta.y)+"\nJumpY: "+std::to_string(players[currentPlayer].jumpY)+"\nX: "+std::to_string(players[currentPlayer].pos.x) + "\nY: " + std::to_string(players[currentPlayer].pos.y) + "\nZ: " + std::to_string(players[currentPlayer].pos.z)+"\nAngle: "+std::to_string(players[currentPlayer].playerAngle);
    DrawText(message.c_str(), 0, 0, 20, WHITE);
    EndDrawing();
}
Vector3 toVector3(float x, float y, float z)
{
    return { x,y,z };
}
