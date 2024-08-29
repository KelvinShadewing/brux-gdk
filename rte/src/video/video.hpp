#pragma once

#include <SDL_render.h>
#include <string>

#include <vector>

#include <simplesquirrel/vm.hpp>

class BaseVideoAPI {
public:
	BaseVideoAPI(std::string driverName, std::string driverVersion) : mVideoDriverName(driverName), mVideoDriverVers(driverVersion) {}
	virtual ~BaseVideoAPI() = default;

	virtual void setTitle(const std::string& title) = 0;
	virtual void setIcon(const std::string& path) = 0;

	virtual void wait(int ticks) = 0;

	virtual void clearScreen() = 0;

	virtual void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;

	virtual int getDrawTarget() = 0;
	virtual void setDrawTarget(uint32_t tex) = 0;
	virtual void resetDrawTarget() = 0;

	virtual int textureCount() = 0;

	virtual uint32_t newTexture(uint32_t w, uint32_t h) = 0;
	virtual void deleteImage(uint32_t img) = 0;

	virtual uint32_t loadImage(const std::string& path) = 0;
	virtual uint32_t loadImageKeyed(const std::string& path, uint32_t key) = 0;

	virtual void drawImage(uint32_t tex, int x, int y) = 0;
	virtual void drawImagePart(uint32_t tex, int x, int y, int ox, int oy, int w, int h) = 0;
	virtual void drawImageEx(uint32_t tex, int x, int y, float angle, int flip, int xscale, int yscale, uint32_t color) = 0;

	virtual void setScaling(float scale) = 0;
	virtual void setScalingFilter(int hint) = 0;
	virtual void setResolution(int w, int h) = 0;

	virtual int screenW() = 0;
	virtual int screenH() = 0;

	virtual int windowW() = 0;
	virtual int windowH() = 0;

	virtual void toggleFullscreen() = 0;

	virtual void setTextureBlendMode(int texture, int blend) = 0;
	virtual void setTextureBlendMode(SDL_Texture* texture, int blend) = 0;

	virtual int findTexture(const std::string& name) = 0;
	virtual std::string getTextureName(int texture) = 0;

	virtual void* getTextureAddr(int tex) = 0;
	virtual int getTextureFilter(int tex) = 0;
	virtual void setTextureFilter(int tex, int filter) = 0;
	virtual void setTextureColorMod(int tex, uint8_t r, uint8_t g, uint8_t b) = 0;
	virtual void setTextureAlphaMod(int tex, uint8_t alpha) = 0;

	virtual void renderCopy(int tex, SDL_Rect* rec, SDL_Rect* des) = 0;
	virtual void renderCopyEx(int tex, SDL_Rect* rec, SDL_Rect* des, double angle, SDL_Point* piv, int flip) = 0;

	virtual void queryTexture(int tex, int* width, int* height) = 0;

	virtual void printTextureNames() = 0;

	/** SHAPES */
	virtual void drawCircle(int x, int y, int radius, bool filled) = 0;
	virtual void drawRect(int x, int y, int w, int h, bool filled) = 0;
	virtual void drawPoint(int x, int y) = 0;
	virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
	virtual void drawLineWide(int x1, int y1, int x2, int y2, int w) = 0;

	virtual void getScale(float* x, float* y) = 0;

	virtual void renderPresent() = 0;

	virtual const bool supportsShaders() { return false; }

	const std::string mVideoDriverName;
	const std::string mVideoDriverVers;
};

extern BaseVideoAPI* gvVideoDriver;

SDL_Texture* xyLoadTexture(const std::string& path);
void xyClearScreen();
void xyWait(int ticks);
void xySetDrawTarget(uint32_t tex);
int xyGetDrawTarget();
void xyResetDrawTarget();
void xyDrawImage(uint32_t tex, int x, int y);
void xyDrawImagePart(uint32_t tex, int x, int y, int ox, int oy, int w, int h);
void xyDrawImageEx(uint32_t tex, int x, int y, float angle, int flip, int xscale, int yscale, uint32_t color);
uint32_t xyLoadImage(const std::string& path);
uint32_t xyLoadImageKeyed(const std::string& path, uint32_t key);
void xySetDrawColor(int r, int g, int b, int a);
void xySetDrawColor(int color);
void xySetBackgroundColor(uint32_t color);
void xyDeleteImage(uint32_t img);
uint8_t xyGetRed(uint32_t color);
uint8_t xyGetGreen(uint32_t color);
uint8_t xyGetBlue(uint32_t color);
uint8_t xyGetAlpha(uint32_t color);
uint32_t xyNewTexture(uint32_t w, uint32_t h);
void xySetScaling(float scale);
void xySetScalingFilter(int hint);
void xySetResolution(int w, int h);
int xyScreenW();
int xyScreenH();
int xyWindowW();
int xyWindowH();

void xyToggleFullscreen();
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
