

public class TreeNode {
	private Object element;
	private TreeNode left, right;
	
	TreeNode(Object element){
		this.element = element;
	}
	
	public TreeNode getRight(){
		return right;
	}
	
	public TreeNode getLeft(){
		return left;
	}
	
	public void setRight(TreeNode right){
		this.right = right;
	}
	
	public void setLeft(TreeNode left){
		this.left = left;
	}
	
	public Object getElement(){
		return element;
	}
	
	public void setElement(Object element){
		this.element = element;
	}
}
