//Código criado e adaptado por António Sequeira e Joel Fernandes (2013152923 e 2014205262), 
//com base no código dado pelo Professor Jorge Henriques TP3_Cameras.cpp


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "RgbImage.h"


//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define TRANSPARENTBLUE     0.0, 0.0, 1.0, 0.5
#define RED		 1.0, 0.0, 0.0, 1.0
#define TRANSPARENTRED    1.0, 0.0, 0.0, 0.5
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define DARKGREEN 0.0, 0.5, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define WHITE2    0.5, 0.5, 0.5, 1.0
#define WHITE3    0.35, 0.35, 0.35, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159




//=========================================================== FACES DA MESA
GLboolean   frenteVisivel=0;
static GLuint     cima[] = {8,11, 10,  9};
static GLuint     esquerda[] = {0,1, 2, 3};
static GLuint     direita[] = {4,7, 6,  5};

float posicaoXPecas1[12] = {0};
float posicaoYPecas1[12] = {0};
float posicaoXPecas2[12] = {0};
float posicaoYPecas2[12] = {0};

float selecaoX;
float selecaoY;

int apresentaHipotesesSelecao = 0;

int contadorSelecao = 0;

int player = 1;

int perspectiva = 0;

static float ladoTabuleiro = 0.5f;

static float radius = ladoTabuleiro/4;

GLboolean transparency = false;



//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen=1440, hScreen=900;		//.. janela (pixeis)
GLfloat		xC=15.0, yC=15.0, zC=30.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Observador 
GLfloat  rVisao=5, aVisao=0.5*PI, incVisao=0.05;
GLfloat  obsP[] ={-ladoTabuleiro*3, 15.0, ladoTabuleiro*4};
GLfloat  angZoom=90;
GLfloat  incZoom=3;

GLint 	 lateral = 0;
GLint 	 rotacao = 0;
GLfloat  escala = 4.5;


GLint 	 corTabuleiro = 0;




//------------Vari�veis Globais----------------//
GLuint  texture[7];
RgbImage imag;
GLint incY = 1;

//------------Vari�vies luz-------------------//


//--foco

bool focoOn = false;

GLfloat difuse[] = {1.0f,1.0f,1.0f,1.0f}; //Cor da luz do foco
GLfloat specular[] = {1.0,1.0,1.0,1.0};
GLfloat anguloFoco = 30.0f;
GLfloat IncreAngulo = 5.0f;
GLfloat angMin = 5.0f;
GLfloat angMax = 60.0f;
GLfloat positionFoco[] = {xC/2, xC-2, -5.0f, 1.0f };
GLfloat antiPositionFoco[] = {xC/2, -(xC-2), -5.0f, 1.0f };
GLfloat direcaoFoco[] = {-1.0f,-1.0f,1.0f};
GLfloat foco_ak = 1.0;
GLfloat foco_al = 0.05f;
GLfloat foco_aq = 0.0f;
GLfloat focoExp = 0.1;

GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0};
GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};

//-----glogal

bool globalOn = true;

GLfloat r = 0.0f,g=0.0f,b= 0.0f,t=1.0f;
GLfloat LightBritness = 0.0f;
GLfloat incBrit = 0.05f;
GLfloat ambiente[] = {r,g,b,t};



//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam=2.0;
static GLfloat vertices[]={
	//�������������������������������������� x=tam (Esquerda)
        -tam,  -tam,  tam,	// 0 
        -tam,   tam,  tam,	// 1 
        -tam,   tam, -tam,	// 2 
        -tam,  -tam, -tam,	// 3 
	//�������������������� Direita
         tam,  -tam,  tam,	// 4 
         tam,   tam,  tam,	// 5 
         tam,   tam, -tam,	// 6 
         tam,  -tam, -tam,	// 7 
	//��������������������� (Cima
        -tam,  tam,  tam,	// 8 
        -tam,  tam, -tam,	// 9 
         tam,  tam, -tam,	// 10 
         tam,  tam,  tam,	// 11 
}; 

static GLfloat normais[] = {
    //�������������������������������������� x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
      -1.0,  0.0,  0.0,
      -1.0,  0.0,  0.0,
      -1.0,  0.0,  0.0,
	//�������������������������������������� x=tam (Direita)
	   1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
	//�������������������������������������� y=tam (Cima)
	   0.0,  1.0,  0.0,
       0.0,  1.0,  0.0,
       0.0,  1.0,  0.0,
       0.0,  1.0,  0.0,
};
//------------------------------------------------------------ Cores
static GLfloat cor[]={
	//�������������������������������������� x=tam (Esquerda) - Red
	  1.0,  0.0, 0.0,	// 0 
      1.0,  0.0, 0.0,	// 1 
      1.0,  1.0, 0.0,	// 2 
      1.0,  1.0, 0.0,	// 3 
	//�������������������������������������� x=2*tam (Direita) - Green
	  0.0,  1.0, 1.0,	// 4 
      0.0,  1.0, 1.0,	// 5 
      0.0,  1.0, 0.0,	// 6 
      0.0,  1.0, 0.0,	// 7 
	//�������������������������������������� y=tam (Cima) - Blue
	  0.0,  0.0, 1.0,	// 8 
      0.0,  0.0, 1.0,	// 9 
      1.0,  0.0, 1.0,	// 10 
      1.0,  0.0, 1.0,	// 11 
}; 

static void drawBox(GLfloat size, GLenum type, GLint textura , GLint versao)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    if(versao == 1 && i == 1){
    	glEnable(GL_TEXTURE_2D);
    	if(textura == 1)
      	glBindTexture(GL_TEXTURE_2D,texture[0]);
      else
      	glBindTexture(GL_TEXTURE_2D,texture[1]);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glPushMatrix();
  	    glBegin(type);
  		    glNormal3fv(&n[i][0]);
  		    glTexCoord2f(0.0f,0.0f);glVertex3fv(&v[faces[i][0]][0]);
  		    glTexCoord2f(1.0f,0.0f);glVertex3fv(&v[faces[i][1]][0]);
  		    glTexCoord2f(1.0f,1.0f);glVertex3fv(&v[faces[i][2]][0]);
  		    glTexCoord2f(0.0f,1.0f);glVertex3fv(&v[faces[i][3]][0]);
  	    glEnd();
  	  glPopMatrix();
      glDisable(GL_TEXTURE_2D);
    }
    else if(versao == 0 && i != 1){
      glEnable(GL_TEXTURE_2D);
      if(textura == 1)
        glBindTexture(GL_TEXTURE_2D,texture[0]);
      else
        glBindTexture(GL_TEXTURE_2D,texture[1]);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glPushMatrix();
        glBegin(type);
          glNormal3fv(&n[i][0]);
          glTexCoord2f(0.0f,0.0f);glVertex3fv(&v[faces[i][0]][0]);
          glTexCoord2f(1.0f,0.0f);glVertex3fv(&v[faces[i][1]][0]);
          glTexCoord2f(1.0f,1.0f);glVertex3fv(&v[faces[i][2]][0]);
          glTexCoord2f(0.0f,1.0f);glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
    }
  }
}

void criaDefineTexturas()
{
    //----------------------------------------- Parede z=0

    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("marble.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());

    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("marble2.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());\

    glGenTextures(1, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("cocacola.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());

    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("ground.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());

    glGenTextures(1, &texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("wall.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());

    glGenTextures(1, &texture[5]);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("ceiling.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());

    glGenTextures(1, &texture[6]);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    imag.LoadBmpFile("nurburgring_nordschleife.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());
}




//================================================================================
//=========================================================================== INIT



void defineLights()
{
    //Ambiente
    GLfloat ambiente[] = {r,g,b,t};
    GLfloat qaAmbientLight[] = {1.0,1.0,1.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambiente);

    //Foco
    glLightfv(GL_LIGHT0,GL_POSITION, positionFoco);
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, difuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);


    glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION, foco_ak);
    glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION, foco_al);
    glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION, foco_aq);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, anguloFoco);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, direcaoFoco);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, focoExp);

}

void inicializa(void)
{
	criaDefineTexturas( );
	glClearColor(BLACK);		//������������������������������Apagar
	glEnable(GL_DEPTH_TEST);	//������������������������������Profundidade
	glShadeModel(GL_SMOOTH);	//������������������������������Interpolacao de cores	

	glEnable(GL_CULL_FACE);		//������������������������������Faces visiveis
	glCullFace(GL_BACK);		//������������������������������Mostrar so as da frente
		
	glVertexPointer(3, GL_FLOAT, 0, vertices); //���������������Vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
    glEnableClientState(GL_COLOR_ARRAY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	defineLights();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
	//Inicia Pe�as Player 1
    int linha=0;
	float l = 0.5f;
	int posicaoNoArray = 0;
	for(int k = 0; k < 3; k++){		
		while(1){
			posicaoXPecas1[posicaoNoArray] = 1.0f*ladoTabuleiro*k;
			posicaoYPecas1[posicaoNoArray] = 2.0f*ladoTabuleiro*l;
			l+=1.0f;
			posicaoNoArray++;
			printf("LINHAxx: %f\n",l);
			if(linha == 0 && l == 4.5f){
				linha = 1;
				l = 1.0f;
				break;
			}
			else if(linha == 1 && l == 5.0f){
				linha = 0;
				l = 0.5f;
				break;
			}
		}
	}

	//Inicia Pe�as Player 2
	linha=1;
	l = 1.0f;
	posicaoNoArray = 0;
	for(int k = 7; k > 4; k--){		
		while(1){
			posicaoXPecas2[posicaoNoArray] = 1.0f*ladoTabuleiro*k;
			posicaoYPecas2[posicaoNoArray] = 2.0f*ladoTabuleiro*l;
			l+=1.0f;
			posicaoNoArray++;
			printf("LINHAyy: %f\n",l);
			if(linha == 0 && l == 4.5f){
				linha = 1;
				l = 1.0f;
				break;
			}
			else if(linha == 1 && l == 5.0f){
				linha = 0;
				l = 0.5f;
				break;
			}
		}
	}


	selecaoX = posicaoXPecas1[contadorSelecao];
	selecaoY = posicaoYPecas1[contadorSelecao];
}



void drawEixos()
{	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i(10, 0, 0); 
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
		glVertex3i(0,  0, 0); 
		glVertex3i(0, 10, 0); 
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i( 0, 0,10); 
	glEnd();

}	

void drawPecas(GLint versao){
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	int linha=0;
	float l = 0.5f;
	//Pe�as Azuis
	for(int k = 0; k < 12; k++){
    if(versao == 1){

  		//Draw Circle Top
  		glPushMatrix();
  			glTranslated(posicaoXPecas1[k]+ladoTabuleiro/2,ladoTabuleiro+ladoTabuleiro/8,posicaoYPecas1[k]-ladoTabuleiro/2);
  	 		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  			glColor4f(BLUE); 
  			//Draw Circle
  			glBegin(GL_POLYGON);
  				for(double i = 0; i < 2 * PI; i += PI / 12)
  	 				glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
  			glEnd();
   
  		glPopMatrix();
  		//Draw Cilinder
  		glPushMatrix();	
  			glColor4f(BLUE);
  			glTranslated(posicaoXPecas1[k]+ladoTabuleiro/2,ladoTabuleiro*1.125,posicaoYPecas1[k]-ladoTabuleiro/2);
  			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  			gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/6,ladoTabuleiro/8,32,32);
  		glPopMatrix();


  		glPushMatrix();	
  			glColor4f(BLUE);
  			glTranslated(posicaoXPecas1[k]+ladoTabuleiro/2,ladoTabuleiro/8,posicaoYPecas1[k]-ladoTabuleiro/2);
  			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  			gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/4,ladoTabuleiro,32,32);
  		glPopMatrix();
    }
    else if(versao == 0){
      //Draw Circle Top
      glPushMatrix();
        glTranslated(posicaoXPecas1[k]+ladoTabuleiro/2,ladoTabuleiro+ladoTabuleiro/8,posicaoYPecas1[k]-ladoTabuleiro/2);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor4f(TRANSPARENTBLUE); 
        //Draw Circle
        glBegin(GL_POLYGON);
          for(double i = 0; i < 2 * PI; i += PI / 12)
            glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
        glEnd();
   
      glPopMatrix();
      //Draw Cilinder
      glPushMatrix(); 
        glColor4f(TRANSPARENTBLUE);
        glTranslated(posicaoXPecas1[k]+ladoTabuleiro/2,ladoTabuleiro*1.125,posicaoYPecas1[k]-ladoTabuleiro/2);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/6,ladoTabuleiro/8,32,32);
      glPopMatrix();


      glPushMatrix(); 
        glColor4f(TRANSPARENTBLUE);
        glTranslated(posicaoXPecas1[k]+ladoTabuleiro/2,ladoTabuleiro/8,posicaoYPecas1[k]-ladoTabuleiro/2);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/4,ladoTabuleiro,32,32);
      glPopMatrix();
    }
	}
	//Pe�as Vermelhas
	for(int k = 0; k < 12; k++){
		//Draw Circle Top
    if(versao == 1){
  		glPushMatrix();
  			glTranslated(posicaoXPecas2[k]+ladoTabuleiro/2,ladoTabuleiro+ladoTabuleiro/8,posicaoYPecas2[k]-ladoTabuleiro/2);
  	 		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  			glColor4f(RED); 
  			//Draw Circle
  			glBegin(GL_POLYGON);
  				for(double i = 0; i < 2 * PI; i += PI / 12)
  	 				glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
  			glEnd();
   
  		glPopMatrix();
  		//Draw Cilinder
  		glPushMatrix();	
  			glColor4f(RED);
  			glTranslated(posicaoXPecas2[k]+ladoTabuleiro/2,ladoTabuleiro*1.125,posicaoYPecas2[k]-ladoTabuleiro/2);
  			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  			gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/6,ladoTabuleiro/8,32,32);
  		glPopMatrix();

  		glPushMatrix();	
  			glColor4f(RED);
  			glTranslated(posicaoXPecas2[k]+ladoTabuleiro/2,ladoTabuleiro/8,posicaoYPecas2[k]-ladoTabuleiro/2);
  			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  			gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/4,ladoTabuleiro,32,32);
  		glPopMatrix();
    }
    else if(versao == 0){
      glPushMatrix();
        glTranslated(posicaoXPecas2[k]+ladoTabuleiro/2,ladoTabuleiro+ladoTabuleiro/8,posicaoYPecas2[k]-ladoTabuleiro/2);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor4f(TRANSPARENTRED); 
        //Draw Circle
        glBegin(GL_POLYGON);
          for(double i = 0; i < 2 * PI; i += PI / 12)
            glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
        glEnd();
   
      glPopMatrix();
      //Draw Cilinder
      glPushMatrix(); 
        glColor4f(TRANSPARENTRED);
        glTranslated(posicaoXPecas2[k]+ladoTabuleiro/2,ladoTabuleiro*1.125,posicaoYPecas2[k]-ladoTabuleiro/2);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/6,ladoTabuleiro/8,32,32);
      glPopMatrix();

      glPushMatrix(); 
        glColor4f(TRANSPARENTRED);
        glTranslated(posicaoXPecas2[k]+ladoTabuleiro/2,ladoTabuleiro/8,posicaoYPecas2[k]-ladoTabuleiro/2);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadratic,ladoTabuleiro/4,ladoTabuleiro/4,ladoTabuleiro,32,32);
      glPopMatrix();
    }
	}

}

void drawSelecao(){
	glColor4f(YELLOW);
	glPushMatrix();
		glTranslated(selecaoX+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY-ladoTabuleiro/2);
	    glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
		glutWireCube(1);		
	glPopMatrix();

	if(apresentaHipotesesSelecao != 0 && player == 1){
		if(selecaoY == ladoTabuleiro*8.0f){
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX+ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY-ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();
		}
		else if(selecaoY == ladoTabuleiro*1.0f){
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX+ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY+ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();			
		}
		else{
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX+ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY-ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();			
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX+ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY+ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();		
		}
	}
	else if(apresentaHipotesesSelecao != 0 && player == 2){
		if(selecaoY == ladoTabuleiro*8.0f){
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX-ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY-ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();
		}
		else if(selecaoY == ladoTabuleiro*1.0f){
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX-ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY+ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();	
		}
		else{
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX-ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY-ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();			
			glColor4f(RED);
			glPushMatrix();
				glTranslated(selecaoX-ladoTabuleiro+ladoTabuleiro/2,ladoTabuleiro/4,selecaoY+ladoTabuleiro-ladoTabuleiro/2);
				glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
				glutWireCube(1);		
			glPopMatrix();	
		}
	}
}

void drawPaint()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[6]);
    glColor3f(1.0f,1.0f,1.0f);
    glRotatef(180,0,0,1);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(6.5,5.62,-14.99);
        glTexCoord2f(1.0f,0.0f);glVertex3f(-6.5,5.62,-14.99);
        glTexCoord2f(1.0f,1.0f);glVertex3f(-6.5,-5.62,-14.99);
        glTexCoord2f(0.0f,1.0f);glVertex3f(6.5,-5.62,-14.99);
    glEnd();
    glPopMatrix();


}

void drawSala(){

	//--------------CH�O----------------//
	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[3]);
    glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
        glBegin(GL_QUADS);
        	glTexCoord2f(0.0f,0.0f); glVertex3i( -xC,  -xC,  xC);
            glTexCoord2f(5.0f,0.0f); glVertex3i( xC, -xC, xC);
            glTexCoord2f(5.0f,5.0f); glVertex3i( xC, -xC, -xC );
            glTexCoord2f(0.0f,5.0f); glVertex3i( -xC, -xC, -xC );
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //-------------TECTO----------------//
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f); glVertex3i( -xC, xC, -xC );
            glTexCoord2f(10.0f,0.0f); glVertex3i( xC, xC, -xC);
            glTexCoord2f(10.0f,10.0f); glVertex3i( xC, xC, xC);
            glTexCoord2f(0.0f,10.0f); glVertex3i( -xC,  xC,  xC);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //-------------PAREDE ATR�S DO JOGADOR 1----------------//   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[4]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
        glRotated(90,1,0,0);
        glBegin(GL_QUADS);
            glNormal3b(1,0,0);
            glTexCoord2f(0.0f,0.0f); glVertex3i( -yC,  -yC, -yC );
            glTexCoord2f(1.0f,0.0f); glVertex3i( -yC, yC, -yC);
            glTexCoord2f(1.0f,1.0f); glVertex3i( -yC, yC, yC);
            glTexCoord2f(0.0f,1.0f); glVertex3i( -yC,  -yC,  yC);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //-------------PAREDE � FRENTE DO JOGADOR 1----------------//   
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[4]);
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
        glRotated(90,1,0,0);
        glBegin(GL_QUADS);
        	glTexCoord2f(0.0f,0.0f); glVertex3i( yC,  -yC,  yC);
            glTexCoord2f(1.0f,0.0f); glVertex3i( yC, yC, yC);
            glTexCoord2f(1.0f,1.0f); glVertex3i( yC, yC, -yC);
            glTexCoord2f(0.0f,1.0f); glVertex3i( yC,  -yC, -yC );
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //-------------PAREDE � ESQUERDA DO JOGADOR 1----------------//   
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[4]);
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
        glBegin(GL_QUADS);
        	glTexCoord2f(0.0f,0.0f); glVertex3i( yC,  yC, -yC );
        	glTexCoord2f(1.0f,0.0f); glVertex3i( -yC, yC, -yC);
            glTexCoord2f(1.0f,1.0f); glVertex3i( -yC, -yC, -yC);
            glTexCoord2f(0.0f,1.0f); glVertex3i( yC,  -yC, -yC);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //-------------PAREDE � DIREITA DO JOGADOR 1----------------//   
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[4]);
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
        glBegin(GL_QUADS);
        	glTexCoord2f(0.0f,0.0f); glVertex3i( yC,  -yC, yC);
            glTexCoord2f(1.0f,0.0f); glVertex3i( -yC, -yC, yC);
            glTexCoord2f(1.0f,1.0f); glVertex3i( -yC, yC, yC);
            glTexCoord2f(0.0f,1.0f); glVertex3i( yC,  yC, yC );
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void drawScene(GLint versao){
	//==================================== Tabuleiro
	int altura = 0;
	int j = 0;
	double x,y;
	for(int i = 0; i < 64; i++){
		j++;
		if(i % 8 == 0){
			j = 0;
			altura++;
			if(corTabuleiro == 0)
				corTabuleiro = 1;
			else
				corTabuleiro = 0;
		}
		x = j*ladoTabuleiro;
		y = altura*ladoTabuleiro;
		if(corTabuleiro == 0){
			corTabuleiro = 1;
		}
		else if(corTabuleiro == 1){ 
			corTabuleiro = 0;
		}
		glPushMatrix();
			//glColor4f(WHITE);
      //glColor4f(1.0f,1.0f,1.0f,0.5f);
			glTranslated(x+ladoTabuleiro/2,0,y-ladoTabuleiro/2);
		  glScaled(ladoTabuleiro,ladoTabuleiro/4,ladoTabuleiro);
			//glutSolidCube(1);
			drawBox(1,GL_QUADS,corTabuleiro,versao);
		glPopMatrix();
	}
}




void display(void){
  	
	//================================================================= APaga ecran/profundidade
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


   //////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // - > REFLEXÂO STENCIL!
   //////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////

	
	//================================================================= N�o modificar
	glViewport (0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen/hScreen, 0.1, 3*zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], ladoTabuleiro*4.0f,0,ladoTabuleiro*4.0f, 0, 1, 0);
	//================================================================= N�o modificar

	//----------------------------------------------------------luzes
	
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);


    defineLights();

    //Desenha foco

    if (!focoOn) {
        glPushMatrix();
            glColor4f(AMARELO);
            glTranslatef(xC/2,xC-2,-5);
            glutSolidSphere(1.0f, 100,100);
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);

  


  glPushMatrix();

    /*Don't update color or depth.*/
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    /* Draw 1 into the stencil buffer. */
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

    drawScene(1);

    /* Re-enable update of color and depth. */ 
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    /* Now, only render where stencil is set to 1. */
    glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if stencil ==1 */
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glPushMatrix();
      glTranslatef(0,ladoTabuleiro/4,0);
      glScalef(1.0, -1.0, 1.0);
      glLightfv(GL_LIGHT0,GL_POSITION, antiPositionFoco);
      glEnable(GL_NORMALIZE);
      glCullFace(GL_FRONT);
      drawPecas(1);
      glDisable(GL_NORMALIZE);
      glCullFace(GL_BACK);
    glPopMatrix();

    glLightfv(GL_LIGHT0,GL_POSITION, positionFoco);

    glDisable(GL_STENCIL_TEST);

    glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1.0f,1.0f,1.0f,0.5f);
      drawScene(1);
    glDisable(GL_BLEND);
    
    /*glFrontFace(GL_CW);  // Switch face orientation.
      glColor4f(0.1, 0.1, 0.7, 1.0);
      drawScene();
    glFrontFace(GL_CCW);*/
    drawScene(0);
  glPopMatrix();
  if(transparency == false)
    drawPecas(1);


  drawEixos();
  drawSelecao();
  drawSala();
  drawPaint();

  glPushMatrix();
    if( transparency == true){
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      drawPecas(0); 
      glDisable(GL_BLEND);
    }
  glPopMatrix();
	
  glutPostRedisplay();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
	
	
}

int testaMovimentoPlayer1(int lado){
	int resultado = 1;
	if(lado == 1){
		for(int i = 0; i < 12; i++){
			if(posicaoYPecas1[i] == posicaoYPecas1[contadorSelecao] + ladoTabuleiro && posicaoXPecas1[i] == posicaoXPecas1[contadorSelecao] + ladoTabuleiro){
				resultado = -1;
			}
		}
	}
	else if(lado == 0){
		for(int i = 0; i < 12; i++){
			if(posicaoYPecas1[i] == posicaoYPecas1[contadorSelecao] - ladoTabuleiro && posicaoXPecas1[i] == posicaoXPecas1[contadorSelecao] + ladoTabuleiro){
				resultado = -1;
			}
		}	
	}
	return resultado;
}

int testaMovimentoPlayer2(int lado){
	int resultado = 1;
	if(lado == 1){
		for(int i = 0; i < 12; i++){
			if(posicaoYPecas2[i] == posicaoYPecas2[contadorSelecao] - ladoTabuleiro && posicaoXPecas2[i] == posicaoXPecas2[contadorSelecao] - ladoTabuleiro){
				resultado = -1;
			}
		}
	}
	else if(lado == 0){
		for(int i = 0; i < 12; i++){
			if(posicaoYPecas2[i] == posicaoYPecas2[contadorSelecao] + ladoTabuleiro && posicaoXPecas2[i] == posicaoXPecas2[contadorSelecao] - ladoTabuleiro){
				resultado = -1;
			}
		}	
	}
	return resultado;
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
	
	
	switch (key) {
	case 'f':
	case 'F':
		if(frenteVisivel == 0)
			frenteVisivel = 1;
		else if(frenteVisivel == 1)
			frenteVisivel = 2;
		else
			frenteVisivel = 0;
		
		break;

	case 'A':
	case 'a':
		lateral--;
		
	break;

	case 'S':
	case 's':
		lateral++;
		
	break;

	case 'e':
	case 'E':
		rotacao+=2;
		
	break;

	case 'd':
	case 'D':
		rotacao-=2;
		
	break;
	case 'w':
	case 'W':
		if(contadorSelecao + 1 > 11)
			contadorSelecao = 11;
		else
			contadorSelecao++;
		if(player == 1){
			selecaoX = posicaoXPecas1[contadorSelecao];
			selecaoY = posicaoYPecas1[contadorSelecao];
		}
		else if(player == 2){
			selecaoX = posicaoXPecas2[contadorSelecao];
			selecaoY = posicaoYPecas2[contadorSelecao];	
		}
	
	break;
	case 'q':
	case 'Q':
		if(contadorSelecao - 1 < 0)
			contadorSelecao = 0;
		else
			contadorSelecao--;
		if(player == 1){
			selecaoX = posicaoXPecas1[contadorSelecao];
			selecaoY = posicaoYPecas1[contadorSelecao];
		}
		else if(player == 2){
			selecaoX = posicaoXPecas2[contadorSelecao];
			selecaoY = posicaoYPecas2[contadorSelecao];	
		}
		
	break;
	case 'h':
	case 'H':
		if(apresentaHipotesesSelecao == 0)
			apresentaHipotesesSelecao = 1;
		else
			apresentaHipotesesSelecao = 0;
	
	break;
	case 'i':
	case 'I':
		if(player == 1 && posicaoYPecas1[contadorSelecao] != ladoTabuleiro*8.0f){
			int valida = testaMovimentoPlayer1(1);
			if(valida != -1){
				posicaoYPecas1[contadorSelecao] += ladoTabuleiro;
				posicaoXPecas1[contadorSelecao] += ladoTabuleiro;

				selecaoY = posicaoYPecas2[0];
				selecaoX = posicaoXPecas2[0];
				player = 2;
				contadorSelecao = 0;

				if(perspectiva == 0){
					obsP[0] = ladoTabuleiro*10;
					obsP[2] = ladoTabuleiro*4;
				}
			}
		}
		else if(player == 2 && posicaoYPecas2[contadorSelecao] != ladoTabuleiro*1.0f){
			int valida = testaMovimentoPlayer2(1);
			if(valida != -1){
				posicaoYPecas2[contadorSelecao] -= ladoTabuleiro;
				posicaoXPecas2[contadorSelecao] -= ladoTabuleiro;

				selecaoY = posicaoYPecas1[0];
				selecaoX = posicaoXPecas1[0];
				player = 1;
				contadorSelecao = 0;

				if(perspectiva == 0){
					obsP[0] = -ladoTabuleiro*3;
					obsP[2] = ladoTabuleiro*4;
				}
			}
		}

	break;
	case 'u':
	case 'U':
		if(player == 1 && posicaoYPecas1[contadorSelecao] != ladoTabuleiro*1.0f){
			int valida = testaMovimentoPlayer1(0);
			if(valida != -1){
				posicaoYPecas1[contadorSelecao] -= ladoTabuleiro;
				posicaoXPecas1[contadorSelecao] += ladoTabuleiro;

				selecaoY = posicaoYPecas2[0];
				selecaoX = posicaoXPecas2[0];
				player = 2;
				contadorSelecao = 0;
				
				if(perspectiva == 0){
					obsP[0] = ladoTabuleiro*10;
					obsP[2] = ladoTabuleiro*4;
				}
			}
		}
		else if(player == 2 && posicaoYPecas2[contadorSelecao] != ladoTabuleiro*8.0f){
			int valida = testaMovimentoPlayer2(0);
			if(valida != -1){
				posicaoYPecas2[contadorSelecao] += ladoTabuleiro;
				posicaoXPecas2[contadorSelecao] -= ladoTabuleiro;

				selecaoY = posicaoYPecas1[0];
				selecaoX = posicaoXPecas1[0];
				player = 1;
				contadorSelecao = 0;

				if(perspectiva == 0){
					obsP[0] = -ladoTabuleiro*3;
					obsP[2] = ladoTabuleiro*4;
				}
			}
		}

	break;
	case 'p':
	case 'P':
		if(player == 1){
			selecaoY = posicaoYPecas2[0];
			selecaoX = posicaoXPecas2[0];
			player = 2;
			if(perspectiva == 0){
				obsP[0] = ladoTabuleiro*10;
				obsP[2] = ladoTabuleiro*4;
			}
		}
		else{
			selecaoY = posicaoYPecas1[0];
			selecaoX = posicaoXPecas1[0];
			player = 1;
			if(perspectiva == 0){
				obsP[0] = -ladoTabuleiro*3;
				obsP[2] = ladoTabuleiro*4;
			}
		}
		
	break;
	case 'o':
	case 'O':
		if(perspectiva == 0){
			perspectiva = 1;
		}
		else if(perspectiva == 1){
			obsP[0] = ladoTabuleiro * 3.5f;
			obsP[1] = 30.0;
			obsP[2] = ladoTabuleiro * 3.5f;
			perspectiva = 2;
		}
		else if(perspectiva == 2){
			if(player == 1){
				obsP[0] = -ladoTabuleiro*3;
				obsP[2] = ladoTabuleiro*4;
			}
			else if(player == 2){
				obsP[0] = ladoTabuleiro*10;
				obsP[2] = ladoTabuleiro*4;
			}
			obsP[1] = 15.0;
			perspectiva = 0;
		}
	
	break;
	case 'l':
    case 'L':
        if(r == 0.0f){
            printf("teste\n");
            r = LightBritness;
            b = LightBritness;
            g = LightBritness;
        }
        else if(r == LightBritness){
            r = 0.0f;
            g = 0.0f;
            b = 0.0f;
        }
        break;
    case '+':
        printf("+britness:%f\n",LightBritness);
        if(LightBritness<1){

            LightBritness+=incBrit;
            r = LightBritness;
            b = LightBritness;
            g = LightBritness;

        }
        break;
    case '-':
        printf("-britness:%f\n",LightBritness);
        if(LightBritness>0.00){
            LightBritness-=incBrit;
            r = LightBritness;
            b = LightBritness;
            g = LightBritness;
            }
        break;

    case 'k':
    case 'K':
        focoOn=!focoOn;
        if (focoOn == false)
            glEnable(GL_LIGHT0);
        else
            glDisable(GL_LIGHT0);
        break;

    case 'm':
        anguloFoco+=IncreAngulo;
        break;
    case 'n':
        anguloFoco-=IncreAngulo;
        break;
    case 'b':
    case 'B':
        if(transparency == false)
          transparency = true;
        else if(transparency == true)
          transparency = false;
        break;
	
//--------------------------- Escape
	case 27:
		exit(0);
		break;	
  }

}

void teclasNotAscii(int key, int x, int y){

		
		if(key == GLUT_KEY_LEFT) 
			aVisao = (aVisao + 0.1) ;
		if(key == GLUT_KEY_RIGHT) 
			aVisao = (aVisao - 0.1) ;
	
	 	if(key == GLUT_KEY_UP && obsP[1]<12)
        	obsP[1]=obsP[1]+incY;
   	 	if(key == GLUT_KEY_DOWN && obsP[1]>-12)
        	obsP[1]=obsP[1]-incY;
   

		obsP[0]=(rVisao)*cos(aVisao)+ladoTabuleiro*(7/2);
		obsP[2]=(rVisao)*sin(aVisao)+ladoTabuleiro*(7/2);

	

}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize (wScreen, hScreen); 
	glutInitWindowPosition (300, 100); 
	glutCreateWindow ("{jh,pjmm}@dei.uc.pt|       |FaceVisivel:'f'|      |Observador:'SETAS'|        |Andar-'a/s'|        |Rodar -'e/d'| ");
  
	inicializa();
	
	glutSpecialFunc(teclasNotAscii); 
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();

	return 0;
}




