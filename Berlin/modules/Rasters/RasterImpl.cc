/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Brent Fulgham <bfulgham@debian.org>
 * Copyright (C) 1999 Stefan Seefeld 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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

#include "Image/RasterImpl.hh"
#include <fstream>

RasterImpl::RasterImpl()
  : data(0)
{
	rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	rinfo = png_create_info_struct(rpng);
}

RasterImpl::RasterImpl(const char *file)
{
	rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	rinfo = png_create_info_struct(rpng);
	ifstream ifs(file);
	PNGDecoder decoder(ifs.rdbuf());
	data = decoder.decode(rpng, rinfo);
}

RasterImpl::~RasterImpl()
{
	// delete data;
	png_destroy_read_struct(&rpng, &rinfo, 0);
}

void RasterImpl::load(const Data& buffer)
{
	/*
	 * free the old data
	 */
	delete data;
	data = NULL;
	
	/*
	 * create streambuf and associate it with the sequence
	 */
	streambuf sbuf;
	unsigned long length = buffer.length();
	sbuf.setg ((char*)(buffer.NP_data()), (char*)(buffer[length]),
			   (char*)(buffer[length]));

	/*
	 * read it in
	 */
	PNGDecoder decoder(&sbuf);
	data = decoder.decode(rpng, rinfo);
}

void RasterImpl::store(Data *&buffer)
{
  /*
   * set up buffer to hold new data
   */
  //   buffer.length(...);
  streambuf sbuf;
  unsigned long length = buffer->length();
  sbuf.setp((char*)(buffer->NP_data()), (char*)(buffer+length));
  /*
   * create temporary write structures here...
   */
  PNGEncoder encoder(&sbuf);
  encoder.encode(rpng, rinfo, data);
}
