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

#include <Babylon/Dictionary.hh>
#include <Prague/Sys/Directory.hh>
#include <Prague/Sys/DLL.hh>
#include <Prague/Filter/gzstream.hh>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace Prague;
using namespace Babylon;

// static variables:
Dictionary       *Dictionary::dictionary = 0;
Dictionary::Guard Dictionary::guard;
Mutex             Dictionary::singletonMutex;

bool Dictionary::isDefined(const UCS4 & _uc) throw (BlockError) {
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

UCS4 Dictionary::uppercase(const UCS4 & _uc)
    throw (UndefinedProperty, BlockError) {
    UCS4 result;
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

UCS4 Dictionary::lowercase(const UCS4 & _uc)
    throw (UndefinedProperty, BlockError) {
    UCS4 result;
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

UCS4 Dictionary::titlecase(const UCS4 & _uc)
    throw (UndefinedProperty, BlockError) {
    UCS4 result;
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

float Dictionary::numericValue(const UCS4 & _uc)
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

int Dictionary::decDigitValue(const UCS4 & _uc)
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
    
int Dictionary::digitValue(const UCS4 & _uc)
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

string Dictionary::blockname(const UCS4 & _uc)
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
    
Gen_Cat Dictionary::category(const UCS4 & _uc)
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

Can_Comb_Class Dictionary::combClass(const UCS4 & _uc)
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
    
Bidir_Props Dictionary::bidirProps(const UCS4 & _uc)
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
    
Char_Decomp Dictionary::decompType(const UCS4 & _uc) 
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

UTF32String Dictionary::decompose(const UCS4 & _uc)
    throw (UndefinedProperty, BlockError) {
    UTF32String result;
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

UCS4 Dictionary::compose(const UCS4 & starter, const UCS4 & last)
    throw (UndefinedProperty, BlockError) {
    UCS4 result;
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
    
bool Dictionary::mustMirror(const UCS4 & _uc)
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

EA_Width Dictionary::EAWidth(const UCS4 & _uc)
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

Line_Break Dictionary::linebreak(const UCS4 & _uc)
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

Dictionary * Dictionary::instance() {
    // Create Dictionary just once
    {
	MutexGuard guard(singletonMutex);
	if (!dictionary) dictionary = new Dictionary;
    }
    
    return dictionary;
} // instance


UTF32String Dictionary::recursiveDecompose(const bool & compat, const UCS4 & _uc)
    throw (UndefinedProperty, BlockError) {
    UTF32String decomp;
    UTF32String result;
    
    rwLock.rlock();
    try {
	if (findChar(_uc)->decompType(_uc) == DECOMP_COMPAT && !compat) {
	    decomp.resize(1); decomp[0] = _uc;
	    return decomp;
	}
	
	decomp = decompose(_uc);
	if(decomp[0] != _uc && !(compat && decompType(_uc) == DECOMP_COMPAT))
	    for (UTF32String::const_iterator i = decomp.begin();
		 i != decomp.end();
		 i++)
		result += recursiveDecompose(compat, *i);
	else
	    result = decomp;
    }
    catch (const Babylon::UndefinedProperty & Except) {
	rwLock.unlock(); throw Except;
    }
    catch (const Babylon::BlockError & Except) {
	rwLock.unlock(); throw Except;
    }
    
    rwLock.unlock();
    return result;
}

Dictionary::Block * Dictionary::findChar(const UCS4 & UC)
    throw (UndefinedProperty, BlockError) {

    rwLock.rlock();
    
    // Binary search version:
    unsigned short i = 0;
    
    // ASCII happens so often that this speeds things up a bit
    if (UC > data[i].end) {
	// binary search for non-ASCII characters
	size_t start = 1; // 0 was allready checked
	size_t end = data.size(); 
	i = (start + end) / 2;
	while (i > start && i < end) {
	    if (UC < data[i].start) end = i;
	    else if (UC > data[i].end) start = i;
	    else break; // we found it...
	    i = (start + end) / 2;
	}
    }
    
    Data *p = &data[i];
    if ( !(UC >= p->start && UC <= p->end)) { // UC belongs to no block
	rwLock.unlock();
	throw UndefinedProperty(UC, Babylon::PROP_CHARACTER);
    }
    
    if (p->block == 0) { // need to dynamically load the relevant script
	if (p->file == "") { // Block is unsupported
	    rwLock.unlock();
	    throw BlockError(p->start, p->end, "Block is not supported.");
	}

	p->block = new Prague::Plugin<Dictionary::Block>(p->file);
	if(*(p->block) == 0) { // Failed to load the plugin for this block
	    rwLock.unlock();
	    throw BlockError(p->start, p->end, p->block->error());
	}
    }
    
    rwLock.unlock();
    return p->block->get();
} // Dictionary::findChar


void Dictionary::update(const string & scanDir)
    throw (FileError) {
    rwLock.wlock();
    clean();
    
    Prague::Directory dir(scanDir, 0);
    
    // start scanning the directory:
    for (Prague::Directory::const_iterator dir_it = dir.begin();
	 dir_it != dir.end();
	 ++dir_it) {
	string name = (*dir_it)->long_name();
	
	if ( !((*dir_it)->is(Prague::Directory::reg)) )
	    continue;
	
	Prague::Plugin<Dictionary::Block> * block =
	    new Prague::Plugin<Dictionary::Block>(name);
	
	if (block == 0)
	    continue;
	
	if (*block == 0)
	    continue;
	
	UCS4 start = (*block)->firstLetter();
	UCS4 end   = (*block)->lastLetter();
	
	Data current;
	current.start = start;
	current.end = end;
	current.file = name;
	current.canRemove = 0;
	current.block = 0;
	
	data.push_back(current);
    }      
    
    sort(data.begin(), data.end());
    
    rwLock.unlock();
} // update_dictionary

Dictionary::Dictionary() : data(0) {
    my_version.resize(1);
    my_version[0] = UC_NULL;
    char *env = getenv("BABYLON_PATH");
    if (!env) {
	cerr << "Please set environment variable BABYLON_PATH first" << endl;
	exit(-1);
    }
    plugindir = env;
    update(plugindir);
} // Dictionary::Dictionary


Dictionary::~Dictionary() {
    rwLock.wlock();
    clean();
    rwLock.unlock();
} // Dictionary::~Dictionary()

void Dictionary::clean() {
    // gets only called in writelocked functions!
    for (size_t i = 0; i < data.size(); i++)
	if (data[i].block)
	    delete data[i].block;
    
    data.clear();
};

Dictionary::Block::Block() {}

Dictionary::Block::~Block() {}

void Dictionary::Block::clean() {}
