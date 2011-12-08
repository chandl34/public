import java.util.*;

public class SudokuSolverMK1 {

	
	// CLASS VARIABLES //
	
	// For simplicity, the following four arrays do not use index 0.
	private int[] possibilityCounter = new int[10];  // Keeps track of how many times a possibility shows up in a row/column/box.
	private boolean[] valuesInUse = new boolean[10];  // Keeps track of which numbers are already in use in a row/column/box.
	private String[] duplicatePossibility = new String[10];  // Holds Strings with only two possibilities.
	private int[] duplicateCounter = new int[10];	// Counts duplicatePossibility to find if there are duplicates
	private int counter; // The actual length of the duplicate arrays.  Iterates each time a value is added.
	
    private Scanner input = new Scanner(System.in);
	private ArrayList<SudokuBlock[][][][]> sudokuBlockArray = new ArrayList<SudokuBlock[][][][]>();
	
	
	// CONSTRUCTOR //
	
	public SudokuSolverMK1(){
		for(int i = 0; i < 7; i++){
			sudokuBlockArray.add(new SudokuBlock[3][3][3][3]);
		}
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){      
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						sudokuBlockArray.get(0)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex] = new SudokuBlock();
					}
				}
			}
		}
	}
	
	
	// SETUP METHODS //
	
	// Solving methods for various coordinate systems
	private void enterSolution(int x, int y, int solution){ // origin is in top left corner, diagonal is point (8, 8)
		sudokuBlockArray.get(0)[x%3][y%3][x/3][y/3].solve(solution);
	}
	
	private void enterSolution(int columnIndex, int rowIndex, int boxColumnIndex, int boxRowIndex, int solution){
		sudokuBlockArray.get(0)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].solve(solution);
	}
	
	private void enterSolution(int index, int x, int y, int solution){ // origin is in top left corner, diagonal is point (8, 8)
		sudokuBlockArray.get(index)[x%3][y%3][x/3][y/3].solve(solution);
	}
	
	private void enterSolution(int index, int columnIndex, int rowIndex, int boxColumnIndex, int boxRowIndex, int solution){
		sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].solve(solution);
	}
	
	
	// USER INTERFACE METHODS
	
	// Automated process helps user to input puzzle data quickly.
	public void setup(){
		int temp;
		System.out.println("Enter values from each row the top left to the bottom right.  Enter 0 if no value exists.");
		for(int y = 0; y < 9; y++){
			for(int x = 0; x < 9; x++){
				temp = input.nextInt();
				switch(temp){
				case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
					enterSolution(0, x, y, temp);
					break;
				case 0:
					break;
				}	
			}
		}
	}
	
	// Prints puzzle to screen.
	public void showPuzzle(int index){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){      
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						if(!sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							System.out.print("- ");
						else{
							System.out.print(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues() + " ");
						}
					}
					System.out.print("  ");
				}
				System.out.println();
			}
			System.out.println();
		}
	}
	
	// Solves the puzzle.  If puzzle is not solved in regular number of operations, puzzle is deemed unsolvable.
	public void solvePuzzle(){
		for(int i = 0; i < 2; i++){
			testBasics(0);
			advancedTest(0);
		}
		if(!isFinished(0))
			System.out.println("Puzzle unsolvable.");	
		showPuzzle(0);
	}
	
	// Finds if the puzzle has been solved.
	private boolean isFinished(int index){
		int numberOfFinishedBlocks = 0;
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							numberOfFinishedBlocks++;
					}
				}
			}
		}
		if(numberOfFinishedBlocks == 81)
			return true;
		return false;
	}
	
	
	// RESET VARIABLES // 
	
	// Resets all necessary variables for basic tests.
	private void resetValues(){
		resetPossibilityCounter();
		resetValuesInUse();
		resetDuplicatePossibilities();
		resetDuplicateCounter();
		counter = 1;
	}
	
	private void resetPossibilityCounter(){
		for(int i = 0; i < possibilityCounter.length; i++){
			possibilityCounter[i] = 0;
		}
	}
	
	private void resetValuesInUse(){
		for(int i = 0; i < valuesInUse.length; i++){
			valuesInUse[i] = false;
		}
	}
	
	private void resetDuplicatePossibilities(){
		for(int i = 0; i < duplicatePossibility.length; i++){
			duplicatePossibility[i] = "";
		}
	}
	
	private void resetDuplicateCounter(){
		for(int i = 0; i < duplicateCounter.length; i++){
			duplicateCounter[i] = 0;
		}
	}
	
	// Duplicates main puzzle for testing.
	private SudokuBlock[][][][] setupTestCases(int index){
		sudokuBlockArray.set(index*2+1, new SudokuBlock[3][3][3][3]);
		sudokuBlockArray.set(index*2+2, new SudokuBlock[3][3][3][3]);
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						sudokuBlockArray.get(index*2+1)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex] = new SudokuBlock(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues());
						sudokuBlockArray.get(index*2+2)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex] = new SudokuBlock(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues());
					}
				}
			}
		}
		return sudokuBlockArray.get(index);
	}
	
	
	// BASIC TESTS //
	
	// Performs all basic tests.
	private void testBasics(int index){
		testRows(index);
		testColumns(index);
		testBoxRows(index);
	}
	
	// Tests each row
	private void testRows(int index){
		
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				// For each row, reset necessary counters/values
				resetValues();
				// This loop goes through an entire row. 
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// And finds which numbers are already being used.
						if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							valuesInUse[Integer.parseInt(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues())] = true;
					}
				}
				// It goes through the entire row again.
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// Looks at unsolved blocks.
						if(!sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							// First it removes used values from each block's possibilities
							for(int i = 1; i < 10; i++){
								if(valuesInUse[i])
									sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(Integer.toString(i));
							}
							for(int i = 1; i < 10; i++){
								// It counts the possibilities in the block
								if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									possibilityCounter[i]++;
							}
						}
					}
				}
				// Goes through the loop again
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						for(int i = 1; i < 10; i++){
							// Checks if row only has one possible solution
							if(possibilityCounter[i] == 1){
								if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									enterSolution(index, columnIndex, rowIndex, boxColumnIndex, boxRowIndex, i);
							}								
						}
						if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
							duplicatePossibility[counter] = sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues();
							counter++;
						}
						// Counts if any duplicates exist
						for(int i = 1; i < counter; i++){
							if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i]))
								duplicateCounter[i]++;
						}
					}
				}
				// Goes through loop any possibilities from blocks that are NOT duplicates
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						for(int i = 1; i < counter; i++){
							if(duplicateCounter[i] == 2 && !sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i])){
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(0, 1));
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(1, 2));
							}	
						}
					}
				}
			}
		}
	}
	
	// Tests each column
	private void testColumns(int index){
		for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
			for(int columnIndex = 0; columnIndex < 3; columnIndex++){
				// For each column, reset necessary counters/values
				resetValues();
				// This loop goes through an entire column. 
				for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
					for(int rowIndex = 0; rowIndex < 3; rowIndex++){
						// And finds which numbers are already being used.
						if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							valuesInUse[Integer.parseInt(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues())] = true;
					}
				}
				// It goes through the entire column again.
				for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
					for(int rowIndex = 0; rowIndex < 3; rowIndex++){
						// Looks at unsolved blocks.
						if(!sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							// First it removes used values from each block's possibilities
							for(int i = 1; i < 10; i++){
								if(valuesInUse[i])
									sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(Integer.toString(i));
							}
							for(int i = 1; i < 10; i++){
								// It counts the possibilities in the block
								if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									possibilityCounter[i]++;
							}
						}
					}
				}
				// Goes through the loop again
				for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
					for(int rowIndex = 0; rowIndex < 3; rowIndex++){
						for(int i = 1; i < 10; i++){
							// Checks if row only has one possible solution
							if(possibilityCounter[i] == 1){
								if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									enterSolution(index, columnIndex, rowIndex, boxColumnIndex, boxRowIndex, i);
							}								
						}
						if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
							duplicatePossibility[counter] = sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues();
							counter++;
						}
						// Counts if any duplicates exist
						for(int i = 1; i < counter; i++){
							if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i]))
								duplicateCounter[i]++;
						}
					}
				}
				// Goes through loop any possibilities from blocks that are NOT duplicates
				for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
					for(int rowIndex = 0; rowIndex < 3; rowIndex++){
						for(int i = 1; i < counter; i++){
							if(duplicateCounter[i] == 2 && !sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i])){
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(0, 1));
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(1, 2));
							}	
						}
					}
				}
			}
		}
	}
	
	// Tests each box (by row)
	private void testBoxRows(int index){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
				// For each column, reset necessary counters/values
				resetValues();
				// This loop goes through each box by rows. 
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// And finds which numbers are already being used.
						if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							valuesInUse[Integer.parseInt(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues())] = true;
					}
				}
				// It goes through the entire box again.
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// Looks at unsolved blocks.
						if(!sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							// First it removes used values from each block's possibilities
							for(int i = 1; i < 10; i++){
								if(valuesInUse[i])
									sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(Integer.toString(i));
							}
							for(int i = 1; i < 10; i++){
								// It counts the possibilities in the block
								if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									possibilityCounter[i]++;
							}
						}
					}
				}
				// Goes through the loop again
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						for(int i = 1; i < 10; i++){
							// Checks if row only has one possible solution
							if(possibilityCounter[i] == 1){
								if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									enterSolution(index, columnIndex, rowIndex, boxColumnIndex, boxRowIndex, i);
							}								
						}
						if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
							duplicatePossibility[counter] = sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues();
							counter++;
						}
						// Counts if any duplicates exist
						for(int i = 1; i < counter; i++){
							if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i]))
								duplicateCounter[i]++;
						}
					}
				}
				// Goes through loop any possibilities from blocks that are NOT duplicates
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						for(int i = 1; i < counter; i++){
							if(duplicateCounter[i] == 2 && !sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i])){
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(0, 1));
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(1, 2));
							}	
						}
					}
				}
			}
		}
	}
	
	
	// LEVEL 4 TESTS //
	
	// Creates two duplicates of the puzzle.  Finds a block with two possibilities.  The first duplicate solves for the first possibility.
	// And the second duplicate solves for the second possibility.
	private void advancedTest(int index){
		if(index <= 0){ // CODE DISABLED -- Set to 2 for duplicates of duplicates
			for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
						for(int columnIndex = 0; columnIndex < 3; columnIndex++){
							// Finds a block with two possibilities
							if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
								// Creates the two duplicates
								setupTestCases(index);
								// Assigns each possibility to each duplicate
								sudokuBlockArray.get(index*2+1)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().substring(0, 1));
								sudokuBlockArray.get(index*2+2)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().substring(1, 2));
								advancedTest(index*2+1);
								advancedTest(index*2+2);
								// Uses basics tests on the duplicates 
								for(int i = 0; i < 2; i++){
									testBasics(index*2+1);
									testBasics(index*2+2);
								}
								// Compares them
								advancedTestCompareValues(index);
							}
						}
					}
				}
			}
		}
	}
	
	// The solutions of the two duplicates are compared.  The original puzzle is changed based on that comparison.
	private void advancedTestCompareValues(int index){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// Solves the main puzzle based on solutions from the duplicates
						if(!sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved() && sudokuBlockArray.get(index*2+1)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved() && (sudokuBlockArray.get(index*2+2)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())){
							if(sudokuBlockArray.get(index*2+1)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(sudokuBlockArray.get(index*2+2)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues()))
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(sudokuBlockArray.get(index*2+1)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues());
							else
								sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(sudokuBlockArray.get(index*2+1)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues() + (sudokuBlockArray.get(index*2+2)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues()));
					
						}
						// Removes possibilities that are not possible in test cases
						else if(!sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							for(int i = 1; i < 10; i++){
								String stringIndex = Integer.toString(i);
								if(sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(stringIndex) && !sudokuBlockArray.get(index*2+1)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(stringIndex) && !(sudokuBlockArray.get(index*2+2)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(stringIndex))){
									sudokuBlockArray.get(index)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(stringIndex);
								//	System.out.println("["+columnIndex+"]["+rowIndex+"]["+boxColumnIndex+"]["+boxRowIndex+"]"+ " REMOVED:  " + i);
								}
							}
						}
					}
				}
			}
		}
	}
	
	
	public static void main(String[] args) {
		SudokuSolverMK1 test = new SudokuSolverMK1();
		
		// example level 1 puzzle
		/**
		System.out.println("Level 1.  Found at http://sudoku.com.au/");
		test.enterSolution(0, 0, 5);
		test.enterSolution(1, 0, 9);
		test.enterSolution(3, 0, 1);
		test.enterSolution(4, 0, 2);
		test.enterSolution(8, 0, 8);
		test.enterSolution(1, 1, 2);
		test.enterSolution(5, 1, 9);
		test.enterSolution(6, 1, 4);
		test.enterSolution(1, 2, 3);
		test.enterSolution(2, 2, 6);
		test.enterSolution(5, 2, 5);
		test.enterSolution(8, 2, 9);
		test.enterSolution(0, 3, 9);
		test.enterSolution(2, 3, 1);
		test.enterSolution(4, 3, 6);
		test.enterSolution(7, 3, 3);
		test.enterSolution(2, 4, 7);
		test.enterSolution(3, 4, 4);
		test.enterSolution(5, 4, 3);
		test.enterSolution(6, 4, 6);
		test.enterSolution(1, 5, 8);
		test.enterSolution(4, 5, 7);
		test.enterSolution(6, 5, 5);
		test.enterSolution(8, 5, 4);
		test.enterSolution(0, 6, 8);
		test.enterSolution(3, 6, 3);
		test.enterSolution(6, 6, 2);
		test.enterSolution(7, 6, 4);
		test.enterSolution(2, 7, 5);
		test.enterSolution(3, 7, 6);
		test.enterSolution(7, 7, 1);
		test.enterSolution(0, 8, 3);
		test.enterSolution(4, 8, 1);
		test.enterSolution(5, 8, 4);
		test.enterSolution(7, 8, 5);
		test.enterSolution(8, 8, 7);
		*/
		
		// example level 2 puzzle
		/** 
		System.out.println("Level 2.  Found at http://sudoku.com.au/");
		test.enterSolution(1, 0, 7);
		test.enterSolution(4, 0, 1);
		test.enterSolution(5, 0, 5);
		test.enterSolution(2, 1, 9);
		test.enterSolution(5, 1, 8);
		test.enterSolution(6, 1, 2);
		test.enterSolution(7, 1, 3);
		test.enterSolution(2, 2, 8);
		test.enterSolution(6, 2, 1);
		test.enterSolution(7, 2, 6);
		test.enterSolution(5, 3, 6);
		test.enterSolution(7, 3, 4);
		test.enterSolution(0, 4, 4);
		test.enterSolution(1, 4, 3);
		test.enterSolution(7, 4, 2);
		test.enterSolution(8, 4, 8);
		test.enterSolution(1, 5, 9);
		test.enterSolution(3, 5, 8);
		test.enterSolution(1, 6, 5);
		test.enterSolution(2, 6, 4);
		test.enterSolution(6, 6, 8);
		test.enterSolution(1, 7, 1);
		test.enterSolution(2, 7, 3);
		test.enterSolution(3, 7, 6);
		test.enterSolution(6, 7, 4);
		test.enterSolution(3, 8, 1);
		test.enterSolution(4, 8, 8);
		test.enterSolution(7, 8, 5);
		*/
		
		// example level 3 puzzle
		/**
		System.out.println("Level 3.  Found at http://sudoku.com.au/");
		test.enterSolution(2, 0, 8);
		test.enterSolution(3, 0, 5);
		test.enterSolution(5, 0, 3);
		test.enterSolution(0, 1, 3);
		test.enterSolution(1, 1, 1);
		test.enterSolution(2, 1, 9);
		test.enterSolution(0, 2, 5);
		test.enterSolution(4, 2, 9);
		test.enterSolution(5, 2, 6);
		test.enterSolution(3, 3, 9);
		test.enterSolution(4, 3, 2);
		test.enterSolution(8, 3, 7);
		test.enterSolution(1, 4, 3);
		test.enterSolution(7, 4, 4);
		test.enterSolution(0, 5, 2);
		test.enterSolution(4, 5, 5);
		test.enterSolution(5, 5, 1);
		test.enterSolution(3, 6, 6);
		test.enterSolution(4, 6, 8);
		test.enterSolution(8, 6, 4);
		test.enterSolution(6, 7, 1);
		test.enterSolution(7, 7, 6);
		test.enterSolution(8, 7, 5);
		test.enterSolution(3, 8, 4);
		test.enterSolution(5, 8, 7);
		test.enterSolution(6, 8, 9);
		*/
		
		// example level 4 puzzle
//		/**
		System.out.println("Level 4.  Found at http://sudoku.com.au/");
		test.enterSolution(0, 0, 8);
		test.enterSolution(0, 1, 7);
		test.enterSolution(3, 1, 3);
		test.enterSolution(5, 1, 5);
		test.enterSolution(6, 1, 6);
		test.enterSolution(2, 2, 4);
		test.enterSolution(4, 2, 9);
		test.enterSolution(2, 3, 1);
		test.enterSolution(5, 3, 9);
		test.enterSolution(7, 3, 2);
		test.enterSolution(1, 4, 5);
		test.enterSolution(4, 4, 4);
		test.enterSolution(7, 4, 3);
		test.enterSolution(1, 5, 3);
		test.enterSolution(3, 5, 7);
		test.enterSolution(6, 5, 8);
		test.enterSolution(4, 6, 2);
		test.enterSolution(6, 6, 5);
		test.enterSolution(2, 7, 3);
		test.enterSolution(3, 7, 4);
		test.enterSolution(5, 7, 1);
		test.enterSolution(8, 7, 7);
		test.enterSolution(8, 8, 2);
//		*/
		
		// world's hardest sudoku puzzle
		/**
		System.out.println("World's Hardest Sudoku Puzzle.  Found at http://yoavs.blogspot.com/2006/11/worlds-hardest-sudoku-puzzle.html");
		test.enterSolution(0, 0, 1);
		test.enterSolution(5, 0, 7);
		test.enterSolution(7, 0, 9);
		test.enterSolution(1, 1, 3);
		test.enterSolution(4, 1, 2);
		test.enterSolution(8, 1, 8);
		test.enterSolution(2, 2, 9);
		test.enterSolution(3, 2, 6);
		test.enterSolution(6, 2, 5);
		test.enterSolution(2, 3, 5);
		test.enterSolution(3, 3, 3);
		test.enterSolution(6, 3, 9);
		test.enterSolution(1, 4, 1);
		test.enterSolution(4, 4, 8);
		test.enterSolution(8, 4, 2);
		test.enterSolution(0, 5, 6);
		test.enterSolution(5, 5, 4);
		test.enterSolution(0, 6, 3);
		test.enterSolution(7, 6, 1);
		test.enterSolution(1, 7, 4);
		test.enterSolution(8, 7, 7);
		test.enterSolution(2, 8, 7);
		test.enterSolution(6, 8, 3);
		*/
		
		test.showPuzzle(0);
		System.out.println("---------------------\n");
		
		test.solvePuzzle();
		/**
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){      
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						System.out.println(test.sudokuBlockArray.get(0)[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues());
					}
				}
			}
		}
		*/
	}
	
}
