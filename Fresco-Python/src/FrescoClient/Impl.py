# Python Warsaw library
# Copyright (c) 2000 by Stephen Davies
# This file is licensed for use under the GPL
#
# Tabstop is 8, SoftTabStop is 4, ShiftWidth is 4 (as per last line)
#
"""
This module contains Python implementations of various Warsaw interfaces. This
allows you to implement, for example, Graphics or Controllers and embed them
in the remove display. Of course, its really slow, but also really useful for
prototyping purposes!
"""
# Import the Warsaw stubs
import Warsaw, Unidraw
import Warsaw__POA

# ---------------
# -- Python base classes

class PyIdentifiable (Warsaw__POA.Identifiable):
    def is_identical(self, other):
	print "PyIdentifiable.is_identical(%s)"%other
	return 0

class PyRefCountBase (Warsaw__POA.RefCountBase):
    def __init__(self):
	self.__refcount = 0
    def increment(self):
	#print "PyRefCountBase.increment()"
	self.__refcount = self.__refcount + 1
    def decrement(self):
	print "PyRefCountBase.decrement()"
	self.__refcount = self.__refcount - 1
	if self.__refcount < 1:
	    print "PyRefCountBase.decrement(): RefCount reached",self.__refcount

class PySubject (Warsaw__POA.Identifiable, Warsaw__POA.RefCountBase):
    def __init__(self):
	PyRefCountBase.__init__(self)
	self.__blocked = 0
	self.__observers = []
    def attach(self, observer):
	self.__observers.append(observer)
    def detach(self, observer):
	obs = self.__observers
	for i in range(len(obs)):
	    while len(obs) > i and observer.is_identical(obs[i]):
		del obs[i]
    def block(self, blocked):
	self.__blocked = blocked
    def notify(self, any):
	if self.__blocked: return
	for observer in self.__observers:
	    try:
		observer.update(any)
	    except:
		print "PySubject.notify(): Error occurred during update."
		raise

class PyGraphic (Warsaw__POA.Graphic, PyIdentifiable, PyRefCountBase):
    def __init__(self):
	PyRefCountBase.__init__(self)
	self.__parents = []

    # Attribute 'body'
    def _get_body(self): return None
    def _set_body(self, body): pass
    
    # Methods
    def append_graphic(self, graphic): # --> void
	pass
    def prepend_graphic(self, graphic): # --> void
	pass
    def remove_graphic(self, tag): # --> void
	pass
    def remove_child_graphic(self, tag): # --> void
	pass

    def add_parent_graphic(self, graphic, parent_tag): # --> Tag
	print "PyGraphic.add_parent_graphic(graphic: %s, tag: %s)"%(graphic, parent_tag),
	mytag = len(self.__parents)
	self.__parents.append( (graphic, parent_tag, mytag) )
	print "-->",mytag
	return mytag
    def remove_parent_graphic(self, parent_tag): # --> void
	print "PyGraphic.remove_parent_graphic(tag: %s)"%parent_tag
	for i in range(len(self.__parents)):
	    if self.__parents[i][1] == parent_tag:
		del self.__parents[i]
		return

    def first_child_graphic(self): # --> Iterator
	pass
    def last_child_graphic(self): # --> Iterator
	pass

    def transformation(self): # --> Transform
	pass

    def request(self): # --> void
	x = Warsaw.Graphic.Requirement(1, 200., 300., 100., 0.)
	y = Warsaw.Graphic.Requirement(1, 200., 300., 100., 0.)
	z = Warsaw.Graphic.Requirement(1, 0., 0., 0., 0.)
	req = Warsaw.Graphic.Requisition(x, y, z, 0)
	return req
	
    def extension(self, alloc_info, region): # --> void
	#Allocation::Info a, Region r
	region.merge_union(alloc_info.allocation)
	# TODO: should use alloc_info.transformation
    def shape(self, Region): # --> void
	pass

    def traverse(self, traversal): # --> void
	traversal.visit(self._this())

    def draw(self, drawTraversal): # --> void
	pass

    def pick(self, pickTraversal): # --> void
	pass

    def allocate(self, tag, alloc_info): # --> void
	pass
    def allocations(self, alloc): # --> void
	pass
    def need_redraw(self): # --> void
	for parent, ptag, mytag in self.__parents:
	    parent.need_redraw()
    def need_redraw_region(self, Region): # --> void
	pass
    def need_resize(self): # --> void
	pass

class PyController (Warsaw__POA.Controller, PyGraphic, PySubject):
    "Python impl of Warsaw::Controller interface"
    def __init__(self):
	PyGraphic.__init__(self)
	PySubject.__init__(self)
	self.__telltale = 0
	self.__constraint = None

    # ---- also implement TellTale interface for Controller
    def _get_constraint(self):
	return self.__constraint
    def _set_constraint(self, constraint):
	self.__constraint = constraint
    def set(mask): # --> void
	if self.__constraint:
	    self.__constraint.trymodify(self._this(), mask, 1)
	self.modify(mask, 1)
    def clear(mask): # --> void
	if self.__constraint:
	    self.__constraint.trymodify(self._this(), mask, 0)
	self.modify(mask, 0)
    def test(mask): # --> bool
	return (self.__telltale & mask) == mask
    def modify(mask, set): # --> void
	if set: flags = self.__telltale | mask
	else: flags = self.__telltale & ~mask
	if flags == self.__telltale: return
	self.__telltale = flags
	any = CORBA.Any(CORBA.TC_ulong, flags)
	self.notify(any)

    # ---- Graphic interface
    def pick(traversal):
	if not traversal.intersects_allocation(): return
	traversal.enter_controller(self._this())
	PyMonoGraphic.traverse(self, traversal)
	if not self.__transparent and not traversal.picked():
	    traversal.hit()
	traversal.leave_controller()

    # ---- Controller interface
    def append_controller(controller): # --> void
	controller.increment()
	self.__children.append(controller)
	controller.set_parent_controller(self._this())
    def prepend_controller(controller): # --> void
	controller.increment()
	self.__children.insert(0, controller)
	controller.set_parent_controller(self._this())
    def remove_controller(controller): # --> void
	for i in range(len(self.__children)):
	    if self.__children[i].is_identical(controller):
		controller.remove_parent_controller()
		del self.__children[i]
		return
    def set_parent_controller(controller): # --> void
	self.__parent = controller
    def remove_parent_controller(): # --> void
	self.__parent = None
    def parent_controller(): # --> Controller
	return self.__parent
    def first_child_controller(): # --> Iterator
	pass
    def last_child_controller(): # --> Iterator
	pass
    def request_focus(controller, input_device): # --> boolean
	pass
    def receive_focus(focus): # --> boolean
	pass
    def lose_focus(input_device): # --> void
	pass
    def first_focus(input_device): # --> boolean
	pass
    def last_focus(input_device): # --> boolean
	pass
    def next_focus(input_device): # --> boolean
	pass
    def prev_focus(input_device): # --> boolean
	pass
    def handle_positional(pickTraversal, input_event): # --> boolean
	pass
    def handle_non_positional(input_event): # --> boolean
	pass



# vim: ts=8:sts=4:sw=4
