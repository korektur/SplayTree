#include <iostream>


struct Nil{};

template<class T, T Data>
struct Const{};

template<bool Cond, class Then, class Else>
struct IF{};

template<class Then, class Else>
struct IF<true, Then, Else>
{
	typedef Then result;
};

template<class Then, class Else>
struct IF<false, Then, Else>
{
	typedef Else result;
};

template<class Left, class Right, class Data>
struct Node
{
	typedef Left left;
	typedef Right right;
	typedef Data data;
};

//////////////Print/////////////////

template<class T>
struct print_value{
	static void print()
	{
		std::cout << "Null" << std::endl;
	}
};

template<class T, T Data>
struct print_value<Const<T, Data>>
{
	static void print() 
	{
		std::cout << Data << std::endl;
	}
};


//////////////FIND//////////////////

template<class Node, class Data>
struct find
{};

template<class Data>
struct find<Nil, Data>
{
	typedef Nil result;
};

template<class Left, class Right, class T, T NData, T Data>
struct find<Node<Left, Right, Const<T, NData>>, Const<T, Data>>
{
private:
	typedef typename find<Left, Const<T, Data>>::result left_case;
	typedef typename find<Right, Const<T, Data>>::result right_case;
	
public:
	typedef typename IF<Data == NData, Node<Left, Right, Const<T, NData>>, typename IF<Data <= NData, left_case, right_case>::result>::result result;
};

template<class Right, class T, T NData, T Data>
struct find<Node<Nil, Right, Const<T, NData>>, Const<T, Data>>
{
private:
	typedef typename find<Right, Const<T, Data>>::result right_case;

public:
	typedef typename IF<Data == NData, Node<Nil, Right, Const<T, NData>>, typename IF<Data <= NData, Nil, right_case>::result>::result result;
};

template<class Left, class T, T NData, T Data>
struct find <Node<Left, Nil, Const<T, NData>>, Const<T, Data>>
{
private:
	typedef typename find<Left, Const<T, Data>>::result left_case;
	
public:
	typedef typename IF<Data == NData, Node<Left, Nil, Const<T, NData>>, typename IF<Data <= NData, left_case, Nil>::result>::result result;
};

template<class T, T NData, T Data>
struct find<Node<Nil, Nil, Const<T, NData>>, Const<T, Data>>
{
	typedef typename IF<Data == NData, Node<Nil, Nil, Const<T, NData>>, Nil>::result result;
};


//////////////INSERT//////////////////

template<class Node, class Data>
struct insert{};

template<class T, T Data>
struct insert<Nil, Const<T, Data>>
{
	typedef Node<Nil, Nil, Const<T, Data>> result;
};

template<class Left, class Right, class T, T NData, T Data>
struct insert<Node<Left, Right, Const<T, NData>>, Const<T, Data>>
{
private:
	typedef typename insert<Left, Const<T, Data>>::result left_case;
	typedef typename insert<Right, Const<T, Data>>::result right_case;

public:
	typedef typename IF<Data <= NData, Node<typename left_case, Right, Const<T, NData>>, Node<Left, typename right_case, Const<T, NData>>>::result result;
};
