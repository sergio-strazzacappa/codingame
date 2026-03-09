import java.util.Scanner;

class Solution {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();

        int[] temp = new int[n];
        int result = 0;
        int closestTemp = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            int t = in.nextInt();
            temp[i] = t;
        }

        for (int i = 0; i < n; i++) {
            if (Math.abs(temp[i]) < Math.abs(closestTemp)) {
                closestTemp = temp[i];
            } else {
                if (Math.abs(temp[i]) == Math.abs(closestTemp)) {
                    if (temp[i] > 0) {
                        closestTemp = temp[i];
                    }
                }
            }
        }
        if (n > 0) {
            result = closestTemp;
        }
        System.out.println(result);
    }
}