public class SudokuBlock {
	
	
	// CLASS VARIABLES //
	
	private String possibleValues;
	private int numberOfPossibleValues;
	
	
	// CONSTRUCTOR //
	
	// Default constructor - initializes all numbers as possible values for the block.
	public SudokuBlock(){
		possibleValues = "123456789";
		numberOfPossibleValues = 9;
	}
	
	public SudokuBlock(String possibleValues){
		this.possibleValues = possibleValues;
		numberOfPossibleValues = possibleValues.length();
	}
	
	
	// ACCESSORS //
	
	// Returns true if block has been solved.
	public boolean isSolved(){
		return(getNumberOfPossibleValues() == 1);
	}
	
	// Returns true if (int possibility) is a possible value for the block.
	public boolean isAPossibleValue(int possibility){
		return(possibleValues.contains(Integer.toString(possibility)));
	}
	
	// Returns a String containing all of the possible values for the block.
	public String getPossibleValues(){
		return possibleValues;
	}
	
	// Returns the number of possible values for the block.
	public int getNumberOfPossibleValues(){
		return possibleValues.length();
	}
		
	
	// MUTATORS //
	
	// Solves block with (int solution).
	public void solve(int solution){
		possibleValues = Integer.toString(solution);
	}
	
	// Removes (int possibility) as a possibility for the block.
	public void removePossibility(String possibility){
		if(possibleValues.contains(possibility))
			possibleValues = possibleValues.replace(possibility, "");
	}
	
	public void setPossibleValues(String possibleValues){
		this.possibleValues = possibleValues;
	}
	
	
	public static void main(String[] args) {
		System.out.println(6%13);
	}
	
}
