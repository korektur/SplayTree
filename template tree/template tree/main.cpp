#include "splaytree.h"

typedef Node<Node<Nil, Nil, Const<int, 5>>, Node<Nil, Nil, Const<int, 8>>, Const<int, 6>> tree;

int main(){
	typedef find<insert<tree, Const<int, 21>>::result, Const<int, 21>>::result ans;
	print_value<ans::data>::print();
	system("pause");
	return 0;
}