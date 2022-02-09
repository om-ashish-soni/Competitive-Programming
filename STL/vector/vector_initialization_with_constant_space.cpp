vector<string> vs = vector<string>(5);
vector<int> vi{vector<int>(5,0)};

// You can initialize the data members at the point of declaration, but not with () brackets:

class Foo {
    vector<string> name = vector<string>(5);
    vector<int> val{vector<int>(5,0)};
};

// Before C++11, you need to declare them first, then initialize them e.g in a contructor

class Foo {
    vector<string> name;
    vector<int> val;
 public:
  Foo() : name(5), val(5,0) {}
};
