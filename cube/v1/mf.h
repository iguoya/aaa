#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <utility>

using std::vector;
using std::list;
using std::map;
using std::string;
using std::pair;
using std::cout;
using std::cin;
using std::endl;
using std::make_pair;

class MF {
public:
    static vector<list<MF *> > MF_TREE;
    //set rules
    void set_rules();
    //roll
    void roll(const map<int, int> &);
    //compare
    bool compare(MF *);
    static bool row_same_row(int[], int[]);
    vector<map<int, int> >& get_rules() {return rule_format;};
    void show_mf();
    void add_tree_leafs(list<MF *> );
    static list<MF *> born_tree_leafs(const list<MF *> );
    list<MF *> born_children();
    bool compare_family(MF *&);
    bool compare_list_children(const list<MF *>, MF *&);
    static list<MF *> check_list_children(list<MF *>);
    MF();
    ~MF();
    int r[6][4];//现有的节点关系
    int num;
private:
    
    vector<map<int, int> > rule_format;    //所有可能的节点替换对
};
