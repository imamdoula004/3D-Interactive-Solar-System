# 🌌 3D Interactive Solar System (OpenGL – C++)

A **3D interactive Solar System simulation** developed using **C++ and OpenGL (GLUT)** for the **Computer Graphics** course in the **B.Sc. in Computer Science & Engineering** program at **Canadian University of Bangladesh**.

The project visualizes the Sun, planets, moons, orbital paths, and planetary motion in real time using texture mapping, animation, and keyboard-based interaction.

---

## ✨ Features

- 🌞 Sun, 8 planets, and Earth’s Moon  
- 🪐 Saturn with textured rings  
- 🔄 Real-time rotation and revolution  
- 🌠 Star-field background environment  
- 🧭 Free camera movement in 3D space  
- 🧠 Informative HUD with planet data  
- ⏩ Adjustable simulation speed  
- 🎯 Planet selection and highlighting  

---

## 🛠 Technologies Used

- **Language:** C++  
- **Graphics API:** OpenGL  
- **Windowing & Input:** GLUT / FreeGLUT  
- **Image Loading:** stb_image.h  
- **IDE:** Code::Blocks  

---

## 📁 Project Structure

```
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
```

⚠️ **Important:**  
The `textures` folder **must remain in the same directory as the compiled executable**, otherwise textures will not load.
You can download the jpg from here: https://www.solarsystemscope.com/textures/
---

## 🖥️ How to Run the Project (No Virtual Environment)

This project runs **directly on your local machine** using **Code::Blocks**.  
No virtual machine or virtual environment is required.

---

## 🔧 Step 1: Install Code::Blocks

1. Download Code::Blocks **with MinGW** from:  
   https://www.codeblocks.org/downloads/
2. Choose **Code::Blocks + MinGW (recommended)**

---

## 🔧 Step 2: Install OpenGL & FreeGLUT (Windows)

1. Download FreeGLUT from:  
   https://www.transmissionzero.co.uk/software/freeglut-devel/
2. Extract the archive.

### Copy files to the following locations:

**Header files (.h):**
```
C:\Program Files\CodeBlocks\MinGW\include\GL\
```

**Library files (.a):**
```
C:\Program Files\CodeBlocks\MinGW\lib\
```

**DLL file:**
```
C:\Windows\System32\
```

(Copy `freeglut.dll`)

---

## 🔧 Step 3: Create the Project in Code::Blocks

1. Open **Code::Blocks**
2. Go to:
```
File → New → Project → Console Application
```
3. Select **C++**
4. Name the project (e.g., `SolarSystem`)
5. Finish setup

---

## 🔧 Step 4: Add Project Files

1. Replace the auto-generated `main.cpp` with the provided one  
2. Copy `stb_image.h` into the project directory  
3. Copy the `textures` folder into the project directory  

---

## 🔧 Step 5: Link Required Libraries

1. Right-click the project → **Build options**
2. Select the **project name**
3. Open **Linker settings**
4. Add the following libraries **in this order**:

```
opengl32
glu32
freeglut
```

5. Click **OK**

---

## ▶️ Step 6: Build and Run

1. Click **Build & Run**
2. The **3D Interactive Solar System** window should appear

---

## 🎮 Keyboard Controls

### Camera Movement

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `Q` | Move up |
| `E` | Move down |

### Interaction

| Key | Action |
|---|---|
| `I` | Cycle through planets & show HUD |
| `+` | Increase simulation speed |
| `-` | Decrease simulation speed |
| `R` | Reset speed |

---

## ❗ Common Issues & Fixes

### Textures not loading
✔ Ensure:
- `textures/` folder is beside the executable  
- File names match exactly (case-sensitive)

---

### `freeglut.dll` missing error
✔ Copy `freeglut.dll` to:
```
C:\Windows\System32\
```

---

### Black screen
✔ Check:
- OpenGL libraries are linked correctly  
- `glEnable(GL_DEPTH_TEST)` is enabled  

---

## 🎓 Academic Context

- **Course:** Computer Graphics  
- **Program:** B.Sc. in Computer Science & Engineering  
- **University:** Canadian University of Bangladesh  

This project demonstrates:
- 3D transformations  
- Texture mapping  
- Real-time animation  
- Interactive graphics programming  

---

## 🚀 Future Improvements

- Lighting and shading models  
- Elliptical orbits  
- Mouse-controlled camera  
- UI panel instead of bitmap HUD  
- Planet zoom and focus mode  

---

## 📜 License

This project is intended for **educational use**.  
You are free to fork, modify, and extend it.
