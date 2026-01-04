🌌 3D Interactive Solar System (OpenGL – C++)

A 3D interactive Solar System simulation developed using C++ and OpenGL (GLUT) for the Computer Graphics course in the B.Sc. in Computer Science & Engineering program at Canadian University of Bangladesh.

The project visualizes the Sun, planets, moons, orbital paths, and planetary motion in real time with textures, animation, and keyboard-based interaction.

✨ Features

🌞 Sun, 8 planets, and Earth’s Moon

🪐 Saturn with textured rings

🔄 Real-time rotation and revolution

🌠 Textured star background

🧭 Free camera navigation

🧠 Informative HUD (planet facts, periods, size, distance)

⏩ Adjustable simulation speed

🎯 Planet selection and highlighting

🛠 Technologies Used

Language: C++

Graphics API: OpenGL

Windowing & Input: GLUT / FreeGLUT

Image Loading: stb_image.h

IDE: Code::Blocks

📁 Project Structure
3D-Solar-System/
│
├── main.cpp
├── stb_image.h
├── textures/
│   ├── sun.jpg
│   ├── mercury.jpg
│   ├── venus.jpg
│   ├── earth.jpg
│   ├── moon.jpg
│   ├── mars.jpg
│   ├── jupiter.jpg
│   ├── saturn.jpg
│   ├── saturn_ring.jpg
│   ├── uranus.jpg
│   ├── neptune.jpg
│   └── stars.jpg
└── README.md


⚠️ Important:
The textures folder must be in the same directory as the compiled executable.

🖥️ How to Run the Project (No Virtual Environment)

This project runs directly on your local machine using Code::Blocks.

🔧 Step 1: Install Required Software
1. Install Code::Blocks (with MinGW)

Download:

https://www.codeblocks.org/downloads/

Choose:

Code::Blocks with MinGW (recommended)

🔧 Step 2: Install OpenGL & FreeGLUT (Windows)
Option A: Using FreeGLUT (Recommended)

Download FreeGLUT:

https://www.transmissionzero.co.uk/software/freeglut-devel/

Extract the files and copy:

Copy .h files to:
C:\Program Files\CodeBlocks\MinGW\include\GL\

Copy .a files to:
C:\Program Files\CodeBlocks\MinGW\lib\

Copy freeglut.dll to:
C:\Windows\System32\

🔧 Step 3: Create Project in Code::Blocks

Open Code::Blocks

Go to:

File → New → Project → Console Application


Select:

C++

Name the project (e.g., SolarSystem)

Finish setup

🔧 Step 4: Add Project Files

Replace the generated main.cpp with the provided main.cpp

Copy stb_image.h into the project directory

Copy the textures folder into the project directory

🔧 Step 5: Link OpenGL Libraries

Right-click the project → Build options

Select the project name (not Debug/Release only)

Go to Linker settings

Add the following libraries in order:

opengl32
glu32
freeglut


Click OK

▶️ Step 6: Build and Run

Click Build & Run

The 3D Interactive Solar System window will appear

🎮 Keyboard Controls
Camera Movement
Key	Action
W	Move camera forward
S	Move camera backward
A	Move camera left
D	Move camera right
Q	Move camera up
E	Move camera down
Interaction
Key	Action
I	Cycle through planets & show HUD
+	Increase simulation speed
-	Decrease simulation speed
R	Reset speed
❗ Common Issues & Fixes
Textures Not Showing?

✔ Ensure:

textures/ folder is beside the executable

File names match exactly (case-sensitive)

freeglut.dll Missing Error?

✔ Copy freeglut.dll to:

C:\Windows\System32\

Black Screen?

✔ Check:

OpenGL libraries are linked correctly

Depth testing is enabled (glEnable(GL_DEPTH_TEST))

🎓 Academic Purpose

Course: Computer Graphics

Program: B.Sc. in Computer Science & Engineering

University: Canadian University of Bangladesh

This project demonstrates:

3D transformations

Texture mapping

Animation

Interactive graphics programming using OpenGL

📌 Future Enhancements

Lighting and shading models

Elliptical orbits

Mouse-controlled camera

UI panel instead of bitmap HUD

Planet zoom & focus mode

📜 License

This project is intended for educational use.
Feel free to fork and improve.
