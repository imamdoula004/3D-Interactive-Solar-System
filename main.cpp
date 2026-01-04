#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstring>

#define DEG2RAD 0.0174533f

// ---------------- CAMERA ----------------
float camX = 0, camY = 30, camZ = 70;
int windowWidth = 1200, windowHeight = 900;

// ---------------- PLANET STRUCT ----------------
struct Planet {
    std::string name;
    float distance;
    float orbitSpeed;
    float rotationSpeed;
    float size;
    GLuint textureID;
    std::string texFile;
    bool hasRing;
    std::string ringFile;
    std::string shortFact;
    std::string detailedInfo;
    float orbitalPeriod;
    float rotationPeriod;

    Planet(std::string n, float d, float oS, float rS, float s, std::string file,
           std::string sf, std::string df, float op = 0, float rp = 0, bool ring = false, std::string rFile = "")
        : name(n), distance(d), orbitSpeed(oS), rotationSpeed(rS), size(s),
          textureID(0), texFile(file), hasRing(ring), ringFile(rFile),
          shortFact(sf), detailedInfo(df), orbitalPeriod(op), rotationPeriod(rp) {}
};

std::vector<Planet> planets;
GLuint starsTex;

// ---------------- HUD / Controls ----------------
int currentPlanet = 0; // starts with Sun
bool showHUD = false;
float speedMultiplier = 1.0f; // 1x real-time

// ---------------- TEXTURE LOADER ----------------
GLuint LoadTexture(const char* filename) {
    int w, h, channels;
    unsigned char* data = stbi_load(filename, &w, &h, &channels, 0);
    if (!data) { printf("Failed to load: %s\n", filename); return 0; }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return tex;
}

// ---------------- DRAW FUNCTIONS ----------------
void drawSphere(float radius, GLuint tex) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    gluSphere(q, radius, 36, 36);
    gluDeleteQuadric(q);
    glDisable(GL_TEXTURE_2D);
}

void drawRing(float innerR, float outerR, GLuint tex) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++) {
        float rad = i * DEG2RAD;
        glTexCoord2f(0, 0); glVertex3f(cos(rad) * innerR, 0, sin(rad) * innerR);
        glTexCoord2f(1, 1); glVertex3f(cos(rad) * outerR, 0, sin(rad) * outerR);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawOrbitalPath(float radius) {
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float rad = i * DEG2RAD;
        glVertex3f(cos(rad) * radius, 0, sin(rad) * radius);
    }
    glEnd();
}

void drawStars() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, starsTex);
    glPushMatrix();
    glRotatef(glutGet(GLUT_ELAPSED_TIME) * 0.002f, 0, 1, 0);
    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    gluSphere(q, 200, 50, 50);
    gluDeleteQuadric(q);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// ---------------- DISPLAY TEXT ----------------
void renderBitmapString(float x, float y, void* font, const char* string) {
    glRasterPos2f(x, y);
    while (*string) glutBitmapCharacter(font, *string++);
}

// ---------------- TITLE ----------------
void drawWindowTitle() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 0.8f, 0.0f); // gold color
    const char* title = "3D Interactive Solar System";
    int titleLength = strlen(title) * 18; // double the previous width estimate
    int x = (windowWidth - titleLength) / 2;
    int y = windowHeight - 50; // push down a little

    // Render text twice with offset for bold effect
    for (int dx = 0; dx <= 1; dx++)
        for (int dy = 0; dy <= 1; dy++) {
            glRasterPos2i(x + dx, y + dy);
            for (const char* c = title; *c != '\0'; c++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// ---------------- DISPLAY ----------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);

    drawStars();

    // Draw Sun
    drawSphere(planets[0].size, planets[0].textureID);

    // Draw orbital paths
    for (size_t i = 1; i < planets.size(); i++)
        drawOrbitalPath(planets[i].distance);

    // Draw planets
    for (size_t i = 1; i < planets.size(); i++) {
        Planet& p = planets[i];
        float orbitAngle = glutGet(GLUT_ELAPSED_TIME) * p.orbitSpeed * 0.001f * speedMultiplier;
        float spinAngle = glutGet(GLUT_ELAPSED_TIME) * p.rotationSpeed * 0.02f * speedMultiplier;

        glPushMatrix();
        glRotatef(orbitAngle, 0, 1, 0);
        glTranslatef(p.distance, 0, 0);
        glRotatef(spinAngle, 0, 1, 0);

        // Highlight current planet
        if ((int)i == currentPlanet) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glutWireSphere(p.size + 0.3f, 20, 20);
        }

        drawSphere(p.size, p.textureID);

        // Moon orbit
        if (i == 3) {
            glPushMatrix();
            glRotatef(glutGet(GLUT_ELAPSED_TIME) * 5.0f, 0, 1, 0);
            glTranslatef(2.0f, 0, 0);
            drawSphere(planets[4].size, planets[4].textureID);
            glPopMatrix();
        }

        // Rings
        if (p.hasRing)
            drawRing(p.size * 1.4f, p.size * 2.0f, p.textureID);

        glPopMatrix();
    }

    // Draw window title
    drawWindowTitle();

    // ---------------- HUD ----------------
    if (showHUD) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, windowWidth, 0, windowHeight);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3f(1, 1, 1);
        int yPos = windowHeight - 60; // leave space for title
        Planet& p = planets[currentPlanet];

        char buffer[512];

        void* fontLarge = GLUT_BITMAP_TIMES_ROMAN_24;
        void* fontSmall = GLUT_BITMAP_HELVETICA_18;

        sprintf(buffer, "Planet: %s", p.name.c_str());
        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
                renderBitmapString(20 + dx, yPos + dy, fontLarge, buffer);
        yPos -= 35;

        sprintf(buffer, "Distance from Sun: %.1f units", p.distance);
        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
                renderBitmapString(20 + dx, yPos + dy, fontSmall, buffer);
        yPos -= 30;

        sprintf(buffer, "Radius: %.2f units", p.size);
        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
                renderBitmapString(20 + dx, yPos + dy, fontSmall, buffer);
        yPos -= 30;

        sprintf(buffer, "Orbital Period: %.2f days", p.orbitalPeriod);
        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
                renderBitmapString(20 + dx, yPos + dy, fontSmall, buffer);
        yPos -= 30;

        sprintf(buffer, "Rotation Period: %.2f hours", p.rotationPeriod);
        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
                renderBitmapString(20 + dx, yPos + dy, fontSmall, buffer);
        yPos -= 30;

        sprintf(buffer, "Short Fact: %s", p.shortFact.c_str());
        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
                renderBitmapString(20 + dx, yPos + dy, fontSmall, buffer);
        yPos -= 30;

        sprintf(buffer, "Detailed Info: %s", p.detailedInfo.c_str());
        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
                renderBitmapString(20 + dx, yPos + dy, fontSmall, buffer);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    glutSwapBuffers();
}

// ---------------- IDLE ----------------
void idle() { glutPostRedisplay(); }

// ---------------- KEYBOARD ----------------
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': camZ -= 2; break;
    case 's': camZ += 2; break;
    case 'a': camX -= 2; break;
    case 'd': camX += 2; break;
    case 'q': camY += 2; break;
    case 'e': camY -= 2; break;

    case 'i':
        showHUD = true;
        currentPlanet++;
        if (currentPlanet >= (int)planets.size()) currentPlanet = 0;
        break;

    case '+': speedMultiplier *= 2.0f; break;
    case '-': speedMultiplier *= 0.5f; break;
    case 'r': speedMultiplier = 1.0f; break;
    }
}

// ---------------- INIT ----------------
void init() {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    planets.clear();
    planets.push_back(Planet("Sun", 0, 0, 0, 5.0f, "textures/sun.jpg", "Star at the center.", "The Sun is a G-type main-sequence star."));
    planets.push_back(Planet("Mercury", 8, 10, 1.0f, 0.8f, "textures/mercury.jpg", "Closest planet.", "Smallest planet in solar system.", 88, 1407));
    planets.push_back(Planet("Venus", 12, 8, 0.8f, 1.2f, "textures/venus.jpg", "Second planet.", "Hot planet with thick atmosphere.", 225, 5832));
    planets.push_back(Planet("Earth", 16, 5, 2.0f, 1.5f, "textures/earth.jpg", "Our home planet.", "Third planet from Sun.", 365, 24));
    planets.push_back(Planet("Moon", 0, 0, 5.0f, 0.5f, "textures/moon.jpg", "Earth's Moon.", "Natural satellite of Earth.", 27.3, 655));
    planets.push_back(Planet("Mars", 20, 4, 1.5f, 1.3f, "textures/mars.jpg", "Red planet.", "Fourth planet from Sun.", 687, 24.6));
    planets.push_back(Planet("Jupiter", 28, 2, 2.5f, 2.5f, "textures/jupiter.jpg", "Largest planet.", "Fifth planet from Sun.", 4333, 9.9));
    planets.push_back(Planet("Saturn", 36, 1.5, 2.0f, 2.0f, "textures/saturn.jpg", "Has rings.", "Sixth planet from Sun.", 10759, 10.7, true, "textures/saturn_ring.jpg"));
    planets.push_back(Planet("Uranus", 44, 1.0, 1.5f, 1.7f, "textures/uranus.jpg", "Ice giant.", "Seventh planet from Sun.", 30687, 17.2));
    planets.push_back(Planet("Neptune", 52, 0.8, 1.5f, 1.6f, "textures/neptune.jpg", "Ice giant.", "Eighth planet from Sun.", 60190, 16.1));

    for (size_t i = 0; i < planets.size(); i++)
        planets[i].textureID = LoadTexture(planets[i].texFile.c_str());

    starsTex = LoadTexture("textures/stars.jpg");
}

// ---------------- RESHAPE ----------------
void reshape(int w, int h) {
    if (h == 0) h = 1;
    windowWidth = w; windowHeight = h;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 1, 500);
    glMatrixMode(GL_MODELVIEW);
}

// ---------------- MAIN ----------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D Interactive Solar System");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
