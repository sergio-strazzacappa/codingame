import java.util.Scanner;

class Solution {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        String message = in.nextLine();
        int ascii = 0;
        String binary = "";
        String answer = "";
        boolean firstZero = true;
        boolean firstOne = true;
        boolean firstChar = true;

        for (int i = message.length() - 1; i >= 0; i--) {
            ascii = message.charAt(i);

            for (int j = ascii; j > 0; j /= 2) {
                binary = (j % 2) + binary;
            }

            if (ascii < 64 && ascii >= 32) {
                binary = "0" + binary;
            }
            if (ascii < 32 && ascii >= 16) {
                binary = "00" + binary;
            }
            if (ascii < 16 && ascii >= 8) {
                binary = "000" + binary;
            }
            if (ascii < 8 && ascii >= 4) {
                binary = "0000" + binary;
            }
            if (ascii < 4 && ascii >= 2) {
                binary = "00000" + binary;
            }
            if (ascii < 2 && ascii >= 1) {
                binary = "000000" + binary;
            }
        }

        for (int i = 0; i < binary.length(); i++) {
            if (firstChar) {
                if (binary.charAt(i) == '0') {
                    answer += "00 0";
                    firstZero = false;
                    firstOne = true;
                } else {
                    answer += "0 0";
                    firstZero = true;
                    firstOne = false;
                }
            }
            if (binary.charAt(i) == '0' && firstZero && !firstChar) {
                answer += " 00 0";
                firstZero = false;
                firstOne = true;
            } else if (binary.charAt(i) == '1' && firstOne && !firstChar) {
                answer += " 0 0";
                firstZero = true;
                firstOne = false;
            } else if (binary.charAt(i) == '0' && !firstZero && !firstChar) {
                answer += "0";
                firstOne = true;
            } else if (binary.charAt(i) == '1' && !firstOne && !firstChar) {
                answer += "0";
                firstZero = true;
            }
            firstChar = false;
        }
        System.out.println(answer);
    }
}
