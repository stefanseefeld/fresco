/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
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

#include "Prague/config.hh"
#include "Prague/Sys/DLL.hh"
#if defined(HAVE_DLFCN_H)
#include <dlfcn.h>
#elif defined(HAVE_DL_H)
#include <dl.h>
#endif

using namespace Prague;

DLL::DLL(const std::string &name, bool now) throw(std::runtime_error, std::logic_error) : my_name(name)
{
    if (!my_name.empty())
    {
#if defined(HAVE_DLOPEN)
        int flags = now ? RTLD_NOW : RTLD_LAZY;
        flags |= RTLD_GLOBAL;
        my_handle = dlopen(my_name.c_str(), flags);
        if (!my_handle)
        {
            std::string message = "Failed to load " + my_name + ": " + dlerror();
            throw std::runtime_error(message);
        }
#elif defined(HAVE_SHL_LOAD)
        shl_t shl_handle = shl_load(my_name.c_str(),
                                    (now ? BIND_DEFERRED : BIND_IMMEDIATE) | BIND_NONFATAL | BIND_VERBOSE, 0);
        if (!shl_handle)
        {
            std::string message = "Failed to load " + my_name + ": " + strerror(errno);
            throw std::runtime_error(message);
        }
        else my_handle = shl_handle;
#endif
    }
    else throw std::logic_error("empty filename");
}

DLL::~DLL() throw()
{
#if defined(HAVE_DLCLOSE)
    dlclose(my_handle);
#elif defined(HAVE_SHL_UNLOAD)
    shl_unload (reinterpret_cast<shl_t>(my_handle));
#endif
}

void *DLL::resolve(const std::string &symbol) throw(std::runtime_error)
{
#if defined(HAVE_DLSYM)
    void *tmp = dlsym(my_handle, symbol.c_str());
    if (!tmp)
    {
        std::string message = "Failed to resolve \"" + symbol +
                              "\" in loaded file \"" + my_name +
                              "\": " + dlerror();
        throw std::runtime_error(message);
    }
#elif defined(HAVE_SHL_FINDSYM)
    void *tmp;
    if (shl_findsym(reinterpret_cast<shl_t *>(&my_handle), symbol.c_str(), TYPE_UNDEFINED, &tmp) != 0 ||
        my_handle == 0 || tmp == 0)
    {
        std:string message = "Failed to resolve \"" + symbol +
                             "\" in loaded file \"" + my_name +
                             "\": " + strerror(errno);
        throw std::runtime_error(message);
    }
#endif
    return tmp;
};
