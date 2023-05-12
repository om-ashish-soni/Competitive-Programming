// problem link : https://practice.geeksforgeeks.org/problems/level-order-traversal-in-spiral-form/1?page=1&category[]=Stack&sortBy=submissions
// solution : below code

class Spiral
{
    //Function to return a list containing the level order 
    //traversal in spiral form.	
    void dfs(Node root,ArrayList<ArrayList<Integer>> mat,int level){
        if(root==null) return;
        if(level>=mat.size()){
            mat.add(new ArrayList<Integer>());
        }
        ArrayList<Integer> row=mat.get(level);
        row.add(new Integer(root.data));
        dfs(root.left,mat,level+1);
        dfs(root.right,mat,level+1);
        return;
    }
    ArrayList<Integer> findSpiral(Node root) 
    {
        ArrayList<ArrayList<Integer>> mat=new ArrayList<ArrayList<Integer>>();
        
        dfs(root,mat,0);
        for(int i=0;i<mat.size();i+=2){
            Collections.reverse(mat.get(i));
        }
        ArrayList<Integer> arr=new ArrayList<Integer>();
        for(int i=0;i<mat.size();i++){
            for(int j=0;j<mat.get(i).size();j++){
                arr.add(mat.get(i).get(j));
            }
        }
        return arr;
    }
}
