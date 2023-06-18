#ifndef PROJECTION_TEST_H
#define PROJECTION_TEST_H

#include <string>
#include <vector>
#include "../../math3/mesh3.hpp"
#include "../../math3/camera3.hpp"

class ProjectionTest{
public:
    const int k_escape = 41;
    const int k_a = 4;
	const int k_b = 5;
	const int k_c = 6;
	const int k_d = 7;
	const int k_e = 8;
	const int k_f = 9;
	const int k_g = 10;
	const int k_h = 11;
	const int k_i = 12;
	const int k_j = 13;
	const int k_k = 14;
	const int k_l = 15;
	const int k_m = 16;
	const int k_n = 17;
	const int k_o = 18;
	const int k_p = 19;
	const int k_q = 20;
	const int k_r = 21;
	const int k_s = 22;
	const int k_t = 23;
	const int k_u = 24;
	const int k_v = 25;
	const int k_w = 26;
	const int k_x = 27;
	const int k_y = 28;
	const int k_z = 29;
	const int k_lshift = 225;
	const int k_space = 44;
    std::string app_name;
    bool quit;
    int test_sprite;
    Camera3 camera;
    std::vector<Mesh3> objects;
    ProjectionTest();
    void StartGame();
    void Update();

    void Draw(); //unnecessary


};

#endif