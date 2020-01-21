/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include<iostream>

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  ListNode* temp;
  while (curr) {
    temp = curr->next;
    delete curr;
    curr = temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  length_++;
  ListNode *new_node = new ListNode(ndata);
  if (head_) {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  } else {
    head_ = new_node;
    tail_ = new_node;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  length_++;
  ListNode *new_node = new ListNode(ndata);
  if (tail_) {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  } else {
    tail_ = new_node;
    head_ = new_node;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}


/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if (startPoint && endPoint) {
    if (startPoint == endPoint) {return;}
    ListNode * curr = startPoint->next;
    ListNode * start_prev = startPoint->prev;
    ListNode * curr_prev = curr->prev;
    ListNode * end_next = endPoint->next;
    ListNode * temp;
    startPoint->prev = curr;
    while (curr != endPoint) {
      temp = curr->next;
      curr->next = curr_prev;
      curr->prev = temp;
      curr_prev = curr;
      curr = temp;
    }
    endPoint->next = curr_prev;
    startPoint->next = end_next;
    endPoint->prev = start_prev;
    if(end_next) {
        end_next->prev = startPoint;
    }
    if (start_prev) {
      start_prev->next = endPoint;
    }
    temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  int count;
  ListNode * curr = head_;
  ListNode * startPoint;
  ListNode * endPoint;
  while (curr) {
    count = n;
    startPoint = curr;
    while(--count && curr->next) {
      curr = curr->next;
    }
    endPoint = curr;
    if(startPoint == head_) {
      head_ = endPoint;
    } if(endPoint == tail_) {
      tail_ = startPoint;
    }
    reverse(startPoint, endPoint);
    curr = (endPoint) ? endPoint->next : nullptr;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;
  ListNode * old_tail;
  ListNode * curr_prev;
  ListNode * curr_next;
  while (curr != tail_ && curr) {
    curr = curr->next;
    old_tail = tail_;
    if(curr && curr != tail_) {
      curr_prev = curr->prev;
      curr_next = curr->next;
      curr_prev->next = curr_next;
      curr_next->prev = curr_prev;
      old_tail->next = curr;
      curr->prev = old_tail;
      tail_ = curr;
      tail_->next = nullptr;
      curr = curr_next;
    }
  }
}


/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
    /// @todo Graded in MP3.2
    while (splitPoint--) {
          start = start->next;
    }
    start->prev->next = NULL;
    start->prev = NULL;
    return start;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}


template <typename T>
void List<T>::mergeHelper(ListNode *& first, ListNode *& second) {
  first->next = second;
  second->prev = first;
  first = second;
  second = second->next;
}


/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
    ListNode * result = (first->data < second->data)? first : second;
    ListNode * smaller = result;
    ListNode * ptr_2 = (first->data < second->data)? second : first;
    ListNode * ptr_1 = smaller->next;
    while (ptr_1 && ptr_2) {
        if (ptr_2->data < ptr_1->data) {
            mergeHelper(smaller, ptr_2);
        } else {
            mergeHelper(smaller, ptr_1);
        }
    } if (!ptr_1) {
        smaller->next = ptr_2;
        if (ptr_2) { ptr_2->prev = smaller; }
    } if (!ptr_2) {
        smaller->next = ptr_1;
        if (ptr_1) { ptr_1->prev = smaller; }
    }
    return result;
}


/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength == 1) { return start; }
    else {
       ListNode * second = split(start, chainLength/2);
       start = mergesort(start, chainLength/2);
       second = mergesort(second, chainLength - chainLength/2);
       start = merge(start, second);
    }
    return start;
}
