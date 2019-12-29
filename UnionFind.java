https://leetcode.com/problems/friend-circles/
Time Complexity for DFS/ BFS/ Union Find:
https://leetcode.com/problems/friend-circles/solution/

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
