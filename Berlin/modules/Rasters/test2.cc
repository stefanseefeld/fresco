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
#include <GL/glut.h>
#include <ggi/ggi.h>
#include <GL/ggimesa.h>
#include "Image/RasterImpl.hh"

void display(void);
void reshape(int w, int h);

png_bytep mem;    // Raw region for the image
png_uint_32 width, height;
ggi_visual_t vis;

int main(int argc, char* argv[])
{
	cout << "Hi.  I'm a really, really lame tester for the Raster stuff." << endl;
	cout << "Please don't be fooled into thinking that I am actually doing any Berlin stuff at the moment." << endl;
	cout << "But watch me do my one trick...." << endl;

	cout << "Setting up the ORB" << endl;
	CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv, "omniORB2");
	CORBA::BOA_ptr boa = orb->BOA_init(argc, argv, "omniORB2_BOA");
	boa->impl_is_ready(0,1);
	
	
	ImageKit* kit = new ImageKit();
	kit->_obj_is_ready(boa);
	
	RasterImpl_var rasterfari = kit->open("test.png");
	width = rasterfari->getWidth();
	height = rasterfari->getHeight();
	Data memory;
	rasterfari->getData(memory);
	mem = memory.NP_data();
		
	cout << "Well, we have the raster, but I can't do anything with it" << endl;

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
