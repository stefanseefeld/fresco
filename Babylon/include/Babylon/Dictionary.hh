/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999,2000 Tobias Hunger <Tobias@berlin-consortium.org>
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
#ifndef _Dictionary_hh_
#define _Dictionary_hh_

#include <Babylon/defs.hh>
#include <Prague/Sys/Plugin.hh>
#include <Prague/Sys/Thread.hh>
#include <fstream>

namespace Babylon {

  class Dictionary
  {
    struct Guard { ~Guard() { delete Dictionary::dictionary;}};
    friend struct Guard;
    
  public:
    void update(const string &) throw (FileError);
    static Dictionary * instance();

  private:
    Dictionary * lock() { rwLock.rlock(); return this; };
    void unlock() { rwLock.unlock(); };

    // Query functions:
    bool isDefined(const _UCS4 _uc)
    throw (BlockError) {
      bool tmp = 0;
      rwLock.rlock();
      try {
	tmp=findChar(_uc)->isDefined(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {}
      catch (Babylon::BlockError & Except) {
	rwLock.unlock();
	throw Except;
      }
      rwLock.unlock();
      return tmp;
    }

    _UCS4 uppercase(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      _UCS4 result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->uppercase(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    _UCS4 lowercase(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      _UCS4 result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->lowercase(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    _UCS4 titlecase(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      _UCS4 result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->titlecase(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    float numericValue(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      float result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->numericValue(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }	
      rwLock.unlock();
      return result;
    }

    int decDigitValue(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      int result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->decDigitValue(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      } 
      rwLock.unlock();
      return result;
    }

    int digitValue(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      int result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->digitValue(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    } 

    string blockname(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      string result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->blockname(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      } 
      rwLock.unlock();
      return result;
    }

    Gen_Cat category(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      Gen_Cat result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->category(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    Can_Comb_Class combClass(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      Can_Comb_Class result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->combClass(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    Bidir_Props bidirProps(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      Bidir_Props result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->bidirProps(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    Char_Decomp decompType(const _UCS4 _uc) 
    throw (UndefinedProperty, BlockError) {
      Char_Decomp result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->decompType(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }	
      rwLock.unlock();
      return result;
    }

    _UTF32String decompose(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      _UTF32String result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->decompose(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    _UTF32String recursiveDecompose(const bool compat, const _UCS4 _uc)
    throw (UndefinedProperty, BlockError);

    _UCS4 compose(const _UCS4 starter, const _UCS4 last)
    throw (UndefinedProperty, BlockError) {
      _UCS4 result;
      rwLock.rlock();
      try {
	result=findChar(starter)->compose(starter, last);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    bool mustMirror(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      bool result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->mustMirror(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    EA_Width EAWidth(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      EA_Width result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->EAWidth(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    Line_Break linebreak(const _UCS4 _uc)
    throw (UndefinedProperty, BlockError) {
      Line_Break result;
      rwLock.rlock();
      try {
	result=findChar(_uc)->linebreak(_uc);
      }
      catch (Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
      }
      catch (Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
      }
      rwLock.unlock();
      return result;
    }

    class Block {
      // This class is subclassed by plugin libraries.
      // No method bodies here!!

    public:
      Block();
      virtual ~Block();
      virtual void clean();
      
      // Query Functions:
      virtual bool isDefined(const _UCS4) const
	throw (BlockError) = 0;
      virtual _UCS4 uppercase(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual _UCS4 lowercase(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual _UCS4 titlecase(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual float numericValue(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual int decDigitValue(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual int digitValue(const _UCS4) const 
	throw (UndefinedProperty) = 0;
      virtual string blockname(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual Gen_Cat category(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual Can_Comb_Class combClass(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual Bidir_Props bidirProps(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual Char_Decomp decompType(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual _UTF32String decompose(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual _UCS4 compose(const _UCS4, const _UCS4)
	throw (UndefinedProperty) = 0;
      virtual bool mustMirror(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual EA_Width EAWidth(const _UCS4) const
	throw (UndefinedProperty) = 0;
      virtual Line_Break linebreak(const _UCS4) const
	throw (UndefinedProperty) = 0;

      virtual _UCS4 firstLetter() = 0;
      virtual _UCS4 lastLetter() = 0;
    protected:

    private:
    }; // class Block

    struct Data {
      _UCS4 start;
      _UCS4 end;
      string file;
      int operator < (const Data& data) const {return start < data.start;}
      bool canRemove;
      Prague::Plugin<Dictionary::Block> * block;
    }; // struct Data

    Block * findChar(const _UCS4)
      throw (UndefinedProperty, BlockError);

    Dictionary();
    Dictionary(const Dictionary &) {}
    ~Dictionary();
    void clean();

    static Dictionary *dictionary;
    static Guard guard;
    static Prague::Mutex singletonMutex;

    vector<Data> data;

    _UTF32String my_version;

    Prague::RWLock rwLock;

    string plugindir;

    // friends:
    friend class Babylon::Char;
    friend class Babylon::String;
  }; // class Dictionary

}; // namespace Babylon

#endif // _Dictionary_hh_
