#include <SFML/Graphics/Image.hpp>

#include "objloader.h"
#include "string.h"

	face::face(int v1, int v2, int v3, int t1, int t2, int t3, int n1, int n2, int n3, int m)
	{
		vertexIndexes[0]=v1;
		vertexIndexes[1]=v2;
		vertexIndexes[2]=v3;

		textureCoords[0]=t1;
		textureCoords[1]=t2;
		textureCoords[2]=t3;

		normals[0]=n1;
		normals[1]=n2;
		normals[2]=n3;

		mat=m;

		four=false;
	}
	face::face(int v1, int v2, int v3, int v4, int t1, int t2, int t3, int t4, int n1, int n2, int n3, int n4, int m)
	{
		vertexIndexes[0]=v1;
		vertexIndexes[1]=v2;
		vertexIndexes[2]=v3;
		vertexIndexes[3]=v4;

		textureCoords[0]=t1;
		textureCoords[1]=t2;
		textureCoords[2]=t3;
		textureCoords[3]=t4;

		normals[0]=n1;
		normals[1]=n2;
		normals[2]=n3;
		normals[3]=n4;

		mat=m;

		four=true;
	}
	
	material::material(const char* na,float al,float n,float ni2,float* d,float* a,float* s,int i,int t)
	{
		name=na;
		alpha=al;
		ni=ni2;
		ns=n;
		dif[0]=d[0];
		dif[1]=d[1];
		dif[2]=d[2];
		
		amb[0]=a[0];
		amb[1]=a[1];
		amb[2]=a[2];
		
		spec[0]=s[0];
		spec[1]=s[1];
		spec[2]=s[2];
		
		illum=i;
		texture=t;
	}
	
	texcoord::texcoord(float a,float b)
	{
		u=a;
		v=b;
	}

	int count(const std::string& s, char ch)
	{
		int res = 0;
		for (unsigned int i = 0; i < s.length(); i++)
		{
			if (s[i] == ch) res ++;
		}
		return res;
	}

int objloader::load(std::string filename, std::string texturesPath/*,std::vector<collisionplane>* collplane*/)
{
	std::ifstream in(filename.c_str());
	if(!in.is_open())
	{
		std::cout << "Nor oepened" << std::endl;
		return -1;
	}
	std::string path=filename.substr(0,(filename.find_last_of('/')!=std::string::npos ? filename.find_last_of('/')+1 : 0));
	char buf[256];
	int curmat=0;
	//bool coll=false;
	while(!in.eof())
	{
		in.getline(buf,256);
		coord.push_back(new std::string(buf));
	}
	for(unsigned int i=0;i<coord.size();i++)
	{
		if((*coord[i])[0]=='#')
			continue;
		else if((*coord[i])[0]=='v' && (*coord[i])[1]==' ')
		{
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
			vertex.push_back(new sf::Vector3f(tmpx,tmpy,tmpz));
		}else if((*coord[i])[0]=='v' && (*coord[i])[1]=='n')
		{
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			vertexnormals.push_back(new sf::Vector3f(tmpx,tmpy,tmpz));
		}else if((*coord[i])[0]=='f')
		{
			if(count(coord[i]->begin(),coord[i]->end(),' ')==4)
			{
				// Initializing memory
				int v[4], vt[4], vn[4];
				for (int k = 0; k < 4; k++)
				{
					v[k] = -1;
					vt[k] = -1;
					vn[k] = -1;
				}

				// Parsing face data
				if(coord[i]->find("//")!=std::string::npos)
				{
					sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d", &v[0], &vn[0], &v[1], &vn[1], &v[2], &vn[2], &v[3], &vn[3]);
				}
				else if(count(*(coord[i]), '/') == 4)
				{
					sscanf(coord[i]->c_str(),"f %d/%d %d/%d %d/%d %d/%d", &v[0], &vt[0], &v[1], &vt[1], &v[2], &vt[2], &v[3], &vt[3]);
				}
				else if(coord[i]->find("/")!=std::string::npos)
				{
					sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &vt[0], &vn[0],
					                                                                  &v[1], &vt[1], &vn[1],
					                                                                  &v[2], &vt[2], &vn[2],
					                                                                  &v[3], &vt[3], &vn[3]);
				}
				else
				{
					sscanf(coord[i]->c_str(),"f %d %d %d %d", &v[0], &v[1], &v[2], &v[3]);
				}

				// Creating the new face
				faces.push_back(new face(v[0], v[1], v[2], v[3], vt[0], vt[1], vt[2], vt[3], vn[0], vn[1], vn[2], vn[3], curmat));
			}
			else
			{
				// Initializing memory
				int v[3], vt[3], vn[3];
				for (int k = 0; k < 3; k++)
				{
					v[k] = -1;
					vt[k] = -1;
					vn[k] = -1;
				}

				// Parsing face data
				if(coord[i]->find("//")!=std::string::npos)
				{
					sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d", &v[0], &vn[0], &v[1], &vn[1], &v[2], &vn[2]);
				}
				else if(count(*(coord[i]), '/') == 3)
				{
					sscanf(coord[i]->c_str(),"f %d/%d %d/%d %d/%d", &v[0], &vt[0], &v[1], &vt[1], &v[2], &vt[2]);
				}
				else if(coord[i]->find("/")!=std::string::npos)
				{
					sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2]);
				}
				else
				{
					sscanf(coord[i]->c_str(),"f %d %d %d", &v[0], &v[1], &v[2]);
				}

				// Creating the new face
				faces.push_back(new face(v[0], v[1], v[2], v[3], vt[0], vt[1], vt[2], vt[3], vn[0], vn[1], vn[2], vn[3], curmat));
		}
	}else if((*coord[i])[0]=='u' && (*coord[i])[1]=='s' && (*coord[i])[2]=='e')
	{
		char tmp[200];
		sscanf(coord[i]->c_str(),"usemtl %s",tmp);
		/*if(strcmp(tmp,"collision")==0)
		{
			coll=true;
		}else*/{
			//coll=false;
			for(unsigned int i=0;i<materials.size();i++)
			{
				if(strcmp(materials[i]->name.c_str(),tmp)==0)
				{
					curmat=i;
					break;
				}
			}
		}
	}else if((*coord[i])[0]=='m' && (*coord[i])[1]=='t' && (*coord[i])[2]=='l' && (*coord[i])[3]=='l')
	{
		char filen[200];
		sscanf(coord[i]->c_str(),"mtllib %s",filen);
		std::string filen2=path+filen;
		std::ifstream mtlin(filen2.c_str());
		if(!mtlin.is_open())
		{
			std::cout << "connot open the material file" << std::endl;
			clean();
			return -1;
		}
		ismaterial=true;
		std::vector<std::string> tmp;
		char c[200];
		while(!mtlin.eof())
		{
			mtlin.getline(c,200);
			tmp.push_back(c);
		}
		char name[200];
		char filename[200];
		float amb[3],dif[3],spec[3],alpha,ns,ni;
		int illum;
		unsigned int texture = 0;
		bool ismat=false;
		strcpy(filename,"\0");
		std::cout << tmp.size() << std::endl;
		for(unsigned int i=0;i<tmp.size();i++)
		{
			if(tmp[i][0]=='#')
				continue;
			if(tmp[i][0]=='n' && tmp[i][1]=='e' && tmp[i][2]=='w')
			{
				if(ismat)
				{
					if(strcmp(filename,"\0")!=0)	//added
					{
						materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,texture));
						strcpy(filename,"\0");
					}else{
							materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,-1));				
					}
				}
				ismat=false;
				sscanf(tmp[i].c_str(),"newmtl %s",name);
			}else if(tmp[i][0]=='N' && tmp[i][1]=='s')
			{
				sscanf(tmp[i].c_str(),"Ns %f",&ns);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='a')
			{
				sscanf(tmp[i].c_str(),"Ka %f %f %f",&amb[0],&amb[1],&amb[2]);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='d')
			{
				sscanf(tmp[i].c_str(),"Kd %f %f %f",&dif[0],&dif[1],&dif[2]);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='s')
			{
				sscanf(tmp[i].c_str(),"Ks %f %f %f",&spec[0],&spec[1],&spec[2]);
				ismat=true;
			}else if(tmp[i][0]=='N' && tmp[i][1]=='i')
			{
				sscanf(tmp[i].c_str(),"Ni %f",&ni);
				ismat=true;
			}else if(tmp[i][0]=='d' && tmp[i][1]==' ')
			{
				sscanf(tmp[i].c_str(),"d %f",&alpha);
				ismat=true;
			}else if(tmp[i][0]=='i' && tmp[i][1]=='l')
			{
				sscanf(tmp[i].c_str(),"illum %d",&illum);
				ismat=true;
			}else if(tmp[i][0]=='m' && tmp[i][1]=='a')
			{
				sscanf(tmp[i].c_str(),"map_Kd %s",filename);
				texture=loadTexture((texturesPath + "/" + filename).c_str());
				ismat=true;
			}
		}
				if(ismat)
				{
					if(strcmp(filename,"\0")!=0)
					{
						materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,texture));
					}else{
							materials.push_back(new material(name,alpha,ns,ni,dif,amb,spec,illum,-1));				
					}
				}
	}else if((*coord[i])[0]=='v' && (*coord[i])[1]=='t')
	{
		float u,v;
		sscanf(coord[i]->c_str(),"vt %f %f",&u,&v);
		texturevector3d.push_back(new texcoord(u,1-v));
		istexture=true;
	}
}
	if(materials.size()==0)
		ismaterial=false;
	else
		ismaterial=true;
	std::cout << "[OBJ loader] Loaded: " << vertex.size() << " vertices, " << vertexnormals.size() << " normals, " << faces.size() << " faces, " << materials.size() << " materials" << std::endl;
	//draw
	if(isvertexnormal)
		smoothnormals();
	int num;
	num=glGenLists(1);
	glNewList(num,GL_COMPILE);
	int last=-1;
	for(unsigned int i=0;i<faces.size();i++)
	{
		if(last!=faces[i]->mat && ismaterial)
		{
			float diffuse[]={materials[faces[i]->mat]->dif[0],materials[faces[i]->mat]->dif[1],materials[faces[i]->mat]->dif[2],1.0};
			float ambient[]={materials[faces[i]->mat]->amb[0],materials[faces[i]->mat]->amb[1],materials[faces[i]->mat]->amb[2],1.0};
			float specular[]={materials[faces[i]->mat]->spec[0],materials[faces[i]->mat]->spec[1],materials[faces[i]->mat]->spec[2],1.0};
			glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
			glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
			glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
			glMaterialf(GL_FRONT,GL_SHININESS,materials[faces[i]->mat]->ns);
			glColor3f(diffuse[0],diffuse[1],diffuse[2]);
			last=faces[i]->mat;
			if(materials[faces[i]->mat]->texture==-1)
				glDisable(GL_TEXTURE_2D);
			else{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,materials[faces[i]->mat]->texture);
			}
		}
		if(faces[i]->four)
		{
			glBegin(GL_QUADS);

			for (int k = 0; k < 4; k++)
			{
				if (faces[i]->textureCoords[k] > 0)
				{
					glTexCoord2f(texturevector3d[faces[i]->textureCoords[k] - 1]->u,
								 texturevector3d[faces[i]->textureCoords[k] - 1]->v);
				}

				if (faces[i]->normals[k] != -1)
				{
					glNormal3f(vertexnormals[faces[i]->normals[k] - 1]->x,
							   vertexnormals[faces[i]->normals[k] - 1]->y,
							   vertexnormals[faces[i]->normals[k] - 1]->z);
				}

				glVertex3f(vertex[faces[i]->vertexIndexes[k] - 1]->x,
						   vertex[faces[i]->vertexIndexes[k] - 1]->y,
						   vertex[faces[i]->vertexIndexes[k] - 1]->z);
			}

			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);

			for (int k = 0; k < 3; k++)
			{
				if (faces[i]->textureCoords[k] != -1)
				{
					glTexCoord2f(texturevector3d[faces[i]->textureCoords[k] - 1]->u,
								 texturevector3d[faces[i]->textureCoords[k] - 1]->v);
				}

				if (faces[i]->normals[k] != -1)
				{
					glNormal3f(vertexnormals[faces[i]->normals[k] - 1]->x,
							   vertexnormals[faces[i]->normals[k] - 1]->y,
							   vertexnormals[faces[i]->normals[k] - 1]->z);
				}

				glVertex3f(vertex[faces[i]->vertexIndexes[k] - 1]->x,
						   vertex[faces[i]->vertexIndexes[k] - 1]->y,
						   vertex[faces[i]->vertexIndexes[k] - 1]->z);
			}

			glEnd();
		}
	}
	glEndList();
	clean();
	lists.push_back(num);
	return num;
}

void objloader::clean()
{
	for(unsigned int i=0;i<coord.size();i++)
		delete coord[i];
	for(unsigned int i=0;i<faces.size();i++)
		delete faces[i];
	for(unsigned int i=0;i<vertex.size();i++)
		delete vertex[i];
	for(unsigned int i=0;i<materials.size();i++)
		delete materials[i];
	for(unsigned int i=0;i<texturevector3d.size();i++)
		delete texturevector3d[i];
	for(unsigned int i=0;i<vertexnormals.size();i++)
		delete vertexnormals[i];
		
	coord.clear();
	faces.clear();
	vertex.clear();
	materials.clear();
	texturevector3d.clear();
	vertexnormals.clear();
}

objloader::~objloader()
{
	for(std::vector<unsigned int>::const_iterator it=texture.begin();it!=texture.end();it++)
	{
		glDeleteTextures(1,&(*it));
	}
	for(std::vector<unsigned int>::const_iterator it=lists.begin();it!=lists.end();it++)
	{
		glDeleteLists(*it,1);
	}
}

unsigned int objloader::loadTexture(const char* filename)
{
	unsigned int num;
	glGenTextures(1,&num);
	sf::Image img;
	//SDL_Surface* img=SDL_LoadBMP(filename);
	img.loadFromFile(filename);

	glBindTexture(GL_TEXTURE_2D,num);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.getSize().x,img.getSize().y,0,GL_RGBA,GL_UNSIGNED_BYTE,img.getPixelsPtr());
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//SDL_FreeSurface(img);
	texture.push_back(num);
	return num;
}

objloader::objloader()
{
	ismaterial=false;
	isnormals=false;
	istexture=false;
	isvertexnormal=true;
}

void objloader::smoothnormals()
{
	/*for(unsigned int i=1;i<vertex.size()+1;i++)
	{
		float vecX=0.0,vecY=0.0,vecZ=0.0;
		int num=0;
		for(unsigned int j=0;j<faces.size();j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if(faces[j]->vertexIndexes[k]==i)
				{
					vecX+=normals[faces[j]->faceNormalIndex - 1]->x;
					vecY+=normals[faces[j]->faceNormalIndex - 1]->y;
					vecZ+=normals[faces[j]->faceNormalIndex - 1]->z;
					num++;
				}
			}
		}
		if(num)
		{
			vecX/=num;
			vecY/=num;
			vecZ/=num;
		}
		float d=sqrt(vecX*vecX+vecY*vecY+vecZ*vecZ);
		if(d)
		{
		//	vecX/=d;
		//	vecY/=d;
		//	vecZ/=d;
		}
		vertexnormals.push_back(new sf::Vector3f(vecX,vecY,vecZ));
	}*/
}
