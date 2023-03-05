#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <set>
using namespace std;

class TreeNode 
{
    public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) { 
        val = x; 
    }
};

ofstream ofs;

// Acording to Preorder & Inorder, build a Tree
TreeNode* buildTree_byPre(int preorder[], int inorder[],int n)
{
    TreeNode* root = NULL;
    set<TreeNode*> s;
    stack<TreeNode*> st;
    for (int pre = 0, in = 0; pre < n;) 
    {
        TreeNode* node = NULL;
        do
        {
            node = new TreeNode(preorder[pre]);
            if (root == NULL)
            {
                root = node;
            }
            if (st.size() > 0) 
            {
                if (s.find(st.top()) != s.end())
                {
                    s.erase(st.top());
                    st.top()->right = node;
                    st.pop();
                }
                else
                {
                    st.top()->left = node;
                }
            }
            st.push(node);
        } while (preorder[pre++] != inorder[in] && pre < n);

        node = NULL;
        while (st.size() > 0 && in < n && 
                st.top()->val == inorder[in]) 
        {
            node = st.top();
            st.pop();
            in++;
        }

        if (node != NULL) 
        {
            s.insert(node);
            st.push(node);
        }
    }

    return root;
}

// Acording to Postorder & Inorder, build a Tree
TreeNode *buildTree_byPos(int post[], int in[], int n) 
{
    TreeNode* root = NULL;
    stack<TreeNode*> st;
    set<TreeNode*> s;
    for (int p = n - 1, i = n - 1; p>=0;)  
    { 
    TreeNode* node = NULL; 
    
    do
    {
      node = new TreeNode(post[p]); 

      if (root == NULL) { 
        root = node; 
      } 
      
      if (st.size() > 0)  
      { 

        if (s.find(st.top()) != s.end()) 
        { 
          s.erase(st.top()); 
          st.top()->left = node; 
          st.pop(); 
        } 
        else
        { 
          st.top()->right = node; 
        } 
      }
      
      st.push(node); 
      
    } while (post[p--] != in[i] && p >=0); 

    node = NULL; 
    
    while (st.size() > 0 && i>=0 &&  
           st.top()->val == in[i])  
    { 
      node = st.top(); 
      st.pop(); 
      i--; 
    } 
    
    if (node != NULL)  
    { 
      s.insert(node); 
      st.push(node); 
    } 
  } 
  
  return root;

}

// Print the tree in Postorder
void printPostorder(TreeNode* node)
{
    if (node == NULL)
        return;

    printPostorder(node->left);
    printPostorder(node->right);
    ofs << node->val << " ";
}

// Print the tree in Preorder
void printPreorder(TreeNode* node)
{
    if (node == NULL)
        return;

    ofs << node->val << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

// Load the input file, and execute the command function
void Input(){
    char filename[100]={0};  //Input fileName
    while(1){
        cout << "Please input the file: " ;
        cin >> filename;
        ifstream input_file(filename);
        if (!input_file.is_open()) {
            cout<<"fail to open the file！"<<endl; 
            continue;
        }
        cout << "Load file success." << endl << endl;


        // For Output
        filename[0] = 'o';
        filename[1] = 'u';
        ofs.open(filename);

        // Function
        int dataset_num = 0;
        int count_dataset = 0;
        input_file >> dataset_num;
        while (count_dataset<dataset_num)
        {   
            int node_num;
            string ordertype;
            input_file >> ordertype;

            input_file >> node_num;
            int p[node_num], in[node_num];
            for( int i=0; i< node_num; i++){
                input_file >> p[i];
            }
            for( int i=0; i< node_num; i++){
                input_file >> in[i];
            }
            
            if( ordertype.compare("preorder-inorder") == 0 ){
                TreeNode *root = buildTree_byPre( p, in, node_num );
                printPostorder(root);
                ofs << "\n";
            }
            else{
                TreeNode *root = buildTree_byPos( p, in, node_num );
                printPreorder(root);
                ofs << "\n";
            }
            count_dataset++;
        }
        input_file.close();
        ofs.close();
        break;
    }
}

int main(){
    Input();

    return 0;
}