package practice;

public class Main {
	
	public static int partition(int[] A, int low, int high) {
		
		int pivot = A[high];
		int i = low - 1;
		
		System.out.println("Value of pivot: " + pivot);
		System.out.println("Value of the high - 1 : "  + (high - 1));
		
		for(int j = low; j <= high - 1; j++) {
			
			System.out.println("Value of i: " + i + " value of j: " + j);
			
			if(A[j] <= pivot) {
				
				i++;
				System.out.println("\nValue of i in the loop: " + i);
				swap(A, i, j);
				System.out.println("Value of j in the loop: " + j + "\n");
			}
		}
		
		System.out.println("\nArray after the loop before final swapping");
		printArray(A);
	
		swap(A, i + 1, high);
		
		return i + 1;
	}

    private static void swap(int[] A, int i, int j) {
    	
    	int temp = A[i];
    	A[i] = A[j];
    	A[j] = temp;
	}
    
    private static void printArray(int[] A) {
    	
    	for(int i : A) {
    		System.out.print(i + " ");
    	}
    	
    	System.out.println();
    }
    

	public static void main(String[] args) {
		
		int[] A = {3, 8, 6, 1, 5};
		int low = 0;
		int high = A.length - 1;
		
		System.out.println("Value for low: " + low);
		System.out.println("Value for high: " + high);
		System.out.println("Array before partitioning:");
		
		printArray(A);
		
		int pivotIndex = partition(A, low, high);
		
		System.out.println("Array after partitioning:");
		printArray(A);
		
		System.out.println("Pivot index: " + pivotIndex);
		System.out.println("Pivot value: " + A[pivotIndex]);
    }
}
