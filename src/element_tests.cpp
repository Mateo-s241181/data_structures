#include <catch2/catch_test_macros.hpp>

#include "element.h"
#include "element.cpp"
#include <iostream>

TEST_CASE("Constructor", "[binary tree]"){

    Element<int, bool> example_elem(42, true);

    REQUIRE(example_elem.key == 42);
    REQUIRE(example_elem.value == true);
    REQUIRE(example_elem.left_child_ptr == nullptr);
    REQUIRE(example_elem.right_child_ptr == nullptr);
}


//----------------------------------------------------------------------------------------------------------------------------------
//Add an element to a binary tree
//----------------------------------------------------------------------------------------------------------------------------------


TEST_CASE("Add element", "[binary tree]"){

    Element<int, bool> root(1, false);

    REQUIRE(root.key == 1);
    REQUIRE(root.value == false);
    REQUIRE(root.left_child_ptr == nullptr);
    REQUIRE(root.right_child_ptr == nullptr);

    Element<int, bool> new_elem(2, true);

    REQUIRE(new_elem.key == 2);
    REQUIRE(new_elem.value == true);
    REQUIRE(new_elem.left_child_ptr == nullptr);
    REQUIRE(new_elem.right_child_ptr == nullptr);

    root.add_element(&new_elem);

    REQUIRE(root.key == 1);
    REQUIRE(root.value == false);
    REQUIRE(root.left_child_ptr == nullptr);
    REQUIRE(root.right_child_ptr == &new_elem);
    REQUIRE(root.right_child_ptr->key == 2);
    REQUIRE(root.right_child_ptr->value== true);
    REQUIRE(root.right_child_ptr->right_child_ptr == nullptr);
    REQUIRE(root.right_child_ptr->left_child_ptr == nullptr);

    Element<int, bool> another_elem(3, false);

    root.add_element(&another_elem);

    REQUIRE(root.key == 1);
    REQUIRE(root.value == false);
    REQUIRE(root.left_child_ptr == nullptr);
    REQUIRE(root.right_child_ptr == &new_elem);
    REQUIRE(root.right_child_ptr->key == 2);
    REQUIRE(root.right_child_ptr->value== true);
    REQUIRE(root.right_child_ptr->right_child_ptr == &another_elem);
    REQUIRE(root.right_child_ptr->left_child_ptr == nullptr);
    REQUIRE(root.right_child_ptr->right_child_ptr->key == 3);
    REQUIRE(root.right_child_ptr->right_child_ptr->value == false);
    REQUIRE(root.right_child_ptr->right_child_ptr->right_child_ptr == nullptr);
    REQUIRE(root.right_child_ptr->right_child_ptr->left_child_ptr == nullptr);

}


//----------------------------------------------------------------------------------------------------------------------------------
//Create Elements out of a list of keys and values
//----------------------------------------------------------------------------------------------------------------------------------


TEST_CASE("Create Elements", "[binary tree]"){

    std::vector<int> keys = {0, 1, 2, 3, 4, 5};
    std::vector<std::string> values = {"a", "b", "c", "d", "e", "f"};

    std::vector<Element<int, std::string>> elem_vec = create_elements(keys, values);

    REQUIRE(elem_vec[0].key == 0);
    REQUIRE(elem_vec[1].key == 1);
    REQUIRE(elem_vec[2].key == 2);
    REQUIRE(elem_vec[3].key == 3);
    REQUIRE(elem_vec[4].key == 4);
    REQUIRE(elem_vec[5].key == 5);

    REQUIRE(elem_vec[0].value == "a");
    REQUIRE(elem_vec[1].value == "b");
    REQUIRE(elem_vec[2].value == "c");
    REQUIRE(elem_vec[3].value == "d");
    REQUIRE(elem_vec[4].value == "e");
    REQUIRE(elem_vec[5].value == "f");

    for(auto el : elem_vec){

        REQUIRE(el.left_child_ptr == nullptr);
        REQUIRE(el.right_child_ptr == nullptr);
    }

    std::vector<int> keys_empty = {};
    std::vector<bool> values_empty = {};

    std::vector<Element<int, bool>> elem_vec_empty = create_elements(keys_empty, values_empty);

    REQUIRE(elem_vec_empty.empty());

    std::vector<int> keys_len = {1, 2, 3};
    std::vector<bool> values_len = {true, false};

    std::vector<Element<int, bool>> elem_vec_len = create_elements(keys_len, values_len);

    REQUIRE(elem_vec_len.empty());
}


//----------------------------------------------------------------------------------------------------------------------------------
//Create a binary tree out of a list of elements
//----------------------------------------------------------------------------------------------------------------------------------


TEST_CASE("Create binary tree", "[binary tree]"){

    Element<int, std::string> root {3, "a"};

    std::vector<int> keys = {1, 2, 0, 4, 5};
    std::vector<std::string> values = {"b", "c", "d", "e", "f"};

    std::vector<Element<int, std::string>> elem_vec = create_elements(keys, values);

    root.create_binary_tree(&elem_vec);

    REQUIRE(root.key == 3);
    REQUIRE(root.value == "a");

    REQUIRE(root.left_child_ptr->key == 1);
    REQUIRE(root.left_child_ptr->value == "b");
    REQUIRE(root.left_child_ptr == &elem_vec[0]);
    REQUIRE(root.left_child_ptr->parent_ptr == &root);

    REQUIRE(root.right_child_ptr->key == 4);
    REQUIRE(root.right_child_ptr->value == "e");
    REQUIRE(root.right_child_ptr == &elem_vec[3]);
    REQUIRE(root.right_child_ptr->parent_ptr == &root);

    REQUIRE(root.left_child_ptr->left_child_ptr->key == 0);
    REQUIRE(root.left_child_ptr->left_child_ptr->value == "d");
    REQUIRE(root.left_child_ptr->left_child_ptr == &elem_vec[2]);
    REQUIRE(root.left_child_ptr->left_child_ptr->parent_ptr == &elem_vec[0]);

    REQUIRE(root.left_child_ptr->right_child_ptr->key == 2);
    REQUIRE(root.left_child_ptr->right_child_ptr->value == "c");
    REQUIRE(root.left_child_ptr->right_child_ptr == &elem_vec[1]);
    REQUIRE(root.left_child_ptr->right_child_ptr->parent_ptr == &elem_vec[0]);

    REQUIRE(root.right_child_ptr->right_child_ptr->key == 5);
    REQUIRE(root.right_child_ptr->right_child_ptr->value == "f");
    REQUIRE(root.right_child_ptr->right_child_ptr == &elem_vec[4]);
    REQUIRE(root.right_child_ptr->right_child_ptr->parent_ptr == &elem_vec[3]);


    Element<int, std::string> root_2 {2, "x"};
    
    std::vector<Element<int, std::string>> empty_vec {};

    root_2.create_binary_tree(&empty_vec);

    REQUIRE(root_2.key == 2);
    REQUIRE(root_2.value == "x");
    REQUIRE(root_2.left_child_ptr == nullptr);
    REQUIRE(root_2.right_child_ptr == nullptr);
}


TEST_CASE( "Size", "[binary tree]"){

    Element<int, std::string> root {3, "a"};

    std::vector<int> keys = {1, 2, 0, 4, 5};
    std::vector<std::string> values = {"b", "c", "d", "e", "f"};

    std::vector<Element<int, std::string>> elem_vec = create_elements(keys, values);

    root.create_binary_tree(&elem_vec);

    REQUIRE(root.size() == 6);
}

TEST_CASE( "In order", "[binary tree]"){

    Element<int, std::string> root {3, "a"};

    std::vector<int> keys = {1, 2, 0, 4, 5};
    std::vector<std::string> values = {"b", "c", "d", "e", "f"};

    std::vector<Element<int, std::string>> elem_vec = create_elements(keys, values);

    root.create_binary_tree(&elem_vec);

    for (int i = 0; i < root.size(); i++){

        REQUIRE(root.in_order()[i]->key == i);
    }
}

TEST_CASE( "Delete element", "[binary tree]"){

    Element<int, std::string> root {3, "a"};

    std::vector<int> keys = {1, 2, 0, 4, 5};
    std::vector<std::string> values = {"b", "c", "d", "e", "f"};

    std::vector<Element<int, std::string>> elem_vec = create_elements(keys, values);

    root.create_binary_tree(&elem_vec);
    
    root.right_child_ptr->delete_element();
    
    std::vector<int> ordered_vec = {0, 1, 2, 3, 5};

    REQUIRE(root.right_child_ptr->key == 5);
    REQUIRE(root.in_order().size() == 5);

    for(int i = 0; i < 5; i++){

        REQUIRE(root.in_order()[i]->key == ordered_vec[i]);
    }

    root.left_child_ptr->delete_element();

    REQUIRE(root.left_child_ptr->key == 0);

    root.delete_element();

    REQUIRE(root.key == 2);

    REQUIRE(root.left_child_ptr->key == 0);
    
    root.left_child_ptr->delete_element();

    REQUIRE(root.left_child_ptr == nullptr);

}


TEST_CASE( "Height", "[binary tree]"){

    Element<int, std::string> root {3, "a"};

    std::vector<int> keys = {1, 2, 0, 4, 5};
    std::vector<std::string> values = {"b", "c", "d", "e", "f"};

    std::vector<Element<int, std::string>> elem_vec = create_elements(keys, values);

    root.create_binary_tree(&elem_vec);

    REQUIRE(root.get_height() == 3);

    root.left_child_ptr->delete_element();
    root.left_child_ptr->delete_element();
    root.right_child_ptr->delete_element();

    REQUIRE(root.get_height() == 2);
    REQUIRE(root.left_child_ptr->key == 2);
    REQUIRE(root.right_child_ptr->key == 5);

    root.left_child_ptr->delete_element();
    root.right_child_ptr->delete_element();

    REQUIRE(root.get_height() == 1);
}


TEST_CASE( "Balance-factors", "[binary tree]"){

    Element<int, std::string> root {3, "a"};

    std::vector<int> keys = {1, 2, 0, 4, 5};
    std::vector<std::string> values = {"b", "c", "d", "e", "f"};

    std::vector<Element<int, std::string>> elem_vec = create_elements(keys, values);

    root.create_binary_tree(&elem_vec);


    root.calculate_balancefactors();

    REQUIRE(root.balance_factor == 0);
    REQUIRE(root.right_child_ptr->balance_factor == 1);
    REQUIRE(root.right_child_ptr->right_child_ptr->balance_factor == 0);
    REQUIRE(root.left_child_ptr->balance_factor == 0);
    REQUIRE(root.left_child_ptr->left_child_ptr->balance_factor == 0);
    REQUIRE(root.left_child_ptr->right_child_ptr->balance_factor == 0);


    Element<int, std::string> root_2 {4, "a"};

    std::vector<int> keys_2 = {1, 0, 6, 5};
    std::vector<std::string> values_2 = {"b", "c", "d", "f"};

    std::vector<Element<int, std::string>> elem_vec_2 = create_elements(keys_2, values_2);

    root_2.create_binary_tree(&elem_vec_2);

    root_2.calculate_balancefactors();

    REQUIRE(root_2.balance_factor == 0);

    REQUIRE(root_2.left_child_ptr->balance_factor == -1);
    REQUIRE(root_2.right_child_ptr->balance_factor == -1);
}