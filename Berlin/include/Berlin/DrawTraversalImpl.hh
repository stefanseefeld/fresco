/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * http://www.fresco.org
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
#ifndef _Berlin_DrawTraversal_hh
#define _Berlin_DrawTraversal_hh

#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/TraversalImpl.hh>
#include <vector>

namespace Berlin
{

  //. The DrawTraversal walks the SceneGraph and 'makes it visible' by
  //. asking the DrawingKit to render the nodes as the Traversal
  //. passes through them.
  class DrawTraversalImpl : public virtual POA_Fresco::DrawTraversal,
                public TraversalImpl
  {
    public:
      //. Generates a DrawTraversal-Object that will start it the given
      //. graphic. It will consider anything that is inside or intersects
      //. the given Region to be damaged. The Region is 'watched', it does
      //. not matter where it is at this time: It will be reevaluated for
      //. each traversal. The given Transformation will be used on all
      //. objects encountered (in addition to all the other transformations
      //. that might be found during the Traversal). Any graphic in need of
      //. redrawing will do so using the given DrawingKit.
      DrawTraversalImpl(Fresco::Graphic_ptr, Fresco::Region_ptr,
            Fresco::Transform_ptr, Fresco::DrawingKit_ptr);
      DrawTraversalImpl(const DrawTraversalImpl &);
      virtual ~DrawTraversalImpl();
      
      //. This method is called by the ScreenManager just before a traversal.
      //. This means the stack contains a single entry. It is this entry which
      //. this method modifies...
      void damage(Fresco::Region_ptr);
      
      virtual CORBA::Boolean intersects_allocation();
      virtual CORBA::Boolean intersects_region(Fresco::Region_ptr);
    
      virtual void traverse_child(Fresco::Graphic_ptr, Fresco::Tag,
                  Fresco::Region_ptr, Fresco::Transform_ptr);
      virtual void visit(Fresco::Graphic_ptr);
      virtual Fresco::Traversal::order direction();
      virtual CORBA::Boolean ok();
      virtual Fresco::DrawingKit_ptr drawing();
      
      //. Saves the DrawingKit's state and sets it to sane values for
      //. the DrawTraversal.
      void init();
      //. Restores the DrawingKit's state prior to the DrawTraversal.
      void finish();
    private:
      Fresco::DrawingKit_var     my_drawing;
      Fresco::Region_var         my_clipping;
      Impl_var<TransformImpl>    my_id;
      Fresco::DrawTraversal_var  my_this;
  };

} // namespace

#endif 
