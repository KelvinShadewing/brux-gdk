#pragma once

#include <SDL_render.h>
#include <string>

#include <vector>

#include <simplesquirrel/vm.hpp>

class BaseVideoAPI {
public:
	BaseVideoAPI(std::string driverName, std::string driverVersion) : mVideoDriverName(driverName), mVideoDriverVers(driverVersion) {}

	virtual void wait(int ticks);

	virtual void clearScreen() = 0;

	virtual void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;

	virtual int getDrawTarget() = 0;
	virtual void setDrawTarget(Uint32 tex) = 0;
	virtual void resetDrawTarget() = 0;

	virtual Uint32 newTexture(Uint32 w, Uint32 h) = 0;
	virtual void deleteImage(Uint32 img) = 0;

	virtual Uint32 loadImage(const std::string& path) = 0;
	virtual Uint32 loadImageKeyed(const std::string& path, Uint32 key) = 0;

	virtual void drawImage(Uint32 tex, int x, int y) = 0;
	virtual void drawImagePart(Uint32 tex, int x, int y, int ox, int oy, int w, int h) = 0;
	virtual void drawImageEx(Uint32 tex, int x, int y, float angle, int flip, int xscale, int yscale, Uint32 color) = 0;

	virtual void setScaling(float scale) = 0;
	virtual void setScalingFilter(int hint) = 0;
	virtual void setResolution(int w, int h) = 0;

	virtual int screenW() = 0;
	virtual int screenH() = 0;

	virtual int windowW() = 0;
	virtual int windowH() = 0;

	virtual void setTextureBlendMode(int texture, int blend) = 0;

	virtual int findTexture(const std::string& name) = 0;
	virtual std::string getTextureName(int texture) = 0;

	virtual int getTextureFilter(int tex) = 0;
	virtual void setTextureFilter(int tex, int filter) = 0;

	virtual void printTextureNames() = 0;

	/** SHAPES */
	virtual void drawCircle(int x, int y, int radius, bool filled) = 0;
	virtual void drawRect(int x, int y, int w, int h, bool filled) = 0;
	virtual void drawPoint(int x, int y) = 0;
	virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
	virtual void drawLineWide(int x1, int y1, int x2, int y2, int w) = 0;

	virtual const bool supportsShaders() { return false; }

	const std::string mVideoDriverName;
	const std::string mVideoDriverVers;
};

extern BaseVideoAPI* gvVideoDriver;

SDL_Texture* xyLoadTexture(const std::string& path);
void xyClearScreen();
void xyWait(int ticks);
void xySetDrawTarget(Uint32 tex);
int xyGetDrawTarget();
void xyResetDrawTarget();
void xyDrawImage(Uint32 tex, int x, int y);
void xyDrawImagePart(Uint32 tex, int x, int y, int ox, int oy, int w, int h);
void xyDrawImageEx(Uint32 tex, int x, int y, float angle, int flip, int xscale, int yscale, Uint32 color);
Uint32 xyLoadImage(const std::string& path);
Uint32 xyLoadImageKeyed(const std::string& path, Uint32 key);
void xySetDrawColor(int r, int g, int b, int a);
void xySetDrawColor(int color);
void xySetBackgroundColor(Uint32 color);
void xyDeleteImage(Uint32 img);
Uint8 xyGetRed(Uint32 color);
Uint8 xyGetGreen(Uint32 color);
Uint8 xyGetBlue(Uint32 color);
Uint8 xyGetAlpha(Uint32 color);
Uint32 xyNewTexture(Uint32 w, Uint32 h);
void xySetScaling(float scale);
void xySetScalingFilter(int hint);
void xySetResolution(int w, int h);
int xyScreenW();
int xyScreenH();
int xyWindowW();
int xyWindowH();
void xyTextureSetBlendMode(int texture, int blend);
int xyFindTexture(const std::string& name);
std::string xyGetTextureName(int texture);
int xyGetTextureFilter(int tex);
void xySetTextureFilter(int tex, int filter);
void xyPrintTextureNames();

/** SHAPES */
void xyDrawCircle(int x, int y, int radius, bool filled);
void xyDrawRect(int x, int y, int w, int h, bool filled);
void xyDrawPoint(int x, int y);
void xyDrawLine(int x1, int y1, int x2, int y2);
void xyDrawLineWide(int x1, int y1, int x2, int y2, int w);

void xyRegisterGraphicsAPI(ssq::VM& vm);
