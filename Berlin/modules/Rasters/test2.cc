/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Brent A. Fulgham <bfulgham@debian.org>
 * http://www.berlin-consortium.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */

#include <iostream>
#include <fstream>
#include <png.h>
#include <GL/glut.h>
#include <ggi/ggi.h>
#include <GL/ggimesa.h>
#include "Image/PNGDecoder.hh"

void display(void);
void reshape(int w, int h);

png_bytep mem;    // Raw region for the image
png_uint_32 width, height;
ggi_visual_t vis;

void warning(png_structp, png_const_charp msg) { cerr << "warning : " << msg << endl;}
void error(png_structp, png_const_charp msg) { cerr << "error : " << msg << endl;}

int main(int argc, char* argv[])
{
    /*
     * create decoder
     */
    ifstream inFile("test.png");
    PNGDecoder aBuf(inFile.rdbuf());
    cout << "Buffer is loaded" << endl;
     
    /*
     * create raster
     */
    png_structp aPNG = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, error, warning);
    png_infop aINFO = png_create_info_struct(aPNG);

	aBuf.getInfo(aPNG, aINFO);
	
	mem = aBuf.decode(aPNG, aINFO);
    cout << "The image is loaded " << endl;

	height = png_get_image_height(aPNG, aINFO);
	width = png_get_image_width(aPNG, aINFO);
		
    /*
     * Display the image
     */
    // First, initialize GGI
	cout << "# = " << argc << " and " << *argv << endl;
	
    GGIMesaContext ctx;
    glutInit(&argc, argv);
    glutCreateWindow("PNG Test");

	cout << "Setting up GLUT" << endl;
	
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glAlphaFunc(GL_GEQUAL, 0.5);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_DITHER);
    glClearColor(1.0, 1.0, 1.0, 0.0);
	cout << "Entering main loop" << endl;
	
    glutMainLoop();

	    // Clean up
    GGIMesaDestroyContext(ctx);
    ggiClose(vis);
    ggiExit();
}

void display(void)
{
	cout << "We've entered the display method" << endl;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(width, height, GL_RGBA,
			GL_UNSIGNED_BYTE,mem);
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,0,h);
	glMatrixMode(GL_MODELVIEW);
}
