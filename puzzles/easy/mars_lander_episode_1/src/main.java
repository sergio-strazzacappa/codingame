import java.util.Scanner;

class Player {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        int surfaceN = in.nextInt();

        for (int i = 0; i < surfaceN; i++) {
            @SuppressWarnings("unused")
            int landX = in.nextInt();
            @SuppressWarnings("unused")
            int landY = in.nextInt();
        }

        while (true) {
            @SuppressWarnings("unused")
            int x = in.nextInt();
            @SuppressWarnings("unused")
            int y = in.nextInt();
            @SuppressWarnings("unused")
            int hSpeed = in.nextInt();
            int vSpeed = in.nextInt();
            @SuppressWarnings("unused")
            int fuel = in.nextInt();
            @SuppressWarnings("unused")
            int rotate = in.nextInt();
            int power = in.nextInt();

            if (vSpeed <= -40) {
                power = 4;
            }
            System.out.println("0 " + power);
        }
    }
}