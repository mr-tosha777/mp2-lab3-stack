#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

const int MAX_STACK_SIZE = 10000; // Максимальный размер стека

template<typename T>
class TStack
{
private:
    size_t topIndex; // Индекс вершины (количество элементов в стеке)
    size_t capacity; // Сколько всего памяти выделено
    T* pMem;         // Указатель на массив

    // 0. Метод для расширения памяти (если место кончается, создаём массив в 2 раза больше и копируем туда старые данные)
    void Resize(size_t newCapacity)
    {
        T* newMem = new T[newCapacity];
        for (size_t i = 0; i < topIndex; i++)
            newMem[i] = pMem[i];
        delete[] pMem;
        pMem = newMem;
        capacity = newCapacity;
    }

public:
    // 1. Конструктор
    TStack(size_t size = 10) : topIndex(0), capacity(size)
    {
        if (size == 0 || size > MAX_STACK_SIZE)
            throw out_of_range("Stack size should be > 0 and <= MAX_STACK_SIZE");
        pMem = new T[capacity];
    }

    // 2. Конструктор копирования
    TStack(const TStack& s) : topIndex(s.topIndex), capacity(s.capacity)
    {
        pMem = new T[capacity];
        for (size_t i = 0; i < topIndex; i++)
            pMem[i] = s.pMem[i];
    }

    // 3. Конструктор перемещения
    TStack(TStack&& s) noexcept : topIndex(s.topIndex), capacity(s.capacity), pMem(s.pMem)
    {
        s.topIndex = 0;
        s.capacity = 0;
        s.pMem = nullptr;
    }

    // 4. Деструктор
    ~TStack()
    {
        delete[] pMem;
    }

    // 5. Копирующее присваивание
    TStack& operator=(const TStack& s)
    {
        if (this == &s)
            return *this;

        delete[] pMem;

        topIndex = s.topIndex;
        capacity = s.capacity;
        pMem = new T[capacity];

        for (size_t i = 0; i < topIndex; i++)
            pMem[i] = s.pMem[i];

        return *this;
    }

    // 6. Перемещающее присваивание
    TStack& operator=(TStack&& s) noexcept
    {
        if (this == &s)
            return *this;

        delete[] pMem;

        topIndex = s.topIndex;
        capacity = s.capacity;
        pMem = s.pMem;

        s.topIndex = 0;
        s.capacity = 0;
        s.pMem = nullptr;

        return *this;
    }

    // 7. Получить текущий размер (сколько элементов сейчас)
    size_t size() const noexcept
    {
        return topIndex;
    }

    // 8. Проверить на пустоту
    bool empty() const noexcept
    {
        return topIndex == 0;
    }

    // 9. Добавить элемент (Push)
    void push(const T& val)
    {
        if (topIndex >= MAX_STACK_SIZE)
            throw length_error("Stack is full");

        if (topIndex == capacity)
            Resize(capacity * 2); // Если памяти нет — расширяем в 2 раза

        pMem[topIndex] = val;
        topIndex++;
    }

    // 10. Удалить элемент (Pop)
    void pop()
    {
        if (empty())
            throw out_of_range("Stack is empty");
        topIndex--;
    }

    // 11. Посмотреть верхний элемент (не удаляя)
    T& top()
    {
        if (empty())
            throw out_of_range("Stack is empty");
        return pMem[topIndex - 1];
    }

    // Константная версия top (для чтения)
    const T& top() const
    {
        if (empty())
            throw out_of_range("Stack is empty");
        return pMem[topIndex - 1];
    }

    // 12. Очистить стек
    void clear()
    {
        topIndex = 0;
    }
};

#endif