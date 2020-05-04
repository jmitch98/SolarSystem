#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "OrbitalBody.h"
#include "Renderer.h"

#define AU 3.0f
#define KM_TO_AU(km) (km * 2) / 16819000.0f

namespace solarsystem {
extern OrbitalBody* sun;
extern OrbitalBody* earth;
extern OrbitalBody* mercury;
extern OrbitalBody* venus;
extern OrbitalBody* mars;
extern OrbitalBody* jupiter;
extern OrbitalBody* saturn;
extern OrbitalBody* uranus;
extern OrbitalBody* neptune;
extern OrbitalBody* pluto;

extern OrbitalBody* compMercury;
extern OrbitalBody* compVenus;
extern OrbitalBody* compEarth;
extern OrbitalBody* compMars;
extern OrbitalBody* compJupiter;
extern OrbitalBody* compSaturn;
extern OrbitalBody* compUranus;
extern OrbitalBody* compNeptune;
extern OrbitalBody* compMoon;
extern OrbitalBody* compSun;
extern OrbitalBody* compPluto;

extern OrbitalBody* OB1;
extern OrbitalBody* OB2;

extern float simulationSpeed;
extern float simulationSpeedMultiplier;

/**
 * Inits the solar system objects.
 */
void Init();

/**
 * Calls draw on all the solar system bodies by traversing
 * the "scene graph" starting with the sun.
 */
void Draw(renderer::Shader shader);

/**
 * Frees all the memory the solar system allocated.
 */
void Destroy();
}  // namespace solarsystem

#endif
