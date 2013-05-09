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

ConsoleMethodRootGroupBeginWithDocs(SimObject)

/*! Add the field to the list of fields to exclude during write.
    @param fieldName The name of the field to filter out.
    @return No return value
*/
ConsoleMethodWithDocs(SimObject, addFieldFilter, ConsoleVoid, 3, 3, (fieldName))
{
   object->addFieldFilter(argv[2]);
}

/*! Remove the field from the list of fields to exclude during write
    @param fieldName The name of the field to stop filtering out.
    @return No return value.
*/
ConsoleMethodWithDocs(SimObject, removeFieldFilter, ConsoleVoid, 3, 3, (fieldName))
{
   object->removeFieldFilter(argv[2]);
}

ConsoleMethodRootGroupEndWithDocs(SimObject)

/*!
	@defgroup SerializeFunctions Serialization
	@ingroup TorqueScriptFunctions
	@{
*/

/*! Saves the given object to the given filename
    @param object The SimObject to save
    @param filename The name of the file in which to save the object
    @return Returns true on success and flase on failure
*/
ConsoleFunctionWithDocs(saveObject, ConsoleBool, 3, 3, (object, filename))
{
   SimObject *obj = dynamic_cast<SimObject *>(Sim::findObject(argv[1]));
   if(obj == NULL)
      return false;
   
   return Sim::saveObject(obj, argv[2]);
}

/*! Loads an object from the specified filename
    @param filename The name of the file to load the object from
    @return Returns the ID of the object on success, or 0 on failure.
*/
ConsoleFunctionWithDocs(loadObject, ConsoleInt, 2, 2, (filename))
{
   SimObject *obj = Sim::loadObjectStream(argv[1]);
   return obj ? obj->getId() : 0;
}

/*! @} */ // group SerializeFunctions
