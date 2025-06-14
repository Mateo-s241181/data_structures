#ifndef SLL
#define SLL

#include <vector>

template<typename A> struct Element
{

    //an element of a single linked list consists of a value of type A and a pointer to its next element
    A value;
    Element* next;

    //----------------------------------------------------------------------------------------------------
    /// @brief Constructor of an object of type Element (Element of a single linked list)
    Element()
    {
        //Value has the default value of its respective data type
        value = A{};
        next = nullptr;
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    ///@brief Constructor for an Object of type element with an initial value
    Element(A val)
    {
        value = val;
        next = nullptr;
    }

    //----------------------------------------------------------------------------------------------------
    /// @brief Adding an Element to another
    void add_elem(Element* new_el)
    {
        next = new_el;
    }

    //----------------------------------------------------------------------------------------------------
    ///@return the number of elements, that are connected in a chain behind an element
    size_t len()
    {
        if(next == nullptr){
            return 0;
        }

        return 1 + next->len();
    }

};



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



template<typename A> struct sll
{

    //A single linked list is described by a pointer to its first and its last element
    Element<A>* first;
    Element<A>* last;

    Element<A> dummy;


    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor of an object of type sll (single linked list). This function defines, what an empty linked list looks like
    sll()
    {
        dummy = Element<A>();
        first = &dummy;
        last = &dummy;
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /// @return wheter the linked list is empty by definition (contains only a dummy element) 
    bool empty(){
        return first == &dummy && last == &dummy;
    }


    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /// @brief adds an element to the end linked list (infront of the dummy element)
    /// @param new_elem element to be added
    void add_element(Element<A>* new_elem)
    {
        //a new element always points to the dummy
        new_elem->next = &dummy;

        //if the linked list is empty, the new element is both the first and the last
        if(empty()){
            first = new_elem;
            last = new_elem;

            return;
        }

        //if its not empty, the new element is appended to the end
        last->add_elem(new_elem);
        last = new_elem;
    }


    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    ///@return the number of elements in the linked list
    size_t len(){
        return first->len();
    }


    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    ///@brief appends a vector of objects of type A to a linked list
    void append_vector(std::vector<A> v){

        std::vector<Element<A>> elem_vec;

        for(int i = 0; i < v.size(); i++)
        {
            elem_vec.push_back(Element<A>(v[i]));
            add_element(&elem_vec[i]);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    ///@brief Constructor for a linked list with initial values 
    ///@param v vector of values that are to be written into a linked list
    sll(std::vector<A> v)
    {
        dummy = Element<A>();
        first = &dummy;
        last = &dummy;

        append_vector(v);
    }



};







#endif