import java.util.Scanner;

class Player {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        while (true) {
            int highestPeak = 0;
            int highestIndex = 0;

            for (int i = 0; i < 8; i++) {
                int mountainH = in.nextInt();

                if (mountainH > highestPeak) {
                    highestPeak = mountainH;
                    highestIndex = i;
                }
            }
            System.out.println(highestIndex);
        }
    }
}