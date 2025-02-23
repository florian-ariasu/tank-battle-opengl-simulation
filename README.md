## Tank Battle - OpenGL Simulation

### Overview
Tank Battle is a **2D tank combat simulation** built using OpenGL. This project features **realistic terrain generation, tank movement, and projectile mechanics**. The game allows two players to engage in a strategic battle where they must aim, shoot, and move tactically to win.

### Installation & Setup
#### Prerequisites
- CMake (version 3.16 or higher)

#### Build & Run Instructions
1. Clone the repository:
##### HTTPS
```bash
git clone https://github.com/florian-ariasu/tank-wars.git
```

##### SSH
```bash
git clone git@github.com:florian-ariasu/tank-wars.git
```

2. Navigate to it:
```bash
cd tank-wars
```

3. Create and navigate to build directory:
```bash
mkdir build
cd build
```

4. Generate build files:
```bash
cmake ..
```

5. Compile:
  ```bash
make
```

6. Run the game:
```bash
./bin/Debug/GFXFramework
```

### Implemented Functionalities
#### Terrain Generation
- The terrain is generated using the **triangle strip method** in OpenGL.
- Uses **four amplitude-frequency wave functions** to create a realistic, undulating battlefield.
- Ensures smooth interactions between tanks and ground.

#### Tank Mechanics
- **Two tanks** are rendered and controlled independently.
- Movement logic accounts for terrain height to ensure tanks remain aligned with the surface.
- **Rotating turret** allows dynamic aiming and shooting.

#### Projectile System
- Players can shoot projectiles at each other.
- **Projectile trajectory influenced by gravity** for realism.
- Collision detection determines whether a projectile hits an opponent.

#### Health Bar System
- Currently, the tank disappears after multiple hits, but **the health bar has not been implemented yet** (future improvement).
- The health bar will gradually decrease in size as the tank takes damage.

### Planned Features & Contributions
Below are key features that need improvement:

#### Features to Implement
- **Gradual Health Bar Depletion** - Ensure the health bar **updates in real-time** and reduces smoothly as tanks take damage.

- **Terrain Destruction** - Make the terrain **display holes or craters** when projectiles land, increasing tactical depth.

- **Dark Mode** - Add a **dark mode toggle** for better visibility and aesthetics.

### Contributing
In order to contribute, follow these steps:
1. **Fork** this repository.
2. **Clone** your forked repository.
3. Create a **feature branch** (`feature/new-enhancement`).
4. Implement your changes & **commit** with a descriptive message.
5. Push to GitHub and **open a Pull Request (PR)**.

### Licence
This project is licensed under the MIT Licence. See the [LICENCE](./LICENSE) file for further details.
