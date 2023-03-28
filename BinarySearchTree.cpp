#include <bits/stdc++.h>
using namespace std;

template<class t>
class BSTNode  //BSTNode class Implementation
{
private:
    t info;
    BSTNode<t> *left,*right;
public:
    BSTNode()
    {
        left=NULL;
        right=NULL;
    }
    BSTNode(t in,BSTNode<t>* l,BSTNode<t>* r)
    {
        left=l;
        right=r;
        info=in;
    }
    BSTNode* GetLeft()
    {
        return left;
    }
    BSTNode* GetRight()
    {
        return right;
    }
    t GetInfo()
    {
        return info;
    }
    void SetLeft(BSTNode<t>* l)
    {
        left=l;
    }
    void SetRight(BSTNode<t>* r)
    {
        right=r;
    }
    void SetInfo(t in)
    {
        info=in;
    }
};

template<class t>
class BSTFCI //BSTFCI class Implementation
{
public:
    BSTNode<t>* root;
public:

    BSTFCI()
    {
        root=NULL;
    }

    BSTFCI(t in)
    {
        root->SetInfo(in);
        root->SetLeft(NULL);
        root->SetRight(NULL);
    }
    //insert node in tree
    void insert( const t& value)
    {
        BSTNode<t>*current;
        BSTNode<t>*previous;
        BSTNode<t>*NewNode;
        NewNode=new BSTNode<t>;
        assert(NewNode != NULL); //space full
        NewNode->SetInfo(value);
        NewNode->SetLeft(NULL);
        NewNode->SetRight(NULL) ;
        if(root==NULL)
        {root=NewNode; return;}
        else
        {
            current=root;
            while (current!=NULL)
            {
                previous=current;
                if (current->GetInfo()==value)
                {
                    cout << "duplicates are not allowed"<<endl;
                    return;
                }
                else if(current->GetInfo() < value)
                {
                    current=current->GetRight();
                }
                else
                {
                    current=current->GetLeft();
                }
            }
            if (previous->GetInfo() > value) //put node in right position in left
                previous->SetLeft(NewNode);
            else
                previous->SetRight(NewNode); //put node in right position in right
        }
    }
    void printBTS( BSTNode<t> * node)
    {
        if (node == NULL) {
            return;
        }
        printBTS(node->GetLeft()); //print all nodes in left side primary
        cout<<node->GetInfo()<<" ";
        printBTS(node->GetRight()); //print all nodes in right side
    }
    void printBTS()
    {
        printBTS(root);
    }
    bool isBalance(BSTNode<t>* current)
    {
        int leftHeight= height(current->GetLeft());
        int rightHeight= height(current->GetRight());
        if(current==NULL) return true;
        if(abs(leftHeight-rightHeight)>1) //not balance
            return false;
        return true;

    }
    //calculate the height of each node
    int height(BSTNode<t>* current)
    {
        if(current==NULL)
            return 0;
        //calculate height
        return 1+max(height(current->GetRight()),height(current->GetLeft()));

    }
    void PrintRange(BSTNode<t>* root,int l,int h)
    {
        if ( root == NULL )
            return ;
        // If root->info is greater than l,then info in left subtree
        if ( l < root->GetInfo() )
            PrintRange(root->GetLeft(), l, h);

        // if root's info lies in range then prints root's data
        if ( l <= root->GetInfo()&& h >= root->GetInfo() )
            cout<<root->GetInfo()<<" ";
        // If root->info is less than l,then info in right subtree
        if ( h > root->GetInfo() )
            PrintRange(root->GetRight(), l, h);

    }
    void PrintRange(int l,int h)
    {
        PrintRange( root,l,h);
    }
};

template<class t>
bool AreIndentical(BSTNode<t>* r1, BSTNode<t>* r2)
{
    if(r1==NULL&&r2==NULL) //two trees reach to end in same time so that become subtree
        return true;
    if(r1==NULL||r2==NULL) //two trees not reach to end in same time so that its notSubtree
        return false;
    return ((r1->GetInfo()==r2->GetInfo())&& AreIndentical(r1->GetLeft(), r2->GetLeft()) &&
            AreIndentical(r1->GetRight(),r2->GetRight())); //check all nodes the same

}
template<class t>
bool isSubTree(BSTNode<t>* t1, BSTNode<t>* t2)
{
    if(t2==NULL) //tree2==null any null tree is subTree from any tree
        return true;
    else if(t1==NULL)
        return false;
    //Check the tree with root as current node
    if(AreIndentical(t1,t2))
        return true;
    return isSubTree(t1->GetLeft(),t2)|| isSubTree(t1->GetRight(),t2); //try start from all nodes

}

template<class t>
bool isSubTree(BSTFCI<t>* t1, BSTFCI<t>* t2)
{
    return isSubTree(t1->root, t2->root);
}
signed main()
{
    //************* point 1 *************
    //test insert and print function
    BSTFCI<int>test1;
    test1.insert(3);
    test1.insert(7);
    test1.insert(2);
    test1.insert(1);
    test1.insert(5);
    test1.insert(12);
    test1.insert(8);
    test1.printBTS();
    cout<<endl<<endl;
    //*************************************


    //************* point 2 *************
    //test 5 test cases for IsBalance function
    BSTFCI<int>test2;
    test2.insert(2);
    if(test2.isBalance(test2.root))
        cout<<"Is Balance"<<endl;
    else
        cout<<"not balance"<<endl;
    test2.insert(3);
    if(test2.isBalance(test2.root))
        cout<<"Is Balance"<<endl;
    else
        cout<<"not balance"<<endl;
    test2.insert(4);
    if(test2.isBalance(test2.root))
        cout<<"Is Balance"<<endl;
    else
        cout<<"not balance"<<endl;
    test2.insert(1);
    if(test2.isBalance(test2.root))
        cout<<"Is Balance"<<endl;
    else
        cout<<"not balance"<<endl;
    test2.insert(7);
    if(test2.isBalance(test2.root))
        cout<<"is Balance"<<endl;
    else
        cout<<"not balance"<<endl;
    cout<<endl;
    //*************************************



    //************* point 3 *************
    //test 5 test cases for isSubtree
    BSTFCI<int>sub1,sub2,sub3,sub4,sub5;
    if(isSubTree(&test1,&sub1))
        cout<<"Is subTree"<<endl;
    else
        cout<<"Not subTree"<<endl;

    sub2.insert(2);
    if(isSubTree(&test1,&sub2))
        cout<<"Is subTree"<<endl;
    else
        cout<<"Not subTree"<<endl;

    sub3.insert(2);
    sub3.insert(1);
    if(isSubTree(&test1,&sub3))
        cout<<"Is subTree"<<endl;
    else
        cout<<"Not subTree"<<endl;

    sub4.insert(3);
    sub4.insert(2);
    sub4.insert(7);
    sub4.insert(5);
    if(isSubTree(&test1,&sub4))
        cout<<"Is subTree"<<endl;
    else
        cout<<"Not subTree"<<endl;

    sub5.insert(7);
    sub5.insert(12);
    sub5.insert(5);
    sub5.insert(8);
    if(isSubTree(&test1,&sub5))
        cout<<"Is subTree"<<endl;
    else
        cout<<"Not subTree"<<endl;
    cout<<endl;
    //*************************************



    //************* point 4 *************
    cout<<"{ ";
    test1.PrintRange(1,10);
    cout<<"}"<<endl;
    cout<<"{ ";
    test1.PrintRange(3,4);
    cout<<"}"<<endl;
    cout<<"{ ";
    test1.PrintRange(6,6);
    cout<<"}"<<endl;
    cout<<"{ ";
    test1.PrintRange(10,20);
    cout<<"}"<<endl;
    cout<<"{ ";
    test1.PrintRange(2,5);
    cout<<"}"<<endl;
    cout<<endl;
    //*************************************


}

