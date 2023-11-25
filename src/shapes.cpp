#include "shapes.hpp"
#include "window.hpp"
#include <fstream>
#include <sstream>

Mesh::Mesh(std::string fileName)
{
	read(fileName);
}
Mesh::Mesh(){}
void Mesh::read(std::string fileName)
{
	std::fstream file(fileName);
	if(!file)
	{
		printf("Error reading %s\n", fileName.c_str());
		std::exit(EXIT_FAILURE);
	}
	std::vector<Vec3> v;
	std::vector<face> f;
	std::string line = {};
	std::istringstream ss;
	char c;
	while(std::getline(file,line))
	{
		if(line.find("vn") == line.npos && line[0] == 'v')
		{
			ss.str(line);
			ss >> c;
			float x,y,z;
			ss >> x >> y >> z;
			v.emplace_back(x,y,z);
			ss.clear();
		}
		else if(line[0] == 'f')
		{
			ss.str(line);
			int v1, v2, v3;
			ss >> c >> v1 >> v2 >> v3;
			f.emplace_back(v1,v2,v3);
			ss.clear();
		}
	}
	for(auto& i : f)
		m.emplace_back(v[i.v1-1],v[i.v2-1],v[i.v3-1]);
}

Shape3D::Shape3D(float _x, float _y, float _z, int _width, int _height, std::shared_ptr<SDL_Renderer*> _renderer, const char* fileName)
: renderer(_renderer)
, x(_x)
, y(_y)
, z(_z)
, width(_width)
, height(_height)
{
	mesh.read(fileName);
	for(auto& p : mesh.m)
	{
		p.t[0].x = (float)width * p.t[0].x + x;
		p.t[0].y = (float)height * p.t[0].y + y;
		p.t[0].z = (float)width * p.t[0].z + z;

		p.t[1].x = (float)width * p.t[1].x + x;
		p.t[1].y = (float)height * p.t[1].y + y;
		p.t[1].z = (float)width * p.t[1].z + z;

		p.t[2].x = (float)width * p.t[2].x + x;
		p.t[2].y = (float)height * p.t[2].y + y;
		p.t[2].z = (float)width * p.t[2].z + z;
	}
}
Shape3D::Shape3D(float _x, float _y, float _z, int _width, int _height, std::shared_ptr<SDL_Renderer*> _renderer)
: renderer(_renderer)
, x(_x)
, y(_y)
, z(_z)
, width(_width)
, height(_height)
{

}

Matrix Shape3D::get_rx(float angle)
{
	return 
	{
	{1, 0, 0},
	{0, std::cos(angle), -std::sin(angle)},
	{0, std::sin(angle), std::cos(angle)}
	};
}

Matrix Shape3D::get_ry(float angle)
{
	return
	{
	{std::cos(angle), 0, std::sin(angle)},
	{0, 1, 0},
	{-std::sin(angle), 0, std::cos(angle)}
	};
}

Matrix Shape3D::get_rz(float angle)
{
	return 
	{
	{std::cos(angle), -std::sin(angle), 0},
	{std::sin(angle), std::cos(angle), 0},
	{0, 0, 1}
	};
}

Matrix Shape3D::m_mult(const Matrix& a, const Matrix& b)
{
	Matrix result = Matrix(a.size(), std::vector<float>(b[0].size(), 0));
	for (size_t i=0; i < a.size(); i++) 
		for (size_t j=0; j< b[0].size(); j++) 
			for (size_t k=0; k < b.size(); k++) 
				result[i][j] += a[i][k] * b[k][j];

	return result;
}

void Shape3D::transform(const Matrix& rotation, Vec3& point)
{
	float newX = rotation[0][0] * point.x + rotation[1][0] * point.y + rotation[2][0] * point.z;
	float newY = rotation[0][1] * point.x + rotation[1][1] * point.y + rotation[2][1] * point.z;
	float newZ = rotation[0][2] * point.x + rotation[1][2] * point.y + rotation[2][2] * point.z;
	point = {newX,newY,newZ};
}

void Shape3D::translate(const Vec3& shift,  Vec3& point)
{
		point.x += shift.x;
		point.y += shift.y;
		point.z += shift.z;
}

void Shape3D::draw()
{
	for(auto& p : mesh.m)
	{
		SDL_RenderDrawLine(*renderer,p.t[0].x, p.t[0].y, p.t[1].x, p.t[1].y);
		SDL_RenderDrawLine(*renderer,p.t[1].x, p.t[1].y, p.t[2].x, p.t[2].y);
		SDL_RenderDrawLine(*renderer,p.t[2].x, p.t[2].y, p.t[0].x, p.t[0].y);

		translate({-x,-y,-z},p.t[0]);
		if(rotationMatrix.size() != 0) transform(rotationMatrix, p.t[0]);
		translate({x, y, z}, p.t[0]);

		translate({-x,-y,-z},p.t[1]);
		if(rotationMatrix.size() != 0) transform(rotationMatrix, p.t[1]);
		translate({x, y, z}, p.t[1]);

		translate({-x,-y,-z},p.t[2]);
		if(rotationMatrix.size() != 0) transform(rotationMatrix, p.t[2]);
		translate({x, y, z}, p.t[2]);


		// SDL_Vertex v[3] = 
		// {
		// 	{{p.t[0].x,p.t[0].y},{WHITE},{}},
		// 	{{p.t[1].x,p.t[1].y},{WHITE},{}},
		// 	{{p.t[2].x,p.t[2].y},{WHITE},{}},
		// };
		// SDL_RenderGeometry(*renderer,0,v,3,0,0);
	}
}
void Shape3D::rotate(float alpha, float beta, float gamma)
{
	rotationMatrix = m_mult(get_rz(alpha), m_mult(get_ry(beta), get_rx(gamma)));
}

void Shape3D::set_color(const SDL_Color& c)
{
	SDL_SetRenderDrawColor(*renderer, c.r, c.g, c.b, c.a);
}