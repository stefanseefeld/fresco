/*+P
 * This file is part of OffiX,
 * a C++ API for the X Window System and Unix
 * Copyright (C) 1995-98  Stefan Seefeld
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
 -P*/
static char *rcsid = "$Id$";

#include "Prague/Sys/SHM.hh"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <cerrno>

int   SHM::allocate(size_t bytes) { return shmget(IPC_PRIVATE, bytes, IPC_CREAT | 0600);}
void  SHM::deallocate(int id) { shmctl(id, IPC_RMID, 0);}
void *SHM::attach(int id) { return shmat(id, 0, SHM_RND);}
void  SHM::detach(void *p) { shmdt(reinterpret_cast<char *> (p));}
