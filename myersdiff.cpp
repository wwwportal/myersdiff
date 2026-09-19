#include <vector>
#include <string>
#include <cmath>
#include <iostream>

// TO CLARIFY
// - A D-path has D+1 snakes, some of which may be empty
// - There must be a difference, between D and a D-path, right?
//      D is simply the length of the shortest edit script
//      and D-path is the actual path, or edit script?
// - Why is V[1] set to 0 if it's range is defined as -MAX to MAX? Shouldn't V[1] then be -MAX+1? I have some assumptions that could provide an answer. First of all, the vector is 1-indexed and not 0-indexed, so V[1] is the first and not the second component of the vector. If that's the case, then we're simply assigning the first component to be equal to 0, since we already know that for the first diagonal, the furthest ending path will be in diagonal k=0 (or 1 if it's 1-indexed) will be 0. Is this correct?


//////////////////////////
// A = the first sequence
// B = the second sequence
// N = sum of the lengths of A and B
// L = length of the longest common subsequence
//      which is equivalently the length of the shortest edit script
// D = 2(N-L) = the length of the shortest edit script for A and B
// D has also been descripted as the number of non-diagonal edges
// which is also a trace of Length L
// R = the number of diagonal edges in the edit graph, or the total number of match points
// Snakes(D-path) = D+1 
// delta = N-M

// script commands
// void delete(int pos);
// void insert(int pos, char c);

// Prototypes
void LCS(std::string,std::string);
std::vector<int> findMiddleSnake(std::vector<int>&,std::string,std::string,int,int);

// Least Common Subsequence
void LCS(std::string A, std::string B) {
    int N = A.size();
    int M = B.size();
    if (N>0 && M>0) {
        // find the middle snake and length of an optimal path for A and B
        // Middle Snake = ceiling(D/2)+1
        // suppose it is from (x,y) to (u,v)
        std::vector<int> result(5);
        findMiddleSnake(result,A,B,N,M);
        int D = result[0];
        int x = result[1];
        int y = result[2];
        int u = result[3];
        int v = result[4];

        if ( D > 1 ) {
            // erase first element of A
            // erase first element of B
            A.erase(0);
            B.erase(0);
            // erase elements in A after x
            for(int i = x+1; i < A.size(); i++) {
                A.erase(i);
            }
            // erase elements in B after y
            for (int i = y+1; i < B.size(); i++) {
                B.erase(i);
            }

            LCS(A,x,B,y);

            // print elements in A from x+1 to u
            for (int i = x+1; i <= u; i++) {
                std::cout << A[i] << std::endl;
            }

            // erase elements in A before u+1
            // N should be the end of the sequence 
            for (int i = 0; i < u+1; i++) {
                A.erase(i);
            }
            // erase elements in B before v+1
            for ( int i = 0; i < v+1; i++ ) {
                B.erase(i);
            }
                
            LCS(A,N-u,B,M-v);
        } 
        else if ( M > N ) {
            for ( a : A ) {
                std::cout << a << std::endl;
            }
        } 
        else {
            for ( b : A ) {
                std::cout << b << std::endl;
            }
        }
    }
}

std::vector<int> findMiddleSnake(std::vector<int>& result, std::string A, std::string B, int N, int M) {
    std::vector<int> result(5); // middle snake and optimal distance
    const int MAX = N*N;
    // the two vectors for forward and reverse path
    std::vector<int> Vf(2*MAX+1);
    std::vector<int> Vr(2*MAX+1);
    int delta = N-M;
    int x,y,u,v;
    // Find middle snake.
    for ( int D = 0; D <= ceil((const_cast<doubles>(M+N))/2); D++ ) {
        // 
        for ( int k = -D; k <= D; k+=2 ) {
            int k1 = k+MAX; // adjust vector indexing value 
            // Find the end of the furthest reaching forward D-path in diagonal k
            if (k==-D || k! == D && Vf[k1-1] < Vf[k1+1]) {
                x = Vf[k+1];
            }
            else {
                x = Vf[k-1]+1;
            }
            y = x-k;

            while ( x<N && y < M && A[x+1] == B[y+1]) {
                x++;
                y++;
            }
            Vf[k1] = x;

            // from lemma 1, check if possible overlap 
            if (!isEven(delta) && k >= delta-(D-1) && k <= delta+(D-1)) {
                // if the path overlaps the furthest reaching reverse (D-1)-path in diagonal
                
                if( Vf[k]==Vr[k+delta] && x<u ) {
                    // length of an SES is 2D-1, not needed to build SES
                    // last snake of the forward path is the middle path
                    result.push_back(x);
                    result.push_back(y);
                    result.push_back(u);
                    result.push_back(v);
                    result.push_back(2*D-1);
                }

            }
        }
        for ( int k = -D; k <= D; k+=2 ) {
            int k1 = k+MAX; // adjusted to avoid negative indexing
            // find the end of the furthest reaching reverse D-path in diagonal k+delta
            if (k == -D || k == D && Vr[k1-1] < Vr[k1+1]) {
                u = Vr[k1+1];
            } else {
                u = Vr[k1-1]-1;
            }
            v = u-k;
            while( u<N && v<M && A[u] == B[v] ){
                v--;
                u--;
            }
            Vr[k1] = u;
            // possible overlap
            if ( isEven(delta) && k >= -D && k <= D-1 ) {
                // if the path overlaps the furthest reaching forward D-path in diagonal k+delta
                if( Vf[k1]==Vr[k1+delta] && x<u ) {
                    // length of an SES is 2D
                    // the last snake of the reverse path is the middle snake
                    result.push_back(x);
                    result.push_back(y);
                    result.push_back(u);
                    result.push_back(v);
                    result.push_back(2*D);
                }
            }
        }
    }
    return result;
}

int main() {
    std::string A;
    std::string B;
    LCS(A,B);
}
