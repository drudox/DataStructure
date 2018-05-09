# ifndef __DBL_LINKED_LIST_H__
# define __DBL_LINKED_LIST_H__



# include <cstdlib>
# include <iostream>
# include "Node.H"
# include <fstream>
# include <string>


namespace mg {
                namespace tools {
                                   namespace dataStructure {


// forward declaration
template <typename type>
class DBLLinkList ;

struct iterator ;

template <typename T>
std::ostream& 
operator<<(std::ostream& os , const DBLLinkList<T>& l) noexcept ;



/*--------------------------------------------------------------------------------------------
 *
 *  @author Marco Ghiani , Glasgow 2018
 *  @class  double linked list 
 *  
 *
 --------------------------------------------------------------------------------------------*/



template <typename type>
class DBLLinkList {

    public:  
      friend struct iterator;

      template <typename T>
      friend std::ostream& operator<<(std::ostream& os , const DBLLinkList<T>& l) noexcept;
    
    public:   
      
      constexpr DBLLinkList() : firstptr{nullptr} , lastptr{nullptr} , nn{0}
          {}
    
      virtual ~DBLLinkList() = default ;


      inline bool constexpr isEmpty()const noexcept { return firstptr == nullptr ;}
      
      inline auto constexpr size()const noexcept { return nn ;}

      auto push_front(const type&) noexcept ;

      auto push_back(const type& ) noexcept ;

      auto pop_front() noexcept ;

      auto pop_back() noexcept ;

      auto pop_from(std::size_t p);
      
      auto push_to(std::size_t p,const type& v);

      auto constexpr print_front()const noexcept ;
      
      auto constexpr print_back()const noexcept ;
      
      auto constexpr print_number()const noexcept ;
      
      auto swapNode( std::shared_ptr<Node<type>> & , std::shared_ptr<Node<type>> & ) noexcept;
      
      auto swapData( std::shared_ptr<Node<type>> & , std::shared_ptr<Node<type>> & ) noexcept;
      
      auto testSwap(type n1, type n2) noexcept ;
      
      struct iterator ;
   
      auto begin() { return iterator(*this,firstptr); }
      
      const auto cbegin() const { return iterator(*this,firstptr); }
      
      auto end() {return iterator(*this, lastptr->nextPtr); }
      
      const auto cend()const {return iterator(*this, lastptr->nextPtr); }
      
      auto updateNodeNumber() noexcept;
      
      auto find_node(std::size_t n) const noexcept ;
    
    private:
      
      std::shared_ptr<Node<type>> firstptr ;
      std::shared_ptr<Node<type>> lastptr  ;
      
      std::shared_ptr<Node<type>> currentptr;

      std::shared_ptr<Node<type>> getNewNode(const type& val) 
      {
            return std::make_shared<Node<type>>(val); 
      }
      
      std::size_t nn ;

};
//
//-----------------------------------------------------------------------------------


// push node at front !
template <typename T>
inline auto DBLLinkList<T>::push_front(const T& val) noexcept
{
   auto newNode = getNewNode(val) ; 
   
   if(isEmpty())
   {
      firstptr = lastptr = newNode ;
      nn++ ;
      newNode->number = 1 ;
      updateNodeNumber();
   }     
   else
   {
      firstptr->prevPtr = newNode  ;
      newNode->nextPtr  = firstptr ;
      firstptr          = newNode  ;
      firstptr->prevPtr = nullptr  ;
      newNode->number = 1 ;
   
      updateNodeNumber();
      nn++;
   }
}

// push node at the end

template <typename T>
inline auto DBLLinkList<T>::push_back(const T& val) noexcept
{     
   auto newNode = getNewNode(val) ;

   if(isEmpty())
   {
      firstptr = lastptr = newNode ;
      nn++;
      newNode->number = newNode->prevPtr->number + 1 ;
   }  
   else
   {
      lastptr->nextPtr = newNode;
      newNode->prevPtr = lastptr;
      lastptr          = newNode;
      lastptr->nextPtr = nullptr; 
      newNode->number = newNode->prevPtr->number + 1 ;
   
      nn++;
   }   
}

// pop node from front
template <typename T>
inline auto DBLLinkList<T>::pop_front() noexcept 
{
   if(isEmpty())
   {
      std::cerr << "Empty list , pop_front() failed" << std::endl;
      exit(-1);
   }
   else
   {
      auto tempNode = firstptr ;

      if( firstptr == lastptr ) // only one node in the list   
      {
         std::cout << "Last node into the list" << std::endl;    
         firstptr = lastptr = nullptr ;   
      }
      
      firstptr = firstptr->nextPtr ;
      firstptr->prevPtr = nullptr  ;

      auto data = tempNode->data_ ;
      
      //delete tempNode ;
      updateNodeNumber() ;
      nn--;
      return data ;
   }
}

// 
// pop node from back
template <typename T>
inline auto DBLLinkList<T>::pop_back() noexcept 
{
   if(isEmpty())
   {
      std::cerr << "Empty list , pop_back() failed " << std::endl;
      exit(-1);
   }
   else
   {
      auto tempNode = lastptr ;

      if(firstptr == lastptr)
      {
            std::cout << "Last Node into the list" << std::endl;
      }
      
      lastptr = lastptr->prevPtr ;
      lastptr->nextPtr = nullptr ;

      auto data = tempNode->data_ ;
      // delete tmp
      nn--;
      return data ;
   }
}


template<typename T>
inline auto DBLLinkList<T>::find_node(std::size_t n) const noexcept
{
     auto currentPtr = firstptr ;
     
     while(currentPtr->number != n)
         currentPtr = currentPtr->nextPtr ;   
     
     return currentPtr ;
}



template <typename T>
inline auto DBLLinkList<T>::push_to(std::size_t p, const T& v)
{
     auto current = find_node(p);

     auto newNode = getNewNode(v);
      
     current->nextPtr->prevPtr = newNode;
     newNode->nextPtr = current->nextPtr ;
     current->nextPtr = newNode ;
     newNode->prevPtr = current ;

     updateNodeNumber(); 
}

template <typename T>
inline auto DBLLinkList<T>::pop_from(std::size_t p)
{
      auto current = find_node(p) ;
      
      current->prevPtr->nextPtr = current->nextPtr ; 
      current->nextPtr->prevPtr = current->prevPtr ;
      
      auto data = current->data_ ;
      nn-- ;
      updateNodeNumber();

}



//-- print list starting from front
//
template<typename T>
inline auto constexpr DBLLinkList<T>::print_front()const noexcept 
{
    if(isEmpty())
    { 
      std::cout << "Empty List!" << std::endl;
    }
    else
    {
       auto currentPtr = firstptr ;
       while(currentPtr != nullptr)
       {
            std::cout << currentPtr->data_ << "   " ;
            currentPtr = currentPtr->nextPtr ;    
       }     
       std::cout << std::endl ;
    }

}

// reversed print 
template<typename T>
inline auto constexpr DBLLinkList<T>::print_back()const noexcept 
{
    if(isEmpty())
    { 
      std::cout << "Empty List!" << std::endl;
    }
    else
    {
       auto currentPtr = lastptr ;
       while(currentPtr != nullptr)
       {
            std::cout << currentPtr->data_ << "   " ;
            currentPtr = currentPtr->prevPtr;
       }
       std::cout << std::endl;   
     } 
}

template <typename U>
inline auto constexpr DBLLinkList<U>::print_number()const noexcept 
{     
      if(isEmpty())
      {
          std::cout << 0 << std::endl;
      }
      else
      {
         auto currentPtr = firstptr ;
         while(currentPtr != nullptr)
         {
            std::cout << currentPtr->number << "   " ;
            currentPtr = currentPtr->nextPtr ;
         }
         std::cout << std::endl;   
      }
}


template<typename T>
auto DBLLinkList<T>::updateNodeNumber() noexcept
{
      auto tempNode = firstptr ;
      std::size_t i = 1;
      if (tempNode->number != 1 )
          tempNode->number = i;  
      
      while(tempNode != nullptr)
      {
           if(tempNode->prevPtr != nullptr) 
           {
                  tempNode->number =  tempNode->prevPtr->number + 1; 
           } 
           tempNode = tempNode->nextPtr ;
            
      }
}


// making swap of 2 node into the list

template<typename T>
auto DBLLinkList<T>::swapData( std::shared_ptr<Node<T>> & n1 ,
                               std::shared_ptr<Node<T>> & n2  ) noexcept
{
      if(n1 == n2)
      {
          std::cerr << "Attempted swap between the same node!" << std::endl;  
      }
      
      std::swap(n1->data_ , n2->data_);
      std::swap(n1->number, n2->number);
      
}


// swap node  using this when the object contained into the node 
// is allocated into the heap !
//
template <typename T>
auto DBLLinkList<T>::swapNode( std::shared_ptr<Node<T>> & n1 ,
                               std::shared_ptr<Node<T>> & n2  ) noexcept
{
      
      auto tempNode1 = n1;
      auto tempNode2 = n2;
      
      auto temp  = n1->nextPtr ;
      
      if(temp == n2)
      {
         if(n1->prevPtr != n2 )  
         {  
            n2->prevPtr  = n1->prevPtr ; 
         }
         else
         {
            n1->prevPtr = n2->prevPtr  ;
         }

         if(n2->nextPtr != n1)
         {
            n1->nextPtr  = n2->nextPtr ;
         }
         else
         {
           n2->nextPtr = n1->nextPtr ;       
         }

         if(n2->prevPtr != nullptr)  
         { 
            n2->prevPtr->nextPtr = n2 ;
         }
         else
         {
            firstptr = n2;
         }
           //n2->nextPtr->prevPtr = n2 ;
         if(n1->nextPtr != nullptr) 
         {
            n1->nextPtr->prevPtr = n1 ; 
         } //n1->prevPtr->nextPtr = n1 ; 
         else
         {
            lastptr = n1;
         }
         
           n2->nextPtr = tempNode1;
           n1->prevPtr = tempNode2;
           
           n2->number = tempNode1->number ;
           n1->number = tempNode2->number ;
      }      
      else
      {
         n1->nextPtr = n2->nextPtr ;
         n2->nextPtr = temp ;   
         
         if(n1->nextPtr != nullptr )
           n1->nextPtr->prevPtr = n1 ;
         if(n2->nextPtr != nullptr ) 
           n2->nextPtr->prevPtr = n2 ;   
         
         temp = n1->prevPtr ;
         n1->prevPtr =  n2->prevPtr ;
         n2->prevPtr =  temp ;   
         
         if(n1->prevPtr != nullptr)
            n1->prevPtr->nextPtr = n1 ;
         if(n2->prevPtr != nullptr)
            n2->prevPtr->nextPtr = n2 ;
         
         std::swap(n1->number,n2->number);
      }
}

template<typename T>
auto DBLLinkList<T>::testSwap(T n1, T n2) noexcept 
{
     auto current1  = firstptr ;
     auto current2  = firstptr ;   

     while(current1->data_ != n1)

     {
         current1 = current1->nextPtr ;   
     }
     
     while(current2->data_ != n2)
     {
         current2 = current2->nextPtr ;    
     }
     
     swapNode(current1,current2) ;
}


template <typename T>
std::ostream& operator<<(std::ostream& os , const DBLLinkList<T>& l) noexcept
{
      l.print_front();
      
   return os;    
}
    

/**
 *
 *
 */


// struct iterator !
//
//
template <typename T>
struct DBLLinkList<T>::iterator {
      
      inline constexpr iterator(DBLLinkList<T>* l,
                       Node<T>* elem ) noexcept     : lptr_{std::make_shared<DBLLinkList<T>>(l)},
                                                      currPtr_{std::make_shared<Node<T>>(elem)}
             {}
      
      inline constexpr iterator(DBLLinkList<T>& l,
                       std::shared_ptr<Node<T>> elem ) noexcept : lptr_{std::make_shared<DBLLinkList<T>>(l)},
                                                      currPtr_(elem)
             {}

      inline constexpr iterator(DBLLinkList<T> &l) noexcept   : lptr_{std::make_shared<DBLLinkList<T>>(&l)}, 
                                                      currPtr_(l.firstptr)
             {}

      inline constexpr iterator(DBLLinkList<T> &l,
                                       iterator i) noexcept  : lptr_{std::make_shared<DBLLinkList<T>>(&l)},
                                                               currPtr_{i}
            {}
      
      T operator*() const { return currPtr_->data_ ; }
      iterator operator++() 
      {
            //assert( currPtr_ != nullptr );
            currPtr_ = currPtr_->nextPtr ;
            return *this;
      }
      
      bool operator!=(const iterator& rhs ) { return (currPtr_ != rhs.currPtr_ );}

      private:
       std::shared_ptr<DBLLinkList<T>>  lptr_    ;
       std::shared_ptr<Node<T>>         currPtr_ ;
};

  } //dataStructure  
 }//tool
}//mg
# endif
