/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#include "Drawing/openGL/GLDrawable.hh"
#include "Berlin/RegionImpl.hh"
extern "C" {
#include "ggi/ggi.h"
}
#include <iostream>

GLDrawable::GLDrawable()
{
  context = GGIMesaCreateContext();
  if (!context)
    {
      cerr << "GGIMesaCreateContext() failed" << endl;
      exit(4);
    }
  // Configure the mode struct.
  mode.visible.x = mode.visible.y = GGI_AUTO;
  mode.virt.x = mode.virt.y = GGI_AUTO;
  mode.size.x = mode.size.y = GGI_AUTO;
  mode.dpp.x = mode.dpp.y = 1;
  mode.graphtype = GT_AUTO;
  mode.frames = 1;
  // Open the default visual --
  visual = ggiOpen(0);
  if (!visual) { cerr << "ggiOpen(NULL) failed!" << endl; exit(5);} // exit code 5 -- can't acquire a visual
  
  // We've acquired a visual, now let's decide on a mode. See libggi docs
  // on the format of the environment variable GGI_DEFMODE, which we use to
  // get all of our mode preferences.
  
  if(ggiCheckMode(visual, &mode) == 0)
    {
      
      // The mode works! We try to set it....
      if(ggiSetMode(visual, &mode) != 0)
	{
	  cerr << "Cannot set visual, even though GGI says it's ok???\n";
	  exit(6);
	  // Cannot set the mode. Strange... Exit code 6, cannot find
	  // a suitable mode for the visual
	}
      //       cerr << "Successfully set the mode on our visual!\n";
    }
  else
    {
      cerr << "GGI says our mode won't work. Trying the one it suggests...\n";
      // CheckMode said our mode wouldn't work.
      // CheckMode should have modified our mode, so we try again...
      if(ggiCheckMode(visual, &mode) != 0)
	{
	  cerr << "What?? GGI doesn't like its own suggestion. Bailing.\n";
	  // Hmm. internal GGI problem. The mode GGI gave us still won't work.
	  exit( 6 );
	}
      else
	{
	  cerr << "Ahh, GGI likes its own suggestion; trying to set the suggested mode.\n";
	  // ggiCheckMode worked this time, on the mode it gave us last time.
	  // Try to set the mode.
	  if(ggiSetMode(visual, &mode) != 0)
	    {
	      cerr << "Huh?? Still can't set the mode. Bailing.\n";
	      exit( 6 );
	      // What?? after all this, GGI _STILL_ won't set the mode for us?
	      // If we get here GGI is having some serious trouble
	    }
	}
    }
  // If we get here, we've successfully set a mode from GGI_DEFMODE.
  // I know, I'm paranoid, but this implementation will save trouble in the
  // long run. --Aaron

  ggiAddFlags(visual, GGIFLAG_ASYNC);
    
  if (GGIMesaSetVisual(context, visual, GL_TRUE, GL_FALSE))
    {
      cerr << "GGIMesaSetVisual() failed" << endl;
      exit( 7 );
      // exit code 7. Cannot set visual for GGIMesa.
    }
  GGIMesaMakeCurrent(context);
  reshape( mode.visible.x, mode.visible.y );

  // initialize some friendly OpenGL states
//    static GLfloat white[4] = {0.1, 0.1, 0.1, 0.1 };
//    glEnable(GL_LIGHTING);   
//    glLightfv( GL_LIGHT0, GL_AMBIENT, white ); 
//    glEnable(GL_LIGHT0);   
//    glClear( GL_COLOR_BUFFER_BIT );
   glShadeModel(GL_SMOOTH);
    //glDisable(GL_DEPTH_TEST);
//    glDisable(GL_ALPHA_TEST);
    glDisable( GL_LIGHTING );  
  //  glEnable( GL_CULL_FACE ); 
  // glEnable( GL_DEPTH_TEST ); 
   glFrontFace(GL_CW); 
//   glShadeModel(GL_FLAT);
   glEnable(GL_CLIP_PLANE0);
   glEnable(GL_CLIP_PLANE1);
   glEnable(GL_CLIP_PLANE2);
   glEnable(GL_CLIP_PLANE3);
   glEnable(GL_ALPHA_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


// this is just a utility function for reshaping.
void GLDrawable::reshape( int width, int height )
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1.0, 1.0); 
  glTranslatef(0.375,0.375,0.);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


GLDrawable::~GLDrawable()
{
  while (clipping.size())
    {
      RegionImpl *c = clipping.top();
      c->_dispose();
      clipping.pop();
    }
  GGIMesaDestroyContext(context);
}

Coord GLDrawable::dpi(Axis axis)
{
  return 72.;
}

Coord GLDrawable::toCoord(PixelCoord p, Axis axis) { return p/dpi(axis);}
PixelCoord GLDrawable::toPixels(Coord c, Axis axis) { return static_cast<long>(c*dpi(axis));}

void GLDrawable::pushClipping(Region_ptr region, Transform_ptr transformation)
{
  RegionImpl *clip = new RegionImpl(region, transformation);
  clip->_obj_is_ready(CORBA::BOA::getBOA());
  if (clipping.size()) clip->mergeIntersect(Region_var(clipping.top()->_this()));
  clipping.push(clip);
  makeCurrent();
//   PixelCoord x, y, w, h;
//   x = toPixels(clip->lower.x, xaxis);
//   y = toPixels(clip->lower.y, yaxis);
//   w = toPixels(clip->upper.x - clip->lower.x, xaxis);
//   h = toPixels(clip->upper.y - clip->lower.y, yaxis);
//   cout << "GLDrawable::pushClipping " << *clip << '\n';
  double cp0[] = {1., 0., 0., -clip->lower.x};
  double cp1[] = {0.,  1., 0., -clip->lower.y};
  double cp2[] = {-1., 0., 0., clip->upper.x};
  double cp3[] = {0., -1., 0., clip->upper.y};
  //  cout << "GLDrawable::pushClipping " << *clip << endl;
  glClipPlane(GL_CLIP_PLANE0, cp0);
  glClipPlane(GL_CLIP_PLANE1, cp1);
  glClipPlane(GL_CLIP_PLANE2, cp2);
  glClipPlane(GL_CLIP_PLANE3, cp3);
}

void GLDrawable::popClipping()
{
  if (clipping.size())
    {
      RegionImpl *clip = clipping.top();
      clip->_dispose();
      clipping.pop();
      if (!clipping.size()) return;
      clip = clipping.top();
      makeCurrent();
      double cp0[] = {1., 0., 0., -clip->lower.x};
      double cp1[] = {0., 1., 0., -clip->lower.y};
      double cp2[] = {-1., 0., 0., clip->upper.x};
      double cp3[] = {0., -1., 0., clip->upper.y};
      cout << "GLDrawable::pushClipping " << *clip << endl;
      glClipPlane(GL_CLIP_PLANE0, cp0);
      glClipPlane(GL_CLIP_PLANE1, cp1);
      glClipPlane(GL_CLIP_PLANE2, cp2);
      glClipPlane(GL_CLIP_PLANE3, cp3);
    }
}
