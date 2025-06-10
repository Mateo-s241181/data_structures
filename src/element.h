#ifndef ELEMENT
#define ELEMENT


#include <vector>
#include <string>
#include <algorithm>

/// Ein Element eines binären Suchbaumes.
template <typename K, typename V> struct Element {
    
    //Key of the Element
    K key;
    //Value, that is held by the element of the binary tree
    V value;


    Element* parent_ptr;
    //pointers, that point to the children of the element
    Element* left_child_ptr;
    Element* right_child_ptr;

    //values for tracking the topology of the tree
    int balance_factor;
    size_t depth;

    Element(K k, V v){

        key = k;
        value = v;
        parent_ptr = nullptr;
        left_child_ptr = nullptr;
        right_child_ptr = nullptr;

        //balance_factor und depth by default 0
        balance_factor = 0;
        depth = 0;
    }

    bool is_leaf(){
        return left_child_ptr == nullptr && right_child_ptr == nullptr;
    }

    
    /// @brief The function add_element adds a given element to the binary tree. By comparing the key of new_element to the key of first_element, it determines, whether it should be placed on the left or the right side of the tree and places it at the bottom.
    /// @param new_element Element, that needs to be added to the binary tree
    /// @param first_element pointer to some element of the binary tree. If you call the function, you should always enter a pointer to the root of your binary tree.
    void add_element(Element *new_element)
    {
        //Compare keys of both elements to each other and determine, whether new_element shound be placed on the right side of the binary tree
        bool place_on_right_side = new_element->key > key; 

        if (place_on_right_side){

            //check, if the element, the function was called from has an element linked to it on the right side
            if (right_child_ptr == nullptr){

                new_element->parent_ptr = this;
                right_child_ptr = new_element;
                return;
            }

            //Move one layer down on the right side
            right_child_ptr->add_element(new_element);

        } else {

            if (left_child_ptr == nullptr){

                new_element->parent_ptr = this;
                left_child_ptr = new_element;
                return;
            }

            left_child_ptr->add_element(new_element);
        }
    }


    /// @brief Adds a vector of elements into a binary tree, utilizing add_element.
    /// @param elem_vec Vector of Element
    void create_binary_tree(std::vector<Element>* elem_vec_ptr){

        if(elem_vec_ptr->empty()){
            return;
        }

        //range through the original vector. No copy of the vector is created, because the memory adresses of the elements are important.
        for(size_t i = 0; i < elem_vec_ptr->size(); i++){

            add_element(&(elem_vec_ptr->at(i)));
        }

        
    }


    //TODO: Size function definition in cpp file

    /// @returns Returns the number of elements in the tree with the given root.
    size_t size(){
        
        size_t sum {0};

        if (left_child_ptr == nullptr && right_child_ptr == nullptr){
            return 1 + sum;
        }
            
        if (left_child_ptr == nullptr && right_child_ptr != nullptr){
            return 1 + right_child_ptr->size();
        }
            
        if (left_child_ptr != nullptr && right_child_ptr == nullptr){
            return 1 + left_child_ptr->size();
        }
        
        return 1 + left_child_ptr->size() + right_child_ptr->size();
    }


    /// @brief Reads out the pointers to the elements of a binary tree in order, meaning from left to root to right.
    /// @return Vector of pointers to the sorted elements
    std::vector<Element*> in_order(){

        std::vector<Element*> vec {};

        //if the root is a leaf, append directly
        if (left_child_ptr == nullptr && right_child_ptr == nullptr){
            vec.push_back(this);
            return vec;
        }

        

        //append the left
        if(left_child_ptr != nullptr){
            for(auto el: left_child_ptr->in_order()){
                vec.push_back(el);
            }
        }

        //append the root
        vec.push_back(this);

        //append the right
        if(right_child_ptr != nullptr){
            for(auto el: right_child_ptr->in_order()){
                vec.push_back(el);
            }
        }

        return vec;
    }

    /// @brief Deletes an Element out of the binary tree, while making sure the basic structure of the binary tree is still valid
    void delete_element(){


        //check if element is the root of the tree, if yes, delete the element completely
        if(is_leaf() && parent_ptr == nullptr){
            //the memory-adress of the root changes to a nullptr
            return;
        }

        //Check if element is a leaf and delete element out of the tree, by making the pointer to it a nullptr
        if(is_leaf() && parent_ptr != nullptr){
            
            if(parent_ptr->left_child_ptr == this){
                parent_ptr->left_child_ptr = nullptr;
            }
            if(parent_ptr->right_child_ptr == this){
                parent_ptr->right_child_ptr = nullptr;
            }
            return;
        }

        //store the in_order vector in a seperate variable to insure the code uses the same instance of it everytime
        std::vector<Element*> v_ordered = in_order();

        //iterator to the element, which needs to be deleted
        auto del_it = std::find(v_ordered.begin(), v_ordered.end(), this);


        //if there is no smaller element, replace the content with the next biggest
        if(left_child_ptr == nullptr && std::next(del_it) != in_order().end()){

            //Find pointer to the next biggest element
            Element* next_biggest = *(std::next(del_it));

            //replace contents of element to delete
            key = next_biggest->key;
            value = next_biggest->value;

            //delete next biggest element by making the pointer from its parent to it a nullptr
            if(next_biggest->parent_ptr->left_child_ptr == next_biggest){
                next_biggest->parent_ptr->left_child_ptr = nullptr;
            }
            if(next_biggest->parent_ptr->right_child_ptr == next_biggest){
                next_biggest->parent_ptr->right_child_ptr = nullptr;
            }
            return;
        }

        //by default, replace the contents with the next smallest element
        if(del_it != in_order().begin()){
            //Find pointer to the next smallest element
            Element* next_smallest = *(std::prev(del_it));

            //replace contents of element to delete
            key = next_smallest->key;
            value = next_smallest->value;

            //delete next smallest element by making the pointer from its parent to it a nullptr
            if(next_smallest->parent_ptr->left_child_ptr == next_smallest){
                next_smallest->parent_ptr->left_child_ptr = nullptr;
            }
            if(next_smallest->parent_ptr->right_child_ptr == next_smallest){
                next_smallest->parent_ptr->right_child_ptr = nullptr;
            }
        }
    }

    /// @brief Searches for the longest way from the given element to a leaf of the tree
    /// @return The number of steps the algorithm takes to get to a leaf 
    size_t get_height(){

        if(this == nullptr){
            return 0;
        }

        size_t height = 1;

        size_t steps = 0;

        if(is_leaf()){

            //if the steps to the leaf element are bigger than height, the number of steps should bei the new height
            return steps > height ? steps : height;
        }

        //step through every element form left to right just like in previos functions

        //if there is no left element, step to the right
        if(left_child_ptr == nullptr){
            return 1 + right_child_ptr->get_height();
        }

        //if there is no right element, step to the left
        if(right_child_ptr == nullptr){
            return 1 + left_child_ptr->get_height();
        }

        //check which way the height is bigger and return the bigger one
        return left_child_ptr->get_height() > right_child_ptr->get_height() ? 1 + left_child_ptr->get_height() : 1 + right_child_ptr->get_height();

    }


    int get_balancefactor() {

        if(is_leaf()){
            return 0;
        }

        //elements on the right get counted positively
        if(left_child_ptr == nullptr) {
            return right_child_ptr->get_height();
        }

        //elements on the left are counted negatively
        if(right_child_ptr == nullptr){
            return - left_child_ptr->get_height();
        }

        return right_child_ptr->get_height() - left_child_ptr->get_height(); 

    }

    void calculate_balancefactors() {

        std::vector<Element*> ordered_vec = in_order();

        //range through the in_order vector (consists of pointer to the elements)
        for(int i = 0; i < ordered_vec.size(); i++){
            
            ordered_vec[i]->balance_factor = ordered_vec[i]->get_balancefactor();
        }

    }

    void rotate(){


        /*
        TODO:

        Implement Tree-Height tracking
        Implement Tree-Rotation-Algorithm
        */

    }
};

#endif