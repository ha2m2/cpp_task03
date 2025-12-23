#include <string>
#include <iostream>

// Item class 정의
class Item
{
public:
    Item() : name_(""), price_(0) {}

    // 각 멤버 변수를 세팅
    Item(const std::string& name, int price) : name_(name), price_(price) {}

    const std::string& GetName() const
    {
        return name_;
    }

    int GetPrice() const
    {
        return price_;
    }

    void Clear()
    {
        name_ = "";
        price_ = 0;
    }

    // 정보를 출력하는 멤버 함수
    void PrintInfo() const
    {
        std::cout << "[이름: " << name_ << ", 가격: " << price_ << "G]\n";
    }

private:
    std::string name_;
    int price_;
};

// Inventory<T> class 정의
template <typename T>
class Inventory
{
public:
    // 동적 배열 생성
    Inventory(int capacity = 10) : size_(0)
    {
        capacity_ = capacity > 0 ? capacity : 1;
        pItems_ = new T[capacity_];
    }

    // 동적 배열 해제
    ~Inventory()
    {
        if (pItems_ != nullptr)
        {
            delete[] pItems_;
            pItems_ = nullptr;
        }
    };

    // size_++을 활용하여 아이템을 배열에 배치
    // - 예외처리 : capacity_를 초과한다면?
    void AddItem(const T& item)
    {
        if (size_ >= capacity_)
        {
            std::cout << "인벤토리가 꽉 찼습니다!\n";
            return;
        }
        pItems_[size_++] = item;
        std::cout << "아이템을 추가했습니다!\n";
    };

    // size_--을 활용하여 마지막 아이템을 Clear
    void RemoveLastItem()
    {
        if (size_ < 1)
        {
            std::cout << "인벤토리가 비어있습니다.\n";
            return;
        }
        pItems_[size_--].Clear();
        std::cout << "아이템을 제거했습니다!\n";
    }

    // size_
    int GetSize() const
    {
        return size_;
    }

    // capacity_
    int GetCapacity() const
    {
        return capacity_;
    }

    // size_만큼 for를 돌면서 item의 정보를 출력
    void PrintAllItems() const
    {
        if (size_ < 1)
        {
            std::cout << "인벤토리가 비어있습니다.\n";
            return;
        }

        for (int i = 0; i < size_; i++)
        {
            pItems_[i].PrintInfo();
        }
    }

private:
    T* pItems_;
    int capacity_;
    int size_;
};

int main()
{
    Inventory<Item>* itemInventory = new Inventory<Item>();
    for (int i = 0; i < 11; ++i)
    {
        itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
    }

    itemInventory->PrintAllItems();

    delete itemInventory;

    return 0;
}