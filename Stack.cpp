// This program defines a stack

#include <iostream>
#include <string>

template <typename Elem>
class Stack
{
private:
    void operator = (const Stack&) {}
    Stack(const Stack&) {}

public:
    Stack() {}
    virtual ~Stack() {}

    virtual void clear() = 0;
    virtual void push(const Elem&) = 0;
    virtual Elem pop() = 0;
    virtual const Elem& topValue() const = 0;
    virtual int length() const = 0;
};

void Assert(bool print, std::string message);
bool correctOrder(char orderString[], int stringLength);

class AStack : public Stack<char>
{
private:
    int maxSize;
    int top;
    char* listArray;

public:
    AStack(int size = 255)
    {
        maxSize = size;
        top = 0;
        listArray = new char[size];
    }

    ~AStack()
    {
        delete[] listArray;
    }

    void clear()
    {
        top = 0;
    }

    void push(const char& it)
    {
        Assert(top != maxSize, "Stack is full");
        listArray[top++] = it;
    }

    char pop()
    {
        Assert(top != 0, "Stack is empty");
        return listArray[--top];
    }

    const char& topValue() const
    {
        Assert(top != 0, "Stack is empty");
        return listArray[top - 1];
    }

    int length() const
    {
        return top;
    }

};



int main()
{
    char exampleStringA[] = "[()]{}{[()()]()}";
    char exampleStringB[] = "[(])";

    std::cout << "Example String A: " << exampleStringA << std::endl;
    std::cout << "Output: ";
    if (correctOrder(exampleStringA, 16))
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;

    std::cout << std::endl;

    std::cout << "Example String B: " << exampleStringB << std::endl;
    std::cout << "Output: ";
    if (correctOrder(exampleStringB, 16))
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;
}

void Assert(bool print, std::string message)
{
    if (!print)
        throw message;
}

bool correctOrder(char orderString[], int stringLength)
{
    char orderChars[6] = { '(', ')', '[', ']', '{', '}'};
    AStack determineStack;
    char poppedChar = ' ';
    
    for (int i = 0; i < stringLength; i++)
    {
        if (orderString[i] == orderChars[0] || orderString[i] == orderChars[2] ||
            orderString[i] == orderChars[4])
        {
            try 
            {
                determineStack.push(orderString[i]);
            }
            catch (std::string message)
            {
                std::cout << message << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (orderString[i] == orderChars[1] || orderString[i] ==
            orderChars[3] || orderString[i] == orderChars[5])
        {
            try
            {
                poppedChar = determineStack.pop();
            }
            catch (std::string message)
            {
                std::cout << message << std::endl;
                exit(EXIT_FAILURE);
            }

            if (orderString[i] == orderChars[1] && poppedChar != orderChars[0])
                return false;
            else if (orderString[i] == orderChars[3] && poppedChar != orderChars[2])
                return false;
            else if (orderString[i] == orderChars[5] && poppedChar != orderChars[4])
            {
                return false;
            }
        }

        else
        {
            std::cout << "The string must only contain '{}[]()' characters"
                << std::endl;
            return false;
        }
    }

    return true;
}