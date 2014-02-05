#include "splaytree.h"

typedef Const<int, 1> Const1;
typedef Const<int, 2> Const2;
typedef Const<int, 3> Const3;
typedef Const<int, 4> Const4;
typedef Const<int, 5> Const5;
typedef Const<int, 6> Const6;
typedef Const<int, 7> Const7;
typedef Const<int, 8> Const8;
typedef Const<int, 9> Const9;
typedef Const<int, 10> Const10;
typedef Const<int, 11> Const11;
typedef Const<int, 12> Const12;
typedef Const<int, 13> Const13;
typedef Const<int, 14> Const14;
typedef Const<int, 15> Const15;
typedef Const<int, 16> Const16;
typedef Const<int, 17> Const17;
typedef Const<int, 18> Const18;
typedef Const<int, 19> Const19;
typedef Const<int, 20> Const20;

typedef Node<Node<Node<Nil, Nil, Const9>, Node<Node<Nil, Nil, Const11>, Node<Nil, Nil, Const13>, Const12>, Const10>, Node<Nil, Nil, Const20>, Const15> tree;
typedef Node<Node<Nil, Nil, Const18>, Node<Nil, Nil, Const20>, Const19> tree2;

int main(){
	typedef add<tree, Const18>::result res;
	print_tree<res>::print();
	std::cout << std::endl;
	typedef Remove<res, Const12>::result res1;
	print_tree<res1>::print();
	return 0;
}