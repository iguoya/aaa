#include "../MF.cpp"
#include <gtest/gtest.h>  


class MFT : public testing::Test {
protected:
    static void SetUpTestCase() {
    }
    static void TearDownTestCase() {

    }

};

TEST_F(MFT, set_rule) {
    MF *mf = new MF;
    ASSERT_EQ(12, mf->get_rules().size());
    delete mf;
    // mf->show_mf();
    // ASSERT_TRUE(0);
    // //测试正反规则
    // int t[6][4] = {
    // 	{1, 2, 3, 4},
    // 	{5, 6, 7, 8}, 
    // 	{1, 2, 6, 5}, 
    // 	{3, 4, 8, 7}, 
    // 	{1, 5, 8, 4}, 
    // 	{2, 6, 7, 3},
    // };

	
    // 	vector<map<int, int> > r = mf->get_rules();
	
    // 	EXPECT_EQ(12, r.size());

    // 	int flag = 1;
    // 	    int i = 0;

    // 	for(vector<map<int, int> >::iterator it = r.begin();
    // 	    it != r.end(); ++it, ++i) {
    // 	    flag %= 2;
    // 	    int j = 0;
    // 	    for(map<int, int>::iterator ip = it->begin();
    // 		ip != it->end(); ++ip, ++j) {
    // 		if(flag == 1) {
    // 		EXPECT_EQ(t[i][j], ip->first);
    // 		EXPECT_EQ(o[i][j], ip->second);
    // 		} else {
    // 		EXPECT_EQ(t[i][j], ip->first);
    // 		EXPECT_EQ(o1[i][j], ip->second);
    // 		}
    // 	    }
    // 	    ++flag; 
    // 	}
}

TEST_F(MFT, compare_row) {

    int a[] = {1,2,3,4};
    int b[] = {2,3,4,1};
    int c[] = {3,4,1,2};
    int c1[] = {4,1,2,3};
    int c2[] = {2,3,1,4};
    int d[] = {2,1,3,4};
    int e[] = {2,1,4,3};
    int f[] = {3,2,1,4};
 
    //同向
    EXPECT_TRUE(MF::row_same_row(a, b));
    EXPECT_TRUE(MF::row_same_row(a, c));
    EXPECT_TRUE(MF::row_same_row(a, c1));
    EXPECT_FALSE(MF::row_same_row(a, c2));
    //逆向
    EXPECT_FALSE(MF::row_same_row(a, d));
    EXPECT_TRUE(MF::row_same_row(a, e));
    EXPECT_TRUE(MF::row_same_row(a, f));
  
}
TEST_F(MFT, roll) {
    MF *T = new MF;
    map<int, int> r;
    r[1] = 2;
    r[2] = 3;
    r[3] = 4;
    r[4] = 1;
    int exp[6][4] = {
	{2,3,4,1},
	{5,6,7,8},
	{2,3,6,5},
	{4,1,8,7},
	{2,5,8,1},
	{3,6,7,4},
    };
    MF *m = new MF(*T);
    m->roll(r);
    for(int i = 0; i != 6; ++i) {
	for(int j = 0; j!=4; ++j) {
	    EXPECT_EQ(exp[i][j], m->r[i][j]);
	}
    }
    delete m;
    r.clear();
    // another test
    r[1] = 5;
    r[2] = 1;
    r[6] = 2;
    r[5] = 6;
    int exp1[6][4] = {
	{5,1,3,4},
	{6,2,7,8},
	{5,1,2,6},
	{3,4,8,7},
	{5,6,8,4},
	{1,2,7,3},
    };
    m = new MF(*T);
    m->roll(r);
    for(int i = 0; i != 6; ++i) {
	for(int j = 0; j!=4; ++j) {
	    //	    	    cout<<m->r[i][j]<<",";
	    EXPECT_EQ(exp1[i][j], m->r[i][j]);
	}
	//		cout<<endl;
    }
    delete m;    
}
TEST_F(MFT, compare_mf) {
    int a[4] = {1,2,3,4};
    int b[4] = {3,4,1,2};
    int c[4] = {3,2,1,4};
    int d[4] = {4,3,2,1};
    int e[4] = {2,1,3,4};//wrong
    int f[4] = {3,1,2,4};//wrong
    ASSERT_TRUE(MF::row_same_row(a, b));
    ASSERT_TRUE(MF::row_same_row(a, c));
    ASSERT_TRUE(MF::row_same_row(a, d));
    ASSERT_FALSE(MF::row_same_row(a, e));
    ASSERT_FALSE(MF::row_same_row(a, f));
    int aa[4] = {2, 3, 6, 5};
    int bb[4] = {2, 6, 7, 3};
    ASSERT_FALSE(MF::row_same_row(aa, bb));
    
    
    MF *mf = new MF;
    //**************测试 整体状态对比********************
    EXPECT_TRUE(mf->compare(mf));
    vector<map<int, int> > rule_format = mf->get_rules();
    for(vector<map<int, int> >::size_type it = 0;
	it != mf->get_rules().size(); ++it) {
	MF *n_mf = new MF(*mf);
	n_mf->roll(rule_format[it]);
	EXPECT_FALSE(n_mf->compare(mf));
	delete n_mf;
    }
    delete mf;
}

TEST_F(MFT, main) {
    MF *mf = new MF;
    list<MF *> root;
    list<MF *> parents;
    list<MF *> list_children;
    root.push_back(mf);
    //第一层
    EXPECT_EQ(1, root.size());
    MF::MF_TREE.push_back(root);
    EXPECT_EQ(1, MF::MF_TREE.size());
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
    int sum = 0;
    for(int i = 0; i < MF::MF_TREE.size(); ++i) {
	sum += MF::MF_TREE[i].size();
    }
    cout<<"sum :"<<sum<<endl;
}

int main(int argc, char **argv) {
    //    testing::AddGlobalTestEnvironment(new MFEnvironment);
    testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();  
}
