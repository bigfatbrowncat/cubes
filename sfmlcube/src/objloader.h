#include <SFML/System/Vector3.hpp>

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#ifndef OBJLOADER_H
#define OBJLOADER_H

#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif


struct face
{
	bool four;
	int vertexIndexes[4];
	int textureCoords[4];
	int normals[4];
	int mat;

	face(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3, int m);
	face(int v1, int v2, int v3, int v4, int t1, int t2, int t3, int t4, int n1, int n2, int n3, int n4, int m);
};

struct material{
	std::string name;
	float alpha,ns,ni;
	float dif[3],amb[3],spec[3];
	int illum;
	int texture;
	material(const char* na,float al,float n,float ni2,float* d,float* a,float* s,int i,int t);
};

struct texcoord{
	float u,v;
	texcoord(float a,float b);
};

class objloader{
	std::vector<std::string*> coord;
	std::vector<sf::Vector3f*> vertex;
	std::vector<face*> faces;
	//std::vector<sf::Vector3f*> normals;
	std::vector<unsigned int> texture;
	std::vector<unsigned int> lists;
	std::vector<material*> materials;
	std::vector<texcoord*> texturevector3d;
	std::vector<sf::Vector3f*> vertexnormals;
	bool ismaterial,isnormals,istexture,isvertexnormal;
	unsigned int loadTexture(const char* filename);
	void clean();
public:
	objloader();
	~objloader();
	int load(std::string, std::string texturesPath);
	void draw(int listIndex);

};

#endif
