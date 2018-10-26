#include "mf.h"
vector<list<MF *> > MF::MF_TREE;

int main() {
    MF *mf = new MF;
    list<MF *> root;
    list<MF *> parents;
    list<MF *> list_children;
    root.push_back(mf);
    //第一层
    MF::MF_TREE.push_back(root);

    //第二层
    list_children = root;    
    int i = 1;
    while(true) {
	parents = list_children;
	list_children = MF::born_tree_leafs(parents);
	list_children = MF::check_list_children(list_children);
	if(!list_children.size())
	    break;
	MF::MF_TREE.push_back(list_children);
	cout<<"leaf size:"<<list_children.size()<<endl;
	cout<<"tree size:"<<MF::MF_TREE.size()<<endl;
	++i;
    }
    int sum = -1;
    for(vector<list<MF *> >::size_type it = 0; it < MF::MF_TREE.size(); ++it) {
	sum += MF::MF_TREE[i].size();
    }
    cout<<"sum :"<<sum<<endl;
    return 0;
}
