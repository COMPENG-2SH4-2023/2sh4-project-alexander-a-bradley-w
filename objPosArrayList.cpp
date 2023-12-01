#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList()
{
    // Default constructor
    sizeList = 0; // empty list
    sizeArray = 200; // default capacity
    aList = new objPos[200]; // heap data member: array or objPos instances

    // Set all elements to be blank / invalid coordinates and blank character
    for(int index=0; index<200; index++)
    {
        // -1 is being used as an indicator of a blank object (so that its coords can't accidentally be used)
        aList[index].setObjPos(-1,-1,'\0');
    }
}

objPosArrayList::~objPosArrayList()
{
    // Deleter
    delete[] aList; // delete the heap allocation
    aList = 0; // prevent misuse of pointer
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Safeguard
    if(sizeList==sizeArray)
    {
        return; // do not insert anything
    }

    // Shuffle all elements down by 1
    for(int index=sizeList; index>0; index--)
    {
        aList[index] = aList[index-1]; // shuffle the previous element into the current slot
    }

    // Now insert the head
    aList[0] = thisPos; // using the copy constructor

    // Increment the size of the list
    ++sizeList;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Safeguard
    if(sizeList==sizeArray)
    {
        return; // do not insert anything
    }

    // Add tail
    aList[sizeList] = thisPos; // using the copy constructor

    // increment the size of the list
    ++sizeList;
}

void objPosArrayList::removeHead()
{
    // Safeguard
    if(sizeList<=0)
    {
        return; // do not do anything
    }

    // Suffle forward
    for(int index=0; index<(sizeList-1); index++)
    {
        aList[index] = aList[index+1]; // replace by following element
    }

    // reduce size
    --sizeList; // no need to acutally delete last element (lazy delete)
}

void objPosArrayList::removeTail()
{
    // Safeguard
    if(sizeList<=0)
    {
        return; // do not do anything
    }

    // reduce size
    --sizeList; // no need to acutally delete last element (lazy delete)
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1]);
    // sizelist is the index of the next free slot
    // so sizelist-1 is the index of the tail element
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    // Safeguard
    // sizelist is the index of the next free slot
    // so sizelist-1 is the index of the tail element
    if(index<0 || index>=sizeList) // checking for valid indexes from 0 to sizelist-1
    {
        return; // do not write anything into returnPos
    }

    // Set the returnPos to have the same parameters as the object at position index in the list
    returnPos.setObjPos(aList[index]);
}

void objPosArrayList::reverseList()
{
    objPos tempPos;
    for(int i = 0; i < sizeList/2; i++)
    {
        // We want to swap as follows:
        // 0 1 2 3 4 5
        // 5 4 3 2 1 0
        // We will thus use the standard swapping procedure for indexes i and (sizeList-1)-i
        tempPos = aList[i];
        aList[i] = aList[(sizeList-1)-i];
        aList[(sizeList-1)-i] = tempPos;
    }
}