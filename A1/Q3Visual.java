package practice;

public class Main {
	
	public static boolean freaky(int n) {
		
		if(n < 2) {
			return false;
		}
		
		int x = 2;
		
		while(x < n) {
						
			if(n % x == 0) {
				return false;
			}
			x ++;
		}
				
		return true;
	}

	public static void main(String[] args) {
		
		boolean a = freaky(5);
		System.out.println("Returned: " + a);
	}
}
