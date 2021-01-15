// https://www.hackerrank.com/challenges/accessing-inherited-functions/problem

#include <fstream>
#include <iostream>

// This is used as replacement for the cin stream on hackerrank
std::ifstream fin("input/test_case_0.txt", std::ifstream::in);

using namespace std;

class A {
   public:
    A() { callA = 0; }

   private:
    int callA;
    void inc() { callA++; }

   protected:
    void func(int &a) {
        a = a * 2;
        inc();
    }

   public:
    int getA() { return callA; }
};

class B {
   public:
    B() { callB = 0; }

   private:
    int callB;
    void inc() { callB++; }

   protected:
    void func(int &a) {
        a = a * 3;
        inc();
    }

   public:
    int getB() { return callB; }
};

class C {
   public:
    C() { callC = 0; }

   private:
    int callC;
    void inc() { callC++; }

   protected:
    void func(int &a) {
        a = a * 5;
        inc();
    }

   public:
    int getC() { return callC; }
};

class D : public A, public B, public C {
    int val;

   public:
    // Initially val is 1
    D() { val = 1; }

    // Implement this function
    void update_val(int new_val) {
        this->val = new_val;
        int product = 1;
        while (product < new_val) {
            // std::cout<<"Value before call "<<new_val<<std::endl;
            if ((new_val / product) % 2 == 0) {
                this->A::func(product);
            } else if ((new_val / product) % 3 == 0) {
                this->B::func(product);
            } else if ((new_val / product) % 5 == 0) {
                this->C::func(product);
            }

            // std::cout<<"Value after call "<<new_val<<std::endl;
            // break;
        }
    }
    // For Checking Purpose
    void check(int);  // Do not delete this line.
};

void D::check(int new_val) {
    update_val(new_val);
    cout << "Value = " << val << endl
         << "A's func called " << getA() << " times " << endl
         << "B's func called " << getB() << " times" << endl
         << "C's func called " << getC() << " times" << endl;
}

int main() {
    D d;
    int new_val;
    fin >> new_val;
    // cout<<new_val<<endl;
    d.check(new_val);
    return 0;
}