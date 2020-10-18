#include <raylib.h>
#include "player.h"
#include <string>
constexpr auto PLAYER_RADIUS = 1.0f;
void draw(), update();
Camera3D camera = { 0 };
Vector3 toVector3(float x, float y, float z);
Vector3 playerPos = toVector3(0.0f, 0.0f, 0.0f);
Vector3 cameraOffset = toVector3(0.0f, 10.0f, 10.0f);
player player1 = player();
bool cameraStatic = false;
int main()
{
    InitWindow(1024, 768, "Raylib 3D Test");
    camera.position = toVector3(10.0f, 10.0f, 10.0f);
    camera.target = toVector3(0.0f, 0.0f, 0.0f);
    camera.up = toVector3(0.0f, 1.0f, 0.0f);
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update();
        draw();
    }
}
void update()
{
    //Key press code here
    if (IsKeyDown(KEY_LEFT))
    {
        cameraOffset.x -= 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        cameraOffset.x += 0.1f;
    }
    if (IsKeyDown(KEY_UP))
    {
        cameraOffset.z -= 0.1f;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        cameraOffset.z += 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT_SHIFT))
    {
        cameraOffset.y += 0.1f;
    }
    if (IsKeyDown(KEY_RIGHT_CONTROL))
    {
        cameraOffset.y -= 0.1f;
    }
    if (IsKeyPressed(KEY_H))
    {
        cameraStatic = !cameraStatic;
    }
    if (IsKeyPressed(KEY_K))
    {
        player1.wireFrame = !player1.wireFrame;
    }
    player1.update();
    if (cameraStatic)
    {
        camera.position = cameraOffset;
    }
    else
    {
        camera.position = toVector3(player1.pos.x + cameraOffset.x, player1.pos.y + cameraOffset.y, player1.pos.z + cameraOffset.z);
    }
    camera.target = player1.pos;
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
    player1.drawPlayer();
    EndMode3D();
    std::string message = "Jumpstart: " + std::to_string(player1.jumpStart)+"\nJumpfinish: " + std::to_string(player1.jumpFinish)+"\ndeltaY: "+ std::to_string(player1.delta.y)+"\nJumpY: "+std::to_string(player1.jumpY)+"\nX: "+std::to_string(player1.pos.x) + "\nY: " + std::to_string(player1.pos.y) + "\nZ: " + std::to_string(player1.pos.z);
    DrawText(message.c_str(), 0, 0, 20, WHITE);
    EndDrawing();
}
Vector3 toVector3(float x, float y, float z)
{
    return { x,y,z };
}
void calculateJump(player player)
{

}