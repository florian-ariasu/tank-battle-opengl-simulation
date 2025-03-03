#pragma once

#include "components/simple_scene.h"

namespace m1
{
   class Lab3 : public gfxc::SimpleScene
   {
   public:
      Lab3();
      ~Lab3();

      void Init() override;

   private:
      void FrameStart() override;
      void Update(float deltaTimeSeconds) override;
      void OnKeyPress(int key, int mods) override;

   protected:
      float cx, cy;
      float translateX, translateY;
      float scaleX, scaleY;
      float angularStep;

      // Tank rendering functions
      void CreateFirstTank(float deltaTimeSeconds);
      void CreateSecondTank(float deltaTimeSeconds);

      // Tank rendering variables
      std::vector<float> ground;

      float tankXStart = 650.0f;
      float tankSecondXStart = 1750.0f;

      float tankAngle;
      float tankSecondAngle;

      float turretAngle = 0.8f;
      float turretSecondAngle = 0.4f;

      glm::mat4 turretMatrix;
      glm::mat4 turretSecondMatrix;

      glm::mat4 modelMatrix;
      glm::mat4 modelSecondMatrix;

      // Projectile variables
      struct Projectile
      {
         glm::vec3 position;
         glm::vec3 velocity;
         float lifetime; 
      };

      std::vector<Projectile> tankProjectiles1;
      std::vector<Projectile> tankProjectiles2;

      // Projectile function
      void UpdateProjectiles(std::vector<Projectile>& projectiles, float deltaTimeSeconds);

      // Tank health variables
      float tank1Health = 100.0f;
      float tank2Health = 100.0f;
      const float DAMAGE_PER_HIT = 25.0f; // Damage dealt by each projectile
      bool tank1Alive = true;
      bool tank2Alive = true;

      // Health bar rendering function
      void RenderHealthBar(float x, float y, float health, const glm::vec3& color);

   };
} // namespace m1
