//
//  main.cpp
//  hw2_BinaryTree
//
//  Created by 蔡易妏 on 2021/12/6.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <fstream>
#include <typeinfo>

using namespace std;
using std::ifstream; using std::vector;

//Build 2 Class, one is TreeNode, which contains what a node needs.
//The other one is Tree Class, including all the tree can do.
//Excluding these two class, there are PartOne fuction, PartTwo function, and the main function that calls the two above-mentioned ones.
class TreeNode{
friend class Tree;
private:
    int data;
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    
public:
    TreeNode(int key):leftchild(0),rightchild(0), parent(0),data(key){};   //Constructor
};

class Tree{
public:
    TreeNode* Search( int key );
    void Insert( int key );
    void Delete( int key );
    void Preorder( TreeNode *node );
    void Inorder( TreeNode *node );
    void Postorder( TreeNode *node );
    void Levelorder( TreeNode *node );
    void PostorderDelete( TreeNode *node, int trapIndex );
    void FindSwordMeaty(int sword, int meaty);
    TreeNode *root;
    Tree(): root(0){};
private:
    TreeNode* Successor(TreeNode *current);
    TreeNode* Leftmost(TreeNode *current);
};


// Get the leftmost node of subtree, on the basis of the parameter, current node, being the root node of the subtree.
TreeNode* Tree::Leftmost(TreeNode *current){
    while(current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}


// Get the next node in Inorder,  on the basis of the parameter, current node.
// If the current node has rightchild that can be easy, the right subtree's leftmost node is the object.
// However, if there's not rightchild, we should find the current node's parent, untill which is its parent's leftchild. And that leftchild node's parent is the object answer.
TreeNode* Tree::Successor(TreeNode *current){
    if(current->rightchild != NULL){
        return  Leftmost(current->rightchild);
    }
    
    TreeNode *successor = current->parent;
    while( successor!=NULL && current==successor->rightchild ){     // current要是successor的leftchild 才會符合
        current = successor;
        successor = successor->parent;
    }
    return successor;
}


// Search the node whether it exists or not.
// First, if root==NULL, the tree is empty.
// Then, turn to L or R tree by compare the key to the current node.
TreeNode* Tree::Search( int key ){
    if(root==NULL) {
        return 0; }
    TreeNode *current = root;
    while( current != NULL && current->data != key){
        if( key < current->data ){
            current = current->leftchild;
        }
        else{
            current = current->rightchild;
        }
    }
    return current;
}


// Insert the key into right place
// Make soldier to explore, begining with root. Compre key to soldier, and soldier would go to the L or R subtree; in the same time, objectParent would continuously be soilder's parent. Untill soilder==NULL, which is the node position of the insert key.
void Tree::Insert( int key ){
    TreeNode *objectParent = 0; // the object position's parent
    TreeNode *soilder = 0;    // to explore
    TreeNode *insert_node = new TreeNode(key);
    
    soilder = root;
    
    while(soilder != NULL){
        objectParent = soilder;
        if( insert_node->data < soilder->data){
            soilder = soilder->leftchild;
        }
        else{
            soilder = soilder->rightchild;
        }
    }
    
    insert_node->parent = objectParent;
    if( objectParent == NULL ){
        this->root = insert_node;   //BST is empty
    }
    else if( insert_node->data < objectParent->data){
        objectParent->leftchild = insert_node;
    }
    else{
        objectParent->rightchild = insert_node;
    }
}


// Delete the node, and make BST reasonable.
// First, Search the key, knowing whether it exists or not ,and get the the position of the delete node & its child.
// Second, There are 3 cases for delete.
// Case 1, the delete node doesn't have children, then delete it directly, that's all.
// Case 2, the delete node has only 1 child, then make its child replace it, and relink to the deleteNode's parent.
// Case3, the delete node has 2 children, then go get its successor to replace it. And relink successor's parent to its child(NULL).
void Tree::Delete( int key ){
    TreeNode *deleteNode = this->Search( key );     //BST contains key or not?
    if(deleteNode==NULL) {
        cout << "Number " << key << " is not exist." << endl;
        return;
    }
    
    TreeNode *objectNode = 0;   //the position of deleteNode
    TreeNode *childNode = 0;    //the position of deleteNode's child
    
    if( deleteNode->leftchild==NULL || deleteNode->rightchild==NULL ){      //case1(no child), case2(1child)--easy
        objectNode = deleteNode;
    }
    else {
        objectNode = Successor(deleteNode);     //case3, 找比key大的數中最小的那個(==right subtree最左的node
    }
    
    if( objectNode->leftchild != NULL ){        //assign childNode
        childNode = objectNode->leftchild;      //但總覺得，不會有leftchild?? 因為既然都是取successor了
    }
    else{
        childNode = objectNode->rightchild;
    }
    
    if( childNode!=NULL){                           //childNode relink parent
        childNode->parent = objectNode->parent;
    }
    if( objectNode->parent == NULL){                //parent relink childNode
        this->root = childNode;
    }
    else if( objectNode == objectNode->parent->leftchild ){
        objectNode->parent->leftchild = childNode;
    }
    else{
        objectNode->parent->rightchild = childNode;
    }
    
    if( objectNode != deleteNode ){
        deleteNode->data = objectNode->data;    // change data only，link still
    }
    delete objectNode;  // release memory
    objectNode = 0;
    
    cout << "Number " << key << " is deleted." << endl;
}


// Output BST in root-leftchild-rightchild order.
void Tree::Preorder( TreeNode *node ){
    if(node){
        cout << node->data << " ";
        Preorder( node->leftchild );
        Preorder( node->rightchild );
    }
}


// Output BST in leftchild-root-rightchild order.
void Tree::Inorder( TreeNode *node ){
    if(node){
        Inorder( node->leftchild );
        cout << node->data << " ";
        Inorder( node->rightchild );
    }
}


// Output BST in leftchild-rightchild-root order.
void Tree::Postorder( TreeNode *node ){
    if(node){
        Postorder( node->leftchild );
        Postorder( node->rightchild );
        cout << node->data << " ";
    }
}


// Output BST from low level to high level, and left to right in every level. Using queue FIFO.
void Tree::Levelorder( TreeNode *node ){
    queue <TreeNode*> q;    //include<queue>
    q.push( node );     //push root AS queue(level-order traversal) START
    
    while( !q.empty() ){
        TreeNode *current = q.front();
        q.pop();
        cout << current->data << " ";
        
        if( current->leftchild != NULL ){
            q.push( current->leftchild );
        }
        if( current->rightchild != NULL ){
            q.push( current-> rightchild );
        }
    }
}


// This function is for PartTwo Meaty to delete the trapIndex node in postorder.
// Check every node in BST in postorder.
void Tree::PostorderDelete( TreeNode *node, int trapIndex ){
    if(node){
        PostorderDelete( node->leftchild, trapIndex );
        PostorderDelete( node->rightchild, trapIndex );
        int x = node->data;
        while(x){
            if(x%10 == trapIndex){
                Delete(node->data);
                break;
            }
            x/=10;
        }
    }
}


// This function is for PartTwo Meaty to find sword and Meaty. Meanwhile, output the finding path.
// Find Sword, the same way as Search function.
// Find Meaty, using stack(FILO) to store the finding path, so that when we find nothing in the subtree that would make turn back to the subtree's parent easier. If find the Meaty, turn the satck up-side-down and ouput the path.
void Tree::FindSwordMeaty(int sword, int meaty){
    //Find Sword
    TreeNode *current = root;
    cout << current->data;
    while( current != NULL && current->data != sword){
        if( sword < current->data ){
            current = current->leftchild;
        }
        else{
            current = current->rightchild;
        }
        cout << "->" << current->data  ;     // have output sword
    }
    
    //Find Meaty
    if(sword==meaty) {
        return;
    }
    
    stack <TreeNode*> s;
    TreeNode *crown = current;  //current is sword ,which is the finding subtree'root in next step
    
    // while-loop to Find Meaty in the subtree of crown==root.
    while(1){
        while(current != NULL && current->data != meaty ){  // scan the subtree to the NULL
            if( meaty < current->data){
                current = current->leftchild;
            }
            else{
                current = current->rightchild;
            }
            s.push(current);
        }
        
        if( current!=NULL && current->data == meaty ) {     // Find Meaty!!
            stack <TreeNode*> temp_s;
            while ( !s.empty() ) {      // turn the stack up-side-down
                current = s.top();
                s.pop();
                temp_s.push(current);
            }
            
            while ( !temp_s.empty() ) {     // output the path
                current = temp_s.top();
                cout << "->" << current->data;
                temp_s.pop();
            }
            return;
        }
        
        //if( current==NULL ) ,Meaty is not under the subtree of the crown. So go to crown's parent, and make stack empty.
        while ( !s.empty() ) {
            s.pop();
        }
        
        crown = crown->parent;
        current = crown;
        cout << "->" << crown->data;    //Don't forgat to output crown.
    }
}


// Input the bstmap file, line by line, assign to array and build BST.
int Input( int array[] ){
    char filename[100]={0};  //Input fileName
    int i=0;
    while(1){
        cout << "Please input the map file: " ;
        cin >> filename;
        ifstream inFile;
        inFile.open(filename);
        
        if (!inFile.is_open()) {cout<<"fail to open the file！"<<endl; continue;}
        
        cout << "Load file success." << endl << endl;
        while (inFile) {
            string str;
            getline(inFile,str);
            try {
                array[i] = stoi(str);
            } catch (exception& e) {
                break;
            }
            i++;
        }
        break;
    }
    return i;
}


// PartTwo, input bstmap and build BST, delete trapIndex, find sword & Meaty.
void PartTwo(){
    Tree T2;
    int sword, meaty, trapIndex;
    
    int temp[1024]={0};
    int number;
    number = Input(temp);
    
    for(int i=0; i<number; i++){
        T2.Insert(temp[i]);
    }
    
    cout << "Please input the sword location: " ;
    cin >> sword;
    cout << "Please input the Meaty's location: " ;
    cin >> meaty;
    cout << "Please input the broccoli trap's index (0~9): " ;
    cin >> trapIndex;
    cout << endl;
    
    T2.PostorderDelete( T2.root, trapIndex );
    
    cout << endl << "Capoo successfully found his favorite meaty<3." << endl;
    cout << endl << "Shortest path to find the meaty :" << endl;
    T2.FindSwordMeaty( sword, meaty);
    cout << endl;
    
    return;
}


// PartOne, do inser, delete, search, prrint, return in user's order.
void PartOneBST(){
    Tree T;
    char st='S';
    
    while( st != 'r' ){
        cout << "(I)nsert a number" << endl;
        cout << "(D)elete a number" << endl;
        cout << "(S)earch a number" << endl;
        cout << "(P)rint 4 kinds of order" << endl;
        cout << "(R)eturn" << endl;
        cin >> st;
        
        switch (st) {
            case 'i':{
                cout << "Enter numbers: ";
                int num=0;
                cin >> num;
                while(num!=-1){
                    TreeNode* existNode = T.Search(num);
                    if( existNode!=NULL ){   
                        cout << "Error. Number " << num << " exists." << endl;
                    }
                    else{
                        T.Insert(num);
                        cout << "Number " << num << " is inserted." << endl;
                    }
                    cin >> num;
                }
                break;
            }
            case 'd':{
                cout << "Enter numbers: ";
                int num=0;
                cin >> num;
                while(num!=-1){
                    T.Delete(num);
                    cin >> num;
                }
                break;
            }
            case 's':{
                cout << "Enter elements to searching : ";
                int num=0;
                cin >> num;
                while(num!=-1){
                    TreeNode* existNode = T.Search(num);
                    if( existNode!=NULL ){
                        cout << "Bingo! " << num << " is found." << endl;
                    }
                    else{
                        cout << "SORRY. " << num << " is not found." << endl;
                    }
                    cin >> num;
                }
                break;
            }
            case 'p':{
                cout << "The tree in prefix order : ";
                T.Preorder( T.root );
                cout << endl;
                cout << "The tree in infix order : ";
                T.Inorder( T.root );
                cout << endl;
                cout << "The tree in post order : ";
                T.Postorder( T.root );
                cout << endl;
                cout << "The tree in level order : ";
                T.Levelorder( T.root );
                cout << endl;
                break;
            }
            case 'r':{
                break;
            }
        }
    }
}


// where main menu is, and initiate with PartOne function
int main(int argc, const char * argv[]) {
    int num = 1;
    while ( num!=0 ) {
        if(num==0) { break; }
        if(num==2){
            PartTwo();
        }
        if (num==1){
            PartOneBST();
        }
        cout << "(1)Binary Searching Tree." << endl;                //main menu
        cout << "(2)Finding Meaty." << endl;
        cout << "(0)Escape and face to music next year." << endl;

        cin >> num;
    }
    
    return 0;
}
