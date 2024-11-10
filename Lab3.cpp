#include<iostream>

#include "Test.h"
#include "Sequence.h"

#include "Containers.h"

int main() {
    std::cout << "Insert Sequence type:\n"
        "1. Array\n"
        "2. LinkedList\n"
        "3. Containers\n"
        ;
    int type;
    std::cin >> type;
    if (type < 3) {
        Sequence<int>* seq;
        if (type == 1) {
            seq = new ArraySequence<int>;
        }
        else {
            seq = new LinkedListSequence<int>;
        }
        while (true) {
            std::cout << "Choose option:\n"
                "1. Insert in back\n"
                "2. Insert in front\n"
                "3. Insert at pos\n"
                "4. Show array\n"
                "5. Test\n"
                "6. Exit\n";
            std::cin >> type;
            if (type == 1) {
                std::cout << "insert value\n";
                int number;
                std::cin >> number;
                seq->Append(number);
                continue;
            }
            if (type == 2) {
                std::cout << "insert value\n";
                int number;
                std::cin >> number;
                seq->Prepend(number);
                continue;
            }
            if (type == 3) {
                std::cout << "insert index\n";
                size_t index;
                std::cin >> index;
                std::cout << "insert value\n";
                int number;
                std::cin >> number;
                seq->InsertAt(number, index);
                continue;
            }
            if (type == 4) {
                for (size_t i = 0; i < seq->GetSize(); ++i) {
                    std::cout << seq->Get(i) << " ";
                }
                std::cout << "\n";
                continue;
            }
            if (type == 5) {
                Test();
                continue;
            }
            if (type == 6) {
                delete seq;
                return 0;
            }
        }
    }
    else if (type == 3) {
        std::cout << "Choose Container:\n"
            "1. Queue\n"
            "2. Stack\n"
            "3. PriorityQueue\n"
            "4. Deque\n"
            "5. Test all\n"
            "6. Exit\n"
            ;
        std::cin >> type;
        if (type == 1) {
            Queue<int> queue;
            while (true) {
                std::cout <<
                    "Choose option:\n"
                    "1. Insert \n"
                    "2. Check front\n"
                    "3. Erase\n"
                    "4. Test\n"
                    "5. Exit\n";
                std::cin >> type;
                if (type == 1) {
                    std::cout << "insert value\n";
                    int value;
                    std::cin >> value;
                    queue.Push(value);
                    continue;
                }
                if (type == 2) {
                    std::cout << queue.Front() << std::endl;
                    continue;
                }
                if (type == 3) {
                    queue.Pop();
                    continue;
                }
                if (type == 4) {
                    TestQueue();
                    continue;
                }
                if (type == 5) {
                    return 0;
                }
            }
        }
        if (type == 2) {
            Stack<int> stack;
            while (true) {
                std::cout <<
                    "Choose option:\n"
                    "1. Insert \n"
                    "2. Check front\n"
                    "3. Erase\n"
                    "4. Test\n"
                    "5. Exit\n";
                std::cin >> type;
                if (type == 1) {
                    std::cout << "insert value\n";
                    int value;
                    std::cin >> value;
                    stack.Push(value);
                    continue;
                }
                if (type == 2) {
                    std::cout << stack.Front() << std::endl;
                    continue;
                }
                if (type == 3) {
                    stack.Pop();
                    continue;
                }
                if (type == 4) {
                    TestStack();
                    continue;
                }
                if (type == 5) {
                    return 0;
                }
            }
        }
        if (type == 3) {
            PriorityQueue<int, int> pqueue;
            while (true) {
                std::cout <<
                    "Choose option:\n"
                    "1. Insert \n"
                    "2. Check top\n"
                    "3. Erase\n"
                    "4. Check Size\n"
                    "5. Test\n"
                    "6. Exit\n";
                std::cin >> type;
                if (type == 1) {
                    std::cout << "insert key\n";
                    int key;
                    std::cin >> key;
                    std::cout << "insert value\n";
                    int value;
                    std::cin >> value;
                    pqueue.Push(key, value);
                    continue;
                }
                if (type == 2) {
                    std::cout << pqueue.Top().first << " " << pqueue.Top().second << std::endl;
                    continue;
                }
                if (type == 3) {
                    pqueue.Pop();
                    continue;
                }
                if (type == 4) {
                    std::cout << "Size is: " << pqueue.Size() << std::endl;
                    continue;
                }
                if (type == 5) {
                    TestPriorityQueue();
                    continue;
                }
                if (type == 6) {
                    return 0;
                }
            }
        }
        if (type == 4) {
            BlockedDeque<int> queue;
            while (true) {
                std::cout <<
                    "Choose option:\n"
                    "1. Insert back\n"
                    "2. Insert front\n"
                    "3. Check back\n"
                    "4. Check front\n"
                    "5. Erase back\n"
                    "6. Erase front\n"
                    "7. Test\n"
                    "8. Exit\n";
                std::cin >> type;
                if (type == 1) {
                    std::cout << "insert value\n";
                    int value;
                    std::cin >> value;
                    queue.PushBack(value);
                    continue;
                }
                if (type == 2) {
                    std::cout << "insert value\n";
                    int value;
                    std::cin >> value;
                    queue.PushFront(value);
                    continue;
                }
                if (type == 3) {
                    std::cout << queue.Back() << std::endl;
                    continue;
                }
                if (type == 4) {
                    std::cout << queue.Front() << std::endl;
                    continue;
                }
                if (type == 5) {
                    queue.PopBack();
                    continue;
                }
                if (type == 6) {
                    queue.PopFront();
                    continue;
                }
                if (type == 7) {
                    TestDeque();
                    continue;
                }
                if (type == 8) {
                    return 0;
                }
            }
        }
    }
    if (type == 5) {
        TestContainers();
    }
}