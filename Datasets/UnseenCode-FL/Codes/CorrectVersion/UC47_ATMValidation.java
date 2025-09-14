package a;

import com.code_intelligence.jazzer.api.FuzzedDataProvider;

public class c02_ATMValidation {

	
	public static boolean isValidWithdrawal(double amount, double accountBalance) {
        boolean flag;
        if(amount > 0 && accountBalance > 0 && amount <= accountBalance) {
        	flag = true;
        }
        else flag = false;
        return flag;
    }

    public static void main(String[] args) {
        // testcase-VT:
        double[][] testCases = {
        		{2598.16, 1784.78}, //amount > 0 && accountBalance > 0 && amount > accountBalance
        		{197.64, 102.47}, //amount > 0 && accountBalance > 0 && amount > accountBalance
        		{1015.07, 4908.75}, //amount > 0 && accountBalance > 0 && amount <= accountBalance
        		{-1939.66, 2509.62}, //amount <= 0 && accountBalance > 0 && amount <= accountBalance
        		{1707.62, -753.75}, //amount > 0 && accountBalance <= 0 && amount > accountBalance 
        };

        
        for (double[] testCase : testCases) {
            boolean result = isValidWithdrawal(testCase[0], testCase[1]);
            System.out.printf("isValidWithdrawal(%.1f, %.1f) = %b%n",
                testCase[0], testCase[1], result);
        }
    }
}


class t02 {
    public static void fuzzerTestOneInput(FuzzedDataProvider data) {
        // generate 2 random double value
        double a = data.consumeDouble();
        double b = data.consumeDouble();

        // call target method
        boolean result = c02_ATMValidation.isValidWithdrawal(a,b);

//        System.out.println("Testing with: a=" + a + ", b=" + b + ", c=" + c + " => ");
        System.out.println("Testing with: a=" + a + ", b=" + b + ", => Result: " + result);
    }

}
