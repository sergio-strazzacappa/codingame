import java.util.Scanner;

class Solution {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        int l = in.nextInt();
        int h = in.nextInt();

        if (in.hasNextLine()) {
            in.nextLine();
        }

        String T = in.nextLine();
        T = T.toUpperCase();

        String[] line = new String[h];
        String answer = "";

        char c = ' ';
        int ascii = 0;

        for (int i = 0; i < h; i++) {
            String row = in.nextLine();
            line[i] = row;
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < T.length(); j++) {
                c = T.charAt(j);

                if (c < 'A' || c > 'Z') {
                    ascii = 'Z' - 64;
                } else {
                    ascii = c - 65;
                }
                answer = line[i].substring(ascii * l, ascii * l + l);
                System.out.print(answer);
            }
            System.out.println();
        }
    }
}