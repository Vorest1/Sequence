#include<iostream>
#include<cassert>
#include<vector>

#include"Test.h"
#include"Sequence.h"
#include"Containers.h"

class Counter {
public:
    Counter();
    Counter(const Counter& other);
    ~Counter();
    static size_t GetCount();
private:
    static size_t _count;
};

size_t Counter::_count = 0;

Counter::Counter() {
    ++_count;
}

Counter::Counter(const Counter& other) {
    ++_count;
}


Counter::~Counter() {
    --_count;
}

size_t Counter::GetCount() {
    return _count;
}

bool operator<(const Counter& first, const Counter& second) {
    return &first < &second;
}

void TestSequence() {
    TestArraySequence();
    TestLinkedListSequence();
}

void Test() {
    TestDynamicArray();
    TestLinkedList();

    TestSequence();

    TestContainers();
}

void TestContainers() {
    TestQueue();
    TestStack();
    TestPriorityQueue();
    TestDeque();
    TestVector();
}

void TestDynamicArray() {
    std::cout << "Dynamic array tests." << std::endl << std::endl;

    std::cout << "Test1. Array constructor/destructor memory test: ";
    {
        Counter static_array[5];
        DynamicArray<Counter> array(static_array, 5);
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Size constructor memory test: ";
    {
        DynamicArray<Counter> array(5);
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test3. Copy constructor memory test: ";
    {
        DynamicArray<Counter> array(5);
        DynamicArray<Counter> copy(array);
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test4. GetSize test: ";
    {
        DynamicArray<int> array(5);
        int static_array[6];
        DynamicArray<int> array_from_array(static_array, 6);
        DynamicArray<int> copy_array(array_from_array);
        assert(array.GetSize() == 5);
        assert(array_from_array.GetSize() == 6);
        assert(copy_array.GetSize() == 6);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test5. Set and Get test: ";
    {
        DynamicArray<int> array(5);
        array.Set(3, 2);
        bool had_exception = false;
        try {
            array.Set(5, 5);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        assert(array.Get(2) == 3);
        had_exception = false;
        try {
            array.Get(5);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test6. Operator[] test: ";
    {
        DynamicArray<int> array(5);
        array[2] = 3;
        assert(array[2] == 3);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test7. Resize test: ";
    {
        DynamicArray<int> array(5);
        array.Resize(7);
        assert(array.GetSize() == 7);
        array.Set(10, 6);
        assert(array.Get(6) == 10);
    }
    std::cout << "Done" << std::endl;
    std::cout << std::endl;
}

void Equal(const LinkedList<int>& list, int* array) {
    for (size_t i = 0; i < list.GetSize(); ++i) {
        assert(list.Get(i) == array[i]);
    }
}

void Equal(const Sequence<int>& seq, int* array) {
    for (size_t i = 0; i < seq.GetSize(); ++i) {
        assert(seq.Get(i) == array[i]);
    }
}

void TestLinkedList() {
    std::cout << "Linked list tests." << std::endl << std::endl;

    std::cout << "Test1. List constructor/destructor memory test: ";
    {
        Counter static_array[5];
        LinkedList<Counter> list(static_array, 5);
    }
    assert(Counter::GetCount() == 0);
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        LinkedList<int> list(static_array, 5);
        Equal(list, static_array);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Default constructor memory test: ";
    {
        LinkedList<Counter> array();
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test3. Copy constructor memory test: ";
    {
        LinkedList<Counter> array;
        LinkedList<Counter> copy(array);
    }
    assert(Counter::GetCount() == 0);
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        LinkedList<int> list(static_array, 5);
        LinkedList<int> copy(list);
        Equal(copy, static_array);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test4. GetSize test: ";
    {
        LinkedList<int> list;
        int static_array[6];
        LinkedList<int> list_from_array(static_array, 6);
        LinkedList<int> copy_list(list_from_array);
        assert(list.GetSize() == 0);
        assert(list_from_array.GetSize() == 6);
        assert(copy_list.GetSize() == 6);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test5. Get test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        LinkedList<int> list(static_array, 5);
        bool had_exception = false;
        try {
            list.Get(5);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        assert(list.Get(2) == 3);
        assert(list.GetFirst() == 1);
        assert(list.GetLast() == 5);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test6. Last and First test: ";
    {
        DynamicArray<int> array(5);
        array[2] = 3;
        assert(array[2] == 3);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test7. Append and Prepend test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        int static_array_prep[6] = { 0, 1, 2, 3 ,4, 5 };
        int static_array_app[7] = { 0, 1, 2, 3 ,4, 5, 6 };
        LinkedList<int> list(static_array, 5);
        list.Prepend(0);
        Equal(list, static_array_prep);
        list.Append(6);
        Equal(list, static_array_app);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test8. SubList test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        int static_array_sub[3] = { 2, 3, 4 };
        LinkedList<int> list(static_array, 5);
        LinkedList<int>* sub_list = list.GetSubList(1, 3);
        Equal(*sub_list, static_array_sub);
        delete sub_list;
        bool had_exception = false;
        try {
            list.GetSubList(4, 3);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        had_exception = false;
        try {
            list.GetSubList(10, 15);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        {
            Counter static_counter_array[5];
            LinkedList<Counter> list(static_counter_array, 5);
            LinkedList<Counter>* sub = list.GetSubList(0, 2);
            delete sub;
        }
        assert(Counter::GetCount() == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test9. Concat test: ";
    {
        int static_array_first[5] = { 1, 2, 3 ,4, 5 };
        int static_array_second[3] = { 2, 3, 4 };
        int static_array_res[] = { 1, 2, 3, 4, 5, 2, 3, 4 };
        LinkedList<int> first(static_array_first, 5);
        LinkedList<int> second(static_array_second, 3);

        LinkedList<int>* res = first.Concat(&second);
        Equal(*res, static_array_res);
        {
            Counter static_counter_array[5];
            LinkedList<Counter> first(static_counter_array, 5);
            LinkedList<Counter> second(static_counter_array, 3);
            LinkedList<Counter>* res = first.Concat(&second);
            delete res;
        }
        assert(Counter::GetCount() == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << std::endl;
}

void TestArraySequence() {
    std::cout << "Array Sequence tests." << std::endl << std::endl;

    std::cout << "Test1. Array Sequence constructor/destructor memory test: ";
    {
        Counter static_array[5];
        ArraySequence<Counter> list(static_array, 5);
    }
    assert(Counter::GetCount() == 0);
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        ArraySequence<int> list(static_array, 5);
        Equal(list, static_array);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Default constructor memory test: ";
    {
        ArraySequence<Counter> array();
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test3. Copy constructor memory test: ";
    {
        ArraySequence<Counter> array;
        ArraySequence<Counter> copy(array);
    }
    assert(Counter::GetCount() == 0);
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        ArraySequence<int> list(static_array, 5);
        ArraySequence<int> copy(list);
        Equal(copy, static_array);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test4. GetSize test: ";
    {
        ArraySequence<int> list;
        int static_array[6];
        ArraySequence<int> list_from_array(static_array, 6);
        ArraySequence<int> copy_list(list_from_array);
        assert(list.GetSize() == 0);
        assert(list_from_array.GetSize() == 6);
        assert(copy_list.GetSize() == 6);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test5. Get test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        ArraySequence<int> list(static_array, 5);
        bool had_exception = false;
        try {
            list.Get(5);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        assert(list.Get(2) == 3);
        assert(list.GetFirst() == 1);
        assert(list.GetLast() == 5);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test6. Last and First test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        ArraySequence<int> array(static_array, 5);
        array[2] = 3;
        assert(array[2] == 3);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test7. Append and Prepend test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        int static_array_prep[6] = { 0, 1, 2, 3 ,4, 5 };
        int static_array_app[7] = { 0, 1, 2, 3 ,4, 5, 6 };
        ArraySequence<int> list(static_array, 5);
        list.Prepend(0);
        Equal(list, static_array_prep);
        list.Append(6);
        Equal(list, static_array_app);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test8. SubSequence test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        int static_array_sub[3] = { 2, 3, 4 };
        ArraySequence<int> list(static_array, 5);
        Sequence<int>* sub_list = list.GetSubSequence(1, 3);
        Equal(*sub_list, static_array_sub);
        delete sub_list;
        bool had_exception = false;
        try {
            list.GetSubSequence(4, 3);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        had_exception = false;
        try {
            list.GetSubSequence(10, 15);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        {
            Counter static_counter_array[5];
            ArraySequence<Counter> list(static_counter_array, 5);
            Sequence<Counter>* sub = list.GetSubSequence(0, 2);
            delete sub;
        }
        assert(Counter::GetCount() == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test9. Concat test: ";
    {
        int static_array_first[5] = { 1, 2, 3 ,4, 5 };
        int static_array_second[3] = { 2, 3, 4 };
        int static_array_res[] = { 1, 2, 3, 4, 5, 2, 3, 4 };
        ArraySequence<int> first(static_array_first, 5);
        ArraySequence<int> second(static_array_second, 3);

        Sequence<int>* res = first.Concat(&second);
        Equal(*res, static_array_res);
        {
            Counter static_counter_array[5];
            ArraySequence<Counter> first(static_counter_array, 5);
            ArraySequence<Counter> second(static_counter_array, 3);
            Sequence<Counter>* res = first.Concat(&second);
            delete res;
        }
        assert(Counter::GetCount() == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << std::endl;
}

void TestLinkedListSequence() {
    std::cout << "List Sequence tests." << std::endl << std::endl;

    std::cout << "Test1. List Sequence constructor/destructor memory test: ";
    {
        Counter static_array[5];
        LinkedListSequence<Counter> list(static_array, 5);
    }
    assert(Counter::GetCount() == 0);
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        LinkedListSequence<int> list(static_array, 5);
        Equal(list, static_array);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Default constructor memory test: ";
    {
        LinkedListSequence<Counter> array();
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test3. Copy constructor memory test: ";
    {
        LinkedListSequence<Counter> array;
        LinkedListSequence<Counter> copy(array);
    }
    assert(Counter::GetCount() == 0);
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        LinkedListSequence<int> list(static_array, 5);
        LinkedListSequence<int> copy(list);
        Equal(copy, static_array);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test4. GetSize test: ";
    {
        LinkedListSequence<int> list;
        int static_array[6];
        LinkedListSequence<int> list_from_array(static_array, 6);
        LinkedListSequence<int> copy_list(list_from_array);
        assert(list.GetSize() == 0);
        assert(list_from_array.GetSize() == 6);
        assert(copy_list.GetSize() == 6);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test5. Get test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        LinkedListSequence<int> list(static_array, 5);
        bool had_exception = false;
        try {
            list.Get(5);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        assert(list.Get(2) == 3);
        assert(list.GetFirst() == 1);
        assert(list.GetLast() == 5);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test6. Last and First test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        LinkedListSequence<int> array(static_array, 5);
        array[2] = 3;
        assert(array[2] == 3);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test7. Append and Prepend test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        int static_array_prep[6] = { 0, 1, 2, 3 ,4, 5 };
        int static_array_app[7] = { 0, 1, 2, 3 ,4, 5, 6 };
        LinkedListSequence<int> list(static_array, 5);
        list.Prepend(0);
        Equal(list, static_array_prep);
        list.Append(6);
        Equal(list, static_array_app);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test8. SubSequence test: ";
    {
        int static_array[5] = { 1, 2, 3 ,4, 5 };
        int static_array_sub[3] = { 2, 3, 4 };
        LinkedListSequence<int> list(static_array, 5);
        Sequence<int>* sub_list = list.GetSubSequence(1, 3);
        Equal(*sub_list, static_array_sub);
        delete sub_list;
        bool had_exception = false;
        try {
            list.GetSubSequence(4, 3);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        had_exception = false;
        try {
            list.GetSubSequence(10, 15);
        }
        catch (std::out_of_range) {
            had_exception = true;
        }
        assert(had_exception);
        {
            Counter static_counter_array[5];
            LinkedListSequence<Counter> list(static_counter_array, 5);
            Sequence<Counter>* sub = list.GetSubSequence(0, 2);
            delete sub;
        }
        assert(Counter::GetCount() == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test9. Concat test: ";
    {
        int static_array_first[5] = { 1, 2, 3 ,4, 5 };
        int static_array_second[3] = { 2, 3, 4 };
        int static_array_res[] = { 1, 2, 3, 4, 5, 2, 3, 4 };
        LinkedListSequence<int> first(static_array_first, 5);
        LinkedListSequence<int> second(static_array_second, 3);

        Sequence<int>* res = first.Concat(&second);
        Equal(*res, static_array_res);
        {
            Counter static_counter_array[5];
            LinkedListSequence<Counter> first(static_counter_array, 5);
            LinkedListSequence<Counter> second(static_counter_array, 3);
            Sequence<Counter>* res = first.Concat(&second);
            delete res;
        }
        assert(Counter::GetCount() == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << std::endl;
}

void TestQueue() {
    std::cout << "Queue tests." << std::endl << std::endl;

    std::cout << "Test1. Queue memory test: ";
    {
        Queue<Counter> queue;
        queue.Push(Counter());
        queue.Push(Counter());
        queue.Push(Counter());
        queue.Push(Counter());
        queue.Pop();
        queue.Pop();
        queue.Pop();
        queue.Push(Counter());
        queue.Push(Counter());
        queue.Pop();
        queue.Push(Counter());
        queue.Push(Counter());
        queue.Pop();
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Order test: ";
    {
        Queue<int> queue;
        queue.Push(1);
        queue.Push(2);
        queue.Push(3);
        queue.Push(4);
        assert(queue.Front() == 1);
        queue.Pop();
        queue.Pop();
        assert(queue.Front() == 3);
    }
    std::cout << "Done" << std::endl;
    std::cout << std::endl;
}

void TestStack() {
    std::cout << "Stack tests." << std::endl << std::endl;

    std::cout << "Test1. Stack memory test: ";
    {
        Stack<Counter> stack;
        stack.Push(Counter());
        stack.Push(Counter());
        stack.Push(Counter());
        stack.Push(Counter());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        stack.Push(Counter());
        stack.Push(Counter());
        stack.Pop();
        stack.Push(Counter());
        stack.Push(Counter());
        stack.Pop();
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Order test: ";
    {
        Stack<int> stack;
        stack.Push(1);
        stack.Push(2);
        stack.Push(3);
        stack.Push(4);
        assert(stack.Front() == 4);
        stack.Pop();
        stack.Pop();
        assert(stack.Front() == 2);
    }
    std::cout << "Done" << std::endl;
    std::cout << std::endl;
}

void TestPriorityQueue() {
    std::cout << "PriorityQueue tests." << std::endl << std::endl;

    std::cout << "Test1. memory test: ";
    {
        PriorityQueue<Counter, int> heap;
        heap.Push(Counter(), 0);
        heap.Push(Counter(), 0);
        heap.Pop();
        heap.Push(Counter(), 0);
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Default comporator test: ";
    {
        PriorityQueue<int, int> heap;
        heap.Push(3, 1);
        assert(heap.Top().first == 3);
        assert(heap.Top().second == 1);
        heap.Push(5, 2);
        heap.Pop();
        heap.Push(8, 3);
        assert(heap.Top().first == 5);
        assert(heap.Top().second == 2);
        heap.Push(4, 0);
        assert(heap.Top().first == 4);
        assert(heap.Top().second == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test3. Greater comporator test: ";
    {
        PriorityQueue<int, int, std::greater<int>> heap;
        heap.Push(3, 1);
        assert(heap.Top().first == 3);
        assert(heap.Top().second == 1);
        heap.Push(5, 2);
        heap.Pop();
        heap.Push(8, 3);
        assert(heap.Top().first == 8);
        assert(heap.Top().second == 3);
        heap.Push(4, 0);
        assert(heap.Top().first == 8);
        assert(heap.Top().second == 3);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test4. Heap sort test: ";
    {
        std::vector<int> vec = { 4, 2, 8, 1, 7 , 9 , 2 };
        std::vector<int> sorted = { 1, 2, 2, 4, 7, 8, 9 };
        PriorityQueue<int, int> heap;
        for (size_t i = 0; i < vec.size(); ++i) {
            heap.Push(vec[i], vec[i]);
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i] = heap.Top().first;
            heap.Pop();
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            assert(vec[i] == sorted[i]);
        }
    }
    std::cout << "Done" << std::endl;
}

void TestDeque() {
    std::cout << "BlockedDeque tests." << std::endl << std::endl;

    std::cout << "Test1. BlockedDeque memory test: ";
    {
        BlockedDeque<Counter> deque;
        deque.PushFront(Counter());
        deque.PushFront(Counter());
        deque.PushBack(Counter());
        deque.PushFront(Counter());
        deque.PopBack();
        deque.PopBack();
        deque.PopFront();
        deque.PushFront(Counter());
        deque.PushBack(Counter());
        deque.PopFront();
        deque.PushBack(Counter());
        deque.PushFront(Counter());
        deque.PopBack();
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Order test: ";
    {
        BlockedDeque<int> deque;
        deque.PushFront(2);
        deque.PushFront(1);
        deque.PushBack(3);
        deque.PushBack(4);
        assert(deque.Front() == 1);
        deque.PopBack();
        deque.PopFront();
        assert(deque.Back() == 3);
    }
    std::cout << "Done" << std::endl;
    std::cout << std::endl;
}

bool EqualWithPrecission(double first, double second) {
    return first - 0.01 < second && first + 0.01 > second;
}

void TestVector() {
    std::cout << "Vector tests." << std::endl << std::endl;

    std::cout << "Test1. Abs test: ";
    {
        double arr[4] = { 1, 1, 1 ,1 };
        Vector<double> vec(arr, 4);
        assert(EqualWithPrecission(2, vec.Abs()));
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Sum test: ";
    {
        double arr1[4] = { 1, 1, 1 ,1 };
        double arr2[3] = { 2, 3, 4 };
        Vector<double> vec1(arr1, 4);
        Vector<double> vec2(arr2, 3);
        vec1 += vec2;
        assert(EqualWithPrecission(7.14, vec1.Abs()));
    }
    std::cout << "Done" << std::endl;
    std::cout << "Test3. Multyply on number test: ";
    {
        double arr1[4] = { 1, 1, 1 , 1 };
        Vector<double> vec1(arr1, 4);
        vec1 *= 2;
        assert(EqualWithPrecission(4, vec1.Abs()));
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test4. Multyply on vector test: ";
    {
        double arr1[5] = { 1, 2, 3, 4, 5 };
        double arr2[4] = { 3, 4, 5, 6 };
        Vector<double> vec1(arr1, 5);
        Vector<double> vec2(arr2, 4);
        assert(EqualWithPrecission(50, vec1 * vec2));
    }
    std::cout << "Done" << std::endl;
    std::cout << std::endl;
}