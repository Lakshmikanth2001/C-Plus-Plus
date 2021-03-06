#include<iostream>
#include<queue>
using namespace std;
struct node // binary tree node structure
{
	int data;
	node *left;   // left pointer
	node *right; // right pointer
};
node *creat_node(int data)
{
	node *root=new node;
	root->data=data;
	root->left=NULL;
	root->right=NULL;
	return root;
}
void swap(int &a,int &b) // call by reference value
{
	int temp;
	temp=a;
	a=b;
	b=temp;
}
class tree{
	// every type of binary tree has following function
	public:
		 void preorder(node *root);
		 void inorder(node *root);
		 void postorder(node *root);
		 void BFS(node *root);
};
void tree::BFS(node *root)
{
	if(root!=NULL)
	{
		queue<node*> q;
		q.push(root);
		while(!q.empty())
		{
			node *temp=q.front();
			cout<<temp->data<<" ";
			if(temp->left!=NULL)
			{
				q.push(temp->left); // pushing left child into the queue
			}
			if(temp->right!=NULL)
			{
				q.push(temp->right); // to push right child into the queue
			}
			q.pop(); // popping out the present root from the queue
		}
	}
}
void tree::inorder(node *root)
{
	if(root==NULL)
	{
		return ;// to return void 
	}
	else
	{
		inorder(root->left); // to travel to left of root
		cout<<root->data<<" ";
		inorder(root->right); // back tracking all right node
	}
}
void tree::preorder(node *root)
{
	if(root==NULL)
	{
		return ;// to return void 
	}
	else
	{
		cout<<root->data<<" ";
		preorder(root->left); // to travel to left of root
		preorder(root->right); // back tracking all right node
	}
}
void tree::postorder(node *root)
{
	if(root==NULL)
	{
		return ;// to return void 
	}
	else
	{
		postorder(root->left); // to travel to left of root
		postorder(root->right); // back tracking all right node
		cout<<root->data<<" ";
	}
}
class BST:public tree // inheriting all function of tree class
{
	private:
		bool isleaf(node *root);
		int child_count(node *root);
		node *rootNode=NULL; // to store the root node
		
	public:
		node *parent(node *root,node *child); // helpher function to find parent of the node
		node *min(node *root);
		node *max(node *root); // return node which has max value
		node *insert(node *root,int data); // recurcive insert method that can be extended for AVL tree
		void remove(node *root,int data); //BST deletion
};
node *BST::parent(node *root,node *child)
{
	if(root==NULL)
	{
		return NULL;
	}
	else if(root->left!=NULL and root->left->data==child->data)
	{
		return root;
	}
	else if(root->right!=NULL and root->right->data==child->data)
	{
		return root;
	}
	else
	{
		if(root->data>child->data)
		{
			return parent(root->left,child);
		}
		else
		{
			return parent(root->right,child);
		}
		return root;
	}
}
node * BST::max(node *root)
{
	if(root==NULL)
	{
		// no element is present
		return NULL;
	}
	else if(root->right==NULL)
	{
		// no element is greater than the root
		return root;
	}
	while(root->right!=NULL)
	{
		root=root->right;
	}
	return root;
}
node * BST::min(node *root)
{
	if(root==NULL)
	{
		// no element is present 
		return NULL;
	}
	else if(root->left==NULL)
	{
		//no elemnt is present that is smaller than root
		return root;
	}
	while(root->left!=NULL)
	{
		root=root->left;
	}
	return root;
}
int BST::child_count(node *root)
{
	if(root==NULL)
	{
		return 0;
	}
	else if(root->left!=NULL and root->right!=NULL)
	{
		return 2;
	}
	else if(root->left==NULL or root->right==NULL)
	{
		return 1;
	}
	return 0;
}
bool BST::isleaf(node *root)
{
	if(root==NULL)
	{
		return false;	
	}	
	else if(root->left==NULL and root->right==NULL)
	{
		return true;
	}
	return false;
		
}
node *BST::insert(node *root,int data)
{
	if(this->rootNode==NULL)
	{
		this->rootNode=creat_node(data);
		return this->rootNode;
	}
	else if(root==NULL)
	{
		return creat_node(data);
	}
	else
	{
		if(root->data<data)
		{
			root->right=insert(root->right,data);
		}
		else
		{
			root->left=insert(root->left,data);
		}
	}
	return root; // default return
}
void BST::remove(node *root,int data)
{
	if(root==NULL)
	{
		return ;
	}
	// not considering root deletion and we are reaching the parent of the node that is to be deleted
	
	// by reaching the parent of that node we can perform deletion  
	else if(!this->isleaf(root) and data!=this->rootNode->data) 
	{
		node *temp;
		temp=root->left; // temporvary node to point the node that is to be deleted
		if(temp!=NULL and temp->data==data)
		{
			if(this->isleaf(temp)) // deletion process for leaf node
			{
				root->left=NULL;
				delete(temp);
				return ;
			}
			else if(this->child_count(temp)!=2)//deletion process if node contains only sinlge child
			{
				if(temp->left!=NULL)
				{
					root->left=temp->left;
					delete(temp);
					return ;
				}
				else if(temp->right!=NULL)
				{
					root->left=temp->right;
					delete(temp);
					return ;
				}
			}
			else
			{
				// deletion process when node contains 2 child nodes
				node *x=max(temp->left); // righ most element of left sub tree
				node *y=min(temp->right); // left most element of right sub tree;
				if(x!=NULL)
				{
					node *parent_element=this->parent(root,x);
					swap(x->data,temp->data); 
					this->remove(parent_element,data);
				}
				else if(y!=NULL)
				{
					node *parent_element=this->parent(root,y);
					swap(y->data,temp->data);
					this->remove(parent_element,data);
				}
				return ;
			}
		}
		temp=root->right; // temporvary node to point the node that is to be deleted
		if(temp!=NULL and temp->data==data)
		{
			if(this->isleaf(temp)) // deletion process for leaf node
			{
				root->right=NULL;
				delete(temp);
			}
			else if(this->child_count(temp)!=2)
			{
				if(temp->left!=NULL)
				{
					root->right=temp->left;
					delete(temp);
					return ;
				}
				else if(temp->right!=NULL)
				{
					root->right=temp->right;
					delete(temp);
					return ;
				}
			}
			else
			{
				// deletion process when node contains 2 child nodes
				node *x=max(temp->left); // righ most element of left sub tree
				node *y=min(temp->right); // left most element of right sub tree;
				if(x!=NULL)
				{
					node *parent_element=this->parent(root,x);
					swap(x->data,temp->data); // replaing x with temp
					this->remove(parent_element,data); // know as temp parent is know and x is leaf node again call remove function
				}
				else if(y!=NULL)
				{
					node *parent_element=this->parent(root,y);
					swap(y->data,temp->data);  //replaing y with temp
					this->remove(parent_element,data); // know as temp parent is know and x is leaf node again call remove function
				}
			}
		}
		else
		{
			if(root->data>data)
			{
				remove(root->left,data);
			}
			else
			{
				remove(root->right,data);
			}
		}
	}
	else if(this->rootNode->data==data)
	{
		if(this->isleaf(rootNode))
		{
			this->rootNode=NULL;
			return ;
		}
		// deletion process when node contains 2 child nodes
		node *x=max(root->left); // righ most element of left sub tree
		node *y=min(root->right); // left most element of right sub tree;
		if(x!=NULL)
		{
			node *parent_element=this->parent(this->rootNode,x);
			swap(x->data,root->data);
			this->remove(parent_element,data);
			this->rootNode->data=root->data;
			return ;
		}
		else if(y!=NULL)
		{
			node *parent_element=this->parent(this->rootNode,y);
			swap(y->data,root->data);
			this->remove(parent_element,data);
			this->rootNode->data=root->data;
			return ;
		}
	}
}
void test()
{
	BST *B=new BST ();
	node *root=NULL;
	root=B->insert(root,9);
	root=B->insert(root,7);
	root=B->insert(root,10);
	root=B->insert(root,5);
	root=B->insert(root,11);
	root=B->insert(root,13);
	B->BFS(root);cout<<endl;
	B->inorder(root);cout<<endl;
	B->remove(root,8); // removing the leaft element
	B->remove(root,7); // removing the element with only one child
	B->remove(root,9); // removing the root and node with two elements
	B->inorder(root);cout<<endl;
	B->BFS(root);cout<<endl; // all corner cases are verified please let me know if i missed any
}
int main()
{
	test();
}
