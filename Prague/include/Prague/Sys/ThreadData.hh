/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this file is based on an idea from the ESSI2 Project
 * Authors: Nicolas Becavin <becavin@essi.fr>
 *          Stephane Peter <speter@essi.fr>
 *          Mickael Navarro <navarro@essi.fr>
 *          Jerome Dufon <dufon@essi.fr>
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
#ifndef _ThreadData_hh
#define _ThreadData_hh

#include <Prague/Sys/Thread.hh>

namespace Prague
{

template <class T>
class Thread::Data
{
public:
//   class Exception : public LibThreadsException
//   {
//   public:
//     Exception(LibThreadsException::ThreadExceptionType i, char *name) 
//       : LibThreadsException(i,name) {}
//   };

//   /// This exception is risen when no more keys can be created.
//   class TooMuchTSDsException : public Exception {
//   public:
//    TooMuchTSDsException() : Exception(TOO_MUCH_TSDS, "Too much TSDs defined") {}
//   };

//   /// This exception is very unlikely to be raised. However it is thrown if a NULL TSD is accessed.
//   class InvalidKeyException : public Exception {
//   public:
//     InvalidKeyException() : Exception(INVALID_KEY, "Illegal key") {}
//   };

public:
  Data(T v)// throw (TooMuchTSDsException, InvalidKeyException)
    {
      if(pthread_key_create(&key, destructor));// throw TooMuchTSDsException();
      if(pthread_setspecific(key, new T(value)));// throw InvalidKeyException();
    }
  Data()// throw (TooMuchTSDsException, InvalidKeyException)
    {
      if(pthread_key_create(&key, destructor));// throw TooMuchTSDsException();
      if(pthread_setspecific(key, new T));// throw InvalidKeyException();
    }
  ~Data()
    {
      delete reinterpret_cast<T *>(pthread_getspecific(key));
      pthread_key_delete(key);
    }
  const T &var(void) const// throw (InvalidKeyException)
    {
      T *data = reinterpret_cast<T *>(pthread_getspecific(key));
      if (data) return *data;
//       else throw InvalidKeyException();
    }
  T &var(void) throw (InvalidKeyException)
    {
      T *data = reinterpret_cast<T *>(pthread_getspecific(key));
      if(data) return *data;
//       else throw InvalidKeyException();
    }

  Data<T> &operator = (const T &t)// throw (InvalidKeyException)
    {
      T *data = reinterpret_cast<T *>(pthread_getspecific(key));
      if(data) *data = t;
      else if(pthread_setspecific(key, new T(t)));// throw InvalidKeyException ();
      return *this;
    }
  Data<T> &operator = (T t) throw (InvalidKeyException)
    {
      T *data = reinterpret_cast<T *>(pthread_getspecific(key));
      if (data) *data = t;
      else if(pthread_setspecific(key, new T(t)));// throw InvalidKeyException ();
      return *this;
    }
  Data<T> &operator = (const Data<T> &t)// throw (InvalidKeyException)
    {
      T *data = reinterpret_cast<T *>(pthread_getspecific(key));
      if(data) *data = *t;
      else if(pthread_setspecific(key, new T(*t)));// throw InvalidKeyException ();
      return *this;
    }
  const T *operator->() const// throw (InvalidKeyException)
    {
      T *data = reinterpet_cast<T *>(pthread_getspecific(key));
      if(data) return data;
//       else throw InvalidKeyException();
    }
  T *operator->()// throw (InvalidKeyException)
    {
      T *data = reinterpet_cast<T *>(pthread_getspecific(key));
      if(data) return data;
//       else throw InvalidKeyException();
    }
  const T &operator *() const { return var();}
        T &operator *()       { return var();}
protected:
  pthread_key_t key;
private:
  static void destructor(void *data) { delete data;}
  Data(const Data<T> &); 
};

};

#endif /* _ThreadData_hh */
