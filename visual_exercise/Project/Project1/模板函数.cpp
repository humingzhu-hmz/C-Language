//#include <stdio.h>
////template 定义一个通用类型T，这样在如果想对不同类型的变量进行相同操作时，不必
//// 定义多个逻辑一致的函数并传入不同类型变量进行操作 
//template <typename T>
//void swap(T& a, T& b)//引用传递，将实参与形参绑定在一起，对形参的操作会直接影响实参，非值传递
//{
//	T temp = a;
//	a = b;
//	b = temp;
//}
//int main()
//{
//	int x = 10, y = 20;
//	double m = 1.34, n = 4.33;
//	char ch1 = 'a', ch2 = 'A';
//	fprintf(stdout, "before the exchange:x=%d,y=%d\n", x, y);
//	swap<int>(x, y);//<type>可以省略，编译器会自动推导
//	fprintf(stdout, "\nafter the exchange:x=%d,y=%d\n", x, y);
//	fprintf(stdout, "\nbefore the exchange:m=%lf,n=%lf\n", m, n);
//	swap(m, n);
//	fprintf(stdout, "\nafter the exchange:m=%lf,n=%lf\n", m, n);
//	fprintf(stdout, "\nbefore the exchange:ch1=%c,ch2=%c\n", ch1, ch2);
//	swap(ch1, ch2);
//	fprintf(stdout, "\nafter the exchange:ch1=%c,ch2=%c\n", ch1, ch2);
//	return 0;
//}