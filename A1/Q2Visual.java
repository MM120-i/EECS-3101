package practice;

public class Main {
	
	public static int FindCheckDigit(int[] A) {
		
		int check_digit = 0;
		int n = A.length;
		
		for(int i = 0; i < n; i++) {
			
			check_digit = check_digit + A[i];
			System.out.println("First loop iterated " + i + " times");
		}
		
		check_digit = check_digit % 10;
		
		System.out.println("\nValue of check_digit is: " + check_digit + "\n");

		for(int i = 0; i < n; i++) {
			
			System.out.println("Second loop iterated " + i + " times");

			if(A[i] == check_digit) {
				return i;
			}
		}
		
		return -1;
	}

	public static void main(String[] args) {
		
		int[] A = {0, 3, 5, 2, 1, 9};
		
		System.out.println("\nFinal answer: " + FindCheckDigit(A));
	}
}
