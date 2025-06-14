#include <catch2/catch_test_macros.hpp>

#include "sll.h"

#include <string>

TEST_CASE("element constructor" , "[sll element]")
{
    Element<int> x{};

    REQUIRE(x.value == 0);
    REQUIRE(x.next == nullptr);

    Element<std::string> s{};

    REQUIRE(s.value == "");
    REQUIRE(s.next == nullptr);
}

TEST_CASE("add element to another", "[sll element]")
{
    Element<int> x{};
    
    Element<int> y{};

    y.value = 25;

    x.add_elem(&y);

    REQUIRE(x.next->value == 25);
    REQUIRE(x.next->next == nullptr);
    REQUIRE(x.next == &y);
    
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//Linked Lists
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("constructor", "[linked list]")
{
    sll<int> linked_list{};

    REQUIRE(linked_list.dummy.next == nullptr);
    REQUIRE(linked_list.first == &linked_list.dummy);
    REQUIRE(linked_list.last == &linked_list.dummy);
}

TEST_CASE("adding an element", "[linked list]")
{
    sll<int> linked_list{};

    Element<int> x{};
    x.value = 25;

    Element<int> y{};
    x.value = 26;

    linked_list.add_element(&x);

    REQUIRE(linked_list.first == &x);
    REQUIRE(linked_list.last == &x);
    REQUIRE(x.next == &linked_list.dummy);

    linked_list.add_element(&y);

    REQUIRE(linked_list.first == &x);
    REQUIRE(linked_list.last == &y);
    REQUIRE(x.next == &y);
    REQUIRE(y.next == &linked_list.dummy);
}

TEST_CASE("length", "[linked list]")
{
    sll<int> linked_list{};

    Element<int> x{};
    x.value = 25;

    Element<int> y{};
    x.value = 26;

    REQUIRE(linked_list.len() == 0);

    linked_list.add_element(&x);

    REQUIRE(linked_list.len() == 1);

    linked_list.add_element(&y);

    REQUIRE(linked_list.len() == 2);

}

TEST_CASE("append vector", "[linked list]"){
    
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    sll<int> x{};

    x.append_vector(v);

    REQUIRE(!x.empty());
    REQUIRE(x.first->value == 0);
}

TEST_CASE("all in one constructor", "[linked list]")
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    sll<int> linked_list{v};

    REQUIRE(linked_list.len() == 10);

    REQUIRE(!linked_list.empty());
    REQUIRE(linked_list.first->value == 0);
    REQUIRE(linked_list.first->next->value == 1);
    REQUIRE(linked_list.first->next->next->value == 2);
    REQUIRE(linked_list.first->next->next->next->value == 3);
    REQUIRE(linked_list.first->next->next->next->next->value == 4);
    REQUIRE(linked_list.first->next->next->next->next->next->value == 5);
    REQUIRE(linked_list.first->next->next->next->next->next->next->value == 6);
    REQUIRE(linked_list.first->next->next->next->next->next->next->next->value == 7);
    REQUIRE(linked_list.first->next->next->next->next->next->next->next->next->value == 8);
    REQUIRE(linked_list.first->next->next->next->next->next->next->next->next->next->value == 9);
    REQUIRE(linked_list.last->value == 9);


}
