#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED
#pragma once

#include <algorithm>
/**
 * @mainpage Introduction

Implementation of deque in C++.


*/


/**
 * @brief Deque class
 * @tparam valueType the type of data stored in the deque.
 */
template<class valueType>
class deque {
private:

  /**
  * @brief Node class represents one element of deque that stores some data.
  */
  class node {

    valueType data;/** <Stored data*/
    node* nextNode;/** <Pointer to next element*/
    node* prevNode;/** <Pointer to previous element*/

    /**
    * @brief Default constructor for class node
    */
    node() noexcept {

      nextNode = nullptr;
      prevNode = nullptr;

    };

    /**
    * @brief Copy constructor for class node
    * @param[in] data is valueType variable that we want to put in deque
    */
    node(valueType const& data) {

      this->data = data;
      nextNode = nullptr;
      prevNode = nullptr;

    };

    /**
    * @brief Move constructor for class node
    * @param[in] data is rvalue reverence to rValue variable that we want to put in deque
    */
    node(valueType&& data) noexcept {

      this->data = std::move(data);//ok?
      nextNode = nullptr;
      prevNode = nullptr;

    };

  };

  node* head;/** <Pointer to dummy*/
  node* end;/** >Pointer to last element in deque*/
  int numOfElem;/** <Number of elements in deque*/

public:

  /**
  * @brief Default constructor for class deque
  */
  deque() noexcept  {

    numOfElem = 0;
    try {
      head = new node;
    }
    catch (const std::bad_alloc& exception) {
      std::cout << "Allocation failed: " << exception.what() << std::endl;
      return;
    };
    end = head;

  };

  /**
  * @brief Constructor from initializer_list for class deque
  */
  deque(std::initializer_list<valueType> args): deque() {

    for (auto& a : args)
      pushBack(a);

  }

  /**
  * @brief Copy constructor for class deque
  * @param[in] other is const reference to lValue
  */
  deque(const deque& other)noexcept  :deque() {

    node* tmp = other.head;

    if (tmp == nullptr)
      return;
    tmp = tmp->nextNode;
    while (tmp != nullptr) {

      node* newNode;
      try {
        newNode = new node(tmp->data);
      }
      catch (const std::bad_alloc& exception) {
        std::cout << "Allocation failed: " << exception.what() << std::endl;
        return;
      };

      end->nextNode = newNode;
      newNode->prevNode = end;
      end = newNode;
      tmp = tmp->nextNode;

      numOfElem++;
    }

  };

  /**
  * @brief Move constructor for class deque
  * @param[in] other is rValue reference to rValue
  */
  deque(deque&& other) noexcept {

    this->head = other.head;
    this->end = other.end;
    this->numOfElem = other.numOfElem;
    other.head = nullptr;
    other.end = nullptr;
    other.numOfElem = 0;

  };

  /**
  * @brief Method to clear deque
  */
  void destroy(void) {

    node* tmp;
    while (head != nullptr) {
      tmp = head;
      head = head->nextNode;
      delete tmp;
    }

    numOfElem = 0;

  };

  /**
  * @brief Destructor for class deque
  */
  ~deque() { destroy(); };

  /**
  * @brief Method to put element to the end of the deque + copy semantics
  * @param[in] data is const reference to lValue
  */
  void pushBack(valueType const& data) {

    if (head == nullptr)
      throw "Deque isn't initialized";

    node* newNode;
    try {
      newNode = new node(data);
    }
    catch (const std::bad_alloc& exception) {
      std::cout << "Allocation failed: " << exception.what() << std::endl;
      return;
    };

    end->nextNode = newNode;
    newNode->prevNode = end;
    end = newNode;

    numOfElem++;

  };

  /**
  * @brief Method to put element to the end of the deque + move semantics
  * @param[in] data is rValue reference to rValue
  */
  void pushBack(valueType&& data) {

    if (head == nullptr)
     throw "Deque isn't initialized";

    node* newNode;
    try {
      newNode = new node(std::move(data));
    }
    catch (const std::bad_alloc& exception) {
      std::cout << "Allocation failed: " << exception.what() << std::endl;
      return;
    };
    end->nextNode = newNode;
    newNode->prevNode = end;
    end = newNode;

    numOfElem++;

  };

  /**
  * @brief Method to put element to the beginning of the deque + copy semantics
  * @param[in] data is const reference to lValue
  */
  void pushFront(valueType const& data) {

    if (head == nullptr)
      throw "Deque isn't initialized";

    node* newNode;
    try {
      newNode = new node(data);
    }
    catch (const std::bad_alloc& exception) {
      std::cout << "Allocation failed: " << exception.what() << std::endl;
      return;
    };

    node* tmp = head->nextNode;
    tmp->prevNode = newNode;
    head->nextNode = newNode;
    newNode->nextNode = tmp;
    newNode->prevNode = head;

    numOfElem++;

  };

  /**
  * @brief Method to put element to the beginning of the deque + move semantics
  * @param[in] data is rValue reference to rValue
  */
  void pushFront(valueType&& data) {


    if (head == nullptr)
      throw "Deque isn't initialized";

    node* newNode;
    try {
      newNode = new node(std::move(data));
    }
    catch (const std::bad_alloc& exception) {
      std::cout << "Allocation failed: " << exception.what() << std::endl;
      return;
    };

    node* tmp = head->nextNode;
    tmp->prevNode = newNode;
    head->nextNode = newNode;
    newNode->nextNode = tmp;
    newNode->prevNode = head;

    numOfElem++;

  };

  /**
  * @brief Method to remove element from the end of the deque
  */
  void popBack(void) {

    if (head == nullptr || head->nextNode == nullptr)
      throw "Deque is empty";

    node* tmp = end;
    end = end->prevNode;
    end->nextNode = nullptr;
    delete tmp;

    numOfElem--;

  };

  /**
  * @brief Method to see element from the end of the deque
  * @return const reference to valueType element
  */
  valueType const& peekBack(void) {

    if (head == nullptr || head->nextNode == nullptr)
      throw "Deque is empty";

    return end->data;

  };

  /**
  * @brief Method to remove element from the beginning of the deque
  */
  void popFront(void) {

    if (head == nullptr || head->nextNode == nullptr)
      throw "Deque is empty";

    node* tmp = head->nextNode;
    head->nextNode = tmp->nextNode;
    tmp->nextNode->prevNode = head;
    delete tmp;

    numOfElem--;

  };

  /**
  * @brief Method to see element from the end of the deque
  * @return const reference to valueType element
  */
  valueType const& peekFront(void) {

    if (head == nullptr || head->nextNode == nullptr)
      throw "Deque is empty";

    return head->nextNode->data;

  };

  /**
  * @brief Method to get print elements of the deque
  */
  void print(void) {


    if (head == nullptr)
      return;

    std::cout << "deque:";

    node* tmp = head->nextNode;
    while (tmp != nullptr) {

      std::cout << tmp->data << " ";
      tmp = tmp->nextNode;

    }

    std::cout << std::endl;

  };

  /**
  * @brief Copy operator=
  * @param[in] other is const reference on lvalue
  * @return reference to deque
  */
  deque& operator=(const deque& other) {

    if(&other == this)
      return *this;

    destroy();
    numOfElem = 0;
    try {
      head = new node;
    }
    catch (const std::bad_alloc& exception) {
      std::cout << "Allocation failed: " << exception.what() << std::endl;
      return *this;
    };
    end = head;

    node* tmp = other.head;

    if (tmp == nullptr)
      return *this;
    tmp = tmp->nextNode;
    while (tmp != nullptr) {

      node* newNode;
      try {
        newNode = new node(tmp->data);
      }
      catch (const std::bad_alloc& exception) {
        std::cout << "Allocation failed: " << exception.what() << std::endl;
        return *this;
      };
      end->nextNode = newNode;
      newNode->prevNode = end;
      end = newNode;
      tmp = tmp->nextNode;

      numOfElem++;

    }

    return *this;
  
  };

  /**
  * @brief Move operator=
  * @param[in] other is rValue reference on rValue
  * @return reference to deque
  */
  deque& operator=(deque&& other) noexcept {

    if (&other == this)
      return *this;

    destroy();

    this->head = other.head;
    this->end = other.end;
    this->numOfElem = other.numOfElem;
    other.head = nullptr;
    other.end = nullptr;
    other.numOfElem = 0;
    return *this;

  }

  /**
  * @brief Operator to sum two deques together + copy semantics
  * @param[in] other is const reference on lvalue
  * @return reference to deque
  */
  deque& operator+=(const deque& other) noexcept {

    node* tmp = other.head;

    if (tmp == nullptr)
      return *this;

    tmp = tmp->nextNode;
    while (tmp != nullptr) {

      node* newNode;
      try {
        newNode = new node(tmp->data);
      }
      catch (const std::bad_alloc& exception) {
        std::cout << "Allocation failed: " << exception.what() << std::endl;
        return *this;
      };
      end->nextNode = newNode;
      newNode->prevNode = end;
      end = newNode;
      tmp = tmp->nextNode;

      numOfElem++;

    }

    return *this;

  }

  /**
  * @brief Operator to sum two deques together + move semantics
  * @param[in] other is rValue reference on rValue
  * @return reference to deque
  */
  deque& operator+=(deque&& other) {

    //if other deque is our deque =>
    //won't do anything because otherwise we will delete our deque
    if (&other == this)
      return *this;

    node* tmp = other.head;

    if (tmp == nullptr)
      return *this;
    this->end->nextNode = other.head->nextNode;
    this->numOfElem += other.numOfElem;

    other.head = nullptr;
    other.end = nullptr;
    other.numOfElem = 0;

    return *this;

  }

  /**
  * @brief Method to check if deque is empty
  * @return true if deque is empty else false
  */
  bool isEmpty(void) {

    if (numOfElem == 0)
      return true;
    return false;

  }

  /**
  * @brief Method to get number of elements in deque
  * @return size of deque
  */
  int size(void) { return numOfElem; }

};
#endif