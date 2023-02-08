#include "api/maths.hpp"

#include "brux/main.hpp"

#include "brux/maths.hpp"

namespace BruxAPI {

///////////
// MATHS //
///////////

float randFloat(float a) {
	return xyRandomFloat(a);
}

int randInt(int a) {
	return xyRandomInt(a);
}

float distance2(float x1, float y1, float x2, float y2) {
	return xyDistance(x1, y1, x2, y2);
}

bool inDistance2(float x1, float y1, float x2, float y2, float d) {
	return xyInDistance2(x1, y1, x2, y2, d);
}

float distance3(float x1, float y1, float z1, float x2, float y2, float z2) {
	return xyDistance3(x1, y1, z1, x2, y2, z2);
}

float wrap(float x, float mx, float mn) {
	return xyWrap(x, mn, mx);
}

int floor(float f) {
	return std::floor(f);
}

int ceil(float f) {
	return std::ceil(f);
}

int round(float f) {
	return std::round(f);
}

float pointAngle(float x1, float y1, float x2, float y2) {
	return xyPointAngle(x1, y1, x2, y2);
}

float abs(float f) {
	return std::abs(f);
}

float lendirX(float l, float d) {
	return xyLenDirX(l, d);
}

float lendirY(float l, float d) {
	return xyLenDirY(l, d);
}

std::string binstr(int i) {
	int l = static_cast<int>(log2(i)) + 1;
	std::string s;

	switch (l) {
		case 0:
			s = "0";
			break;
		case 1:
			s = std::bitset<1>(i).to_string();
			break;
		case 2:
			s = std::bitset<2>(i).to_string();
			break;
		case 3:
			s = std::bitset<3>(i).to_string();
			break;
		case 4:
			s = std::bitset<4>(i).to_string();
			break;
		case 5:
			s = std::bitset<5>(i).to_string();
			break;
		case 6:
			s = std::bitset<6>(i).to_string();
			break;
		case 7:
			s = std::bitset<7>(i).to_string();
			break;
		case 8:
			s = std::bitset<8>(i).to_string();
			break;
		case 9:
			s = std::bitset<9>(i).to_string();
			break;
		case 10:
			s = std::bitset<10>(i).to_string();
			break;
		case 11:
			s = std::bitset<11>(i).to_string();
			break;
		case 12:
			s = std::bitset<12>(i).to_string();
			break;
		case 13:
			s = std::bitset<13>(i).to_string();
			break;
		case 14:
			s = std::bitset<14>(i).to_string();
			break;
		case 15:
			s = std::bitset<15>(i).to_string();
			break;
		case 16:
			s = std::bitset<16>(i).to_string();
			break;
		case 17:
			s = std::bitset<17>(i).to_string();
			break;
		case 18:
			s = std::bitset<18>(i).to_string();
			break;
		case 19:
			s = std::bitset<19>(i).to_string();
			break;
		case 20:
			s = std::bitset<20>(i).to_string();
			break;
		case 21:
			s = std::bitset<21>(i).to_string();
			break;
		case 22:
			s = std::bitset<22>(i).to_string();
			break;
		case 23:
			s = std::bitset<23>(i).to_string();
			break;
		case 24:
			s = std::bitset<24>(i).to_string();
			break;
		case 25:
			s = std::bitset<25>(i).to_string();
			break;
		case 26:
			s = std::bitset<26>(i).to_string();
			break;
		case 27:
			s = std::bitset<27>(i).to_string();
			break;
		case 28:
			s = std::bitset<28>(i).to_string();
			break;
		case 29:
			s = std::bitset<29>(i).to_string();
			break;
		case 30:
			s = std::bitset<30>(i).to_string();
			break;
		case 31:
			s = std::bitset<31>(i).to_string();
			break;
		case 32:
			s = std::bitset<32>(i).to_string();
			break;
		default:
			s = std::bitset<64>(i).to_string();
			break;
	}

	return s;
}

} // namespace BruxAPI
