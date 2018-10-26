#include <vector>
#include <list>
#include "mf.h"


class MF_TREE {
public:
    set_root(MF *r) { root = r; };
    void add_tree_level(list<MF *> );
    //    static list<MF *> born_tree_leafs(const list<MF *> );
    // 
 private:
    MF * root;
    vector<list<MF *> > nodes;
};

MF_TREE::set
