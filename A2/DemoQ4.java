package practice;

public class Main {
	
	// Function to multiply two monotone numbers represented as strings
    public static String multiplyMonotone(String x, String y) {
    	
        int m = x.length();
        int n = y.length();

        // Result array to store the intermediate products
        int[] result = new int[m + n];

        // Iterate over each digit of y (from least significant to most significant)
        for (int i = n - 1; i >= 0; i--) {
        	
            int carry = 0;
            int yDigit = y.charAt(i) - '0';

            // Iterate over each digit of x (from least significant to most significant)
            for (int j = m - 1; j >= 0; j--) {
            	
                int xDigit = x.charAt(j) - '0';

                // Multiply current digits and add to the appropriate position in result
                int product = xDigit * yDigit + carry + result[i + j + 1];
                result[i + j + 1] = product % 10;
                carry = product / 10;
            }

            // Store any remaining carry in the appropriate position in result
            result[i] = carry;
        }

        // Build the result string from the result array
        StringBuilder sb = new StringBuilder();
        
        for (int digit : result) {
            sb.append(digit);
        }

        // Remove leading zeros (if any)
        while (sb.length() > 1 && sb.charAt(0) == '0') {
            sb.deleteCharAt(0);
        }

        return sb.toString();
    }

    public static void main(String[] args) {
    	
        // Test cases
        String x1 = "3333";
        String y1 = "7777";
        System.out.println(multiplyMonotone(x1, y1)); // Output: 25902041

        String x2 = "1111";
        String y2 = "9999";
        System.out.println(multiplyMonotone(x2, y2)); // Output: 11108889
    }
}
