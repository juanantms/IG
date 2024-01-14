//**************************************************************************
// Práctica 5 
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS,SELECT} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_colores();
void    draw_seleccion(int r, int g, int b);
void 	draw(_modo modo, float r, float g, float b, float grosor);

/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
void   full_color(float r, float g, float b);


vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;

};

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};
class _mcubo: public _triangulos3D
{
public:

	_mcubo(float tam=0.5);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************
// tipo indica si es una figura por revolución normal o bien un cono o una esfera
// tipo=0 normal, tipo=1 cono, tipo=2 esfera
// tapa_in=0 sin tapa, tapa_in=1 con tapa
// tapa_su=0 sin tapa, tapa_su=1 con tapa

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void  parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su);
};

 
//************************************************************************
// cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
       _cilindro(float radio=1.0, float altura=2.0, int num=12);
};

//************************************************************************
// cono
//************************************************************************

class _cono: public _rotacion
{
public:
       _cono(float radio, float altura, int num);
};

//************************************************************************
// esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
       _esfera(float radio, int num1, int num2);
};


//************************************************************************
// rotacion archivo PLY
//************************************************************************

class _rotacion_PLY: public _rotacion
{
public:
       _rotacion_PLY();
void  parametros_PLY(char *archivo, int num);
};


//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};


//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

class _pala: public _triangulos3D
{
public:
      _pala(float radio=1.0, float ancho=2.0, int num=8);
};

//************************************************************************
// brazo
//************************************************************************

class _brazo: public _triangulos3D
{
public:
      _brazo();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina: public _triangulos3D
{
public:
       _cabina();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// sustentación
//************************************************************************

class _sustentacion: public _triangulos3D
{
public:
      _sustentacion();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

class _excavadora: public _triangulos3D
{
public:
       _excavadora();
       
void  draw(_modo modo, float r, float g, float b, float grosor);
void  seleccion(); // método para selección

float giro_cabina;
float giro_primer_brazo;
float giro_segundo_brazo;
float giro_pala;

float giro_primer_brazo_max;
float giro_primer_brazo_min;
float giro_segundo_brazo_max;
float giro_segundo_brazo_min;
float giro_pala_max;
float giro_pala_min;

float tamanio_pala;

// atributos para la selección

_vertex3f color_pick;
vector<_vertex3i> color_select;
vector<int> activo;
int piezas;
int grosor_select;  


protected:
_pala pala;
_brazo brazo;
_cabina cabina;
_sustentacion sustentacion;
};


//************************************************************************
// cabina
//************************************************************************

class _cabina_AT_ST: public _triangulos3D
{
public:
       _cabina_AT_ST();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

float ancho2;
float alto2;
float fondo2;

float ancho3;
float alto3;
float fondo3;

float ancho4;
float alto4;
float fondo4;

float ancho5;
float alto5;
float fondo5;

float ancho6;
float alto6;
float fondo6;

float ancho7;
float alto7;
float fondo7;

float ancho8;
float alto8;
float fondo8;

float ancho9;
float alto9;
float fondo9;

float ancho10;
float alto10;
float fondo10;


protected:
_cubo cubo;          // 1
_cubo cubo2;         // 2 
_mcubo frontal;      // 3
_mcubo arriba;       // 4
_mcubo atras;        // 5
_mcubo orificio1;    // 6
_mcubo orificio2;    // 7
_mcubo orificio3;    // 8
_cubo tapa1;         // 9
_cubo tapa2;         // 10
};


//************************************************************************
// Torretas
//************************************************************************

class _torretas_AT_ST: public _triangulos3D
{
public:
      _torretas_AT_ST();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float radio_der;
int num1_der;
int num2_der;

float radio_izq;
int num1_izq;
int num2_izq;

float radio_eje;
float altura;
int num_eje;

float radio_sop;
float altura_sop;
int num_sop;

float radio_can;
float altura_can;
int num_can;

float radio_can_es;
float altura_can_es;
int num_can_es;

float ancho;
float alto;
float fondo;


protected:
_esfera::_rotacion esf_der;
_esfera::_rotacion esf_izq;
_cilindro::_rotacion eje;
_cilindro::_rotacion soporte_torreta;
_cilindro::_rotacion canion;
_cubo soporte_canion;
_cilindro::_rotacion canion_especial;
};

class _torreta_principal_AT_ST: public _triangulos3D
{
public:
      _torreta_principal_AT_ST();
void  draw(_modo modo, float r, float g, float b, float grosor);
       

float radio_can;
float altura_can;
int num_can;


float ancho_principal;
float alto_principal;
float fondo_principal;

protected:
_cilindro::_rotacion canion;
_cubo soporte_principal;
};


//************************************************************************
// Base
//************************************************************************

class _base_AT_ST: public _triangulos3D
{
public:
      _base_AT_ST();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

protected:
_cubo base;
};


//************************************************************************
// Base
//************************************************************************

class _patas_AT_ST: public _triangulos3D
{
public:
      _patas_AT_ST();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho_sup;
float alto_sup;
float fondo_sup;

float ancho_cen;
float alto_cen;
float fondo_cen;

float radio;
float altura;
int num;

float ancho_inf;
float alto_inf;
float fondo_inf;

float ancho1;
float alto1;
float fondo1;

float ancho2;
float alto2;
float fondo2;

protected:
_cubo soporte_superior;
_cubo soporte_central;
_cilindro::_rotacion soporte;
_cubo soporte_inferior;
_cubo pie1;
_mcubo pie2;
};


//************************************************************************
// AT ST (montaje del objeto final)
//************************************************************************
class _at_st: public _triangulos3D {
public:
       _at_st();
       void draw(_modo modo, float r, float g, float b, float grosor);
       void  seleccion();

       float giro_cabina;
       float giro_cabina_vertical;
       float giro_torretas;
       float giro_torreta_principal;

       float giro_cabina_max;
       float giro_cabina_min;
       float giro_cabina_vertical_max;
       float giro_cabina_vertical_min;
       float giro_torreta_max;
       float giro_torreta_min;

       // atributos para la selección

       _vertex3f color_pick;
       vector<_vertex3i> color_select;
       vector<int> activo;
       int piezas;
       int grosor_select;  

protected:
       _base_AT_ST base;
       _cabina_AT_ST cabina;
       _torretas_AT_ST torretas;
       _torreta_principal_AT_ST torreta_pricipal;
       _patas_AT_ST patas;
};