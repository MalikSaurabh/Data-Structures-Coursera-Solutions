#include<bits/stdc++.h>
using namespace std;
  
void max_sliding_window_naive(vector<int> const & A, int w) 
{    
    int n = A.size();
    vector<int> B;
    B.resize(n - w + 1);
    deque<int> Q;
    for (int i = 0; i < w; i++) 
    {
        while (!Q.empty() && A[i] >= A[Q.back()])
            Q.pop_back();
            Q.push_back(i);
    }
            
    for (int i = w; i < n; i++) 
    {
        B[i - w] = A[Q.front()];
        while (!Q.empty() && A[i] >= A[Q.back()])
            Q.pop_back();
        while (!Q.empty() && Q.front() <= i - w)
            Q.pop_front();
        Q.push_back(i);
    }
    B[n - w] = A[Q.front()];
    for(int i=0; i<B.size(); i++)
        cout << B[i]<<" ";

    return;   
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
