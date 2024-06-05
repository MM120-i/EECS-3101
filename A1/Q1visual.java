package practice;

import java.util.ArrayList;

public class Main {
	
	public static void reverse(ArrayList<Integer> lst) {
		
		int n = lst.size();
		int i = 0;
		int j = n - 1;
		
		System.out.println("Value of i before the loop = " + i);
		System.out.println("Value of j before the loop = " + j);
		System.out.println("i\tj");
		
		while(i <= j) {	
			// swap process
			i++;
			System.out.print(i);
			j--;
			System.out.println("\t" + j);
		}
		
		System.out.println("Value of i after the loop = " + i);
		System.out.println("Value of j after the loop = " + j);
	}

	public static void main(String[] args) {
		
		ArrayList<Integer> list = new ArrayList<Integer>();
		
		for(int i = 0; i < 5; i++) {
			list.add(i);
		}
		
		reverse(list);
	}

}
