#include <bits/stdc++.h>
using namespace std;
struct seg
{
    int l, h;
};
struct node
{
    seg s; 
    int max;
    node *left, *right;
};
node *create(seg s)
{
    node *curr = new node;
    curr->s = s;
    curr->max = s.h;
    curr->left = curr->right = NULL;
}
node *mininterval(node* n)
{
    node* curr = n;
    while (curr->left != NULL)
        curr = curr->left;
 
    return curr;
}
bool checkoverlap(seg s1, seg s2)
{
    if (s1.l<= s2.h && s2.l <= s1.h)
    return true;
    else    
    return false;
}
node *insertinterval(node *root, seg s)
{
    if (root == NULL)
        return create(s);
    int l = root->s.l;
    if (s.l < l)
        root->left = insertinterval(root->left, s);
    else
        root->right = insertinterval(root->right, s);
    if (root->max < s.h)
        root->max = s.h;
 
    return root;
}
node *deleteinterval(node *root, seg k)
{
    
    if (root == NULL) return root;
    if (k.l< root->s.l)
        root->left = deleteinterval(root->left, k);
    else if (k.l > root->s.l)
        root->right = deleteinterval(root->right, k);
    else
    {
    	
        if (root->left == NULL)
        {
            node *curr = root->right;
            free(root);
            return curr;
        }
        else if (root->right == NULL)
        {
            node *curr = root->left;
            free(root);
            return curr;
        }
        node *curr = mininterval(root->right);
        root->s = curr->s;
 
        root->right = deleteinterval(root->right, curr->s);
    }
    return root;
}

seg search(node *root, seg s)
{
    seg temp;
    temp.l=temp.h=-9999;
    if (root == NULL) return temp;
    if (checkoverlap((root->s), s))
        return root->s;
    if (root->left != NULL && root->left->max >= s.l)
        return search(root->left, s);
    else    
    return search(root->right, s);
}
int main()
{
    
    int cnt;
    cout<<"enter number of intervals you want to enter"<<endl;
    cin>>cnt;
    cout<<"enter the intervals"<<endl;;
    seg s;
    node *root = NULL;
    for (int i = 0; i < cnt; i++)
    {
    	cin>>s.l>>s.h;
        root = insertinterval(root, s);
    }
    cout<<"enter the interval to search for overlap"<<endl;
    cin>>s.l>>s.h;
       seg result =search(root, s);
    if (result.l == -9999 && result.h==-9999)
        cout << "Not found overlap"<<endl;
    else
        cout << "Overlaps with interval "<< result.l << ", " << result.h <<endl;
     cout<<"enter the interval you want to delete"<<endl;
	 cin>>s.l>>s.h;   
	 root=deleteinterval(root,s);
	 cout<<"enter the interval to search after deletion"<<endl;
    cin>>s.l>>s.h;
       result = search(root, s);
    if (result.l == -9999 && result.h==-9999)
        cout << "Not found overlap"<<endl;
    else
        cout << "Overlaps with interval " << result.l << ", " << result.h <<endl;
    return 0;
}