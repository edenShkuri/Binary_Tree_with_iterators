/**
 * -------------------
 * @author Eden Shkuri
 * -------------------
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "doctest.h"
using namespace std;

#include "BinaryTree.hpp"
using namespace ariel;

TEST_CASE("int Binary tree"){
    BinaryTree<int> bt_int;
    CHECK_NOTHROW(bt_int.add_root(5));
    CHECK_NOTHROW(bt_int.add_root(10));
    CHECK_NOTHROW(bt_int.add_left(10, 4));
    CHECK_NOTHROW(bt_int.add_left(10, 5));
    CHECK_NOTHROW(bt_int.add_right(10, 18));
    CHECK_NOTHROW(bt_int.add_right(18,18));
    CHECK_THROWS(bt_int.add_left(4,4));//4 doesn't exist
    CHECK_NOTHROW(bt_int.add_left(5,4));
    CHECK_NOTHROW(bt_int.add_right(5, 3));
    CHECK_NOTHROW(bt_int.add_left(3, 7));

    int arrPost[]={4,7,3,5,18,18,10};
    int arrIn[]={4,5,7,3,10,18,18};
    int arrPre[]={10,5,4,3,7,18,18};
    int i=0;
    for (auto it=bt_int.begin_postorder(); it!=bt_int.end_postorder(); ++it) {
        CHECK((*it)==arrPost[i]);
        i++;
    }
    i=0;
    for (const int& element: bt_int) { 
        CHECK(element==arrIn[i]);
        i++;
    }
    i=0;
    for (auto it=bt_int.begin_preorder(); it!=bt_int.end_preorder(); ++it) {
        CHECK((*it)==arrPre[i]);
        i++;
    }

    SUBCASE("add sun to node that exist twice"){
        CHECK_NOTHROW(bt_int.add_right(3,4));
        CHECK_NOTHROW(bt_int.add_left(4, 1));

        string arrPre_opt1="10,5,4,3,7,4,1,18,18,",
         arrIn_opt1="4,5,7,3,1,4,10,18,18,",
         arrPost_opt1="4,7,1,4,3,5,18,18,10,",

         arrPre_opt2="10,5,4,1,3,7,4,18,18,",
         arrIn_opt2="1,4,5,7,3,4,10,18,18,",
         arrPost_opt2="1,4,7,4,3,5,18,18,10,",

         ansPre,ansIn,ansPost;
        
        for (auto it=bt_int.begin_postorder(); it!=bt_int.end_postorder(); ++it) {
            ansPost+=to_string(*it);
            ansPost+=",";
        }
        for (auto it=bt_int.begin_inorder(); it!=bt_int.end_inorder(); ++it) {
            ansIn+=to_string(*it);
            ansIn+=",";
        }
        for (auto it=bt_int.begin_preorder(); it!=bt_int.end_preorder(); it++) {
            ansPre+=to_string(*it);
            ansPre+=",";
        }
        
        CHECK(((ansPre==arrPre_opt1)||(ansPre==arrPre_opt2)));
        CHECK(((ansIn==arrIn_opt1)||(ansIn==arrIn_opt2)));
        CHECK(((ansPost==arrPost_opt1)||(ansPost==arrPost_opt2)));

    }

    CHECK_NOTHROW(cout<<bt_int<<endl);


    SUBCASE("check operator =="){
        BinaryTree<int> int_BinaryTree;
        CHECK_NOTHROW(cout<<int_BinaryTree<<endl);

        CHECK_NOTHROW(int_BinaryTree.add_root(8));
        CHECK_NOTHROW(int_BinaryTree.add_left(8,2));
        CHECK_NOTHROW(int_BinaryTree.add_left(2,3));
        CHECK_NOTHROW(int_BinaryTree.add_left(3,4));
        CHECK_NOTHROW(int_BinaryTree.add_left(4,5));
        CHECK_NOTHROW(int_BinaryTree.add_left(5,6));
        CHECK_NOTHROW(int_BinaryTree.add_root(1));
        //adding to non-exists nodes
        CHECK_THROWS(int_BinaryTree.add_left(8,9));
        CHECK_THROWS(int_BinaryTree.add_left(10,0));
        CHECK_THROWS(int_BinaryTree.add_right(7,6));
        CHECK_THROWS(int_BinaryTree.add_right(8,5));
        
        //in this tree - post order and in order is the same
        for (auto itPRE=int_BinaryTree.begin_postorder(), itIN=int_BinaryTree.begin_inorder();
             (itPRE!=int_BinaryTree.begin_postorder() && itIN!=int_BinaryTree.end_inorder());
             ++itPRE, itIN++) 
            {
                CHECK((*itPRE)==(*itIN));
            }    
        
        CHECK_NOTHROW(cout<<int_BinaryTree<<endl);
    }
    
}

TEST_CASE("char Binary tree"){
BinaryTree<char> bt_char;
    CHECK_THROWS(bt_char.add_right('A','C'));//there is no nodes in the tree
    CHECK_NOTHROW(bt_char.add_root('A'));
    CHECK_NOTHROW(bt_char.add_right('A','C'));
    CHECK_NOTHROW(bt_char.add_left('A','B'));
    CHECK_NOTHROW(bt_char.add_left('B','D'));
    CHECK_NOTHROW(bt_char.add_right('B','E'));
    CHECK_THROWS(bt_char.add_right('c','E'));
    CHECK_THROWS(bt_char.add_right('*','o'));
    CHECK_THROWS(bt_char.add_left('=','+'));


    SUBCASE("check the tree is correct"){
        char arrPre[]={'A','B','D','E','C'};
        char arrIn[]={'D','B','E','A','C'};
        char arrPost[]={'D','E','B','C','A'};
        int i=0;
        for (auto it=bt_char.begin_postorder(); it!=bt_char.end_postorder(); it++) {
            CHECK((*it)==arrPost[i]);
            i++;
        }
        i=0;
        for (auto it=bt_char.begin_inorder(); it!=bt_char.end_inorder(); it++) {
            CHECK((*it)==arrIn[i]);
            i++;
        }
        i=0;
        for (auto it=bt_char.begin_preorder(); it!=bt_char.end_preorder(); it++) {
            CHECK((*it)==arrPre[i]);
            i++;
        }
    }


    SUBCASE("check override by add_right/add_left"){
        CHECK_NOTHROW(bt_char.add_root('a'));
        CHECK_NOTHROW(bt_char.add_left('a','b'));

        CHECK_THROWS(bt_char.add_left('A','0'));
        CHECK_THROWS(bt_char.add_left('B','6'));

        char arrPre[]={'a','b','D','E','C'};
        char arrIn[]={'D','b','E','a','C'};
        char arrPost[]={'D','E','b','C','a'};
        int i=0;
            for (auto it=bt_char.begin_postorder(); it!=bt_char.end_postorder(); ++it) {
                CHECK((*it)==arrPost[i]);
                i++;
            }
            i=0;
            for (const char& element: bt_char) { 
                CHECK(element==arrIn[i]);
                i++;
            }
            i=0;
            for (auto it=bt_char.begin_preorder(); it!=bt_char.end_preorder(); ++it) {
                CHECK((*it)==arrPre[i]);
                i++;
            }
    }
    
    CHECK_NOTHROW(cout<<bt_char<<endl);
}

TEST_CASE("string Binary tree"){
BinaryTree<string> bt_string;
    CHECK_NOTHROW(bt_string.add_root("Event"));
    CHECK_NOTHROW(bt_string.add_root("jorge"));
    CHECK_NOTHROW(bt_string.add_left("jorge", "Drama"));
    CHECK_NOTHROW(bt_string.add_left("jorge", "Event"));
    CHECK_NOTHROW(bt_string.add_right("jorge", "18"));
    CHECK_NOTHROW(bt_string.add_right("18","19"));
    CHECK_THROWS(bt_string.add_left("Drama","Drama"));//"Drama" doesn't exist
    CHECK_NOTHROW(bt_string.add_left("Event","Drama"));
    CHECK_NOTHROW(bt_string.add_right("Event", "c"));
    CHECK_NOTHROW(bt_string.add_left("c", "7"));


    string arrPost[]={"Drama","7","c","Event","19","18","jorge"};
    string arrIn[]={"Drama","Event","7","c","jorge","18","19"};
    string arrPre[]={"jorge","Event","Drama","c","7","18","19"};
    int len_by_pre[]={5,5,5,1,1,2,2};

    int i=0;
    for (auto it=bt_string.begin_postorder(); it!=bt_string.end_postorder(); ++it) {
        CHECK((*it)==arrPost[i]);
        i++;
    }

    i=0;
    for (const string& element: bt_string) { 
        CHECK(element==arrIn[i]);
        i++;
    }


        SUBCASE("check -> opperator"){
        i=0;
        for (auto it=bt_string.begin_preorder(); it!=bt_string.end_preorder(); ++it) {
            CHECK((*it)==arrPre[i]);
            CHECK(it->length()==len_by_pre[i]);
            i++;
        }

        i=0;
        string element_number="->I'm_the_elemunt_number_",
        tmp="_in_inorder";
        for (auto it=bt_string.begin_inorder(); it!=bt_string.end_inorder(); it++) {
            it->append(element_number);
            it->append(to_string(i));
            it->append(tmp);
            i++;
        }

        string NewarrPost[]={"Drama->I'm_the_elemunt_number_0_in_inorder",
                        "7->I'm_the_elemunt_number_2_in_inorder",
                        "c->I'm_the_elemunt_number_3_in_inorder",
                        "Event->I'm_the_elemunt_number_1_in_inorder",
                        "19->I'm_the_elemunt_number_6_in_inorder",
                        "18->I'm_the_elemunt_number_5_in_inorder",
                        "jorge->I'm_the_elemunt_number_4_in_inorder"};

        i=0;
        for (auto it=bt_string.begin_postorder(); it!=bt_string.end_postorder(); ++it) {
            CHECK((*it)==NewarrPost[i]);
            i++;
        }
    }
    CHECK_NOTHROW(cout<<bt_string<<endl);
}