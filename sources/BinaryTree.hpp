
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <string>
#include <list>


namespace ariel{

    template<class T>
    class BinaryTree{
    
        struct TreeNode {
        T data;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
        TreeNode(T info): data(info), left(nullptr), right(nullptr){}
        };
        TreeNode *root=nullptr;

        

        public:
            BinaryTree<T>(){}
           
            void copy(TreeNode *& thisRoot, TreeNode *& sourceRoot)
            {
                if(sourceRoot == NULL)
                {
                    thisRoot = NULL;
                }
                else
                {
                    thisRoot = new TreeNode(sourceRoot->data);
                    copy(thisRoot->left, sourceRoot->left);
                    copy(thisRoot->right, sourceRoot->right);
                }
            }

            BinaryTree<T>(BinaryTree<T> &other)//copy constractor
            {
                if(other.root == NULL){
                    root = NULL;
                }
                else{
                    copy(this->root, other.root);
                }
            }

            ~BinaryTree<T>() {//distractor
                if (root != nullptr) {
                    delete root;
                }
            }


            BinaryTree<T> &operator=(BinaryTree<T> &&other) noexcept {//move =
                delete root;
                root = other.root;
                other.root = nullptr; 
            }

            BinaryTree<T>(BinaryTree<T> &&other) noexcept {//move constractor
                root = other.root;
                other.root = nullptr; 
            }

            BinaryTree<T> &operator=(BinaryTree<T> other){//= operator
                if (this == &other) {
                    return *this;
                }
                delete root;
                root = new TreeNode(other.root->data);
                copy(this->root,other.root);
                return *this;
            }

            


            BinaryTree<T>& add_root(const T& data){
                if(root==nullptr){
                    root =new TreeNode(data);   
                }
                else{
                    root->data=data;
                }
                // cout<<"add_root"<<endl;
                return *this;
            }        

            BinaryTree<T>& add_left(const T& exist,const T& New){
                if(root==nullptr){
                    throw (std::string)"there is no root yes";
                }
                // cout<<"add_left"<<endl;
                std::stack<TreeNode*> s;
                   TreeNode *curr = root;
                   while (curr != nullptr || !s.empty())
                   {   
                       
                       while (curr !=  NULL)
                       {
                           s.push(curr);
                           curr = curr->left;
                       }

                       curr = s.top();
                       s.pop();
                       if(curr->data==exist){
                           if(curr->left==nullptr){
                            curr->left=new TreeNode(New);
                           }
                           else{
                             curr->left->data=New;
                           }
                            // cout<<"add "<<New<<" to "<<exist<<endl;
                            return *this;
                       }
                       curr = curr->right;
                   }
            throw std::invalid_argument{"this node isn't in the tree"};
            }

            BinaryTree<T>& add_right(const T& exist,const T& New){
                 if(root==nullptr){
                    throw (std::string)"there is no root yes";
                }
                // cout<<"add_right"<<endl;
                std::stack<TreeNode*> s;
                   TreeNode *curr = root;
                   while (curr != nullptr || !s.empty())
                   {   
                       while (curr !=  NULL)
                       {
                           s.push(curr);
                           curr = curr->left;
                       }
                       curr = s.top();
                       s.pop();
                       if(curr->data==exist){
                            if(curr->right==nullptr){curr->right=new TreeNode(New);}
                            else{curr->right->data=New;}
                            return *this;
                       }
                       curr = curr->right;
                   }
            throw std::invalid_argument{"this node isn't in the tree"};
            }


 class iterator{

	  private:
        std::stack<TreeNode*> s;
        int Order;
		TreeNode* current_node;
        std::list<TreeNode*> PostList;

	public:

		iterator(int order, TreeNode* ptr=nullptr):current_node(ptr){
                Order=order;
                if(current_node!=nullptr){
                    if(order==0){//preorder
                        if(current_node->right!=nullptr){
                            s.push(current_node->right);
                        }
                        if(current_node->left!=nullptr){
                            s.push(current_node->left);
                        }
                    }
                    else if(order==1){//inorder
                        while (current_node!=nullptr)
                        {
                          s.push(current_node);
                          current_node=current_node->left;
                        } 
                        current_node=s.top();
                        s.pop();
                    }
                    else{
                        while(current_node != nullptr || !s.empty()){
                            if(current_node != nullptr){
                                s.push(current_node);
                                current_node = current_node->left;
                            }else{
                                TreeNode *temp = s.top()->right;
                                if (temp == nullptr) {
                                    temp = s.top();
                                    s.pop();
                                    PostList.push_back(temp);
                                    while (!s.empty() && temp == s.top()->right) {
                                        temp = s.top();
                                        s.pop();
                                        PostList.push_back(temp);
                                    }
                                } else {
                                    current_node = temp;
                                }
                            }
                        }
                        current_node=PostList.front();   
                        PostList.pop_front(); 
                    }
    		    }
        }

		T& operator*() const {
			return current_node->data;
		}

		T* operator->() const {
			return &(current_node->data);
		}

		// ++i;
		iterator& operator++() {
            if(Order==0){
                if(s.empty()){
                    current_node=nullptr;
                    return *this;
                }
                current_node=s.top();
                s.pop();
    
                if(current_node->right!=nullptr){
                    s.push(current_node->right);
                }
                if(current_node->left!=nullptr){
                    s.push(current_node->left);
                }
            }
            else if(Order==1){
                if(!s.empty() || current_node->right!=nullptr){
                    current_node=current_node->right;

                    while(current_node!=nullptr){
                        s.push(current_node);
                        current_node=current_node->left;
                    }
                    current_node=s.top();
                    s.pop();
                    }
                else{
                    current_node=nullptr;
                    }
            }
            else{
                if(PostList.size()!=0){
                current_node=PostList.front();   
                PostList.pop_front();   
                }
                else {current_node=nullptr;}
            }
		return *this;
		}

		// i++;
		 iterator operator++(int) {
			iterator tmpIT= *this;
            if(Order==0){   
                if(s.empty()){
                    current_node=nullptr;
                    return tmpIT;
                }
                current_node=s.top();
                s.pop();
    
                if(current_node->right!=nullptr){
                    s.push(current_node->right);
                }
                if(current_node->left!=nullptr){
                    s.push(current_node->left);
                }
            }
            else if(Order==1){
                if(!s.empty() || current_node->right!=nullptr){
                    current_node=current_node->right;

                    while(current_node!=nullptr){
                        s.push(current_node);
                        current_node=current_node->left;
                    }
                    current_node=s.top();
                    s.pop();
                    }
                else{
                    current_node=nullptr;
                    }
            }
            else{
                if(PostList.size()!=0){
                current_node=PostList.front();   
                PostList.pop_front();   
                }
                else {current_node=nullptr;}
            }
			return tmpIT;
		}

		bool operator==(const iterator& other) const {
			return current_node == other.current_node;
		}

		bool operator!=(const iterator& other) const {
			return current_node != other.current_node;
		}
	};  


            iterator begin_preorder(){
                return iterator(0, root);
            }
            iterator end_preorder(){
                return iterator(0, nullptr);
            }
            iterator begin_inorder(){
                return iterator(1, root);
            }
            iterator end_inorder(){
                return iterator(1, nullptr);
            }
            iterator begin_postorder(){
                return iterator(2, root);
            }
            iterator end_postorder(){
                return iterator(2, nullptr);
            }
            iterator begin(){
                return iterator(1, root);
            }
            iterator end(){
                return iterator(1, nullptr);
            }

            friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T> &bt){
                os<<"__________________\nPRINT TREE(preorder)\n----------------\n";
                if (bt.root == NULL){
                    return os;
                }
                std::stack<TreeNode*> s;
                s.push(bt.root);
            
                while (!s.empty()) {
                    TreeNode* node = s.top();
                    os<<node->data<<" ";
                    s.pop();
                    if (node->right){
                        s.push(node->right);
                    }
                    if (node->left){
                        s.push(node->left);
                    }
                }
                os<<"\n__________________\n";
                return os;
            }

    };
}

