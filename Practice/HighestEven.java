package practice;

// Tutorial 5 question 1
public class HighestEven {
	
	public static int recHighestEven(int[] A, int b, int e) {
		
		if(b == e) {
			
			if(A[b] % 2 == 0) {
				return b;
			}
			else {
				return b - 1;
			}
		}
		else {
			
			int m = (b + e) / 2;
			
			if(A[m + 1] % 2 == 1) {
				return recHighestEven(A, b, m);
			}
			else {
				return recHighestEven(A, m + 1, e);
			}
		}
	}

    public static void main(String[] args) {
    	
    	int[] A = {2, 9, 5, 1, 3, 4, 8};
    	int b = 0, e = A.length;
    	
    	System.out.println("recHighestEven : " + recHighestEven(A, b, e));
    }
}
