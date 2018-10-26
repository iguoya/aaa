#include "mf.h"
static int global_num = 1;
MF::MF() {
    int rules[6][4] = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{1, 2, 6, 5},
	{3, 4, 8, 7},
	{1, 5, 8, 4},
	{2, 6, 7, 3}
    };
    num = 0;
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 4; ++j)
            r[i][j] = rules[i][j];
    set_rules();
}

void MF::show_mf() {
    cout<<"*****begin*******"<<endl;
    for(int i = 0; i < 6; ++i) {
	for(int j = 0; j < 4; ++j)
	    cout<<r[i][j]<<", ";
	cout<<endl;
    }
    cout<<"*****end*******"<<endl;
}
void MF::set_rules() {
    rule_format.clear();
    for(int i = 0; i < 6; ++i) {
	map<int, int> s_rule, r_rule;
	for(int j = 0; j <= 3; ++j) {
	    if(j == 3) {
		s_rule.insert(make_pair(r[i][j], r[i][0]));
	    } else {
		s_rule.insert(make_pair(r[i][j], r[i][j+1]));
	    }
	    if(j == 0) {
		r_rule.insert(make_pair(r[i][j],r[i][3]));
	    } else {
		r_rule.insert(make_pair(r[i][j],r[i][j-1]));
	    }
	}
	rule_format.push_back(s_rule);		//正向规则
	rule_format.push_back(r_rule);    	//反向规则
    }
}
//根据规则，生成节点对, 依照节点对产生新规则结构
void MF::roll(const map<int, int> &p_rule) {
    for(int i = 0; i < 6; ++i) {
	for(int j = 0; j < 4; ++j) {
	    //如果r[i][j] in p_rule's key , change its value
	    for(map<int, int>::const_iterator it = p_rule.begin();
		it != p_rule.end(); ++it)
		if(r[i][j] == it->first) {
		    r[i][j] = it->second;
		    break;
		}
	}
    }
}
bool MF::row_same_row(int a[], int b[]) {

    //判断队列元素是否相同
    for(int i = 0; i < 4; ++i) {
	int flag = 0;
	for(int j = 0; j < 4; ++j) {
	    if(a[i] == b[j]) {
		flag = 1;
		break;
	    }
	}
	if (flag == 0) {
	    return false;
	}
    }

    // 两个队列 元素相同
    //eg: {1,2,3,4} == {3,4,1,2} or {3,2,1,4},{4, 3, 2, 1}
    //but != {2,1,3,4}
    int ix = 0, flag = 0;
    //正向对比
    for(int i = 0; i != 4; ++i) {
	ix = i;
	flag = 0;
	for(int j = 0; j != 4; ++j) {
	    if(a[ix] != b[j] && flag == 1) {
		flag = 2;
		break;
	    }
	    if(a[ix] == b[j]) {
		ix = (ix+1) % 4;
		flag = 1;
	    }
	}
	if (flag == 2) break;//正向失败,试试反向对比
	if (flag == 1)
	    return true;
    }
    //反向对比
    int jm = 0;
    for(int i = 0; i != 4; ++i) {
	flag = 0;
	for(int j = 3; j >= -1; --j) {
	    jm = (j+4)%4;
	    //	    cout<<a[i]<<" vs "<<b[jm]<<" "<<j<<" "<<jm<<" "<<i<<endl;
	    if(a[i] != b[jm] && flag == 1)
		return false;
	    if(a[i] == b[jm]) {
		++i;
		flag = 1;
	    }
	}
	if (flag == 1) return true;
    }
    return false;
}

bool MF::compare(MF *obj) {
    for(int i = 0; i< 6; ++i) {
	int flag = 0;
    	//whether r[i] is same the row in obj 
    	for(int j = 0; j < 6; ++j) {
	    if(row_same_row(r[i], obj->r[j])) {
		flag = 1;
		break;
	    } 
	}
	if (flag == 0)  {
	    return false;
	}
    }
    return true;
}

void MF::add_tree_leafs(list<MF *> leafs) {
    MF::MF_TREE.push_back(leafs);
}


list<MF *> MF::born_tree_leafs(const list<MF *> parents) {
    list<list<MF *> > children;
    list<MF *> list_children;
    for(list<MF *>::const_iterator it = parents.begin();
	it != parents.end(); ++it) {
	children.push_back((*it)->born_children());
    }
    for(list<list<MF *> >::iterator it = children.begin();
	it != children.end(); ++it)
	for(list<MF *>::iterator ip = it->begin();
	    ip != it->end(); ++ip)
	    list_children.push_back(*ip);
	    
    return list_children;
}

bool MF::compare_family(MF *&same) {
    for(vector<list<MF *> >::iterator it = MF_TREE.begin();
	it != MF_TREE.end(); ++it) {
	for(list<MF *>::iterator ip = it->begin();
	    ip != it->end(); ++ip) {
	    if(compare(*ip)) {
		same = *ip; 
		return true;
	    }
	}
    }
    return false;
}
bool MF::compare_list_children(const list<MF *> list_children,
			       MF *&same) {
    for(list<MF *>::const_iterator ix = list_children.begin();
	ix != list_children.end(); ++ix) {
	if(compare(*ix)) {
	    same = *ix;
	    return true;
	}
    }
    return false;
}

list<MF *> MF::check_list_children(list<MF *> children) {
    list<MF *> list_children;
    MF *t = NULL;
    for(list<MF *>::iterator ip = children.begin();
	ip != children.end(); ++ip) {
	//	cout<<(*ip)->num<<endl;
	//	(*ip)->show_mf();
	//对比tree形式的父辈队列, 对比list形式的children队列
	if((*ip)->compare_family(t)) {
	    // cout<<"same family\n";
	    // (*ip)->show_mf();
	    // cout<<"----";
	    // t->show_mf();
	    // cout<<endl;
	    delete (*ip);
	    continue;
	}
	if((*ip)->compare_list_children(list_children, t)) {
	    // cout<<"-------------------------\n";
	    // cout<<"same children\n";
	    // (*ip)->show_mf();
	    // cout<<(*ip)->num<<"----"<<t->num<<endl;
	    // t->show_mf();
	    // cout<<"--------------------------\n";
	    delete (*ip);
	    continue;
	}
	list_children.push_back(*ip);
    }
    return list_children;
}


list<MF *> MF::born_children() {
    list<MF *> children;
    for(vector<map<int, int> >::size_type it = 0;
	it != rule_format.size(); ++it) {
	MF *n_mf = new MF(*this);
	n_mf->roll(rule_format[it]);
	n_mf->num = global_num;
	++global_num;
	n_mf->set_rules();
	children.push_back(n_mf);
    }
    return children;
}
MF::~MF() {
}

