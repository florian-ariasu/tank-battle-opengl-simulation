# Tank Battle - OpenGL Simulation 🚀

### 🎮 Overview
Tank Battle is a **2D physics-based tank combat simulation** built using OpenGL. This project features **realistic terrain generation, tank movement, projectile mechanics, and a static life bar system**. The game allows two players to engage in a strategic battle where they must aim, shoot, and move tactically to win.

### 🛠️ Installation & Setup
#### Prerequisites
- CMake (version 3.16 or higher)

#### Build & Run Instructions
1. Clone the repository:
##### HTTPS
```bash
git clone https://github.com/florian-ariasu/tank-battle.git
```

##### SSH
```bash
git clone git@github.com:florian-ariasu/tank-wars.git
```

2. Navigate to it:
```bash
cd tank-battle
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

### ✅ Implemented Functionalities
#### 🌍 Terrain Generation
- The terrain is generated using the **triangle strip method** in OpenGL.
- Uses **four amplitude-frequency wave functions** to create a realistic, undulating battlefield.
- Ensures smooth interactions between tanks and ground.

#### 🏆 Tank Mechanics
- **Two tanks** are rendered and controlled independently.
- Movement logic accounts for terrain height to ensure tanks remain aligned with the surface.
- **Rotating turret** allows dynamic aiming and shooting.

#### 💥 Projectile System
- Players can shoot projectiles at each other.
- **Projectile trajectory influenced by gravity** for realism.
- Collision detection determines whether a projectile hits an opponent.

#### ❤️ Life Bar System
- Health bar **does not** reduce when tanks take damage.
- Currently, the tank disappears after multiple hits, but **the life bar does not decrease gradually** (future improvement).

### 🔥 Planned Features & Contributions
Below are key features that need improvement:

#### 🔧 Features to Implement
1️⃣ **Gradual Life Bar Depletion** - Ensure the life bar **updates in real-time** and reduces smoothly as tanks take damage.

2️⃣ **Terrain Destruction** - Make the terrain **display holes or craters** when projectiles land, increasing tactical depth.

3️⃣ **Dark Mode** - Add a **dark mode toggle** for better visibility and aesthetics.

### 🤝 Contributing
In order to contribute, follow these steps:
1. **Fork** this repository.
2. **Clone** your forked repository.
3. Create a **feature branch** (`feature/new-enhancement`).
4. Implement your changes & **commit** with a descriptive message.
5. Push to GitHub and **open a Pull Request (PR)**.

#### 📬 Contact
For discussions, feature requests, or inquiries, please visit my GitHub profile: [florian-ariasu](https://github.com/florian-ariasu). Contributions and feedback are always appreciated!

### 📜 License
This project is licensed under the **MIT License** – feel free to use and modify it!
