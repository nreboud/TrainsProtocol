/**
 * @brief List: handles a list of elements thanks to a linked list. NB: with the provided primitives (@a list_append() and \a list_remove_first()), this structure offers only the functionalities of a queue.
 * @file list.h
 * @author Michel SIMATIC
 * @date  14/04/2012
 * @note extension 30/05/2012 by Damien GRAUX
 */

#ifndef _LIST_H_
#define _LIST_H_
#include <pthread.h>

/** 
 * @brief Internal data structure used to build the linked list
 */
typedef struct LINK LINK;
struct LINK {
  void *value;       /**< Value hold by the @a LINK */
  LINK *next;        /**< Pointer to next LINK in the list */
  LINK *previous;    /**< Pointer to previous LINK in the list */
};

/** 
 * @brief Data structure holding a list
 */
typedef struct{
  LINK * first;              /**< Pointer on head of the list */
  LINK * last;               /**< Pointer on tail of the list */
  pthread_mutex_t listMutex; /**< Mutex to handle concurrent access to the list */
} t_list;

/**
 * @brief Creates a new list
 * @return Pointer to the new list
 */
t_list *list_new();

/**
 * @brief Removes the first element of @a aList
 * @param[in] aList List to work on
 * @return The first element of \a aList or NULL if \a aList is empty
 */
void *list_removeFirst(t_list *aList);

/**
 * @brief Appends element @a anElt to @a aList
 * @param[in] aList List to work on
 * @param[in] anElt Element to add to \a aList
 */
void list_append(t_list *aList, void *anElt);

/**
 * @brief Extends @a aList with the @a b_list at queue
 * @param[in] aList The list which will be extended
 * @param[in] b_list The list wich will be added at the queue
 */
void list_extend(t_list* aList, t_list* b_list);

/**
 * @brief Removes all the elements from @a aList but let it alive
 * @param[in] aList The list which is going to be cleaned
 */
void list_cleanList(t_list* aList);

/**
 * @brief Frees @a aList
 * @param[in] aList List to work on
 * @warning If elements of @a aList were pointers to allocated structures, these elements are not freed.
 */
void list_free(t_list *aList);

#endif /* _LIST_H_ */
