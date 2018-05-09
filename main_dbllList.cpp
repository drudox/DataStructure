# include <iostream>
# include <iomanip>
# include "linkedlist.H"



using namespace std;
using namespace mg::tools::dataStructure ;

int main(){

  DBLLinkList<double> l1 ;
  l1.push_front(0.06);
  l1.push_back(1.11);
  l1.push_back(2.12);
  l1.push_back(3.32);
  l1.push_back(4.89);
  l1.push_back(5.212);
  l1.push_back(6.2);

  cout << l1.size() << endl ; 
  cout << "--------------------------------------------------------------------------" << endl;

      

  l1.print_front(); 
  l1.print_back();     
  cout << "--------------------------------------------------------------------------" << endl;
  
  l1.testSwap(5.212,3.32);
  l1.print_front();
  l1.print_back();
  cout << "--------------------------------------------------------------------------" << endl;
  
  auto it1 = l1.begin() ;
  
  for(auto x : l1)
      cout << x << "  " ; 
  cout << endl;    
  cout << "--------------------------------------------------------------------------" << endl;
  
//  cout << l1 ;
  l1.print_number();    
  cout << "--------------------------------------------------------------------------" << endl;
  
  l1.push_to(4,101.2);
  l1.print_front() ;
  l1.print_back() ;
  cout << "--------------------------------------------------------------------------" << endl;
  l1.print_number() ;
  cout << "--------------------------------------------------------------------------" << endl;
  cout << "... after pop_front" << endl;
  cout << "--------------------------------------------------------------------------" << endl;
  l1.pop_front();
  l1.print_front();
  l1.print_number();
  cout << "--------------------------------------------------------------------------" << endl;
  l1.pop_from(3);
  l1.print_front();
  l1.print_back();
  l1.print_number();
  cout << "--------------------------------------------------------------------------" << endl;

  return 0;
}

