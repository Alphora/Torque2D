//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

/*! @class SimSet
	A container for a sequence of unique SimObjects.  Torque2D will automatically remove references to any SimObjects
	as they are deleted.

	@par Overview

	A SimSet is an ordered set of references to SimObjects.
	As the name implies, a SimObject can appear no more than once within a particular SimSet.
	Attempting to add an object to a SimSet twice will not change the SimSet nor warn you.
	However, a SimObject can be a member of any number of SimSets and acts independently of any SimSet it is in.

	A Simset merely references your SimObjects.  The deletion of a SimSet does not affect the SimObjects it holds,
	and removing a SimObject from a SimSet does not delete the SimObject.
	
	If a SimSet contains a SimObject and that SimObject is deleted, that SimObject will also be automatically
	removed from the SimSet.  This is one of its most powerful features.

	Note that only SimObjects can be held in SimSets.  Strings, for instance, can not.
	But, because SimObject is the base class for almost *all* script classes, you can add any script class to a SimSet.

	The SimSet's member objects are stored initially in the order of insertion (add()),
	and can be removed (remove()), retrieved (getObject()), and queried (isMember()).
	The SimSet can have all its members counted (getCount()), printed (listObjects()), and removed (clear()).
	A member can be reordered via bringToFront() and pushToBack(), or re-ordered relative to another via reorderChild().

	@par Examples

	**Creating and Adding**

	We create the SimSet, then create objects to put in it, then we add them all in.

	@code
	new SimSet(Fruit);
	echo(Fruit.getCount());
	> 0

	// Apple, Pear, etc will be SimObjects
	new SimObject(Apple);
	new SimObject(Pear);
	new SimObject(Orange);
	new SimObject(Fig);
	new SimObject(Persimmon);

	// add our fruit to the SimSet named Fruit
	Fruit.add(Apple);
	Fruit.add(Pear);
	Fruit.add(Orange);
	Fruit.add(Fig);
	Fruit.add(Persimmon);
	echo(Fruit.getCount());
	> 5
	@endcode

	**Uniqueness**

	Continuing the above example, each member of the SimSet appears exactly once: the SimSet is a mathematically proper set.

	@code
	// Apple is already added.
	Fruit.add(Apple);
	echo(Fruit.getCount());
	> 5
	@endcode

	**Re-ordering**

	The members of a SimSet are well ordered. Let us move a different object to the front.

	@code
	echo(Fruit.getObject(0).getName());
	> Apple

	Fruit.bringToFront(Persimmon);
	echo(Fruit.getObject(0).getName());
	> Persimmon
	@endcode

	Now we move a different member to the back.

	@code
	Fruit.pushToBack(Apple);
	echo(Fruit.getObject(4).getName());
	> Apple
	@endcode

	Finally, we move the Fig member to precede Pear. Note that all of the other members retain their relative order.

	@code
	Fruit.listObjects();
	> 2887,"Persimmon": SimObject 
	> 2884,"Pear": SimObject 
	> 2885,"Orange": SimObject 
	> 2886,"Fig": SimObject 
	> 2883,"Apple": SimObject 

	Fruit.reorderChild(Fig, Pear);
	Fruit.listObjects();
	> 2887,"Persimmon": SimObject 
	> 2886,"Fig": SimObject 
	> 2885,"Orange": SimObject 
	> 2884,"Pear": SimObject 
	> 2883,"Apple": SimObject 
	@endcode

	**Removing**

	@code
	echo(Fruit.isMember(Apple));
	> 1

	Fruit.remove(Apple);
	echo(Fruit.isMember(Apple));
	> 0

	// Apple was not deleted
	echo(isObject(Apple));
	> 1

	Fruit.clear();
	echo(Fruit.getCount());
	> 0

	// The fruit SimObjects are not deleted.  For example...
	echo(isObject(Persimmon));
	> 1
	@endcode

*/

ConsoleMethodGroupBeginWithDocs(SimSet, SimObject)

/*! Prints the object data within the set
    @return No return value
*/
ConsoleMethodWithDocs(SimSet, listObjects, ConsoleVoid, 2, 2, ())
{
   object->lock();
   SimSet::iterator itr;
   for(itr = object->begin(); itr != object->end(); itr++)
   {
      SimObject *obj = *itr;
      bool isSet = dynamic_cast<SimSet *>(obj) != 0;
      const char *name = obj->getName();
      if(name)
         Con::printf("   %d,\"%s\": %s %s", obj->getId(), name,
         obj->getClassName(), isSet ? "(g)":"");
      else
         Con::printf("   %d: %s %s", obj->getId(), obj->getClassName(),
         isSet ? "(g)" : "");
   }
   object->unlock();
}

/*! Appends given SimObject (or list of SimObjects) to the SimSet.
    @param obj_1..obj_n list of SimObjects to add
    @return No return value
*/
ConsoleMethodWithDocs(SimSet, add, ConsoleVoid, 3, 0, (obj1, [obj2]*))
{
   for(S32 i = 2; i < argc; i++)
   {
      SimObject *obj = Sim::findObject(argv[i]);
      if(obj)
         object->addObject(obj);
      else
         Con::printf("Set::add: Object \"%s\" doesn't exist", argv[i]);
   }
}

/*! Removes given SimObject (or list of SimObjects) from the SimSet.
    @param obj_1..obj_n list of SimObjects to remove
	The SimObjects are not deleted.  An attempt to remove a SimObject that is not present
	in the SimSet will print a warning and continue.
    @return No return value
*/
ConsoleMethodWithDocs(SimSet, remove, ConsoleVoid, 3, 0, (obj1, [obj2]*))
{
   for(S32 i = 2; i < argc; i++)
   {
      SimObject *obj = Sim::findObject(argv[i]);
      object->lock();
      if(obj && object->find(object->begin(),object->end(),obj) != object->end())
         object->removeObject(obj);
      else
         Con::printf("Set::remove: Object \"%s\" does not exist in set", argv[i]);
      object->unlock();
   }
}

//-----------------------------------------------------------------------------

/*! Deletes all the objects in the SimSet.
    @return No return value
*/
ConsoleMethodWithDocs(SimSet, deleteObjects, ConsoleVoid, 2, 2, ())
{
    object->deleteObjects();
}

//-----------------------------------------------------------------------------

/*! Clears the Simset
	This does not delete the cleared SimObjects.
    @return No return value
*/
ConsoleMethodWithDocs(SimSet, clear, ConsoleVoid, 2, 2, ())
{
   object->clear();
}

//-----------------------------------------------------------------------------

/*! Call a method on all objects contained in the set.
	@param method The name of the method to call.
	@param args The arguments to the method.
	@note This method recurses into all SimSets that are children to the set.
	@see callOnChildrenNoRecurse" )
*/
ConsoleMethodWithDocs(SimSet, callOnChildren, void, 3, 0, ( string method, [string args]* ))
{
   object->callOnChildren( argv[2], argc - 3, argv + 3 );
}

//////////////////////////////////////////////////////////////////////////-
//	Make Sure Child 1 is Ordered Just Under Child 2.
//////////////////////////////////////////////////////////////////////////-
/*! Bring child 1 before child 2
	Both SimObjects must already be child objects.  If not, the operation silently fails.
    @param child1 The child you wish to set first
    @param child2 The child you wish to set after child1
    @return No return value.
*/
ConsoleMethodWithDocs(SimSet, reorderChild, ConsoleVoid, 4,4,  (SimObject child1, SimObject child2))
{
   SimObject* pObject = Sim::findObject(argv[2]);
   SimObject* pTarget	 = Sim::findObject(argv[3]);

   if(pObject && pTarget)
   {
      object->reOrder(pObject,pTarget);
   }
}

/*! @return Returns the number of objects in the SimSet
*/
ConsoleMethodWithDocs(SimSet, getCount, ConsoleInt, 2, 2, ())
{
   return object->size();
}

/*! Returns a member SimObject of the SimSet
	@param index into this ordered collection (zero-based).
	@return Returns the ID of the desired object or -1 on failure
*/
ConsoleMethodWithDocs(SimSet, getObject, ConsoleInt, 3, 3, (index))
{
   S32 objectIndex = dAtoi(argv[2]);
   if(objectIndex < 0 || objectIndex >= S32(object->size()))
   {
      Con::printf("Set::getObject index out of range.");
      return -1;
   }
   return ((*object)[objectIndex])->getId();
}

/*! @return Returns true if specified object is a member of the set, and false otherwise
*/
ConsoleMethodWithDocs(SimSet, isMember, ConsoleBool, 3, 3, (object))
{
   SimObject *testObject = Sim::findObject(argv[2]);
   if(!testObject)
   {
      Con::printf("SimSet::isMember: %s is not an object.", argv[2]);
      return false;
   }

   object->lock();
   for(SimSet::iterator i = object->begin(); i != object->end(); i++)
   {
      if(*i == testObject)
      {
         object->unlock();
         return true;
      }
   }
   object->unlock();

   return false;
}

/*! Returns the object with given internal name
    @param name The internal name of the object you wish to find
    @param searchChildren Set this true if you wish to search all children as well.
    @return Returns the ID of the object.
*/
ConsoleMethodWithDocs( SimSet, findObjectByInternalName, ConsoleInt, 3, 4, (string name, [bool searchChildren]?))
{

   StringTableEntry pcName = StringTable->insert(argv[2]);
   bool searchChildren = false;
   if (argc > 3)
      searchChildren = dAtob(argv[3]);

   SimObject* child = object->findObjectByInternalName(pcName, searchChildren);
   if(child)
      return child->getId();
   return 0;
}

/*! Brings SimObject to front of set.
	If the SimObject is not in the set, do nothing.
    @return No return value.
*/
ConsoleMethodWithDocs(SimSet, bringToFront, ConsoleVoid, 3, 3, (object))
{
   SimObject *obj = Sim::findObject(argv[2]);
   if(!obj)
      return;
   object->bringObjectToFront(obj);
}

/*! Sends item to back of set.
	If the SimObject is not in the set, do nothing.
    @return No return value.
*/
ConsoleMethodWithDocs(SimSet, pushToBack, ConsoleVoid, 3, 3, (object))
{
   SimObject *obj = Sim::findObject(argv[2]);
   if(!obj)
      return;
   object->pushObjectToBack(obj);
}

ConsoleMethodGroupEndWithDocs(SimSet)
