#ifndef CUBE_HPP
#define CUBE_HPP
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include <memory>
#include <vector>

#define WHITE 255,255,255,0
#define RED 255,0,0,0
#define CYAN 0,255,255,0
#define GREEN 0,255,0,0
#define PINK 255,0,255,0
#define BLACK 0,0,0,0

typedef std::vector<std::vector<float>> Matrix;


struct Vec3
{
	float x,y,z;
	Vec3():x(0),y(0),z(0){}
	Vec3(double _x, double _y, double _z):x(_x),y(_y),z(_z){}
};

struct Edge
{
	size_t a,b;
	Edge():a(0),b(0){}
	Edge(size_t _a, size_t _b):a(_a),b(_b){}
};

struct Triangle
{
	Vec3 t[3];
	Triangle(Vec3 v1, Vec3 v2, Vec3 v3)
	{
		t[0] = v1;
		t[1] = v2;
		t[2] = v3;
	}
};

struct face
{
	int v1, v2, v3;
	face(int _v1 = 0, int _v2 = 0, int _v3 = 0):v1(_v1),v2(_v2),v3(_v3){}
};

struct Mesh
{
	std::vector<Triangle> m;
	Mesh(std::string fileName);
	Mesh();
	void read(std::string fileName);
};

class Shape3D
{
	private:
	std::shared_ptr<SDL_Renderer*> renderer;
	float x,y,z;
	float width, height;
	Mesh mesh;
	Matrix rotationMatrix;

	Matrix get_rx(float angle);
	Matrix get_ry(float angle);
	Matrix get_rz(float angle);
	Matrix m_mult(const Matrix& a, const Matrix& b);
	void transform(const Matrix& rotation,  Vec3& vec);
	void translate(const Vec3& shift,  Vec3& point);

	public:
	Shape3D(float _x, float _y, float _z, int _width, int _height, std::shared_ptr<SDL_Renderer*> _renderer, const char* fileName);
	void draw();
	void rotate(float alpha, float beta, float gamma);
	void set_color(const SDL_Color& c);
	
};

#endif