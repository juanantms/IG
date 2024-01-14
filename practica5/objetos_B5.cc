//**************************************************************************
// Práctica 5
//**************************************************************************

#include "objetos_B5.h"
#include "file_ply_stl.hpp"
#include <time.h> 


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();

}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores( )
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glColor3f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo seleccion
//*************************************************************************

void _triangulos3D::draw_seleccion(int r, int g, int b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3ub(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r, g, b, grosor);break;
	case EDGES:draw_aristas(r, g, b, grosor);break;
	case SOLID:draw_solido(r, g, b);break;
	case SOLID_COLORS:draw_solido_colores();break;
	case SELECT:draw_seleccion(r, g, b);break;
	}
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)  
  {colores_caras[i].r=rand()%1000/1000.0;
   colores_caras[i].g=rand()%1000/1000.0;
   colores_caras[i].b=rand()%1000/1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
     }
   else 
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
     } 
  }
}
void _triangulos3D::full_color(float r, float g, float b) {
  int i, n_c;
    n_c = caras.size();
    colores_caras.resize(n_c);
    for (i = 0; i < n_c; i++)
    {
      colores_caras[i].r = r;
      colores_caras[i].g = g;
      colores_caras[i].b = b;
    }
}

//*************************************************************************
// objetos o modelos
//*************************************************************************


//*************************************************************************
// clase medio cubo
//*************************************************************************

_mcubo::_mcubo(float tam)
{
  // vertices
  vertices.resize(6);
  vertices[0].x = -tam;
  vertices[0].y = -tam;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = -tam;
  vertices[1].z = tam;
  vertices[2].x = -tam;
  vertices[2].y = -tam;
  vertices[2].z = -tam;
  vertices[3].x = tam;
  vertices[3].y = -tam;
  vertices[3].z = -tam;
  vertices[4].x = tam;
  vertices[4].y = tam;
  vertices[4].z = -tam;
  vertices[5].x = -tam;
  vertices[5].y = tam;
  vertices[5].z = -tam;
  

  // triangulos
  caras.resize(8);
  caras[0]._0 = 0;
  caras[0]._1 = 2;
  caras[0]._2 = 5;

  caras[1]._0 = 4;
  caras[1]._1 = 3;
  caras[1]._2 = 1;

  caras[2]._0 = 2;
  caras[2]._1 = 0;
  caras[2]._2 = 1;

  caras[3]._0 = 2;
  caras[3]._1 = 3;
  caras[3]._2 = 1;

  caras[4]._0 = 5;
  caras[4]._1 = 4;
  caras[4]._2 = 3;

  caras[5]._0 = 5;
  caras[5]._1 = 2;
  caras[5]._2 = 3;

  caras[6]._0 = 1;
  caras[6]._1 = 5;
  caras[6]._2 = 0;

  caras[7]._0 = 1;
  caras[7]._1 = 4;
  caras[7]._2 = 5;


  // colores de las caras
  colors_random();
}


//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 

//colores de las caras
colors_random();
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
int i;
//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

//colores de las caras
colors_random();
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



void _objeto_ply::parametros(char *archivo)
{
int i, n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);
// vértices

for (i=0;i<n_ver;i++)
  {vertices[i].x=ver_ply[3*i];
   vertices[i].y=ver_ply[3*i+1];
   vertices[i].z=ver_ply[3*i+2];
  }

// vértices
for (i=0;i<n_car;i++)
  {caras[i].x=car_ply[3*i];
   caras[i].y=car_ply[3*i+1];
   caras[i].z=car_ply[3*i+2];
  }
 
//colores de las caras
colors_random();
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
float radio;

// tratamiento de los vértice
radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);

num_aux=perfil.size();
if (tipo==1) num_aux=num_aux-1;
vertices.resize(num_aux*num+2);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

caras.resize(2*(num_aux-1)*num+2*num);
int c=0;
for (j=0;j<num;j++)
 {
  for (i=0;i<num_aux-1;i++)
    {caras[c]._0=i+j*num_aux;
     caras[c]._1=((j+1)%num)*num_aux+i;
     caras[c]._2=1+i+j*num_aux;
     c+=1;
     caras[c]._0=((j+1)%num)*num_aux+i;
     caras[c]._1=((j+1)%num)*num_aux+1+i;
     caras[c]._2=1+i+j*num_aux;
     c+=1;
   }
 }
 
 //tapa inferior
 int total=num_aux*num;
 vertices[total].x=0.0;
 if (tipo==2) vertices[total].y=-radio;
 else vertices[total].y=perfil[0].y;
 vertices[total].z=0.0;

for (j=0;j<num;j++)
 {
     caras[c]._0=j*num_aux;
     caras[c]._1=((j+1)%num)*num_aux;
     caras[c]._2=total;
     c+=1;
 } 
 
//tapa superior
 vertices[total+1].x=0.0;
 if (tipo==1) vertices[total+1].y=perfil[1].y;
 if (tipo==0) vertices[total+1].y=perfil[num_aux-1].y;
 if (tipo==2) vertices[total+1].y=radio;
 vertices[total+1].z=0.0;
 
 for (j=0;j<num;j++)
 {
     caras[c]._0=total+1;
     caras[c]._1=((j+1)%num)*num_aux+num_aux-1;
     caras[c]._2=num_aux-1+j*num_aux;
     c+=1;
 }

//colores de las caras
colors_random();
}


//************************************************************************
// objeto cilindro (caso especial de rotacion)
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=-altura/2.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=radio; aux.y=altura/2.0; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,0,1,1);
}


//************************************************************************
// objeto cono (caso especial de rotacion)
//************************************************************************

_cono::_cono(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=0; aux.z=0.0;
perfil.push_back(aux);
aux.x=0.0; aux.y=altura; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,1,1,1);
}

//************************************************************************
// objeto esfera (caso especial de rotacion)
//************************************************************************

_esfera::_esfera(float radio, int num1, int num2)
{
vector<_vertex3f> perfil;
_vertex3f aux;
int i;
for (i=1;i<num1;i++)
  {aux.x=radio*cos(M_PI*i/(num1*1.0)-M_PI/2.0);
   aux.y=radio*sin(M_PI*i/(num1*1.0)-M_PI/2.0);
   aux.z=0.0;
   perfil.push_back(aux);
  }
parametros(perfil,num2,2,1,1);
}


//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************

_rotacion_PLY::_rotacion_PLY()
{

}

void _rotacion_PLY::parametros_PLY(char *archivo, int num)
{

}


//************************************************************************

//************************************************************************
// objeto por extrusión
//************************************************************************


_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=poligono.size();
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras 

caras.resize(num_aux*2);
int c=0;
for (i=0;i<num_aux;i++)         
  {
   caras[c]._0=i*2;
   caras[c]._1=(i*2+2)%(num_aux*2);
   caras[c]._2=i*2+1;    
   c=c+1;
   caras[c]._0=(i*2+2)%(num_aux*2);
   caras[c]._1=(i*2+2)%(num_aux*2)+1;
   caras[c]._2=i*2+1;    
   c=c+1;    
   }  
   
//colores de las caras
colors_random();
}


//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

_pala::_pala(float radio, float ancho, int num)
{
vector<_vertex3f> perfil;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int i, j;

vertice_aux.x=radio; vertice_aux.y=0; vertice_aux.z=-ancho/2.0;
perfil.push_back(vertice_aux);
vertice_aux.z=ancho/2.0;
perfil.push_back(vertice_aux);

// tratamiento de los vértices

for (j=0;j<=num;j++)
  {for (i=0;i<2;i++)	
     {
      vertice_aux.x=perfil[i].x*cos(M_PI*j/(1.0*num))-
                    perfil[i].y*sin(M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].x*sin(M_PI*j/(1.0*num))+
                    perfil[i].y*cos(M_PI*j/(1.0*num));
      vertice_aux.z=perfil[i].z;
      vertices.push_back(vertice_aux);
     }
  }
  
// tratamiento de las caras 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=(j+1)*2+1;
    caras.push_back(cara_aux);
    
    cara_aux._0=j*2;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=j*2+1;
    caras.push_back(cara_aux);
   }
   
// tapa inferior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=-ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
// tapa superior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2+1;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
}

//************************************************************************
// brazo
//************************************************************************

_brazo::_brazo()
{
ancho=0.6;
alto=0.1;
fondo=0.1;
colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
};

void _brazo::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
glTranslatef(0.5,0,0);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina()
{
ancho=0.4;
alto=0.6;
fondo=0.4;
cubo.colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion()
{
ancho=1.2;
alto=0.3;
fondo=0.8;
radio=0.15;
base.colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
};

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glTranslatef(2*ancho/6,-alto/2.0,0);
glRotatef(90,1,0,0);
glScalef(radio, fondo/2.2, radio);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-2*ancho/6,-alto/2.0,0);
glRotatef(90,1,0,0);
glScalef(radio, fondo/2.2, radio);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glScalef(ancho, alto, fondo);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_excavadora::_excavadora()
{
giro_cabina = 0.0;
giro_primer_brazo = 0.0;
giro_primer_brazo_max = 0;
giro_primer_brazo_min = -90;
giro_segundo_brazo = 0.0;
giro_segundo_brazo_max = 30;
giro_segundo_brazo_min = 0;
giro_pala = 0.0;
giro_pala_max = 50.0;
giro_pala_min = -90.0;

tamanio_pala=0.15;


int color=80;
piezas=5;
grosor_select=2;
color_pick=_vertex3f(1.0,0.0,0.0); 
color_select.resize(piezas);
activo.resize(piezas);

for (int i=0;i<piezas;i++)
  {activo[i]=0;
   color_select[i].r=color_select[i].g=color_select[i].b=color;
   color+=20;
  }
};

//************************************************************************

void _excavadora::draw(_modo modo, float r, float g, float b, float grosor)
{
float r_p,g_p,b_p;
int tam=2;

r_p=color_pick.r;
g_p=color_pick.g;
b_p=color_pick.b;

glPushMatrix();

if (activo[0]==1) sustentacion.draw(EDGES, r_p, g_p, b_p, grosor_select);
else sustentacion.draw(modo, r, g, b, grosor);

glTranslatef(0,(cabina.alto+sustentacion.alto)/2.0,0);
glRotatef(giro_cabina,0,1,0);
if (activo[1]==1) cabina.draw(EDGES, r_p, g_p, b_p, grosor_select);
else cabina.draw(modo, r, g, b, grosor);

glTranslatef(cabina.ancho/2.0,0,0);
glRotatef(giro_segundo_brazo,0,0,1);
if (activo[2]==1) brazo.draw(EDGES, r_p, g_p, b_p, grosor_select);
else brazo.draw(modo, r, g, b, grosor);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_primer_brazo,0,0,1);
if (activo[3]==1) brazo.draw(EDGES, r_p, g_p, b_p, grosor_select);
else brazo.draw(modo, r, g, b, grosor);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_pala,0,0,1);
glTranslatef(tamanio_pala,0,0);
glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
if (activo[4]==1) pala.draw(EDGES, r_p, g_p, b_p, grosor_select);
else pala.draw(modo, r, g, b, grosor);

glPopMatrix();
};

//************************************************************************

void _excavadora::seleccion()
{
_vertex3i color;

glPushMatrix();
color=color_select[0];
sustentacion.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(0,(cabina.alto+sustentacion.alto)/2.0,0);
glRotatef(giro_cabina,0,1,0);
color=color_select[1];
cabina.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(cabina.ancho/2.0,0,0);
glRotatef(giro_segundo_brazo,0,0,1);
color=color_select[2];
brazo.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_primer_brazo,0,0,1);
color=color_select[3];
brazo.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_pala,0,0,1);
glTranslatef(tamanio_pala,0,0);
glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
color=color_select[4];
pala.draw(SELECT, color.r, color.g, color.b, 1);

glPopMatrix();
};




//************************************************************************
// cabina AT ST
//************************************************************************

_cabina_AT_ST::_cabina_AT_ST()
{
  ancho = 0.65;
  alto = 0.9;
  fondo = 0.8;
  cubo.full_color(0.6431, 0.6314, 0.6275);

  ancho2 = 0.65;
  alto2 = 0.2;
  fondo2 = 0.2;
  cubo2.full_color(0.6431, 0.6314, 0.6275);

  ancho3 = 0.65;
  alto3 = 1.1;
  fondo3 = 0.2;
  frontal.full_color(0.6431, 0.6314, 0.6275);

  ancho4 = 0.65;
  alto4 = 0.1;
  fondo4 = 0.8;
  arriba.full_color(0.6431, 0.6314, 0.6275);
  
  ancho5 = 0.65;
  alto5 = 1;
  fondo5 = 0.1;
  //atras.colors_chess(0.6431, 0.6431, 0.6314, 0.6314, 0.6275, 0.6275);
  atras.full_color(0.6431, 0.6314, 0.6275);

  ancho6 = 0.18;
  alto6 = 0.2;
  fondo6 = 0.04;
  orificio1.full_color(0, 0, 0);

  ancho7 = 0.18;
  alto7 = 0.2;
  fondo7 = 0.04;
  orificio2.full_color(0, 0, 0);

  ancho8 = 0.35;
  alto8 = 0.35;
  fondo8 = 0.08;
  orificio3.full_color(0, 0, 0);

  ancho9 = 0.18;
  alto9 = 0.03;
  fondo9 = 0.3;
  tapa1.full_color(0.6431, 0.6314, 0.6275);

  ancho10 = 0.18;
  alto10 = 0.03;
  fondo10 = 0.3;
  tapa2.full_color(0.6431, 0.6314, 0.6275);

};

void _cabina_AT_ST::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glTranslatef(0,0,0.03);
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -((alto + alto2) / 2.0), (ancho / 2));
  glScalef(ancho2, alto2, fondo2);
  cubo2.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -alto2/2, (ancho / 2)+fondo3);
  glScalef(ancho3, alto3, fondo3);
  frontal.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, (alto + alto4) / 2.0, 0.03);
  glScalef(ancho4, alto4, fondo4);
  arriba.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, alto4/2,  -(ancho/2)-fondo5+0.02);
  glRotatef(180,120,0,1);
  glScalef(ancho5, alto5, fondo5);
  atras.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ancho/3-0.05, (alto/3)-0.05, (ancho2+ancho)/3+0.04);
  glScalef(ancho6, alto6, fondo6);
  orificio1.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-(ancho/3)+0.05, (alto/3)-0.05, (ancho2+ancho)/3+0.04);
  glScalef(ancho7, alto7, fondo7);
  orificio2.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -((alto + alto2) / 2) + 0.101, (ancho2+ancho)/3+0.16);
  glScalef(ancho8, alto8, fondo8);
  orificio3.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ancho/3-0.05, (alto/3)+0.05, (ancho2+ancho)/3+0.04);
  glScalef(ancho9, alto9, fondo9);
  tapa1.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-(ancho/3)+0.05, (alto/3)+0.05, (ancho2+ancho)/3+0.04);
  glScalef(ancho10, alto10, fondo10);
  tapa2.draw(modo, r, g, b, grosor);
  glPopMatrix();


};

//************************************************************************
// Torretas AT ST
//************************************************************************

_torretas_AT_ST::_torretas_AT_ST()
{
  radio_der = 0.3;
  num1_der = 50;
  num2_der = 50;
  esf_der = _esfera(radio_der, num1_der, num2_der);
  esf_der.full_color(0, 0, 0);

  radio_izq = 0.3;
  num1_izq = 50;
  num2_izq = 50;
  esf_izq = _esfera(radio_der, num1_der, num2_der);
  esf_izq.full_color(0, 0, 0);

  radio_eje = 0.2;
  altura = 1.3;
  num_eje = 30;
  eje = _cilindro(radio_eje, altura, num_eje);
  eje.full_color(0.1, 0.1, 0.1);

  radio_sop = 0.05;
  altura_sop = 0.2;
  num_sop = 20;
  soporte_torreta = _cilindro(radio_sop, altura_sop, num_sop);
  soporte_torreta.full_color(0.2,0.2,0.2);

  ancho = 0.2;
  alto = 0.3;
  fondo = 0.06;
  soporte_canion.full_color(0.3,0.3,0.3);

  radio_can = 0.05;
  altura_can = 0.6;
  num_can = 15;
  canion = _cilindro(radio_can, altura_can, num_can);
  canion.full_color(0.1, 0.1, 0.1);

  radio_can_es = 0.1;
  altura_can_es = 0.8;
  num_can_es = 8;
  canion_especial = _cilindro(radio_can_es, altura_can_es, num_can_es);
  canion_especial.full_color(0.1, 0.1, 0.1);

};

void _torretas_AT_ST::draw(_modo modo, float r, float g, float b, float grosor)
{



 glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  glTranslatef(0.36,0,0);
  esf_der.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  glTranslatef(-0.36,0,0);
  esf_izq.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  glRotatef(90,0,0,1);
  glTranslatef(0,0,0);
  eje.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  glRotatef(90,0,0,1);
  glTranslatef(0,0.75,0);
  soporte_torreta.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  glRotatef(90,0,0,1);
  glTranslatef(0,-0.75,0);
  soporte_torreta.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho, alto, fondo);
  glTranslatef(3.3,0,0);
  soporte_canion.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  glRotatef(90,1,0,0);
  glTranslatef(0.95,0.15,-0.1);
  canion.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.6, 0.6, 0.6);
  glRotatef(90,1,0,0);
  glTranslatef(1.2,0.1,0.1);
  canion.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.6, 0.6, 0.6);
  glRotatef(90,1,0,0);
  glTranslatef(1,0.1,0.1);
  canion.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.7, 0.7, 0.7);
  glRotatef(90,1,0,0);
  glTranslatef(-0.85,0.15,0);
  canion_especial.draw(modo, r, g, b, grosor);
  glPopMatrix();





};

_torreta_principal_AT_ST::_torreta_principal_AT_ST()
{
  
  radio_can = 0.05;
  altura_can = 0.6;
  num_can = 15;
  canion = _cilindro(radio_can, altura_can, num_can);
  canion.full_color(0.1, 0.1, 0.1);

  ancho_principal = 0.25;
  alto_principal = 0.2;
  fondo_principal = 0.2;
  soporte_principal.full_color(0.3,0.3,0.3);

};

void _torreta_principal_AT_ST::draw(_modo modo, float r, float g, float b, float grosor)
{



  glPushMatrix();
  glScalef(ancho_principal, alto_principal, fondo_principal);
  soporte_principal.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.6, 0.6, 0.6);
  glRotatef(90,1,0,0);
  glTranslatef(-0.1,0.23,0);
  canion.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.6, 0.6, 0.6);
  glRotatef(90,1,0,0);
  glTranslatef(0.1,0.23,0);
  canion.draw(modo, r, g, b, grosor);
  glPopMatrix();


};



//************************************************************************
// Base AT ST
//************************************************************************

_base_AT_ST::_base_AT_ST()
{
  ancho = 0.3;
  alto = 0.1;
  fondo = 0.3;
  base.full_color(0.6431, 0.6314, 0.6275);
};

void _base_AT_ST::draw(_modo modo, float r, float g, float b, float grosor)
{

  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho*1.75, alto*1.2, fondo*2);
  glTranslatef(0, -0.5, 0);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho*1.8, alto*1.5, fondo*2.2);
  glTranslatef(0, -0.8, 0.045);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

};


//************************************************************************
// Patas AT ST
//************************************************************************

_patas_AT_ST::_patas_AT_ST()
{
  ancho_sup = 0.05;
  alto_sup = 0.15;
  fondo_sup = 0.6;
  soporte_superior.full_color(0.6431, 0.6314, 0.6275);

  ancho_cen = 0.07;
  alto_cen = 0.2;
  fondo_cen = 0.8;
  soporte_central.full_color(0.6431, 0.6314, 0.6275);

  radio=0.17;
  altura=0.1;
  num=35;
  soporte = _cilindro(radio, altura, num);
  soporte.full_color(0.6431, 0.6314, 0.6275);

  ancho_inf = 0.07;
  alto_inf = 0.2;
  fondo_inf = 1.6;
  soporte_inferior.full_color(0.6431, 0.6314, 0.6275);

  ancho1 = 0.3;
  alto1 = 0.08;
  fondo1 = 0.5;
  pie1.full_color(0.6431, 0.6314, 0.6275);

  ancho2 = 0.1;
  alto2 = 0.4;
  fondo2 = 0.4;
  pie2.full_color(0.6431, 0.6314, 0.6275);


};

void _patas_AT_ST::draw(_modo modo, float r, float g, float b, float grosor)
{

  //Pata izquierda

  glPushMatrix();
  glRotatef(25, 1, 0, 0);
  glScalef(ancho_sup, alto_sup, fondo_sup);
  glTranslatef(6, -1.3, 0.3);
  soporte_superior.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(5, -1, 0, 0);
  glScalef(ancho_cen, alto_cen, fondo_cen);
  glTranslatef(4.7, -2, 0);
  soporte_central.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glScalef(0.7, 0.7, 0.7);
  glTranslatef(-0.5, -0.48, 0.5);
  soporte.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glScalef(0.8, 1, 0.8);
  glTranslatef(-0.53, -0.34, -0.5);
  soporte.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(75, 1, 0, 0);
  glScalef(ancho_inf, alto_inf, fondo_inf);
  glTranslatef(4.7, -2.3, 0.7);
  soporte_inferior.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho1, alto1, fondo1);
  glTranslatef(1.05, -26, 0.7);
  pie1.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho2, alto2, fondo2);
  glTranslatef(3.3, -4.8, 0.7);
  pie2.draw(modo, r, g, b, grosor);
  glPopMatrix();


  //Pata derecha

  glPushMatrix();
  glRotatef(25, 1, 0, 0);
  glScalef(ancho_sup, alto_sup, fondo_sup);
  glTranslatef(-6, -1.3, 0.3);
  soporte_superior.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(5, -1, 0, 0);
  glScalef(ancho_cen, alto_cen, fondo_cen);
  glTranslatef(-4.7, -2, 0);
  soporte_central.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glScalef(0.7, 0.7, 0.7);
  glTranslatef(-0.5, 0.48, 0.5);
  soporte.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glScalef(0.8, 1, 0.8);
  glTranslatef(-0.53, 0.34, -0.5);
  soporte.draw(modo, r, g, b, grosor);
  glPopMatrix();
  
  glPushMatrix();
  glRotatef(75, 1, 0, 0);
  glScalef(ancho_inf, alto_inf, fondo_inf);
  glTranslatef(-4.7, -2.3, 0.7);
  soporte_inferior.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho1, alto1, fondo1);
  glTranslatef(-1.05, -26, 0.7);
  pie1.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho2, alto2, fondo2);
  glTranslatef(-3.3, -4.8, 0.7);
  pie2.draw(modo, r, g, b, grosor);
  glPopMatrix();



};

//************************************************************************

void _at_st::seleccion()
{

  _vertex3i color;

  glPushMatrix();
  
  color = color_select[0];
  base.draw(SELECT, color.r, color.g, color.b, 1);

  color = color_select[1];
  patas.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();


  glPushMatrix();

  glTranslatef(0, (cabina.alto + base.alto) / 2.0, 0.2);
  glRotatef(giro_cabina,0,1,0);
  glRotatef(giro_cabina_vertical,1,0,0);
  color = color_select[2];
  cabina.draw(SELECT, color.r, color.g, color.b, 1);
  

  glPushMatrix();
  glTranslatef(0, -0.5, 0.57);
  glRotatef(giro_torreta_principal,1,0,0);
  color = color_select[3];
  torreta_pricipal.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.1, 0.2);
  glRotatef(giro_torretas,1,0,0);
  color = color_select[4];
  torretas.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();
  
  glPopMatrix();
};

//************************************************************************
// AT ST (montaje del objeto final)
//************************************************************************

_at_st::_at_st(){
  giro_cabina = 0.0;
  giro_torretas = 0.0;
  giro_torreta_principal = 0.0;
  
  giro_cabina_max = 30;
  giro_cabina_min = -30;
  giro_cabina_vertical_max = 15;
  giro_cabina_vertical_min = -5;
  giro_torreta_max = 25;
  giro_torreta_min = -20;

  int color=80;
  piezas=5;
  grosor_select=2;
  color_pick=_vertex3f(1.0,0.0,0.0); 
  color_select.resize(piezas);
  activo.resize(piezas);

  for (int i=0;i<piezas;i++)
    {activo[i]=0;
    color_select[i].r=color_select[i].g=color_select[i].b=color;
    color+=20;
    }

};

void _at_st::draw(_modo modo, float r, float g, float b, float grosor)
{

  float r_p,g_p,b_p;
  int tam=2;

  r_p=color_pick.r;
  g_p=color_pick.g;
  b_p=color_pick.b;


  glPushMatrix();

  if (activo[0]==1) base.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else {
    base.draw(modo, r, g, b, grosor);
    base.draw(EDGES, 0, 0, 0, grosor);
  } 
  
  if (activo[1]==1) patas.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else {
    patas.draw(modo, r, g, b, grosor);
    patas.draw(EDGES, 0, 0, 0, grosor);
  } 

  glPopMatrix();


  glPushMatrix();

  glTranslatef(0, (cabina.alto + base.alto) / 2.0, 0.2);
  glRotatef(giro_cabina,0,1,0);
  glRotatef(giro_cabina_vertical,1,0,0);
  if (activo[2]==1) cabina.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else {
    cabina.draw(modo, r, g, b, grosor);
    cabina.draw(EDGES, 0, 0, 0, grosor);
  } 
  
  glPushMatrix();
  glTranslatef(0, -0.5, 0.57);
  glRotatef(giro_torreta_principal,1,0,0);
  if (activo[3]==1) torreta_pricipal.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else {
    torreta_pricipal.draw(modo, r, g, b, grosor);
  } 
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.1, 0.2);
  glRotatef(giro_torretas,1,0,0);
  if (activo[4]==1) torretas.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else {
    torretas.draw(modo, r, g, b, grosor);
  } 
  glPopMatrix();
  
  glPopMatrix();
};
