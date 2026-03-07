import java.util.Scanner;

class Player {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        while (true) {
            String enemy1 = in.next();
            int dist1 = in .nextInt();

            String enemy2 = in.next();
            int dist2 = in.nextInt();

            if (dist1 < dist2) {
                System.out.println(enemy1);
            } else {
                System.out.println(enemy2);
            }
        }
    }
}