#ifndef __DOUBLE_LINKED_NODE_H__
#define __DOUBLE_LINKED_NODE_H__


# include <memory>



namespace mg {
                namespace tools {
                                   namespace dataStructure {

template<typename NodeType>
class DBLLinkList ;

template<typename NodeType>
class List ;

/*------------------------------------------------------------------
 *  @Author Marco Ghiani 2018 Glasgow
 *  @class  double linked node Node  
 -------------------------------------------------------------------*/



template <typename object_type>
class Node 
{

   public:   
    template<typename NodeType>
    friend class DBLLinkList ;

    template<typename NodeType>
    friend class List ;

    


   public:
     
     Node() : data_{object_type{}} , prevPtr{nullptr} , nextPtr{nullptr} 
      {}

     Node(object_type val ) : data_{val}, prevPtr{nullptr}, nextPtr{nullptr} 
      {}  
     
     virtual ~Node() = default ;
     
     bool operator< (const Node& n) { return data_ <  n.data_ ;} 
     
     bool operator<=(const Node& n) { return data_ <= n.data_ ;} 
      
     bool operator> (const Node& n) { return data_ >  n.data_ ;}

     bool operator>=(const Node& n) { return data_ >= n.data_ ;}
     
     bool operator==(const Node& n) { return data_ == n.data_ ;}

     bool operator!=(const Node& n) { return data_ != n.data_ ;}

   private:   
      
      object_type data_ ;

      std::shared_ptr<Node> prevPtr ;  
      std::shared_ptr<Node> nextPtr ;  
      
      std::size_t number ;
 
};


  }//dataStructure
 }//tool
}//mg
# endif


