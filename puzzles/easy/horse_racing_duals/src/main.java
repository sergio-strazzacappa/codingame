import java.util.Scanner;
import java.util.Arrays;

class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int strength[] = new int[n];

        for (int i = 0; i < n; i++) {
            int pi = in.nextInt();
            strength[i] = pi;
        }

        Arrays.sort(strength);
        int closest = Integer.MAX_VALUE;

        for (int i = 0; i < strength.length - 1; i++) {
            closest = Math.min(closest, strength[i + 1] - strength[i]);
        }
        System.out.println(closest);
    }
}