import java.util.*;

class Player {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        int lightX = in.nextInt();
        int lightY = in.nextInt();
        int initialTX = in.nextInt();
        int initialTY = in.nextInt();

        int positionX = initialTX;
        int positionY = initialTY;

        while (true) {
            @SuppressWarnings("unused")
            int remainingTurns = in.nextInt();

            String direction = "";

            if (positionY < lightY) {
                direction += "S";
                positionY++;
            }
            if (positionY > lightY) {
                direction += "N";
                positionY--;
            }
            if (positionX < lightX) {
                direction += "E";
                positionX++;
            }
            if (positionX > lightX) {
                direction += "W";
                positionX--;
            }
            System.out.println(direction);
        }
    }
}