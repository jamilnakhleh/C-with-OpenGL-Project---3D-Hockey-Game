//fares salameh 206163784	
//jamil nakhleh 307977090

#include<stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <time.h>
int l;
bool firstin = true; // var la tawze3 el cubes in another points on the table ... mesh kol mara in REAL TIME y3'ayer  ma7alat .. bas awal ma nsha3'el..
bool checker2[4] = { false }; // array for collision between Cubes And 7ofra ...
int score = 0;
int rot = 0, rotl = 0, rotr = 0;
float mx = 0.0;
float govah = -5;
float px = -3.5, py = 1.0, pz = 0.0;
float speed = 0.001, speedmakel = 0.2;
char str[100] = "SCORE: ";
int len, ll;
int flagscore[4] = { 0 };
bool flag2[3] = { false }; // flag2 lal adweye .. kolhon OFF 
// varZ la tawze3 el cubes in another points on the table ...
float a1x, a1y = 0, a1z, a2x, a2y = 0, a2z, a3x, a3y = 0, a3z, a4x, a4y = 0, a4z;

// setting X,Y,Z el sides for cubes ...
void cub()
{
	glBegin(GL_QUADS);
	// Front
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, 1, 0.5);
	glVertex3f(0.5, 1, 0.5);
	glVertex3f(0.5, 0, 0.5);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, 1, -0.5);
	glVertex3f(-0.5, 1, -0.5);

	// Left side
	glNormal3f(-0.5, 0, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, 1, 0.5);
	glVertex3f(-0.5, 1, -0.5);
	glVertex3f(-0.5, 0, -0.5);

	// Right side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, 1, -0.5);
	glVertex3f(0.5, 1, 0.5);

	glNormal3f(0, 1, 0);
	glVertex3f(0.5, 1, 0.5);
	glVertex3f(0.5, 1, -0.5);
	glVertex3f(-0.5, 1, -0.5);
	glVertex3f(-0.5, 1, 0.5);
	glEnd();

}

// setting X,Y,Z the 7ofar ( THE MALKODET )
void cub2()
{
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1, 0.1, 1);
	glVertex3f(1, 0.1, -1);
	glVertex3f(-1, 0.1, -1);
	glVertex3f(-1, 0.1, 1);

	glEnd();

}

// struct for the player - THE MAKEL ...
typedef struct{
	float x;
	float y;
	float z;
}makel;
makel makels[1];

// points for the MAKEL on the table ...
void init_makel()
{
	makels[0].x = 0.0;
	makels[0].y = 0.0;
	makels[0].z = 6.5;

}

// struct for the lights cube ...
struct kad{
	int status;
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
};
kad arr[6]; // the lights ...

// setting the x,y,z,status for lights cubes ...
void init_kad()
{
	arr[0].x = -14.0;
	arr[0].y = 15.0;
	arr[0].z = -4.0;
	arr[0].status = 0;
	/////////////////////
	arr[1].x = -14.0;
	arr[1].y = 15.0;
	arr[1].z = 0.0;
	arr[1].status = 0;
	//////////////////////
	arr[2].x = 14.0;
	arr[2].y = 15.0;
	arr[2].z = -4.0;
	arr[2].status = 0;
	//////////////////////
	arr[3].x = 14.0;
	arr[3].y = 15.0;
	arr[3].z = 0.0;
	arr[3].status = 0;
	//////////////////////
	arr[4].x = 0;
	arr[4].y = 15.0;
	arr[4].z = -10.0;
	arr[4].status = 0;
	//////////////////////

}

//KEYBOARDS ...
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'r') // up
	{
		if (rot <= 40)
		{
			rot += 5;
			rot %= 360;
		}
		glutPostRedisplay();
	}
	if (key == 'd') // down
	{
		if (rotl <= 40)
		{
			rotl -= 5;
			rotl %= 360;
		}
		glutPostRedisplay();
	}
	if (key == 'f') // right 
	{
		if (rotr <= 40)
		{
			rotr += 5;
			rotr %= 360;
		}
		glutPostRedisplay();
	}
	if (key == 'e')
	{
		if (rot >= 5)
		{
			rot -= 5;
			rot %= 360;
		}
		glutPostRedisplay();
	}
	if (key == 'n') // left for MAKEL 
	{
		if (makels[0].x > -6.8)
			makels[0].x -= speedmakel;
		glutPostRedisplay();

	}
	if (key == 'm') // right for MAKEL
	{
		if (makels[0].x < 6.5)
			makels[0].x += speedmakel;
		glutPostRedisplay();
	}
	if (key == '1') // light ON for the left wall
	{
		if (flag2[0] == false)
		{
			px += 100000000;
			arr[0].status = 1;
			arr[1].status = 1;
			flag2[0] = true;
		}
	}
	if (key == '2') // light OFF for the left wall
	{
		if (flag2[0] == true)
		{
			px -= 100000000;
			arr[0].status = 0;
			arr[1].status = 0;
			flag2[0] = false;
		}
	}
	if (key == '4') // light ON for the right wall
	{
		if (flag2[1] == false)
		{
			flag2[1] = true;
			pz += 100000000;
			arr[2].status = 1;
			arr[3].status = 1;
		}
	}
	if (key == '5') // light OFF for the right wall
	{
		if (flag2[1] == true)
		{
			flag2[1] = false;
			pz -= 100000000;
			arr[2].status = 0;
			arr[3].status = 0;
		}
	}
	if (key == '7') // light ON for the center wall
	{
		if (flag2[2] == false)
		{
			flag2[2] = true;
			py += 100000000;
			arr[4].status = 1;
			arr[5].status = 1;
		}
	}
	if (key == '8') // light OFF for the center wall
	{
		if (flag2[2] == true)

		{
			py -= 100000000;
			arr[4].status = 0;
			arr[5].status = 0;
			flag2[2] = false;
		}
	}
	if (key == 'z') // more speed of cubes
	{
		speed += 0.001;
		speedmakel += 0.001;
	}
	if (key == 'x') // les speed of cubes
	{
		if (speed > 0.001)
			speed -= 0.001;
		if (speedmakel > 0.2)
			speedmakel -= 0.001;
	}


	if (key == 27) exit(1); // bye bye !

	glutPostRedisplay();
}

// ( draw ) - color function for CUBE - ye3elot.. after setting the colors we call cub() ( setting sides back,bottom etc..)
void color_cube(float red, float green, float blue)
{
	glColor3f(red, green, blue);
	cub();
}

// struct lal 7ofaar ..
typedef struct{
	float x;
	float y;
	float z;
}Cube2;
Cube2 our_cubes2[2]; // 7omat magen - el 7ofar

// setting the x,y,z,status for 7ofar cubes ...
void init_cubes2() // points lal 7ofar el tenteen...
{
	our_cubes2[0].x = 4;
	our_cubes2[0].y = 0.1;
	our_cubes2[0].z = -4;
	////////////////////////////
	our_cubes2[1].x = -4;
	our_cubes2[1].y = 0.1;
	our_cubes2[1].z = -4;
	l = rand() % 14 + (-7);
	srand(time(NULL));
	int b = l;
}

// cube struct
typedef struct{
	float x;
	float y;
	float z;
	float red;
	float green;
	float blue;
	int statusx;
	int statusy;
	int statusz;
}Cube;

Cube our_cubes[4]; // our lovely cubes  

// tawzee3 el cubes on the table ...
void init_cubes() 
{
	if (firstin == true)
	{
		// mamno3 ykono fe al ma7alat aa mn shan hek the solution is DO WHILE !
		// el ma7alat bshakel Randomally..
		//////////////////////////////// first cube
		l = rand() % 14 + (-7);
		a1x = float(l);
		l = rand() % 10 + (-5);
		a1z = float(l);

		//////////////////////////////// second cube place
		do{
			l = rand() % 14 + (-7);
		} while (l == a1x || l == a1x + 1 || l == a1x - 1);
		a2x = float(l);

		do{
			l = rand() % 10 + (-5);
		} while (l == a1z || l == a1z + 1 || l == a1z - 1);
		a2z = float(l);

		//////////////////////////////// third cube place
		do{
			l = rand() % 14 + (-7);
		} while (l == a1x || l == a1x + 1 || l == a1x - 1 || l == a2x || l == a2x + 1 || l == a2x - 1);
		a3x = float(l);

		do{
			l = rand() % 10 + (-5);
		} while (l == a1z || l == a1z + 1 || l == a1z - 1 || l == a2z || l == a2z + 1 || l == a2z - 1);
		a3z = float(l);
		///////////////////////////////// last cube place
		do{
			l = rand() % 14 + (-7);
		} while (l == a1x || l == a1x + 1 || l == a1x - 1 || l == a2x || l == a2x + 1 || l == a2x - 1 || l == a3x || l == a3x + 1 || l == a3x - 1);
		a4x = float(l);
		do{
			l = rand() % 10 + (-5);
		} while (l == a1z || l == a1z + 1 || l == a1z - 1 || l == a2z || l == a2z + 1 || l == a2z - 1 || l == a3z || l == a3z + 1 || l == a3z - 1);
		a4z = float(l);
		firstin = false;
	}
	// setting ....
	our_cubes[0].x = a1x;
	our_cubes[0].y = a1y;
	our_cubes[0].z = a1y;
	our_cubes[0].red = 0.5;
	our_cubes[0].green = 0.3;
	our_cubes[0].blue = 0.2;
	our_cubes[0].statusx = 1;
	our_cubes[0].statusy = 0;
	our_cubes[0].statusz = 0;
	////////////////////////////
	our_cubes[1].x = a2x;
	our_cubes[1].y = a2y;
	our_cubes[1].z = a2z;
	our_cubes[1].red = 0.2;
	our_cubes[1].green = 0.1;
	our_cubes[1].blue = 0.4;
	our_cubes[1].statusx = 1;
	our_cubes[1].statusy = 0;
	our_cubes[1].statusz = 0;
	//////////////////////////////
	our_cubes[2].x = a3x;
	our_cubes[2].y = a3y;
	our_cubes[2].z = a3z;
	our_cubes[2].red = 0.1;
	our_cubes[2].green = 0.1;
	our_cubes[2].blue = 0.8;
	our_cubes[2].statusx = 1;
	our_cubes[2].statusy = 0;
	our_cubes[2].statusz = 1;
	//////////////////////////////
	our_cubes[3].x = a4x;
	our_cubes[3].y = a4y;
	our_cubes[3].z = a4z;
	our_cubes[3].red = 0.4;
	our_cubes[3].green = 0.3;
	our_cubes[3].blue = 0.6;
	our_cubes[3].statusx = 1;
	our_cubes[3].statusy = 0;
	our_cubes[3].statusz = 1;
}
// regel for table .. the sides ..
void regel()
{
	glBegin(GL_QUADS);
	// Front
	glNormal3f(0, 0, 0.5);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -5, 0.5);
	glVertex3f(0.5, -5, 0.5);
	glVertex3f(0.5, 0, 0.5);

	// Back
	glNormal3f(0, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -5, -0.5);
	glVertex3f(-0.5, -5, -0.5);

	// Left side
	glNormal3f(-0.5, 0, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, -5, 0.5);
	glVertex3f(-0.5, -5, -0.5);
	glVertex3f(-0.5, 0, -0.5);

	// Right side
	glNormal3f(0.5, 0, 0);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -5, -0.5);
	glVertex3f(0.5, -5, 0.5);
	glEnd();
}

// the setting sides for the MAKEL ...
void draw4()
{
	glBegin(GL_QUADS);
	// Front
	glColor3f(0.5, 0.35, 0.05);
	glNormal3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 0.5, 1);
	glVertex3f(1, 0.5, 1);

	// Back
	glNormal3f(0, 0, 0.5);
	glVertex3f(1, 0, 0.5);
	glVertex3f(-1, 0, 0.5);
	glVertex3f(-1, 0.5, 0.5);
	glVertex3f(1, 0.5, 0.5);

	// Left side
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0.5);
	glVertex3f(1, 0.5, 0.5);
	glVertex3f(1, 0.5, 1);
	glVertex3f(1, 0, 1);


	// Left side
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0, 0.5);
	glVertex3f(-1, 0.5, 0.5);
	glVertex3f(-1, 0.5, 1);
	glVertex3f(-1, 0, 1);

	glNormal3f(0, 0.5, 0);
	glVertex3f(1, 0.5, 1);
	glVertex3f(-1, 0.5, 1);
	glVertex3f(-1, 0.5, 0.5);
	glVertex3f(1, 0.5, 0.5);


	glEnd();



}

// setting the right / left wall for the table ..
void draw2()
{
	glBegin(GL_QUADS);
	// Front
	glColor3f(0.5, 0.35, 0.05);
	glNormal3f(1, 0, 0);
	glVertex3f(8, 0, -8);
	glVertex3f(8, 1, -8);
	glVertex3f(8, 1, 8);
	glVertex3f(8, 0, 8);

	// Back
	glNormal3f(1, 0, 0);
	glVertex3f(7.5, 0, -8);
	glVertex3f(7.5, 1, -8);
	glVertex3f(7.5, 1, 8);
	glVertex3f(7.5, 0, 8);

	// Left side
	glNormal3f(0, 0, -1);
	glVertex3f(8, 0, -8);
	glVertex3f(8, 1, -8);
	glVertex3f(7.5, 1, -8);
	glVertex3f(7.5, 0, -8);


	// Left side
	glNormal3f(0, 0, 1);
	glVertex3f(8, 0, 8);
	glVertex3f(8, 1, 8);
	glVertex3f(7.5, 1, 8);
	glVertex3f(7.5, 0, 8);

	glNormal3f(0, 1, 0);
	glVertex3f(8, 1, 8);
	glVertex3f(8, 1, -8);
	glVertex3f(7.5, 1, -8);
	glVertex3f(7.5, 1, 8);



	glEnd();



}


// setting the back wall for the table ..
void draw3()
{
	glBegin(GL_QUADS);
	// Front
	glColor3f(0.5, 0.35, 0.05);
	glNormal3f(0, 0, 1);
	glVertex3f(8, 0, 8);
	glVertex3f(-8, 0, 8);
	glVertex3f(-8, 1, 8);
	glVertex3f(8, 1, 8);

	// Back
	glNormal3f(0, 0, 1);
	glVertex3f(8, 0, 7.5);
	glVertex3f(-8, 0, 7.5);
	glVertex3f(-8, 1, 7.5);
	glVertex3f(8, 1, 7.5);

	// Left side
	glNormal3f(1, 0, 0);
	glVertex3f(8, 0, 7.5);
	glVertex3f(8, 1, 7.5);
	glVertex3f(8, 1, 8);
	glVertex3f(8, 0, 8);


	// Left side
	glNormal3f(-1, 0, 0);
	glVertex3f(-8, 0, 7.5);
	glVertex3f(-8, 1, 7.5);
	glVertex3f(-8, 1, 8);
	glVertex3f(-8, 0, 8);

	glNormal3f(0, 1, 0);
	glVertex3f(8, 1, 8);
	glVertex3f(-8, 1, 8);
	glVertex3f(-8, 1, 7.5);
	glVertex3f(8, 1, 7.5);


	glEnd();



}


// we run it at the main - building (Back,Front,etc...) CUBES , MALKODET , LIGHTS , PRINTING THE SCORE ...
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	glRotatef(rot, 0, 1, 0);
	glRotatef(rotl, 1, 0, 0);
	glRotatef(rotr, 0, 0, 1);
	glLoadIdentity();
	glTranslatef(0, -3, -25);
	GLfloat ambientLight[] = { 1.0, 1.0, 1.0, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5, 0.5, 0.5, 1.0f };
	GLfloat mat_shininess[] = { 128.0 };
	//x,y,z,light ...
	// our positions ...
	GLfloat position[] = { px, py, pz, 1.0f };

	// Assign created components to GL_LIGHT0 ...
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glMaterialfv(GL_MAX_LIGHTS, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glRotatef(rot, 1, 0, 0);
	glRotatef(rotl, 1, 0, 0);
	glRotatef(rotr, 0, 0, 1);

	for (int i = 0; i < 5; i++)
	{
		if (arr[i].status == 1)
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(0.0, 0.0, 0.0);

		glTranslatef(arr[i].x, arr[i].y, arr[i].z);
		glutSolidSphere(1, 32, 32);
		glTranslatef(-arr[i].x, -arr[i].y, -arr[i].z);
		glutPostRedisplay();
	}
	// bneyat kobyot  - building cubes
	for (int i = 0; i<4; i++)
	{
		glTranslatef(our_cubes[i].x, our_cubes[i].y, our_cubes[i].z);
		color_cube(our_cubes[i].red, our_cubes[i].green, our_cubes[i].blue);
		glTranslatef(-our_cubes[i].x, -our_cubes[i].y, -our_cubes[i].z);
	}
	// bneyat kobyot

	// The Table ...
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.5);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-8, 0, -8);
	glVertex3f(8, 0, -8);
	glVertex3f(8, 0, 8);
	glVertex3f(-8, 0, 8);
	glEnd();
	//floor
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.2, 0.2);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-15, -5, -15);
	glVertex3f(15, -5, -15);
	glVertex3f(15, -5, 15);
	glVertex3f(-15, -5, 15);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);	// normal straight up
	glVertex3f(15, -5, -15);
	glVertex3f(15, -4, -15);
	glVertex3f(15, -4, 15);
	glVertex3f(15, -5, 15);
	glEnd();

	glBegin(GL_QUADS);

	glNormal3f(1, 0, 0);	// normal straight up
	glVertex3f(-15, -5, -15);
	glVertex3f(-15, -4, -15);
	glVertex3f(-15, -4, 15);
	glVertex3f(-15, -5, 15);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);	// normal straight up
	glVertex3f(-15, -5, -10);
	glVertex3f(-15, -4, -10);
	glVertex3f(15, -4, -10);
	glVertex3f(15, -5, -10);
	glEnd();

	// wra - BACK ...
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.2, 0.5);
	glNormal3f(0, 0, 1);	// normal straight up
	glVertex3f(-15, -5, -10);
	glVertex3f(-15, 20, -10);
	glVertex3f(15, 20, -10);
	glVertex3f(15, -5, -10);
	glEnd();
	// left
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.2, 0.5);
	glNormal3f(1, 0, 0);	// normal straight up
	glVertex3f(-15, -5, -15);
	glVertex3f(-15, 20, -15);
	glVertex3f(-15, 20, 15);
	glVertex3f(-15, -5, 15);
	glEnd();
	// right
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.2, 0.5);
	glNormal3f(1, 0, 0);	// normal straight up
	glVertex3f(15, -5, -15);
	glVertex3f(15, 20, -15);
	glVertex3f(15, 20, 15);
	glVertex3f(15, -5, 15);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.75, 0.75, 0.75);
	glNormal3f(0, 1, 0);	// normal straight up
	glVertex3f(-15, 20, -15);
	glVertex3f(15, 20, -15);
	glVertex3f(15, 20, 15);
	glVertex3f(-15, 20, 15);
	glEnd();
	glColor3f(0.5, 0.35, 0.05);
	glTranslatef(4.5, 0, -4.5);
	regel();
	glTranslatef(-9, 0, 0);
	regel();
	glTranslatef(0, 0, 9);
	regel();
	glTranslatef(9, 0, 0);
	regel();
	glTranslatef(0, 0, -9);
	// 7efaf
	glTranslatef(-20, 0, 4.5);
	draw2();
	glTranslatef(16, 0, 0);
	glTranslatef(0, 0, -15.5);
	draw3();
	glTranslatef(0, 0, 15.5);
	draw2();
	// 7efaf
	// nkoda 7ama
	glColor3f(0.0, 0.0, 0.0);

	for (int j = 0; j<2; j++)
	{
		// here we have the Malkodet ...
		glTranslatef(our_cubes2[j].x, our_cubes2[j].y, our_cubes2[j].z);
		cub2();
		glTranslatef(-our_cubes2[j].x, -our_cubes2[j].y, -our_cubes2[j].z);
	}
	// nkoda 7ama
	glColor3f(0.5, 0.35, 0.05);
	glTranslatef(makels[0].x, makels[0].y, makels[0].z);
	draw4();
	glTranslatef(-makels[0].x, -makels[0].y, -makels[0].z);
	
	glTranslatef(-12, 13, -8);
	// our score is updated when Lma el kobeya bto2a3 :D 
	sprintf(str, "SCORE: %d  ** 'z' to speed up **\n'x'to speed down **", score);
	char *str2 = str;
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(0, 5, 0);
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str2); while (*(++str2));
	glTranslatef(12, -13, 10);
	
	glutSwapBuffers();			// display the output
}


// Colors Functions for lights - WHEN ON / OFF status  ...
void colors() 
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (arr[i].status == 0)
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(0.0, 0.0, 0.0);

		glTranslatef(arr[i].x, arr[i].y, arr[i].z);
		glutSolidSphere(1, 32, 32);
		glTranslatef(-arr[i].x, -arr[i].y, -arr[i].z);
		glutPostRedisplay();
	}
}

// true if we have collision ma3 she 7ofra -  wel i howe one of the CUBES ...
bool black_xx(int i)
{
	int j;
	for (j = 0; j < 4; j++)
	{ // no need for J loop ...
		for (int k = 0; k < 2; k++) // if we have collision between i ( one cube ) and one of the malkodet ..
		{
			if (our_cubes[i].x >= our_cubes2[k].x - 0.6 && our_cubes[i].x <= our_cubes2[k].x + 0.6 && our_cubes[i].z >= our_cubes2[k].z - 0.6 && our_cubes[i].z <= our_cubes2[k].z + 0.6)
			{
				our_cubes[i].z = our_cubes2[k].z;
				return true;
			}
		}
	}
	return false;
}


// htnagshot ben kobeya v makel - collision between cubes and MAKEL ( player )
void move_makelkob(int i) // this i is the current makel ( its every makel cuz it changes ) 
{
	int j;
	for (j = 0; j < 4; j++)
	{
		if (our_cubes[j].statusy == 0)
			if (our_cubes[i].x > makels[0].x - 1.5 && our_cubes[i].x < makels[0].x + 1.5 && our_cubes[i].z > makels[0].z - 0.1)
			{
				if (our_cubes[i].statusz == 1)
					our_cubes[i].statusz = 0;
				else
					our_cubes[i].statusz = 1;
				break;
			}
	}
}

float temp1, temp2, temp3;
int flag = 1;
float getz[4];
float getx[4];


// htnagshottttt ben kobyot
void move_x(int i)
{
	int j;
	for (j = 0; j < 4; j++)
	{
		if (j != i)
			if (our_cubes[j].statusy == 0)
				if (our_cubes[i].x >= our_cubes[j].x - 1 && our_cubes[i].x <= our_cubes[j].x + 1 && our_cubes[i].z >= our_cubes[j].z - 1 && our_cubes[i].z <= our_cubes[j].z + 1)
				{
					if (our_cubes[i].statusx == 1)

						our_cubes[i].statusx = 0;

					else
						our_cubes[i].statusx = 1;

					if (our_cubes[i].statusz == 1)
						our_cubes[i].statusz = 0;
					else
						our_cubes[i].statusz = 1;

					if (our_cubes[j].statusx == 1)
						our_cubes[j].statusx = 0;
					else
						our_cubes[j].statusx = 1;


					if (our_cubes[j].statusz == 1)
						our_cubes[j].statusz = 0;
					else
						our_cubes[j].statusz = 1;
					break;
				}
				else
				{
				}
	}
}

// moving cubes ... kevon x - i is one of the CUBES on the table ...
void statusxx(int i)    
{

	if (our_cubes[i].statusx == 1)
	{
		if (our_cubes[i].x < 7.0)
		{
			getx[i] = our_cubes[i].x;
			our_cubes[i].x += speed;
		}
		else
			our_cubes[i].statusx = 0;
	}
	else
	{
		if (our_cubes[i].x > -7.2)
		{
			getx[i] = our_cubes[i].x;
			our_cubes[i].x -= speed;
		}
		else
			our_cubes[i].statusx = 1;
	}
}

// moving cubes ... kevon z - i is one of the CUBES on the table ... 
void statuszz(int i)
{

	if (our_cubes[i].statusz == 0)
	{
		if (our_cubes[i].z > -7.3)
		{
			our_cubes[i].z -= speed;
		}
		else
			our_cubes[i].statusz = 1;
	}
	else
	{
		if (our_cubes[i].z < 8.3)
			our_cubes[i].z += speed;
		else
		{
			score = score - 5;
			our_cubes[i].statusy = 1;
			getx[i] = our_cubes[i].x;
		}
	}

}

//nfela y - the fall in love ... -  i is one of the CUBES on the table ...
void statusyy(int i) 
{
	// if we have a collision with the 7ofra .. 
	if (our_cubes[i].statusy == 1)
	{
		our_cubes[i].z = 8.5;
		//	our_cubes[i].x = getx[i];
		if (our_cubes[i].y > -5)
		{
			our_cubes[i].y -= speed;
		}
	}
}

// -----------------------------
void idle(void)
{
	colors(); // ON / OFF Lights COLORS ...
	for (int i = 0; i < 5; i++)
	{
		checker2[i] = black_xx(i); // TRUE/FALSE if we have collision ma3 she 7ofra wkol mara Cube 3'er ( we're in loop )...
		if (checker2[i] == true)
		{
			if (our_cubes[i].y >= -5) // nefela byebye
				our_cubes[i].y -= speed;
			our_cubes[i].statusy = 1;
			if (flagscore[i] == 0)
				score = score + 256;
			flagscore[i] = 1;
			glutPostRedisplay();
		}
		else
			if (our_cubes[i].statusy == 0 && checker2[i] == false) // esht3'el 3ade eza ma wselna ll 7ofra..
			{
				move_x(i);
				statusxx(i);
				statuszz(i);
				move_makelkob(i);
				glutPostRedisplay();
			}
		if (our_cubes[i].statusy == 1 && checker2[i] == false) // eza 2ata3na el MAKEL - lazem no2a3 !
		{
			statusyy(i);
		}
		glutPostRedisplay();
	}
}

// Set OpenGL parameters
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	// Lighting parameters
	GLfloat mat_ambdif[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 80.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);	// set both amb and diff components
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		// set specular
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);		// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		// active material changes by glColor3f(..)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	///////////////////////////////// first cube place

}

// The Main ...
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	// RGB display, double-buffered, with Z-Buffer
	glutInitWindowSize(700, 700);					// 500 x 500 pixels
	glutCreateWindow("3D");
	glutDisplayFunc(draw);						// Set the display function
	glutKeyboardFunc(keyboard);					// Set the keyboard function
	glutIdleFunc(idle);							// Set the Idle function
	init_cubes2();
	init_cubes();	
	init_makel();
	init_kad();
	init();
	glutMainLoop();							// Start the main event loop
}