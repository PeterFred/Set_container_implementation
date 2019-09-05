#ifndef A2P2_H
#define A2P2_H
#include <exception>
#include <iostream>
using namespace std;
//========part a-Comments here:
/**
 * Set class based on a mathematical-like set type, with linked-lists as container type.
 * Set members can be inserted and removed whilst size is kept.
 * Methods check for element membership to a set, whether a set is empty, and return set size.
 * Sets can be assigned to other sets with checks for self-assignment.
 * Union (operator +) and intersection (operator *) can be preformed.
 * Exception handling checks for non-existing elements and empty sets.
 * << operator is overloaded and a print() method is implemented for printing flexibility.
 */


//========part b-author's details
void info(){
    cout<<"159.234 Assignment 2P1"<<endl;
    cout<<"P.Freadtovich   ID 98141269\n"<<endl;
}

//========part c-exception classes:
/**
 * Exception class to check for two errors:
 * - when an attempt is made to remove from an empty set
 * - when an attempt is made to remove an element not found in a set
 * Both return a relevant error message when an exception is caught
 */
class RemoveFromEmpty : exception{
public:
    /* To be thrown when attempting to remove an element from an empty set*/
    RemoveFromEmpty(){
        mMessage = "Empty set exception thrown";
    }
    const char* what() const noexcept {return mMessage.c_str();}
private:
    string mMessage;
};

class NonExistingElem : exception{
    /* to be thrown when the element to be removed is not found in the set*/
public:
    NonExistingElem(){
        mMessage = "Non existing element exception thrown";
    }
    const char* what() const noexcept {return mMessage.c_str();}
private:
    string mMessage;
};

//CLASS #######################################################################################
//NB ALL COMMENTS MADE IN DECLARATION OF CLASS TO DESCRIBE IMPLEMENTATION
//========part d-Set class template
/**
 * Set class to take any numerical type.
 *
 * Uses a Node struct implemented as a linked list, with data and size recorded
 *
 * Utilises default / copy / move constructors to implement relevant action on a set
 * Overloads both copy and move assignment operators to implement relevant action on a set
 * Set Union (+) and Set Intersection (*) can be implemented
 *
 * Methods include standard:
 * isElement() - see if an element is in a set
 * isEmpty() - returns True if a set is empty
 * getSize() - return the size of a set
 * insert() - insert an element of EType into a set (if not already an element)
 * remove() - remove an element. Throws exception if removing from an empty set, or if elemnent is not contained in set
 * setToEmptySet(0 - delete all elements of a set and set mFirst to nullptr)
 *
 * Display includes a print function and overloaded << operator which calls the print function
 *
 * @tparam EType - templated for any numerical type
 */
template <typename EType>
class Set{
public:
//constructors----------------------
    /**
     * DEFAULT CONSTRUCTOR. Sets mFirst to nullptr and size to 0
     */
    Set( );
    /**
     * COPY CONSTRUCTOR. Copy's all elements and size
     */
    Set( const Set & rhs );
    /**
     * MOVE CONSTRUCTOR. Moves all elements and size from rhs to lhs, and resets rhs to null
     * @param rhs - Set being moved from
     */
    Set( Set && rhs );
//destructor----------------------
    /**
     * DESTRUCTOR. implements setToEmptySet() method and deletes all nodes, setting mFirst to nullptr
     */
    ~Set( );
//operators overloaded-------------
    /**
     * COPY ASSIGNMENT OPERATOR. Checks for self assignment. Preforms a deep copy from rhs to lhs of operator
     * @param rhs object reference
     * @return *this - pointer to current object
     */
    Set & operator=( const Set & rhs );     //Copy Assignment operator

    /**
   * MOVE ASSIGNMENT OPERATOR. Checks for self assignment. Moves pointer from rhs object to lhs object. Sets rhs pointer to null and size to 0.
   * @param rhs object reference
   * @return *this - pointer to current object
   */
    Set & operator=( Set && rhs );          //Move Assignment Operator

    /**
     * SET UNION - OPERATOR+ Overloaded
     * Creates an empty set RESULT
     * Traverse CURRENT set and add all elements to RESULT
     * Traverse rhs set and if not in CURRENT set add to RESULT
     * return RESULT
     * @param rhs object reference
     * @return RESULT - Union Set
     */
    Set operator+( const Set & rhs ) const; //set union

    /**
     * SET INTERSECTION - OPERATOR * Overloaded
     * Create an empty set RESULT
     * Traverse each element in CURRENT set, and compare with the RHS set.
     * If element found, add to RESULT
     * return RESULT
     * @param rhs object reference
     * @return RESULT - Intersection Set
     */
    Set operator*( const Set & rhs ) const; //set intersection

//methods--------------------------
    /**
     * Checks to see if a value is in a set
     * @param x - EType value (any numerical value)
     * @return boolean - True if element is in set, false if element is not in set
     */
    bool isElement( const EType & x ) const;

    /**
     * Checks to see if a set is empty
     * @return boolean - True if set is empty, false if set is NOT empty
     */
    bool isEmpty( ) const;

    /**
     * Queries the size of a set
     * @return int - the number of elements in a set
     */
    int getSize( ) const;

//display on out all elements in the set between {..}-------------------
    /**
     * Traverses the set and prints all elements in a readable way
     * @param out ostream object
     */
    void print( ostream & out = cout ) const;

    /**
     * Traverses a set, deletes all elements, sets mFirst to nullptr, and sets size to 0
     */
    void setToEmptySet( );

//methods to work with individual elements of a set---------------------
    /**
     * Inserts a new element into the set (if not already in set), increasing set size by 1
     * @param x EType numerical value to be inserted
     */
    void insert( const EType & x );

    /**
     * Checks to see if element is in set, and if so removes element from the set.
     * Throws exception if set is empty, or if element is not in set.
     * Decrements Set size if element found and deleted.
     * @param x EType numerical value to be deleted
     */
    void remove( const EType & x );

private:
    /**
     * Node structure to cretate a link-list for the set
     */
    struct Node{// type of the elements of the Set
        EType mData;    //< Elements of the Set
        Node *mNext;    //< Pointer tot the next elemnent in the Set
        Node( const EType & d = EType( ), Node *n = nullptr )
                : mData( d ), mNext( n ) { }
    };
    Node *mFirst;       //< Pointer to the first element of the set
    int mSize;          //< to have an efficient getSize().
};

//IMPLEMENTATION ############################################################################
//CONSTRUCTORS --------------------------------------------------------------
template <typename EType>
Set<EType>::Set():mFirst(nullptr), mSize(0) {}                      //Default constructor

template <typename EType>
Set<EType>::Set( const Set &rhs): mFirst(nullptr), mSize(0){          // Copy constructor
    Node *current = rhs.mFirst;
    mSize = 0;
    while(current != nullptr){
        this -> insert (current -> mData);
        current = current -> mNext;
    }
}

template <typename EType>                                           //Move constructor
Set<EType>::Set(Set &&rhs): mFirst(nullptr), mSize(0) {
    mFirst = rhs.mFirst;
    mSize = rhs.mSize;
    rhs.mFirst = nullptr;
    rhs.mSize= 0;
}

//DESTRUCTOR ---------------------------------------------------------------------
template <typename EType>
Set<EType>::~Set() {setToEmptySet(); }

//OPERATORS OVERLOADED-------------------------------------------------------------------
template <typename EType>                           //Assignment operator
Set<EType> & Set<EType>::  operator=( const Set & rhs ){
    if(&rhs == this){return *this;}

    Node *current = rhs.mFirst;
    this -> setToEmptySet();
    mSize = 0;

    while(current != nullptr){
        this -> insert(current -> mData);
        current = current -> mNext;
    }
    return *this;
}

template <typename EType>
Set<EType> & Set<EType>::  operator=( Set && rhs ){ //Move Assignment Operator
    if(this != &rhs){
        this->setToEmptySet();

        mFirst = rhs.mFirst;
        mSize = rhs.mSize;

        rhs.mFirst = nullptr;
        rhs.mSize = 0;
    }
    return *this;
}

template <typename EType>
Set<EType> Set<EType>::operator+( const Set & rhs ) const{  //Set Union
    Set<EType> result;
    Node *current = mFirst, *rhs_current = rhs.mFirst;

    while(current != nullptr){
        result.insert(current -> mData);
        current = current -> mNext;
    }

    while(rhs_current != nullptr){
        if(!result.isElement(rhs_current -> mData)){
            result.insert(rhs_current -> mData);
        }
        rhs_current = rhs_current -> mNext;
    }
    return result;
}

template <typename EType>
Set<EType> Set<EType>::operator*( const Set & rhs ) const{   //set intersection
    Set<EType> result;
    Node * current = mFirst;

    while(current != nullptr){
        if(rhs.isElement(current -> mData)){
            result.insert(current -> mData);
        }
        current = current -> mNext;
    }
    return result;
}

//METHODS ------------------------------------------------------------------
template <typename EType>
bool Set<EType>::isElement( const EType & x ) const{
    Node *current = mFirst;

    while(current != nullptr){
        if(current-> mData ==x){
            return true;
        }
        current = current -> mNext;
    }
    return false;
}

template <typename EType>
void Set<EType>::insert( const EType & x ){
    if(!isElement(x)) {
        Node *temp = new Node;
        temp -> mData = x;
        temp -> mNext = mFirst;
        mFirst = temp;
        ++mSize;
    }
}

template <typename EType>
void Set<EType>::remove( const EType & x ) {

    Node *current = mFirst, *prev = nullptr;

    if(current == nullptr){throw RemoveFromEmpty();}

    while (current != nullptr) {
        if (current -> mData == x) {
            --mSize;
            break;
        }
        prev = current;
        current = current -> mNext;
    }

    if(current == nullptr){throw NonExistingElem();}

    if(prev == nullptr){
        mFirst = mFirst -> mNext;
    }else{
        prev -> mNext = current -> mNext;
    }
    delete current;
}


template <typename EType>
bool Set<EType>::isEmpty( ) const {
    if (mFirst == nullptr) {
        return true;
    }
    return false;
}

template <typename EType>
int Set<EType>::getSize( ) const{return mSize;}

//display on out all elements in the set between {..} --------------------------------
template <typename EType>
void Set<EType>::setToEmptySet( ){
    Node *current;
    while(mFirst != nullptr){
        current = mFirst;
        mFirst = mFirst -> mNext;
        delete current;
    }
    mSize = 0;
    mFirst = nullptr;
}

template <typename EType>
void Set<EType>::print( ostream & out ) const{
    Node * temp = mFirst;
    int count = 1;
    out << "{";
    while (temp){
        out << " ";
        out << temp -> mData;
        temp = temp-> mNext;
        if(count < getSize()) { out << ","; }
        count++;
    }
    out << " }";
}
//========part e-the output operator:
template <typename EType>
ostream & operator<< (ostream& out, Set<EType> const & digit ){
    digit.print(out);
    return out;
}

#endif