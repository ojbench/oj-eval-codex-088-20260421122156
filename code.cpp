#include <bits/stdc++.h>
using namespace std;

// Subtask 1: Manually implemented singly-linked list queue
struct Node {
    long long val;
    Node* next;
    Node(long long v): val(v), next(nullptr) {}
};

struct MyQueue {
    Node* head;
    Node* tail;
    size_t sz;
    MyQueue(): head(nullptr), tail(nullptr), sz(0) {}
    ~MyQueue(){
        while(head){
            Node* t=head; head=head->next; delete t;
        }
        tail=nullptr; sz=0;
    }
    void push(long long x){
        Node* n=new Node(x);
        if(!tail){ head=tail=n; }
        else { tail->next=n; tail=n; }
        ++sz;
    }
    long long front(){ return head? head->val : -1; }
    void pop(){
        if(!head) return;
        Node* t=head; head=head->next; if(!head) tail=nullptr; delete t; --sz;
    }
    size_t size() const { return sz; }
};

// Compute last remaining card for subtask 2 efficiently
// Operation each round: move front to back, then discard new front
// Pattern: answer is the largest odd <= n with period 2^k; specifically
// it equals: 2 * (n - 2^floor(log2 n)) + 1? (Not here.) From simulation,
// the answer sequence for n in [1..2^m] is: 1,1,3,1,3,5,7,1,... i.e.,
// last(n) = 2 * (n - 2^k) + 1 when n in (2^k, 2^{k+1}] with odd restriction.
// Observed closed form: let k be highest power of two <= n. Then
// if n == k: return 1; else return 2*((n-k)//2)+1 -> simplifies to 2*(n-k)-1? Not correct.
// Actually from samples: for n in (2^k, 2^{k+1}], last runs over odd numbers 1..(2^{k+1}-1)
// starting from 1 at n=2^k and increases by 2 each step. So:
// last(n) = 2*((n - 2^k) % 2^k) + 1 = 2*(n - 2^k) + 1 for n in [2^k, 2^{k+1}] inclusive
// This formula matches sequence printed in analysis.

static inline unsigned long long highest_power_of_two_leq(unsigned long long n){
    if(n==0) return 0;
    // Set all bits below highest, then +1>>1
    n |= n>>1; n |= n>>2; n |= n>>4; n |= n>>8; n |= n>>16; n |= n>>32;
    return (n+1)>>1;
}

unsigned long long solve_last(unsigned long long n){
    if(n==0) return 0;
    unsigned long long k = highest_power_of_two_leq(n);
    // For n in [k, 2k], answer = 2*(n-k)+1
    return 2*(n - k) + 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long id; unsigned long long n;
    if(!(cin>>id>>n)) return 0;
    if(id==1){
        // Simulate using manual linked list and output top after each round
        MyQueue q;
        for(unsigned long long i=1;i<=n;i++) q.push((long long)i);
        for(unsigned long long round=1; round<= (n>0? n-1: 0); ++round){
            // move front to back
            if(q.size()>0){
                long long x=q.front(); q.pop(); q.push(x);
            }
            // discard new front
            if(q.size()>0){
                q.pop();
            }
            // output new top
            if(q.size()>0) cout<<q.front()<<"\n";
        }
    } else if(id==2){
        cout<<solve_last(n);
    }
    return 0;
}

