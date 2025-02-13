#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

Lab3::Lab3()
{
}

Lab3::~Lab3()
{
}

void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Setting the amplitude and frequency for the 4 ground waves
    float a1 = 70, a2 = 65, a3 = 105, a4 = 45;
    float f1 = 0.014, f2 = 0.012, f3 = 0.009, f4 = 0.010;

    for (int i = 0; i < resolution.x; i++)
    {
        float y1 = a1 * sin(f1 * i);
        float y2 = a2 * sin(f2 * i);
        float y3 = a3 * sin(f3 * i);
        float y4 = a4 * sin(f4 * i);
        ground.push_back(y1 + y2 + y3 + y4 + 550);
    }
}

void Lab3::FrameStart()
{
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    glViewport(0, 0, resolution.x, resolution.y);
}

void Lab3::Update(float deltaTimeSeconds)
{
    // Code for the ground rendering with the values from the ground vector
    glm::ivec2 resolution = window->GetResolution();
    float cx = (float)resolution.x;

    std::vector<VertexFormat> groundMap;

    for (int i = 0; i < resolution.x; i++)
    {
        groundMap.push_back(VertexFormat(glm::vec3(i, ground[i], 0), glm::vec3(0.8f, 0.8f, 0)));
        groundMap.push_back(VertexFormat(glm::vec3(i, 0, 0), glm::vec3(0.8f, 0.8f, 0)));
    }

    Mesh *groundMesh = new Mesh("ground");
    std::vector<unsigned int> indices;

    for (int i = 0; i < resolution.x - 1; i++)
    {
        indices.push_back(i);
    }

    // Populate the ground mesh (second method used) with info from groundMap and indices
    groundMesh->SetDrawMode(GL_TRIANGLE_STRIP);
    groundMesh->InitFromData(groundMap, indices);

    // Render the ground mesh
    RenderMesh(groundMesh, shaders["VertexColor"], glm::mat4(1));

    CreateFirstTank(deltaTimeSeconds);
    CreateSecondTank(deltaTimeSeconds);

    UpdateProjectiles(tankProjectiles1, deltaTimeSeconds);
    UpdateProjectiles(tankProjectiles2, deltaTimeSeconds);
}

void Lab3::RenderHealthBar(float x, float y, float health, const glm::vec3& color) {
    // Background of health bar (grey)
    Mesh* backgroundBar = object2D::CreateRectangle(
        "healthBackground",
        glm::vec3(x, y, 0),
        100,  // width
        10,   // height
        glm::vec3(0.5f, 0.5f, 0.5f),
        true
    );
    RenderMesh(backgroundBar, shaders["VertexColor"], glm::mat4(1));

    // Actual health bar (green/yellow/red based on health)
    Mesh* healthBar = object2D::CreateRectangle(
        "healthForeground",
        glm::vec3(x, y, 0),
        health,  // width based on current health
        10,      // height
        color,
        true
    );
    RenderMesh(healthBar, shaders["VertexColor"], glm::mat4(1));
}

void Lab3::CreateFirstTank(float deltaTimeSeconds)
{
    // If tank is destroyed, don't render it
    if (tank1Health <= 0) {
        return;
    }

    float offsetTankX = 5.0f;
    float tankXFinal = tankXStart + offsetTankX;

    // Get the ground height for both positions
    float tankY = ground[(int)(tankXStart * ground.size() / window->GetResolution().x)];
    float tankYFinal = ground[(int)(tankXFinal * ground.size() / window->GetResolution().x)];

    // Calculate the angle between the two positions
    float tankAngle = atan2((tankYFinal - tankY), (tankXFinal - tankXStart));

    // Define the model matrix for the first tank
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(tankXStart, tankY, 0));
    modelMatrix = glm::rotate(modelMatrix, tankAngle, glm::vec3(0, 0, 1));

    Mesh *trapeze1 = object2D::CreateTrapeze("trapeze1", glm::vec3(-65, 10, 0), 130, 30, glm::vec3(0.757f, 0.604f, 0.42f), true);
    RenderMesh(trapeze1, shaders["VertexColor"], modelMatrix);

    Mesh *trapeze2 = object2D::CreateTrapeze("trapeze2", glm::vec3(40, 0, 0), -80, 10, glm::vec3(0.435f, 0.306f, 0.216f), true);
    RenderMesh(trapeze2, shaders["VertexColor"], modelMatrix);

    Mesh *circle = object2D::CreateSemiCircle("circle", glm::vec3(0, 40, 0), 20, glm::vec3(0.757f, 0.604f, 0.42f), true);
    RenderMesh(circle, shaders["VertexColor"], modelMatrix);

    // Code for the turret of the first tank
    glm::mat4 turretMatrix = modelMatrix;
    turretMatrix = glm::translate(turretMatrix, glm::vec3(0, 40, 0));
    turretMatrix = glm::rotate(turretMatrix, turretAngle, glm::vec3(0, 0, 1));
    turretMatrix = glm::translate(turretMatrix, glm::vec3(0, -40, 0));

    Mesh *rectangle = object2D::CreateRectangle("rectangle", glm::vec3(20, 38, 0), 50, 5, glm::vec3(0.1f, 0.1f, 0.1f), true);
    RenderMesh(rectangle, shaders["VertexColor"], turretMatrix);

    // Only allow movement if tank is alive
    if (window->KeyHold(GLFW_KEY_A))
    {
        tankXStart -= 150 * deltaTimeSeconds;
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        tankXStart += 150 * deltaTimeSeconds;
    }

    // Rotate only 180 degrees
    if (window->KeyHold(GLFW_KEY_W))
    {
        if (turretAngle < glm::radians(180.0f))
        {
            turretAngle += 5 * deltaTimeSeconds;
        }
    }

    if (window->KeyHold(GLFW_KEY_S))
    {
        if (turretAngle > glm::radians(0.0f))
        {
            turretAngle -= 5 * deltaTimeSeconds;
        }
    }
}

void Lab3::CreateSecondTank(float deltaTimeSeconds)
{
    // If tank is destroyed, don't render it
    if (tank2Health <= 0) {
        return;
    }

    float offsetSecondTankX = 5.0f;
    float tankSecondXFinal = tankSecondXStart + offsetSecondTankX;

    // Get the ground height for both positions
    float tankSecondY = ground[(int)(tankSecondXStart * ground.size() / window->GetResolution().x)];
    float tankSecondYFinal = ground[(int)(tankSecondXFinal * ground.size() / window->GetResolution().x)];

    // Calculate the angle between the two positions
    float tankSecondAngle = atan2((tankSecondYFinal - tankSecondY), (tankSecondXFinal - tankSecondXStart));

    // Define the model matrix for the second tank
    modelSecondMatrix = glm::mat4(1);
    modelSecondMatrix = glm::translate(modelSecondMatrix, glm::vec3(tankSecondXStart, tankSecondY, 0));
    modelSecondMatrix = glm::rotate(modelSecondMatrix, tankSecondAngle, glm::vec3(0, 0, 1));

    Mesh *trapezeSecond1 = object2D::CreateTrapeze("trapeze1", glm::vec3(-65, 10, 0), 130, 30, glm::vec3(0.757f, 0.604f, 0.42f), true);
    RenderMesh(trapezeSecond1, shaders["VertexColor"], modelSecondMatrix);

    Mesh *trapezeSecond2 = object2D::CreateTrapeze("trapeze2", glm::vec3(40, 0, 0), -80, 10, glm::vec3(0.435f, 0.306f, 0.216f), true);
    RenderMesh(trapezeSecond2, shaders["VertexColor"], modelSecondMatrix);

    Mesh *circleSecond = object2D::CreateSemiCircle("circle", glm::vec3(0, 40, 0), 20, glm::vec3(0.757f, 0.604f, 0.42f), true);
    RenderMesh(circleSecond, shaders["VertexColor"], modelSecondMatrix);

    // Code for the turret of the second tank
    glm::mat4 turretSecondMatrix = modelSecondMatrix;
    turretSecondMatrix = glm::translate(turretSecondMatrix, glm::vec3(0, 40, 0));
    turretSecondMatrix = glm::rotate(turretSecondMatrix, turretSecondAngle, glm::vec3(0, 0, 1));
    turretSecondMatrix = glm::translate(turretSecondMatrix, glm::vec3(0, -40, 0));

    Mesh *rectangleSecond = object2D::CreateRectangle("rectangle", glm::vec3(20, 38, 0), 50, 5, glm::vec3(0.1f, 0.1f, 0.1f), true);
    RenderMesh(rectangleSecond, shaders["VertexColor"], turretSecondMatrix);

    // Only allow movement if tank is alive
    if (window->KeyHold(GLFW_KEY_LEFT))
    {
        tankSecondXStart -= 150 * deltaTimeSeconds;
    }

    if (window->KeyHold(GLFW_KEY_RIGHT))
    {
        tankSecondXStart += 150 * deltaTimeSeconds;
    }

    // Rotate only 180 degrees
    if (window->KeyHold(GLFW_KEY_UP))
    {
        if (turretSecondAngle < glm::radians(180.0f))
        {
            turretSecondAngle += 5 * deltaTimeSeconds;
        }
    }

    if (window->KeyHold(GLFW_KEY_DOWN))
    {
        if (turretSecondAngle > glm::radians(0.0f))
        {
            turretSecondAngle -= 5 * deltaTimeSeconds;
        }
    }
}

void Lab3::UpdateProjectiles(std::vector<Projectile> &projectiles, float deltaTimeSeconds) {
    glm::vec3 gravity = glm::vec3(0, -100, 0);
    glm::ivec2 resolution = window->GetResolution();

    for (auto it = projectiles.begin(); it != projectiles.end();) {
        // Update velocity (so to simulate gravity)
        it->velocity += gravity * deltaTimeSeconds;

        // Update position
        it->position += it->velocity * deltaTimeSeconds;

        // Decrease lifetime (in case the velocity is too high => waiting time reduced)
        it->lifetime -= deltaTimeSeconds;

        // Calculate ground height at the projectile's x position
        int xIndex = (int)(it->position.x * ground.size() / resolution.x);
        if (xIndex >= 0 && xIndex < ground.size()) {
            float groundHeight = ground[xIndex];

            // Check if projectile hits ground or lifetime expires
            if (it->lifetime <= 0 || it->position.y <= groundHeight) {
                it = projectiles.erase(it);
                continue;
            }
        }

        // Check for tank hits
        if (&projectiles == &tankProjectiles1) {  // Projectiles from tank 1
            // Calculate distance to tank2
            float distanceToTank2 = glm::distance(
                it->position,
                glm::vec3(tankSecondXStart, 
                         ground[(int)(tankSecondXStart * ground.size() / resolution.x)] + 40,  // Adding 40 to match tank height
                         0)
            );

            if (tank2Alive && distanceToTank2 < 65) {  // 65 is approximate tank radius
                tank2Health -= 25.0f;  // Damage per hit
                if (tank2Health <= 0) {
                    tank2Alive = false;
                    tank2Health = 0;
                }
                it = projectiles.erase(it);
                continue;
            }
        } else {  // Projectiles from tank 2
            // Calculate distance to tank1
            float distanceToTank1 = glm::distance(
                it->position,
                glm::vec3(tankXStart, 
                         ground[(int)(tankXStart * ground.size() / resolution.x)] + 40,  // Adding 40 to match tank height
                         0)
            );

            if (tank1Alive && distanceToTank1 < 65) {  // 65 is approximate tank radius
                tank1Health -= 25.0f;  // Damage per hit
                if (tank1Health <= 0) {
                    tank1Alive = false;
                    tank1Health = 0;
                }
                it = projectiles.erase(it);
                continue;
            }
        }

        // Render projectile
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, it->position);
        Mesh *circle = object2D::CreateSemiCircle("projectile", glm::vec3(0, 0, 0), 5, glm::vec3(0.1, 0.1, 0.1), true);
        RenderMesh(circle, shaders["VertexColor"], modelMatrix);

        ++it;
    }
}

void Lab3::OnKeyPress(int key, int mods)
{
    // Only allow shooting if tank is alive
    if (key == GLFW_KEY_SPACE && tank1Health > 0)
    {
        glm::vec3 startPos = glm::vec3(tankXStart, ground[(int)(tankXStart * ground.size() / window->GetResolution().x)] + 40, 0);
        glm::vec3 velocity = glm::vec3(cos(turretAngle), sin(turretAngle), 0) * 300.0f;
        tankProjectiles1.push_back({startPos, velocity, 10.0f});
    }

    if (key == GLFW_KEY_ENTER && tank2Health > 0)
    {
        glm::vec3 startPos = glm::vec3(tankSecondXStart, ground[(int)(tankSecondXStart * ground.size() / window->GetResolution().x)] + 40, 0);
        glm::vec3 velocity = glm::vec3(cos(turretSecondAngle), sin(turretSecondAngle), 0) * 300.0f;
        tankProjectiles2.push_back({startPos, velocity, 10.0f}); 
    }
}
