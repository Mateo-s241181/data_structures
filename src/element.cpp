#include "element.h"


//----------------------------------------------------------------------------------------------------------------------------------------
//Creating elements out of 2 vectors
//----------------------------------------------------------------------------------------------------------------------------------------

/// @brief Creates a vector of elements with given values and keys
/// @param keys vector of keys
/// @param values vector of values, that needs to be the sae size as keys
/// @return Vector of elements
template <typename K, typename V> std::vector<Element<K, V>> create_elements(std::vector<K> keys, std::vector<V> values){

    if (keys.size() != values.size()){
        return std::vector<Element<K, V>> {};
    }

        
    std::vector<Element<K, V>> elem_vec {};

    //range through one of the vectors backwards, grouping each key and value at position i together in an element
    for(size_t i = 0; i < keys.size(); i++){

        Element<K, V> elem(keys[i], values[i]);

        elem_vec.push_back(elem);
    }

    return elem_vec;
}


// template<typename K, typename V> std::vector<Element<K, V>*> in_order(Element<K, V>* root){

//     std::vector<Element<K, V>*> vec {};

//     //if the root is a leaf, append directly
//     if (root->left_child_ptr == nullptr && root->right_child_ptr == nullptr){
//         vec.push_back(root);
//         return vec;
//     }

//     //append the left
//     if(root->left_child_ptr != nullptr){
//         for(auto el: in_order(root->left_child_ptr)){
//             vec.push_back(el);
//         }
//     }

//     //append the root
//     vec.push_back(root);

//     //append the right
//     if(root->right_child_ptr != nullptr){
//         for(auto el: in_order(root->right_child_ptr)){
//             vec.push_back(el);
//         }
//     }

//     return vec;
// }
