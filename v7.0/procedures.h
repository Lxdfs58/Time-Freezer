//
// Created by Davis Chou on 2019/12/25.
//
#ifndef _PROCEDURES_H
#define _PROCEDURES_H

#include <stdexcept>
#include <memory>
#include <list>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Ltexture.h"
#include "Timer.h"
#include "player.h"
#include "bullet.h"
#include "barrierGenerator.h"
#include "enemyGenerator.h"
#include "resource.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Takes key presses and adjusts the player's velocity
void handleEvent( SDL_Event& e ,int& VelX ,int& VelY);

#endif 
