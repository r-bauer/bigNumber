/*
File: LLGEN.C
   Author: Roberto Bauer
   Comments:
               Generic primitives for a double-chained list.
               It does not contain any code-dependent functions.
*/


#define __LLGEN_C__

#include "main.h"


// Redefinition to increase readability of code

#define LLHead 			(L-> slkHead)	// the start of the current list
#define LLTail 			(L-> slkTail)	// the end of the current list
#define NodeCount 		(L-> uiCount)	// nodes in the current list


#define CreateData      (*(L->fCreateData))
#define DeleteData      (*(L->fDeleteData))
#define DuplicatedNode  (*(L->fDuplicatedNode))
#define NodeDataCmp     (*(L->fNodeDataCmp))


/*
    Function:
              AddNodeAtHead

    Purpose:
              Adds a node at the beginning (head) of the unordered list

    Parameters:
              SLIST * L -> pointer to data structure that handles unordered list
              Void * nd -> node to be inserted in non-sorted list

    Return:
            TRUE - added at the top of the list node
            FALSE - could not create a node to insert into the list

    Description:
              Stores a new node always at the top of the list
              First it allocates space for data,
              Then allocates a node with pointer to data,
              Then adds the node in the list.
*/
BOOL
AddNodeAtHead (SLIST * L, void *nd)
{
  SLINK slkPn;					// pointer to the node to be inserted into the list

  slkPn = CreateNode (L, nd);	// create the node and pass the address
  if (slkPn == NULL)			// could not allocate node
	return FALSE;				// returns indicating failure

  // add the node
  if (LLHead == NULL)			// is the first node to be inserted into the list?
	{
	  LLHead = LLTail = slkPn;	// Yes
	}
  else							// no
	{
	  LLHead->prior = slkPn;	// first put the node before the start (head)
	  slkPn->next = LLHead;		// puts the start as next of the new node
	  LLHead = slkPn;			// then point the start to the new node
	}

  ++NodeCount;					// adds the new node in total
  return TRUE;
}


/*
    Function:
              AddNodeAscend

    Purpose:
              Adds an ascending node

    Parameters:
              SLIST * L -> pointer to data structure that handles the list
              Void * nd -> node to be inserted in the list

    Return:
            TRUE - Added in the list the node,
                   If it is duplicate, remove, add or ignore,
                   Depends on the configuration of the list
            FALSE - could not create a node to insert into the list

    Description:
              Adds a node to an ordered list
*/
BOOL
AddNodeAscend (SLIST * L, void *nd)
{
  SLINK slkPn;					// pointer to the node to be inserted into the list
  SLINK slkPrev;				// previous link pointer of list during search
  SLINK slkCurr;				// pointer of the current link of the list during the search
  SNODE snDummy;				// temporary node
  int iCompare;					// comparative result between two nodes
  int iAction;					// action to be taken in case of duplicate nodes

  slkPn = CreateNode (L, nd);	// create the node and pass the address
  if (slkPn == NULL)			// could not allocate node
	return FALSE;				// returns indicating failure

  // ignores the special handling that is done for the start of the list
  // add the temporary node to the beginning of the list
  // and starts to treat the initial node (head) as a node equal to the others
  // simplifying the treatment logic
  snDummy.next = LLHead;
  snDummy.prior = NULL;
  if (snDummy.next != NULL)	// if the list is not empty
	snDummy.next->prior = &snDummy;	// equal, LLHEAD-> prior = & snDummy;

  // prepares to scroll through the list
  slkPrev = &snDummy;			// previous node points to temporary node
  slkCurr = snDummy.next;		// current node points to the starting node of the list

  // search
  // while the node link is valid
  // copy the current node to the previous one
  // copy the next node to the current node
  for (; slkCurr != NULL; slkPrev = slkCurr, slkCurr = slkCurr->next)
	{
	  // uses funcaoh that compares the data of the current node with the node to be inserted
	  iCompare = NodeDataCmp (slkPn->pdata, slkCurr->pdata);
	  if (iCompare <= 0)
		{
		  break;				// the new node is equal to or precedes the current node
		}
	}

  // if you did not go through the list until the end
  // and found a (duplicate) copy of the data in the list
  if ((slkCurr != NULL) && (iCompare == 0))
	{
	  // call funcaoh which returns the desired acaoh
	  // in case of duplicate node
	  iAction = DuplicatedNode (slkPn, slkCurr);
	  // fDuplicateNode returns:
	  // 2 -> add duplicate
	  if (iAction == 2)
		{
		  // nothing does, should be inserted
		  // treatment continues outside
		  // of the conditional 'if ((slkCurr! = NULL) && (iCompare == 0))'
		}
	  // fDuplicateNode returns:
	  // 0 -> no action on the list
	  // 1 -> destroy duplicate
	  else						// if (iAction == 0 || iAction == 1)
		{
		  // first, sort the threaded list and pull the node
		  // temporary start and restore the original start
		  LLHead = snDummy.next;
		  LLHead->prior = NULL;

		  // if appropriate, delete the duplicate node
		  if (iAction == 1)		// || (iAction == 0)
			{
			  DeleteData (slkPn->pdata);	// delete the data that depends on the object's implementation
			  free (slkPn);		// we deallocate the node
			}

		  // if iAction == 0, an error occurred,
		  // the treatment will be done outside this funcaoh
		  return TRUE;			// found a duplicate and took action to ignore or delete
		}
	}

  // will add the node between the previous and the current
  slkPrev->next = slkPn;		// the previous node points to the new node
  slkPn->prior = slkPrev;		// the new node points 'prior' to the previous node
  slkPn->next = slkCurr;		// the new node points 'next' to the current node

  // if the current node points to a valid position in the list
  if (slkCurr != NULL)
	{
	  slkCurr->prior = slkPn;	// the current node points 'prior' to the new node
	}
  // otherwise, it means that you have browsed the list until the end
  else
	{
	  LLTail = slkPn;			// this node is a new end (tail)
	}

  ++NodeCount;					// adds the new node in total

  // we remove the temporary node
  LLHead = snDummy.next;
  LLHead->prior = NULL;

  return TRUE;
}

/*
    Function:
              CreateLList

    Purpose:
              Creates and starts a linked list management structure

    Parameters:
          Pointers to specific functions of the list
              Void * (* fCreateData) (void *) -> creates data
              Int (* fDeleteData) (void *) -> deletes given
              Int (* fDuplicatedNode) (SLINK, SLINK) -> what to do with duplicate data
              Int (* fNodeDataCmp) (void *, void *) -> compare nodes

    Return:
          SLIST pointer
            PL - pointer to an initialized list type structure
            NULL - could not create the linked list

    Description:
              Creates a chained list structure and returns a pointer from the
              It. In error, returns NULL.
              This function accepts pointers for the four specific functions
              From a list and initialize the structure with them.
*/
SLIST *
CreateLList (void *(*fCreateData) (void *),
			 BOOL (*fDeleteData) (void *),
			 int (*fDuplicatedNode) (SLINK, SLINK),
			 int (*fNodeDataCmp) (void *, void *))
{
  SLIST *pL;

  // allocates a structure that manages a linked list
  pL = (SLIST *) malloc (sizeof (SLIST));
  if (pL == NULL)				// if it fails to allocate memory
	return NULL;				// returns to indicacaoh

  // having allocated, initializes variables
  pL->slkHead = NULL;
  pL->slkTail = NULL;
  pL->uiCount = 0;

  // and stores the specific func- tions for treatment of the list
  pL->fCreateData = fCreateData;
  pL->fDeleteData = fDeleteData;
  pL->fDuplicatedNode = fDuplicatedNode;
  pL->fNodeDataCmp = fNodeDataCmp;

  return (pL);					// return address from list
}

/*
    Function:
              CreateNode

    Purpose:
              Create a node for the linked list

    Parameters:
              SLIST * L -> list structure w / pointer to the CreateData funcaoh
              Void * data -> generic pointer with node data

    return:
              SlkNewNode - pointer to a node-like structure
              NULL - could not create a node

    Description:
              Creates a node and then calls the application specific funcaoh
              CreateData () to create the node structure data.
              In case of failure returns NULL

*/
SLINK
CreateNode (SLIST * L, void *data)
{
  SLINK slkNewNode;

  // allocates pointers to next, previous, and given to node
  slkNewNode = (SLINK) malloc (sizeof (SNODE));
  if (slkNewNode == NULL)		// if it fails to allocate memory
	return (NULL);				// returns NULL's indicacaoh

  // succeeding in alocacaoh, initializes the variables
  slkNewNode->prior = NULL;
  slkNewNode->next = NULL;

  // now calls the application specific to alocacah data
  slkNewNode->pdata = CreateData (data);
  // if you can not allocate memory for the node data
  if (slkNewNode->pdata == NULL)
	{
	  free (slkNewNode);		// releases previously allocated memory
	  return (NULL);			// returns NULL to indicate failure
	}
  // allocated all the memory would need
  else
	{
	  return (slkNewNode);		// returns pointer to funcaoh
	}
}

/*
    Function:
              DeleteNode

    Purpose:
              Deletes a node from the linked list

    Parameters:
              SLIST * L -> structure list w / pointer to the funcaoh DeleteData
              SLINK slkToDelete -> the node to be excluded

    return:
              TRUE - delete the node and refresh the list
              FALSE - was not a valid node for exclusion

    Description:
              Delete a node pointed to by slkToDelete.
              Checks whether the node is at the beginning, middle or end for specific treatment.
              Funcaoh calls the specified application from the list to erase the data
*/
BOOL
DeleteNode (SLIST * L, SLINK slkToDelete)
{
  SLINK slkPn;

  if (slkToDelete == NULL)		// make sure it's a valid node
	return FALSE;				// before trying to delete anything


  // is the last in the list
  if (slkToDelete == LLHead && slkToDelete == LLTail)
	{
	  LLHead = NULL;			// the previous one of the beginning must be NULL
	  LLTail = NULL;			// the next end must be NULL
	}
  else if (slkToDelete->prior == NULL)	// is at the beginning of the list (head)
	{
	  LLHead = slkToDelete->next;	// update the start
	  LLHead->prior = NULL;		// the previous one of the beginning must be NULL
	}
  else if (slkToDelete->next == NULL)	// is at the end of the list (tail)
	{
	  LLTail = slkToDelete->prior;	// update the end
	  LLTail->next = NULL;		// the next end must be NULL
	}
  else							// is in the middle of the list
	{
	  slkPn = slkToDelete->prior;	// go to the node before the deletion
	  slkPn->next = slkToDelete->next;	// update to next

	  slkPn = slkToDelete->next;	// go to next node to exclusion node
	  slkPn->prior = slkToDelete->prior;	// and update to the previous one
	}

  DeleteData (slkToDelete->pdata);	// delete the node data
  free (slkToDelete);			// free node memory

  --NodeCount;					// subtract the total node

  return TRUE;
}

/*
    Function:
              FindNode

    Purpose:
              Search entire list obs.:for being unordered

    Parameters:
              SLIST * L -> structure with control variables and comparcaoh funcaoh
              Void * nd -> node to be found

    return:
              SlkPCurr - points to the desired node in the list
              NULL - did not find the node

    Description:
              Find a node, starting the search at the top of the list,
              Each node and comparing the data items with
              The search key.
              You must scroll through the list because it is an unordered
*/
SLINK
FindNode (SLIST * L, void *nd)
{
  SLINK slkPCurr;				// the node we are looking at

  if (LLHead == NULL)
	{							// empty list?
	  return (NULL);			// returning NULL as failure
	}

  // position slkPCurr at the top of the list
  // while valid, proceed to the next
  for (slkPCurr = LLHead;
	   slkPCurr != NULL;
	   slkPCurr = slkPCurr->next)
  {
	// compare, if equal
	if (NodeDataCmp (nd, slkPCurr->pdata) == 0)
	  {
		return (slkPCurr);		// return pointer to posicaoh from list
	  }
  }

  // could not find the node
  return (NULL);
}

/*
    Function:
              FindNodeAscend

    Purpose:
              Search the sorted list.

    Parameters:
              SLIST * L -> structure with control variables and comparcaoh funcaoh
              Void * nd -> node to be found

    return:
              SlkPCurr - points to the desired node in the list
              NULL - did not find the node

    Description:
              Find a node, starting the search at the top of the list,
              Each node and comparing the data items with
              The WHILE search key is not larger than desired,
              By being previously ordered, can not be in the
              Remaining queue
*/
SLINK
FindNodeAscend (SLIST * L, void *nd)
{
  SLINK slkPCurr;				// the node we are looking at
  int iCmpResult;				// comparison result

  if (LLHead == NULL)
	{							// empty list?
	  return (NULL);			// returning NULL as failure
	}

  // position slkPCurr at the top of the list
  // while valid, proceed to the next
  for (slkPCurr = LLHead;
	   slkPCurr != NULL;
	   slkPCurr = slkPCurr->next)
  {
	// save the result so that you can do two further tests
	iCmpResult = NodeDataCmp (nd, slkPCurr->pdata);

	// compares if the searched node is greater than the current position of the list
	if (iCmpResult < 0)
	  {
		return (NULL);			// indicates failure because it can not be in the rest of the queue
	  }


	// compare, if equal
	if (iCmpResult == 0)
	  {
		return (slkPCurr);		// return pointer to posicaoh from list
	  }
  }

  // could not find the node in every list
  return (NULL);
}

/*
    Function:
              DestroyLList

    Purpose:
              Deletes the chained list management structure and its nodes

    Parameters:
              SLIST pointer
              L - list-type structure pointer to be deallocated

    return:
              TRUE -
              FALSE - could not delete the linked list

    Description:
              After checking that it is a valid list, it goes through the
              Deletes the nodes individually, finally releases the
              Memory used by the management structure itself.
*/
BOOL
DestroyLList (SLIST * L)
{
  SLINK slk1, slk2;				// cursors to scroll through the list

  if (L == NULL)				// if there is no valid structure
	return FALSE;				// returns fault indication

  // scroll through the list erasing all nodes
  for (slk1 = LLHead; slk1 != NULL;)
	{
	  slk2 = slk1;				// make a backup of posicaoh
	  slk1 = slk1->next;		// move to the next
	  DeleteNode (L, slk2);		// use the backup to delete the node
	}

  free (L);						// release structure that manages a linked list

  return TRUE;					// informs that the list has been destroyed
}
