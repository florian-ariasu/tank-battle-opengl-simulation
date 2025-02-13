# Tank Battle Project

This project is a simple tank battle game implemented using OpenGL and C++ where two tanks shoot projectiles at each other on a dynamically generated terrain. The game features two tanks, each with a turret that can rotate to aim at the enemy, and the terrain has a unique, wave-based structure created using a triangle strip method.

## Features Implemented:

- **Terrain Generation:** The terrain is generated using a triangle strip method, with the ground created based on four different wave amplitudes and frequencies.
- **Tank Movement:** Two tanks can move along the terrain, with their positions adjusted according to the ground height and a realistic movement system.
- **Turret Rotation:** Each tank has a turret that rotates to aim at the enemy. The turret can rotate only within a 180-degree range.
- **Projectile Launching:** Tanks can fire projectiles. The projectiles follow a parabolic trajectory, affected by gravity.
- **Projectile Impact:** Projectiles hit the terrain and disappear when they reach the ground level.
- **Life Bar:** Each tank has a life bar that decreases when hit by a projectile. 

## How to Play:

- **Move Tank 1:** Use `A` and `D` to move left and right, respectively.
- **Rotate Turret 1:** Use `W` and `S` to rotate the turret up and down.
- **Fire Projectile from Tank 1:** Press `Space` to fire a projectile.
- **Move Tank 2:** Use `Left Arrow` and `Right Arrow` to move left and right, respectively.
- **Rotate Turret 2:** Use `Up Arrow` and `Down Arrow` to rotate the turret up and down.
- **Fire Projectile from Tank 2:** Press `Enter` to fire a projectile.

## Contributing:

Contributions are welcome! Here are some ways you can help improve the project:

1. **Gradual Life Bar:** Implement a system where the life bar gradually decreases as the tank gets hit, instead of disappearing immediately.
2. **Terrain Damage:** Modify the terrain so that holes are created when a projectile hits the ground.
3. **Dark Mode:** Implement a functionality that allows users to toggle between light and dark mode when pressing a button.

If you're interested in contributing, please open a pull request or submit an issue on [my GitHub profile](https://github.com/florian-ariasu).

## License:
This project is open source and available under the MIT License.

