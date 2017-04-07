/*
  File: LLGEN.H
  Author: Roberto Bauer
  Comments:
              Generic primitives for a double-chained list.
*/

#ifndef __LLGEN_H__
#define __LLGEN_H__

#undef EXTERN
#ifdef __LLGEN_C__
#define EXTERN
#else
#define EXTERN extern
#endif


// in a double-chained list consists of a stream of elements
// called no, each has no data type and two pointers
// used to point to the previous and next
typedef struct tagSNODE
{
  struct tagSNODE *prior;		// link to the previous node
  struct tagSNODE *next;		// call the next node
  void *pdata;					// data pointer
}
SNODE;

// set a pointer type to node
  typedef SNODE *SLINK;


// a data structure of a linked list
  typedef struct tagSLIST
  {
	SLINK slkHead;				// node from the beginning of the list
	SLINK slkTail;				// node from end of list
	unsigned int uiCount;		// total of nodes in the list

	// The four specific functions of implementing data
	// from a list chained saoh:

	void *(*fCreateData) (void *);	// Create Data
	// Eh past an object pointer set to the
	// apply, we expect the return of a pointer
	// for what will be the data stored in the list.

	  BOOL (*fDeleteData) (void *);	// Delete Data
	// Eh past an object pointer set to the
	// apply that must be stored in the list
	// chained. FDeleteData should destroy the object

	int (*fDuplicatedNode) (SLINK, SLINK);	// No Duplicate
	// Eh past two pointer. The first pointer is the
	// node that should be added and the second is node that
	// jah is in the list, but is equal (duplicate)
	// the information of the first pointer.
	// fDuplicateNode returns:
	// 0 -> no action on the list
	// 1 -> destroy duplicate
	// 2 -> add duplicate

	  int (*fNodeDataCmp) (void *, void *);	// Compare Noh Data
	// fNodeDataCmp: Eh passed two object pointers set to the
	// given and must compares it, returning a number that is
	// <0, zero, or> 0, depending on the relay between the
	// first and second object.


  } SLIST;


// generic primitives of the linked list
  EXTERN BOOL AddNodeAscend (SLIST *, void *);
  EXTERN BOOL AddNodeAtHead (SLIST *, void *);

  EXTERN SLIST *CreateLList (void *(*fCreateData) (void *),	// create data
							 BOOL (*fDeleteData) (void *),	// deletes given
							 int (*fDuplicatedNode) (SLINK, SLINK),	// node duplicate
							 int (*fNodeDataCmp) (void *, void *));	// compare

  EXTERN SLINK CreateNode (SLIST *, void *);
  EXTERN BOOL DeleteNode (SLIST *, SLINK);
  EXTERN SLINK FindNode (SLIST *, void *);
  EXTERN SLINK FindNodeAscend (SLIST *, void *);
  EXTERN BOOL DestroyLList (SLIST *);


#endif	/* #define __LLGEN_H__ */
