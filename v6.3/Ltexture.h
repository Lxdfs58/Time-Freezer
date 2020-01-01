//
// Created by Davis Chou on 2019/12/17.
//

#ifndef SDL_LESSON_27_DOT_LTEXTURE_H
#define SDL_LESSON_27_DOT_LTEXTURE_H

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL_image.h>

//Texture wrapper class
class LTexture
{
public:
	LTexture();

	~LTexture();

	bool loadFromFile( std::string path );

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H_)
	//Creates image from font string
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif
	void free();

	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0);

	int getWidth();

	int getHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};
#endif
