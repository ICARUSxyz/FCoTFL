package a;

import com.code_intelligence.jazzer.api.FuzzedDataProvider;

import code.c01_TriangleValidation;

public class c01_TriangleValidation {
	public static boolean isValidTriangle(double a, double b, double c) {
		boolean flag;
        if((a > 0) && (b > 0) && (c > 0) 
        		&& (a + b > c) 
        		&& (a + c > b) 
        		&& (b + c > a)) {
        	flag = true;
        }
        else flag = false;
        return flag;
    }

    public static void main(String[] args) {
       //   testcase-VT(vibration testing):
        double[][] testCases = {
        		{1.7, 2.845, 0.99}, //a > 0, b > 0, c > 0, a + b - c > 0, b + c - a > 0, a + c - b <= 0
        		{5.3284, 0.712, 6.9703}, //a > 0, b > 0, c > 0, a + b - c <= 0, b + c - a > 0, a + c - b > 0
        		{4.73336, 19.0923, 15.002}, //a > 0, b > 0, c > 0, a + c - b > 0, a + b - c > 0, b + c - a > 0 
        		{0.179, 6.90, 7.779}, //a > 0, b > 0, c > 0, a + b - c <= 0, b + c - a > 0, a + c - b > 0
        		{18, 1.3413, 13.544},//a > 0, b > 0, c > 0, a + b - c > 0, b + c - a <= 0, a + c - b > 0
        		{-16.6171, 6.9286, 12.4}, // a <= 0 
        		{0.323, -1, 3.223}, // b <= 0
        		{4.73336, 19.0923, -10.643}, // c <= 0         		
        };
        
        for (double[] testCase : testCases) {
            boolean result = isValidTriangle(testCase[0], testCase[1], testCase[2]);
            System.out.printf("isValidTriangle(%.1f, %.1f, %.1f) = %b%n",
                testCase[0], testCase[1], testCase[2], result);
        }
    }
}

class t01 {
    public static void fuzzerTestOneInput(FuzzedDataProvider data) {
        // generate 3 random double value
        double a = data.consumeDouble();
        double b = data.consumeDouble();
        double c = data.consumeDouble();

        // call target method
        boolean result = c01_TriangleValidation.isValidTriangle(a, b, c);

//        System.out.println("Testing with: a=" + a + ", b=" + b + ", c=" + c + " => ");
        System.out.println("Testing with: a=" + a + ", b=" + b + ", c=" + c + " => Result: " + result);
    }

}
