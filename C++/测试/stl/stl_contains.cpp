#include "stl_contains.h"

void string_test()
{
    cout << "string: " << endl;
    string str1{'a', 'b'}, str2;
        cout << str1 << " ";
    str1.assign("abcd");    //��ֵ
        cout << str1 << " ";
    str1 += "efgh";            //����1
        cout << str1 << " ";
    str1.append("ijkl");      //����2
        cout << str1 << " ";
    int pos = str1.find("cde");        //�����Ӵ���һ�γ���λ��
        cout << pos << " ";
    pos = str1.rfind("cde");      //�����Ӵ����һ�γ��ֵ�λ��
        cout << pos << " ";
    str1.replace(0, 3, "guo");             //�滻0-2λ�õ��ַ���
        cout << str1 << " ";

    str2 = str1.substr(0, 3);       //��Ƭ����������0-2λ�õ��Ӵ�
        cout << str2 << " ";
    int ret = str1.compare(str2);   //�ַ����Ƚ� ��ȷ���0
        cout << ret << " ";

    str1.at(0) = 'j';       //�ֲ��ַ��޸ļ�����
    str1[0] = 'j';
    cout << str1.at(0) << str1[0] << " ";

    str1.insert(0, "ZKX");      //�����ַ���
        cout << str1 << " ";
    str1.erase(0, 3);        //ɾ��0-2��3����λ���ַ�
        cout << str1 << " ";
    cout << endl;
}

void vector_test()
{
    cout << "vector: " << endl;
    vector<int> v1{1,2,3}, v2;
    v1.push_back(4);
    v1.push_back(5);    //β����Ԫ��
    v1.pop_back();          //βɾ
    v1.insert(v1.end(), 5);        //����  �����������ָʾλ�ã���Ҫendָ���һ����λ��
    v1.erase(v1.end()-1); // ɾ�� �����������ָʾλ��   ע��-1����ָ��ĩβԪ�أ���Ҫȷ��Ԫ�صĵ�ַ�������ǿգ�
//v1.erase(v1.begin(), v1.end());
    for_each(v1.begin(), v1.end(), [](int& it){ cout << it << " ";} );//����1 �����lambda
	/*
	for ( vector<int>::iterator it = v1.begin(); it != v1.end(); it++ ) {
		cout << *it << " ";         //����2
	}
	*/
	v2.assign(v1.begin(), v1.end());    //��ֵ
    for_each(v2.begin(), v2.end(), [](int& it){ cout << it << " ";} );
    v2.clear();         //�������

    cout << v1.empty() << " " << v1.size()
                    << "/"  << v1.capacity() << " ";    //�����Ƿ�գ��ǿ�0����Ԫ�ظ���,����

    v1.resize(10, 0);   //����������С����λ�ó�ʼ��Ϊ0�������ǿյģ���ʱ���������ģ�
        cout << v1.size() << "/" << v1.capacity() << " ";

    cout << v1.front() << " " << v1.back() << " ";  //��Ԫ�أ�βԪ��
    cout << v1.at(0) << " " << v1[0] << " ";  //�±����

    v2.swap(v1);        //��������
    for_each(v1.begin(), v1.end(), [](int& it){ cout << it << " ";} );//������v1Ϊ��
    v1.swap(v2);

    v1.reserve(100);      //����������С��ֻ��Ԥ���ռ䣨����ʼ����
        cout << v1.size() << "/" << v1.capacity() << " ";
	cout << endl;
}

void deque_test()
{
    cout << "deque˫������: " << endl;
    deque<int> d1{4,2,1,3};
    sort(d1.begin(), d1.end());     //sort�����㷨
    cout << d1[0] << " " <<  d1.at(0) << endl;
    cout << d1.front() << " " <<  d1.back() << endl;


    d1.push_back(5);        //β��
    d1.pop_back();          //βɾ
    d1.push_front(0);       //�����Vector���еģ�ͷ������Ԫ��
    d1.pop_front();         //ͷɾ
    d1.assign( d1.begin(), d1.end() );//��ֵ
    d1.assign( 5, 1);   //��5��1��ֵ��d1
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
    stack<int> st1;        //����ֱ�Ӹ�ֵ��ʼ����ֻ��ʹ��push��ջԪ�ػ���ʹ���Ѵ��ڵ�ջ�����ʼ��
    st1.push(1);     //��ջ
    st1.push(2);
    st1.push(3);
    cout << st1.size() << " ";       //Ԫ�ظ���
    st1.pop();       //��ջջ��Ԫ��
    cout << st1.empty() << " " << st1.size() << " "  << st1.top() << " ";//ջ��Ԫ��
    cout << endl;
}

void queue_test()
{
	cout << "queue: " << endl;
    queue<string> q1;//����ֱ�Ӹ�ֵ��ʼ����ֻ��ʹ��push���Ԫ�ػ���ʹ���Ѵ��ڵĶӶ����ʼ��
    q1.push("sb1");     //���
    q1.push("sb2");
    q1.push("sb3");
    cout << q1.size() << " ";           //Ԫ�ظ���
    q1.pop();       //�Ƴ���ͷԪ��
    cout << q1.empty() << " " << q1.size() << " "
                << q1.front() << " " << q1.back() << " "; //��ͷ����βԪ��
    cout << endl;
}

void list_test()
{
    cout << "list: " << endl;
    list<int> L1{1,2,3}, L2;
    L1.push_front(4);      //ͷ��
    L1.pop_front();       //ͷɾ
    L1.push_back(4);    //β��
    L1.pop_back();       //βɾ

    L1.assign( L1.begin(), L1.end() );//��ֵ
    //L1.assign( 5, 1);   //��5��1��ֵ��d1
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );//���� �����lambda

    list<int>::iterator it = L1.begin();    //�������������,����++����������+n
    L1.insert(++it, 0);     //λ�ò���Ԫ��0
    L1.erase(--it);       //λ��ɾ��
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );//���� �����lambda

    L1.remove(1);       //�Ƴ������е�����1Ԫ��
    cout << L1.front() << " " << L1.back() << " ";  //��ͷ����βԪ�أ���֧��at��[]����Ԫ��

    L1.reverse();   //��ת����
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );
    L1.sort();  //����Ԫ������,��С����
    for_each(L1.begin(), L1.end(), [](int& it){ cout << it << " ";} );

    L2.swap(L1);    //����
    cout << L2.empty() << " " << L2.size() << " ";
    L2.resize(10, 0);       //���������ĳ���Ϊnum
    L2.clear();             //�Ƴ���������������

    cout << endl;
}

void set_test()
{
    cout << "set: " << endl;
    set<int> s1{1,5,4,3,2},s2;  //set�����ڲ���Ĭ�϶�Ԫ�ؽ��� С���� ������
    s1.insert(1);   //��ͬԪ�ػḲ��
    cout << s1.empty() << " " << s1.size() << " ";
    s2.swap(s1);        //����
    s2.erase(s2.begin());       //ɾ��

    for (set<int>::iterator it = s2.begin(); it != s2.end(); it++) {
		cout << *it << " "; //����֧��for_each�������Լ��õ�����  ����
	}

    set<int>::iterator pos = s2.find(5);    //����Ԫ��5���������������
    if(pos != s2.end())
        cout << *pos << " ";

    int num = s2.count(2);        //ͳ��Ԫ�ظ���������set���ظ�Ԫ�أ�ֻ�᷵��0/1��
        cout << num << " ";

    s2.clear();

    multiset<int> ms1;      //multiset ���Բ����ظ�Ԫ��
    ms1.insert(2);
    ms1.insert(2);
    num = ms1.count(2);
        cout << num << " ";

    //����ʹ�÷º�������()����ָ���������
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
    //������ pair��ʹ��
    pair<string, int> p1("GuoJian", 22);
    cout << p1.first << " " << p1.second << " ";

    pair<string, int> p2 = make_pair("GuoJian", 22);
    cout << p2.first << " " << p2.second << endl;
    //map
    map<string, int> m1{ {"hp1", 1}, {"hp2", 2} }, m2;      //������key�ظ������ظ�key����д��Ĳ�����Ч
    m1.insert( pair<string, int>("hp3", 3) );       //����
    m1.insert( make_pair("hp4", 4) );

    for (map<string, int>::iterator it = m1.begin(); it != m1.end(); it++)   //��������֧��for_each
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}
    m1.swap(m2);        //����
    cout << m2.empty() << " " << m2.size() << endl;

    m2.erase( m2.begin() );       //�Լ� ɾ��
    m2.erase( "hp2" );            //�Լ� ɾ��
    for (map<string, int>::iterator it = m2.begin(); it != m2.end(); it++)   //��������֧��for_each
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}

    map<string, int>::iterator pos = m2.find("hp3");     //�Լ�����
    if( pos != m2.end() )
            cout << "key = " << (*pos).first << " value = " << (*pos).second << endl;
    int num = m2.count("hp3");      //ͳ��keyΪhp3��Ԫ�ظ���
            cout << num << endl;

    m2.clear();
    //����key�����������÷º����ı��������
    map<string, int, CompareReg2> m3{ {"0", 1} };
	m3.insert( make_pair("1", 10) );
	m3.insert( make_pair("2", 20) );
	m3.insert( make_pair("3", 30) );

	for ( map<string, int, CompareReg2>::iterator it = m3.begin(); it != m3.end(); it++ ) {
		cout << "key: " << it->first << " value: " << it->second << endl;
	}


}


