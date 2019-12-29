https://leetcode.com/problems/friend-circles/
Time Complexity for DFS/ BFS/ Union Find:
https://leetcode.com/problems/friend-circles/solution/
Question:
/*
There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.

Example 1:
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.

Example 2:
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.

*/

// Union find with weight:
// Path compression is also being used
// This solution takes 2ms for execution.
class Solution {
    int[] parent;
    int[] rank; // we use size as rank.
    
    public int findCircleNum(int[][] M) {
        parent = new int[M.length];
        rank = new int[M.length];
        for(int i = 0; i < M.length; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
        
        for(int i = 0; i < M.length; i++) {
            for(int j = i; j < M[i].length; j++) {
                if (M[i][j] == 1) {
                    union(i, j);
                }
            }
        }
        
        Set<Integer> set = new HashSet<>();
        for(int i = 0; i < M.length; i++) {
            set.add(find(i));
        }
        
        return set.size();
    }
    
    private int find(int x) {
        while(parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        
        return x;
    }
    
    private void union(int x, int y) {
        int parentX = find(x);
        int parentY = find(y);
        
        if (parentX != parentY) {
            if (rank[parentX] > rank[parentY]) {
                parent[parentY] = parentX;
                rank[parentX] += rank[parentY];
            } else {
                parent[parentX] = parentY;
                rank[parentY] += rank[parentX];
            }
        }
    }
}

// Union find without weight:
// No path compression is being used
// This solution takes double time (4ms)
class Solution {
    int[] parent;
    public int findCircleNum(int[][] M) {
        parent = new int[M.length];
        for(int i = 0; i < M.length; i++) {
            parent[i] = i;
        }
        
        for(int i = 0; i < M.length; i++) {
            for(int j = i; j < M[i].length; j++) {
                if (M[i][j] == 1) {
                    union(i, j);
                }
            }
        }
        
        Set<Integer> set = new HashSet<>();
        for(int i = 0; i < M.length; i++) {
            set.add(find(i));
        }
        
        return set.size();
    }
    
    private int find(int x) {
        while(parent[x] != x) {
            x = parent[x];
        }
        
        return x;
    }
    
    private void union(int x, int y) {
        int parentX = find(x);
        int parentY = find(y);
        
        parent[parentX] = parentY;
    }
}


// Union find without weight:
// Uses path compression
// To the contrary it takes the same time for this solution as for weighted union find with path compression.
// This solution takes 2ms for execution.
class Solution {
    int[] parent;
    public int findCircleNum(int[][] M) {
        parent = new int[M.length];
        for(int i = 0; i < M.length; i++) {
            parent[i] = i;
        }
        
        for(int i = 0; i < M.length; i++) {
            for(int j = i; j < M[i].length; j++) {
                if (M[i][j] == 1) {
                    union(i, j);
                }
            }
        }
        
        Set<Integer> set = new HashSet<>();
        for(int i = 0; i < M.length; i++) {
            set.add(find(i));
        }
        
        return set.size();
    }
    
    private int find(int x) {
        while(parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        
        return x;
    }
    
    private void union(int x, int y) {
        int parentX = find(x);
        int parentY = find(y);
        
        parent[parentX] = parentY;
    }
}
