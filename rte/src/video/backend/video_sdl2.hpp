#pragma once

#include <SDL2/SDL.h>

#include "../video.hpp"

class SDL2VideoBackend final : public BaseVideoAPI {
public:
	SDL2VideoBackend();
	~SDL2VideoBackend();

	void setTitle(const std::string& title) override;
	void setIcon(const std::string& path) override;

	void wait(int ticks) override;

	void clearScreen() override;

	void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;

	int getDrawTarget() override;
	void setDrawTarget(Uint32 tex) override;
	void resetDrawTarget() override;

	int textureCount() override;

	Uint32 newTexture(Uint32 w, Uint32 h) override;
	void deleteImage(Uint32 img) override;

	Uint32 loadImage(const std::string& path) override;
	Uint32 loadImageKeyed(const std::string& path, Uint32 key) override;

	void drawImage(Uint32 tex, int x, int y) override;
	void drawImagePart(Uint32 tex, int x, int y, int ox, int oy, int w, int h) override;
	void drawImageEx(Uint32 tex, int x, int y, float angle, int flip, int xscale, int yscale, Uint32 color) override;

	void setScaling(float scale) override;
	void setScalingFilter(int hint) override;
	void setResolution(int w, int h) override;

	int screenW() override;
	int screenH() override;

	int windowW() override;
	int windowH() override;

	void toggleFullscreen() override;

	void setTextureBlendMode(int texture, int blend) override;
	void setTextureBlendMode(SDL_Texture* texture, int blend) override;

	void renderCopy(int tex, SDL_Rect* rec, SDL_Rect* des) override;
	void renderCopyEx(int tex, SDL_Rect* rec, SDL_Rect* des, double angle, SDL_Point* piv, SDL_RendererFlip flip) override;

	int findTexture(const std::string& name) override;
	std::string getTextureName(int texture) override;

	void* getTextureAddr(int tex) override;
	int getTextureFilter(int tex) override;
	void setTextureFilter(int tex, int filter) override;
	void setTextureColorMod(int tex, uint8_t r, uint8_t g, uint8_t b) override;
	void setTextureAlphaMod(int tex, uint8_t alpha) override;

	void queryTexture(int tex, int* width, int* height) override;

	void printTextureNames() override;

	/** SHAPES */
	void drawCircle(int x, int y, int radius, bool filled) override;
	void drawRect(int x, int y, int w, int h, bool filled) override;
	void drawPoint(int x, int y) override;
	void drawLine(int x1, int y1, int x2, int y2) override;
	void drawLineWide(int x1, int y1, int x2, int y2, int w) override;

	void getScale(float* x, float* y) override;

	void renderPresent() override;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	std::vector<SDL_Texture*> mTextures;
	std::vector<std::string> mTextureNames;
private:
	SDL_Texture* loadTexture(const std::string& path);
	SDL_Texture* loadTextureKeyed(const std::string& path, Uint32 key);
};
