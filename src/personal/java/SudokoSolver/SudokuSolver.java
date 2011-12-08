import java.util.Scanner;

public class SudokuSolver {

	
	// CLASS VARIABLES //
	
	// For simplicity, the following four arrays do not use index 0.
	private int[] possibilityCounter = new int[10];  // Keeps track of how many times a possibility shows up in a row/column/box.
	private boolean[] valuesInUse = new boolean[10];  // Keeps track of which numbers are already in use in a row/column/box.
	private String[] duplicatePossibility = new String[10];  // Holds Strings with only two possibilities.
	private int[] duplicateCounter = new int[10];	// Counts duplicatePossibility to find if there are duplicates
	private int counter; // The actual length of the duplicate arrays.  Iterates each time a value is added.
	
    private Scanner input = new Scanner(System.in);
	private SudokuBlock[][][][] block = new SudokuBlock[3][3][3][3];	// Main puzzle
	private SudokuBlock[][][][] test1 = new SudokuBlock[3][3][3][3];	// Puzzle scenario 1
	private SudokuBlock[][][][] test2 = new SudokuBlock[3][3][3][3];	// Puzzle scenario 2
	
	
	// CONSTRUCTOR //
	
	public SudokuSolver(){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){      
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex] = new SudokuBlock();
					}
				}
			}
		}
	}
	
	
	// SETUP METHODS //
	
	// Solving methods for various coordinate systems
	private void enterSolution(SudokuBlock[][][][] testCase, int x, int y, int solution){ // origin is in top left corner, diagonal is point (8, 8)
		testCase[x%3][y%3][x/3][y/3].solve(solution);
	}
	
	private void enterSolution(SudokuBlock[][][][] testCase, int columnIndex, int rowIndex, int boxColumnIndex, int boxRowIndex, int solution){
		testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].solve(solution);
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
					enterSolution(block, x, y, temp);
					break;
				case 0:
					break;
				}	
			}
		}
	}
	
	// Prints puzzle to screen.
	public void showPuzzle(SudokuBlock[][][][] testCase){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){      
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						if(!testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							System.out.print("- ");
						else{
							System.out.print(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues() + " ");
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
		testBasics(block);
		advancedTest();
		testBasics(block);
		if(!isFinished(block))
			System.out.println("Puzzle unsolvable.");	
		showPuzzle(block);
	}
	
	// Finds if the puzzle has been solved.
	private boolean isFinished(SudokuBlock[][][][] testCase){
		int numberOfFinishedBlocks = 0;
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
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
	private SudokuBlock[][][][] setupTestCase(SudokuBlock[][][][] testCase){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex] = new SudokuBlock(block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues());
					}
				}
			}
		}
		return testCase;
	}
	
	
	// BASIC TESTS //
	
	// Performs all basic tests.
	private void testBasics(SudokuBlock[][][][] testCase){
		testRows(testCase);
		testColumns(testCase);
		testBoxRows(testCase);
	}
	
	// Tests each row
	private void testRows(SudokuBlock[][][][] testCase){
		
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				// For each row, reset necessary counters/values
				resetValues();
				// This loop goes through an entire row. 
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// And finds which numbers are already being used.
						if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							valuesInUse[Integer.parseInt(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues())] = true;
					}
				}
				// It goes through the entire row again.
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// Looks at unsolved blocks.
						if(!testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							// First it removes used values from each block's possibilities
							for(int i = 1; i < 10; i++){
								if(valuesInUse[i])
									testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(Integer.toString(i));
							}
							for(int i = 1; i < 10; i++){
								// It counts the possibilities in the block
								if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
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
								if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									enterSolution(testCase, columnIndex, rowIndex, boxColumnIndex, boxRowIndex, i);
							}								
						}
						if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
							duplicatePossibility[counter] = testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues();
							counter++;
						}
						// Counts if any duplicates exist
						for(int i = 1; i < counter; i++){
							if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i]))
								duplicateCounter[i]++;
						}
					}
				}
				// Goes through loop any possibilities from blocks that are NOT duplicates
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						for(int i = 1; i < counter; i++){
							if(duplicateCounter[i] == 2 && !testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i])){
								testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(0, 1));
								testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(1, 2));
							}	
						}
					}
				}
			}
		}
	}
	
	// Tests each column
	private void testColumns(SudokuBlock[][][][] testCase){
		for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
			for(int columnIndex = 0; columnIndex < 3; columnIndex++){
				// For each column, reset necessary counters/values
				resetValues();
				// This loop goes through an entire column. 
				for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
					for(int rowIndex = 0; rowIndex < 3; rowIndex++){
						// And finds which numbers are already being used.
						if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							valuesInUse[Integer.parseInt(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues())] = true;
					}
				}
				// It goes through the entire column again.
				for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
					for(int rowIndex = 0; rowIndex < 3; rowIndex++){
						// Looks at unsolved blocks.
						if(!testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							// First it removes used values from each block's possibilities
							for(int i = 1; i < 10; i++){
								if(valuesInUse[i])
									testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(Integer.toString(i));
							}
							for(int i = 1; i < 10; i++){
								// It counts the possibilities in the block
								if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
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
								if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									enterSolution(testCase, columnIndex, rowIndex, boxColumnIndex, boxRowIndex, i);
							}								
						}
						if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
							duplicatePossibility[counter] = testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues();
							counter++;
						}
						// Counts if any duplicates exist
						for(int i = 1; i < counter; i++){
							if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i]))
								duplicateCounter[i]++;
						}
					}
				}
				// Goes through loop any possibilities from blocks that are NOT duplicates
				for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
					for(int rowIndex = 0; rowIndex < 3; rowIndex++){
						for(int i = 1; i < counter; i++){
							if(duplicateCounter[i] == 2 && !testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i])){
								testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(0, 1));
								testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(1, 2));
							}	
						}
					}
				}
			}
		}
	}
	
	// Tests each box (by row)
	private void testBoxRows(SudokuBlock[][][][] testCase){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
				// For each column, reset necessary counters/values
				resetValues();
				// This loop goes through each box by rows. 
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// And finds which numbers are already being used.
						if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved())
							valuesInUse[Integer.parseInt(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues())] = true;
					}
				}
				// It goes through the entire box again.
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// Looks at unsolved blocks.
						if(!testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							// First it removes used values from each block's possibilities
							for(int i = 1; i < 10; i++){
								if(valuesInUse[i])
									testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(Integer.toString(i));
							}
							for(int i = 1; i < 10; i++){
								// It counts the possibilities in the block
								if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
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
								if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(Integer.toString(i)))
									enterSolution(testCase, columnIndex, rowIndex, boxColumnIndex, boxRowIndex, i);
							}								
						}
						if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
							duplicatePossibility[counter] = testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues();
							counter++;
						}
						// Counts if any duplicates exist
						for(int i = 1; i < counter; i++){
							if(testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i]))
								duplicateCounter[i]++;
						}
					}
				}
				// Goes through loop any possibilities from blocks that are NOT duplicates
				for(int rowIndex = 0; rowIndex < 3; rowIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						for(int i = 1; i < counter; i++){
							if(duplicateCounter[i] == 2 && !testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(duplicatePossibility[i])){
								testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(0, 1));
								testCase[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(duplicatePossibility[i].substring(1, 2));
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
	private void advancedTest(){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// Finds a block with two possibilities
						if(block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getNumberOfPossibleValues() == 2){
							// Creates the two duplicates
							setupTestCase(test1);
							setupTestCase(test2);
							// Assigns each possibility to each duplicate
							test1[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().substring(0, 1));
							test2[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().substring(1, 2));
							// Uses basics tests on the duplicates 
							for(int i = 0; i < 2; i++){
								testBasics(test1);
								testBasics(test2);
							}
							// Compares them
							advancedTestCompareValues();
						}
					}
				}
			}
		}
	}
	
	// The solutions of the two duplicates are compared.  The original puzzle is changed based on that comparison.
	private void advancedTestCompareValues(){
		for(int boxRowIndex = 0; boxRowIndex < 3; boxRowIndex++){
			for(int rowIndex = 0; rowIndex < 3; rowIndex++){
				for(int boxColumnIndex = 0; boxColumnIndex < 3; boxColumnIndex++){
					for(int columnIndex = 0; columnIndex < 3; columnIndex++){
						// Solves the main puzzle based on solutions from the duplicates
						if(!block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved() && test1[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved() && test2[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							if(test1[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().equals(test2[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues()))
								block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(test1[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues());
							else
								block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].setPossibleValues(test1[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues() + test2[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues());
					
						}
						// Removes possibilities that are not possible in test cases
						else if(!block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].isSolved()){
							for(int i = 1; i < 10; i++){
								String stringIndex = Integer.toString(i);
								if(block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(stringIndex) && !test1[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(stringIndex) && !(test2[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].getPossibleValues().contains(stringIndex)))
									block[columnIndex][rowIndex][boxColumnIndex][boxRowIndex].removePossibility(stringIndex);
							}
						}
					}
				}
			}
		}
	}
	
	
	public static void main(String[] args) {
		SudokuSolver test = new SudokuSolver();
		
		// example level 1 puzzle
		/**
		System.out.println("Level 1.  Found at http://sudoku.com.au/");
		test.enterSolution(test.block, 0, 0, 5);
		test.enterSolution(test.block, 1, 0, 9);
		test.enterSolution(test.block, 3, 0, 1);
		test.enterSolution(test.block, 4, 0, 2);
		test.enterSolution(test.block, 8, 0, 8);
		test.enterSolution(test.block, 1, 1, 2);
		test.enterSolution(test.block, 5, 1, 9);
		test.enterSolution(test.block, 6, 1, 4);
		test.enterSolution(test.block, 1, 2, 3);
		test.enterSolution(test.block, 2, 2, 6);
		test.enterSolution(test.block, 5, 2, 5);
		test.enterSolution(test.block, 8, 2, 9);
		test.enterSolution(test.block, 0, 3, 9);
		test.enterSolution(test.block, 2, 3, 1);
		test.enterSolution(test.block, 4, 3, 6);
		test.enterSolution(test.block, 7, 3, 3);
		test.enterSolution(test.block, 2, 4, 7);
		test.enterSolution(test.block, 3, 4, 4);
		test.enterSolution(test.block, 5, 4, 3);
		test.enterSolution(test.block, 6, 4, 6);
		test.enterSolution(test.block, 1, 5, 8);
		test.enterSolution(test.block, 4, 5, 7);
		test.enterSolution(test.block, 6, 5, 5);
		test.enterSolution(test.block, 8, 5, 4);
		test.enterSolution(test.block, 0, 6, 8);
		test.enterSolution(test.block, 3, 6, 3);
		test.enterSolution(test.block, 6, 6, 2);
		test.enterSolution(test.block, 7, 6, 4);
		test.enterSolution(test.block, 2, 7, 5);
		test.enterSolution(test.block, 3, 7, 6);
		test.enterSolution(test.block, 7, 7, 1);
		test.enterSolution(test.block, 0, 8, 3);
		test.enterSolution(test.block, 4, 8, 1);
		test.enterSolution(test.block, 5, 8, 4);
		test.enterSolution(test.block, 7, 8, 5);
		test.enterSolution(test.block, 8, 8, 7);
		*/
		
		// example level 2 puzzle
		/** 
		System.out.println("Level 2.  Found at http://sudoku.com.au/");
		test.enterSolution(test.block, 1, 0, 7);
		test.enterSolution(test.block, 4, 0, 1);
		test.enterSolution(test.block, 5, 0, 5);
		test.enterSolution(test.block, 2, 1, 9);
		test.enterSolution(test.block, 5, 1, 8);
		test.enterSolution(test.block, 6, 1, 2);
		test.enterSolution(test.block, 7, 1, 3);
		test.enterSolution(test.block, 2, 2, 8);
		test.enterSolution(test.block, 6, 2, 1);
		test.enterSolution(test.block, 7, 2, 6);
		test.enterSolution(test.block, 5, 3, 6);
		test.enterSolution(test.block, 7, 3, 4);
		test.enterSolution(test.block, 0, 4, 4);
		test.enterSolution(test.block, 1, 4, 3);
		test.enterSolution(test.block, 7, 4, 2);
		test.enterSolution(test.block, 8, 4, 8);
		test.enterSolution(test.block, 1, 5, 9);
		test.enterSolution(test.block, 3, 5, 8);
		test.enterSolution(test.block, 1, 6, 5);
		test.enterSolution(test.block, 2, 6, 4);
		test.enterSolution(test.block, 6, 6, 8);
		test.enterSolution(test.block, 1, 7, 1);
		test.enterSolution(test.block, 2, 7, 3);
		test.enterSolution(test.block, 3, 7, 6);
		test.enterSolution(test.block, 6, 7, 4);
		test.enterSolution(test.block, 3, 8, 1);
		test.enterSolution(test.block, 4, 8, 8);
		test.enterSolution(test.block, 7, 8, 5);
		*/
		
		// example level 3 puzzle
		/**
		System.out.println("Level 3.  Found at http://sudoku.com.au/");
		test.enterSolution(test.block, 2, 0, 8);
		test.enterSolution(test.block, 3, 0, 5);
		test.enterSolution(test.block, 5, 0, 3);
		test.enterSolution(test.block, 0, 1, 3);
		test.enterSolution(test.block, 1, 1, 1);
		test.enterSolution(test.block, 2, 1, 9);
		test.enterSolution(test.block, 0, 2, 5);
		test.enterSolution(test.block, 4, 2, 9);
		test.enterSolution(test.block, 5, 2, 6);
		test.enterSolution(test.block, 3, 3, 9);
		test.enterSolution(test.block, 4, 3, 2);
		test.enterSolution(test.block, 8, 3, 7);
		test.enterSolution(test.block, 1, 4, 3);
		test.enterSolution(test.block, 7, 4, 4);
		test.enterSolution(test.block, 0, 5, 2);
		test.enterSolution(test.block, 4, 5, 5);
		test.enterSolution(test.block, 5, 5, 1);
		test.enterSolution(test.block, 3, 6, 6);
		test.enterSolution(test.block, 4, 6, 8);
		test.enterSolution(test.block, 8, 6, 4);
		test.enterSolution(test.block, 6, 7, 1);
		test.enterSolution(test.block, 7, 7, 6);
		test.enterSolution(test.block, 8, 7, 5);
		test.enterSolution(test.block, 3, 8, 4);
		test.enterSolution(test.block, 5, 8, 7);
		test.enterSolution(test.block, 6, 8, 9);
		*/
		
		// example level 4 puzzle
	//	/**
		System.out.println("Level 4.  Found at http://sudoku.com.au/");
		test.enterSolution(test.block, 0, 0, 8);
		test.enterSolution(test.block, 0, 1, 7);
		test.enterSolution(test.block, 3, 1, 3);
		test.enterSolution(test.block, 5, 1, 5);
		test.enterSolution(test.block, 6, 1, 6);
		test.enterSolution(test.block, 2, 2, 4);
		test.enterSolution(test.block, 4, 2, 9);
		test.enterSolution(test.block, 2, 3, 1);
		test.enterSolution(test.block, 5, 3, 9);
		test.enterSolution(test.block, 7, 3, 2);
		test.enterSolution(test.block, 1, 4, 5);
		test.enterSolution(test.block, 4, 4, 4);
		test.enterSolution(test.block, 7, 4, 3);
		test.enterSolution(test.block, 1, 5, 3);
		test.enterSolution(test.block, 3, 5, 7);
		test.enterSolution(test.block, 6, 5, 8);
		test.enterSolution(test.block, 4, 6, 2);
		test.enterSolution(test.block, 6, 6, 5);
		test.enterSolution(test.block, 2, 7, 3);
		test.enterSolution(test.block, 3, 7, 4);
		test.enterSolution(test.block, 5, 7, 1);
		test.enterSolution(test.block, 8, 7, 7);
		test.enterSolution(test.block, 8, 8, 2);
	//	*/
		
		// world's hardest sudoku puzzle
		/**
		System.out.println("World's Hardest Sudoku Puzzle.  Found at http://yoavs.blogspot.com/2006/11/worlds-hardest-sudoku-puzzle.html");
		test.enterSolution(test.block, 0, 0, 1);
		test.enterSolution(test.block, 5, 0, 7);
		test.enterSolution(test.block, 7, 0, 9);
		test.enterSolution(test.block, 1, 1, 3);
		test.enterSolution(test.block, 4, 1, 2);
		test.enterSolution(test.block, 8, 1, 8);
		test.enterSolution(test.block, 2, 2, 9);
		test.enterSolution(test.block, 3, 2, 6);
		test.enterSolution(test.block, 6, 2, 5);
		test.enterSolution(test.block, 2, 3, 5);
		test.enterSolution(test.block, 3, 3, 3);
		test.enterSolution(test.block, 6, 3, 9);
		test.enterSolution(test.block, 1, 4, 1);
		test.enterSolution(test.block, 4, 4, 8);
		test.enterSolution(test.block, 8, 4, 2);
		test.enterSolution(test.block, 0, 5, 6);
		test.enterSolution(test.block, 5, 5, 4);
		test.enterSolution(test.block, 0, 6, 3);
		test.enterSolution(test.block, 7, 6, 1);
		test.enterSolution(test.block, 1, 7, 4);
		test.enterSolution(test.block, 8, 7, 7);
		test.enterSolution(test.block, 2, 8, 7);
		test.enterSolution(test.block, 6, 8, 3);
		*/
	//	test.setup();
		test.showPuzzle(test.block);
		System.out.println("---------------------\n");
		
		test.solvePuzzle();
	}
	
}
