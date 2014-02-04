#include <iostream>


struct Nil
{
	typedef Nil left;
	typedef Nil right;
	typedef Nil data;
};

template<class Node>
struct is_Nil
{
	static const bool result = false;
};

template<>
struct is_Nil<Nil>
{
	static const bool result = true;
};

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

template<class A, class B>
struct Node_data_is_same
{
	const static bool result = false;
};

template<class Left1, class Right1, class Left2, class Right2, class T, T Data>
struct Node_data_is_same<Node<Left1, Right1, Const<T, Data>>, Node<Left2, Right2, Const<T, Data>>>
{
	const static bool result = true;
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

///////////////ZIG////////////////

template<class X, class P>
struct Zig{};

template<class Left, class Right, class T, T NData, T Data>
struct Zig<Node<Left, Right, Const<T, NData>>, Const<T, Data>>
{
private:
	typedef Node<typename Left::left, Node<typename Left::right, Right, Const<T, NData>>, Const<T, Data>> left_case;
	typedef Node<Node<Left, typename Right::left, Const<T, NData>>, typename Right::right, Const<T, Data>> right_case;
  
public:
	typedef typename IF<!(is_Nil<Left>::result) && Node_data_is_same<Left, Node<Nil, Nil, Const<T, Data>>>::result, left_case,
		typename IF<!(is_Nil<Right>::result) && Node_data_is_same<Right, Node<Nil, Nil, Const<T, Data>>>::result,
		right_case, Node<Left, Right, Const<T, NData>>>::result>::result result;
};

///////////////ZIG-ZIG////////////////

template<class T1, class T2>
struct Zig_zig{};

template<class Left, class Right, class T, T NData, T Data>
struct Zig_zig<Node<Left, Right, Const<T, NData>>, Const<T, Data>>
{
private:
	typedef Node<typename Left::left::left, Node<typename Left::left::right, 
		Node<typename Left::right, Right, Const<T, NData>>, typename Left::data>, Const<T, Data>> left_case;
	typedef Node<Node<Node<Left, typename Right::left, Const<T, NData>>, 
		typename Right::right::left, typename Right::data>, typename Right::right::right, Const<T, Data>> right_case;

public:
	typedef typename IF<!(is_Nil<Left>::result) && !(is_Nil<typename Left::left>::result) && Node_data_is_same<typename Left::left, Node<Nil, Nil, Const<T, Data>>>::result,
		left_case, typename IF<!(is_Nil<Right>::result) && !(is_Nil<typename Right::right>::result) && Node_data_is_same<typename Right::right, Node<Nil, Nil, Const<T, Data>>>::result,
		right_case, Node<Left, Right, Const<T, NData>>>::result>::result result;
};

///////////////ZIG-ZAG////////////////

template<class T1, class T2>
struct Zig_zag{};

template<class Left, class Right, class T, T NData, T Data>
struct Zig_zag<Node<Left, Right, Const<T, NData>>, Const<T, Data>>
{
private:
	typedef Node<Node<typename Left::left, typename Left::right::left, typename Left::data>, 
		Node<typename Left::right::right, Right, Const<T, NData>>, Const<T, Data>> left_case;
	typedef Node < Node<Left, typename Right::left::left, Const<T, NData>>,
		Node<typename Right::left::right, typename Right::right, typename Right::data>, Const < T, Data >> right_case;

public:
	typedef typename IF<!(is_Nil<Left>::result) && !(is_Nil<typename Left::right>::result) && Node_data_is_same<typename Left::right, Node<Nil, Nil, Const<T, Data>>>::result,
		left_case, typename IF<!(is_Nil<Right>::result) && !(is_Nil<typename Right::left>::result) && Node_data_is_same<typename Right::left, Node<Nil, Nil, Const<T, Data>>>::result,
		right_case, Node<Left, Right, Const<T, NData>>>::result>::result result;
};

///////////////SPLAY////////////////

template<class T1, class T2, bool ifRoot = true>
struct splay
{
	typedef Nil result;
};

template<class Left, class Right, class T, T NData, T Data, bool ifRoot>
struct splay<Node<Left, Right, Const<T, NData>>, Const<T, Data>, ifRoot>
{
private:
	typedef typename IF < Data == NData, Node<Left, Right, Const<T, NData>>, 
		typename IF<Data < NData, typename splay<Left, Const<T, Data>, false>::result, typename splay<Right, Const<T, Data>, false>::result>::result>::result rec;
	typedef typename Zig<rec, Const<T, Data>>::result zig_case;
	typedef typename Zig_zig<rec, Const<T, Data>>::result zig_zig_case;
	typedef typename Zig_zag<rec, Const<T, Data>>::result zig_zag_case;

public:
	typedef typename IF<ifRoot, zig_case, typename IF<Node_data_is_same<zig_zig_case, 
		Node<Left, Right, Const<T, Data>>>::result, zig_zig_case, zig_zag_case>::result>::result result;
};



//////////////FIND//////////////////

template<class Node, class Data, bool ifRoot = true>
struct find
{
	typedef Nil result;
};

template<class Left, class Right, class T, T NData, T Data, bool ifRoot>
struct find<Node<Left, Right, Const<T, NData>>, Const<T, Data>, ifRoot>
{
private:
	typedef typename IF < Data == NData, Node<Left, Right, Const<T, NData>>,
		typename IF<Data < NData, typename find<Left, Const<T, Data>, false>::result, typename find<Right, Const<T, Data>>::result>::result>::result rec;

public:
	typedef typename IF<ifRoot && !(is_Nil<rec>::result), splay<Node<Left, Right, Const<T, NData>>, Const<T, Data>>::result, rec>::result result;
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
	typedef typename IF<Data < NData, Node<typename left_case, Right, Const<T, NData>>, Node<Left, typename right_case, Const<T, NData>>>::result result;
};
