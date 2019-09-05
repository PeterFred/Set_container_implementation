#ifndef A2P2_H
#define A2P2_H
#include <exception>
#include <iostream>
using namespace std;
//========part a-Comments here:
//COMMENTS
//========part b-author's details
void info(){
    cout<<"159.234 Assignment 2P1"<<endl;
    cout<<"Fredatovich P.   ID 98141269\n"<<endl;
}
//========part c-exception classes:
class RemoveFromEmpty : exception{
public:
    RemoveFromEmpty(){/* missing code */}
    const char* what() const noexcept {/* missing code */}
private:
    string mMessage;
};
class NonExistingElem:exception{
/* to be thrown when the element to be removed is not found in
the set --------code missing */
};
//========part d-Set class template
template <typename EType>
class Set{
public:
//constructors
    Set( );
    Set( const Set & rhs );
    Set( Set && rhs );
//destructor
    ~Set( );
//operators overloaded
    Set & operator=( const Set & rhs );
    Set & operator=( Set && rhs );
    Set operator+( const Set & rhs ) const; //set union
    Set operator*( const Set & rhs ) const; //set intersection
//methods
    bool isElement( const EType & x ) const;
    bool isEmpty( ) const;
    int getSize( ) const;
//display on out all elements in the set between {..}
    void print( ostream & out = cout ) const;
    void setToEmptySet( );
//methods to work with individual elements of a set
    void insert( const EType & x );
    void remove( const EType & x );
private:
    struct Node{// type of the elements of the set
        EType mData;
        Node *mNext;
        Node( const EType & d = EType( ), Node *n = nullptr )
                : mData( d ), mNext( n ) { }
    };
    Node *mFirst;
    int mSize; // to have an efficient getSize().
};
//Write the definitions of all Set function members here:


//========part e-the output operator:
template <typename EType>
ostream & operator<< /* code missing here */
#endif