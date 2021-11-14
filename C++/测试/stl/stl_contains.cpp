#include "stl_contains.h"

void string_test()
{
    cout << "string: " << endl;
    string str1{'a', 'b'}, str2;
        cout << str1 << " ";
    str1.assign("abcd");    //赋值
        cout << str1 << " ";
    str1 += "efgh";            //连接1
        cout << str1 << " ";
    str1.append("ijkl");      //连接2
        cout << str1 << " ";
    int pos = str1.find("cde");        //查找子串第一次出现位置
        cout << pos << " ";
    pos = str1.rfind("cde");      //查找子串最后一次出现的位置
        cout << pos << " ";
    str1.replace(0, 3, "guo");             //替换0-2位置的字符串
        cout << str1 << " ";

    str2 = str1.substr(0, 3);       //切片操作，返回0-2位置的子串
        cout << str2 << " ";
    int ret = str1.compare(str2);   //字符串比较 相等返回0
        cout << ret << " ";

    str1.at(0) = 'j';       //局部字符修改及访问
    str1[0] = 'j';
    cout << str1.at(0) << str1[0] << " ";

    str1.insert(0, "ZKX");      //插入字符串
        cout << str1 << " ";
    str1.erase(0, 3);        //删除0-2（3个）位置字符
        cout << str1 << " ";
    cout << endl;
}

void vector_test()
{
    cout << "vector: " << endl;
    vector<int> v1{1,2,3}, v2;
    v1.push_back(4);
    v1.push_back(5);    //尾插入元素
    v1.pop_back();          //尾删
    v1.insert(v1.end(), 5);        //插入  必须迭代器来指示位置（需要end指向的一个空位）
    v1.erase(v1.end()-1); // 删除 必须迭代器来指示位置   注意-1才是指向末尾元素（需要确定元素的地址，而不是空）
//v1.erase(v1.begin(), v1.end());
    for_each(v1.begin(), v1.end(), [](int& it){ cout << it << " ";} );//遍历1 配合了lambda
	/*
	for ( vector<int>::iterator it = v1.begin(); it != v1.end(); it++ ) {
		cout << *it << " ";         //遍历2
	}
	*/
	v2.assign(v1.begin(), v1.end());    //赋值
    for_each(v2.begin(), v2.end(), [](int& it){ cout << it << " ";} );
    v2.clear();         //清空容器

    cout << v1.empty() << " " << v1.size()
                    << "/"  << v1.capacity() << " ";    //容器是否空（非空0），元素个数,容量

    v1.resize(10, 0);   //重设容器大小，空位置初始化为0（并不是空的，此时容器是满的）
        cout << v1.size() << "/" << v1.capacity() << " ";

    cout << v1.front() << " " << v1.back() << " ";  //首元素，尾元素
    cout << v1.at(0) << " " << v1[0] << " ";  //下标访问

    v2.swap(v1);        //容器交换
    for_each(v1.begin(), v1.end(), [](int& it){ cout << it << " ";} );//交换后v1为空
    v1.swap(v2);

    v1.reserve(100);      //设置容器大小，只是预留空间（不初始化）
        cout << v1.size() << "/" << v1.capacity() << " ";
	cout << endl;
}

void deque_test()
{
    cout << "deque双端数组: " << endl;
    deque<int> d1{4,2,1,3};
    sort(d1.begin(), d1.end());     //sort排序算法
    cout << d1[0] << " " <<  d1.at(0) << endl;
    cout << d1.front() << " " <<  d1.back() << endl;


    d1.push_back(5);        //尾插
    d1.pop_back();          //尾删
    d1.push_front(0);       //相比于Vector独有的，头部插入元素
    d1.pop_front();         //头删
    d1.assign( d1.begin(), d1.end() );//赋值
    d1.assign( 5, 1);   //把5个1赋值给d1
    d1.empty();
    d1.size();
    d1.resize(10, 0);
    d1.insert(d1.begin(), 1);
    d1.clear();
    d1.erase(d1.begin());
    d1.erase(d1.begin(), d1.end());
}

void stack_test()
{
	cout << "stack: " << endl;
    stack<int> st1;        //不可直接赋值初始化，只能使用push入栈元素或者使用已存在的栈对象初始化
    st1.push(1);     //入栈
    st1.push(2);
    st1.push(3);
    cout << st1.size() << " ";       //元素个数
    st1.pop();       //出栈栈顶元素
    cout << st1.empty() << " " << st1.size() << " "  << st1.top() << " ";//栈顶元素
    cout << endl;
}

void queue_test()
{
	cout << "queue: " << endl;
    queue<string> q1;//不可直接赋值初始化，只能使用push入队元素或者使用已存在的队对象初始化
    q1.push("sb1");     //入队
    q1.push("sb2");
    q1.push("sb3");
    cout << q1.size() << " ";           //元素个数
    q1.pop();       //移除队头元素
    cout << q1.empty() << " " << q1.size() << " "
                << q1.front() << " " << q1.back() << " "; //队头，队尾元素
    cout << endl;
}

void list_test()
{
    cout << "list: " << endl;
    list<int> L1{1,2,3}, L2;
    L1.push_front(4);      //头插
    L1.pop_front();       //头删
    L1.push_back(4);    //尾插
    L1.pop_back();       //尾删

    L1.assign( L1.begin(), L1.end() );//赋值
    //L1.assign( 5, 1);   //把5个1赋值给d1
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );//遍历 配合了lambda

    list<int>::iterator it = L1.begin();    //链表迭代器定义,可以++，但不可以+n
    L1.insert(++it, 0);     //位置插入元素0
    L1.erase(--it);       //位置删除
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );//遍历 配合了lambda

    L1.remove(1);       //移除容器中的所有1元素
    cout << L1.front() << " " << L1.back() << " ";  //表头，表尾元素，不支持at和[]访问元素

    L1.reverse();   //反转链表
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );
    L1.sort();  //链表元素排序,从小到大
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );

    L2.swap(L1);    //交换
    cout << L2.empty() << " " << L2.size() << " ";
    L2.resize(10, 0);       //重设容器的长度为num
    L2.clear();             //移除容器的所有数据

    cout << endl;
}

void set_test()
{
    cout << "set: " << endl;
    set<int> s1{1,5,4,3,2},s2;  //set容器内部会默认对元素进行 小到大 的排序
    s1.insert(1);   //相同元素会覆盖
    cout << s1.empty() << " " << s1.size() << " ";
    s2.swap(s1);        //交换
    s2.erase(s2.begin());       //删除

    for (set<int>::iterator it = s2.begin(); it != s2.end(); it++) {
		cout << *it << " "; //好像不支持for_each遍历，自己用迭代器  遍历
	}

    set<int>::iterator pos = s2.find(5);    //查找元素5，并返回其迭代器
    if(pos != s2.end())
        cout << *pos << " ";

    int num = s2.count(2);        //统计元素个数（由于set无重复元素，只会返回0/1）
        cout << num << " ";

    s2.clear();

    multiset<int> ms1;      //multiset 可以插入重复元素
    ms1.insert(2);
    ms1.insert(2);
    num = ms1.count(2);
        cout << num << " ";

    //排序，使用仿函数重载()，来指定排序规则
    set<int, CompareReg1> s3;
    s3.insert(1212);
    s3.insert(7);
    s3.insert(21);
	for (set<int, CompareReg1>::iterator it = s3.begin(); it != s3.end(); it++) {
		cout << *it << " ";
	}

    cout << endl;
}

void map_test()
{
    cout << "map: " << endl;
    //插曲： pair的使用
    pair<string, int> p1("GuoJian", 22);
    cout << p1.first << " " << p1.second << " ";

    pair<string, int> p2 = make_pair("GuoJian", 22);
    cout << p2.first << " " << p2.second << endl;
    //map
    map<string, int> m1{ {"hp1", 1}, {"hp2", 2} }, m2;      //不允许key重复，若重复key，后写入的不会生效
    m1.insert( pair<string, int>("hp3", 3) );       //插入
    m1.insert( make_pair("hp4", 4) );

    for (map<string, int>::iterator it = m1.begin(); it != m1.end(); it++)   //遍历，不支持for_each
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}
    m1.swap(m2);        //交换
    cout << m2.empty() << " " << m2.size() << endl;

    m2.erase( m2.begin() );       //以键 删除
    m2.erase( "hp2" );            //以键 删除
    for (map<string, int>::iterator it = m2.begin(); it != m2.end(); it++)   //遍历，不支持for_each
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}

    map<string, int>::iterator pos = m2.find("hp3");     //以键查找
    if( pos != m2.end() )
            cout << "key = " << (*pos).first << " value = " << (*pos).second << endl;
    int num = m2.count("hp3");      //统计key为hp3的元素个数
            cout << num << endl;

    m2.clear();
    //根据key进行排序，利用仿函数改变排序规则
    map<string, int, CompareReg2> m3{ {"0", 1} };
	m3.insert( make_pair("1", 10) );
	m3.insert( make_pair("2", 20) );
	m3.insert( make_pair("3", 30) );

	for ( map<string, int, CompareReg2>::iterator it = m3.begin(); it != m3.end(); it++ ) {
		cout << "key: " << it->first << " value: " << it->second << endl;
	}


}


