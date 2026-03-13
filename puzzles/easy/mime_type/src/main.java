import java.util.Scanner;

class Solution {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int q = in.nextInt();

        String[] exts = new String[n];
        String[] mimes = new String[n];

        for (int i = 0; i < n; i++) {
            String ext = in.next();
            String mt = in.next();

            exts[i] = ext.toUpperCase();
            mimes[i] = mt;
        }
        in.nextLine();

        for (int i = 0; i < q; i++) {
            String fname = in.nextLine();
            String ext = "";

            int lastDot = fname.lastIndexOf('.');
            String extention = "";

            if (lastDot != -1) {
                extention = 
                    fname.substring(lastDot + 1, fname.length()).toUpperCase();
            }

        
            int pos = -1;

            for (int j = 0; j < exts.length; j++) {
                if (extention.equals(exts[j])){
                    pos = j;
                }
            }
            if (pos == -1) {
                System.out.println("UNKNOWN");
            } else {
                System.out.println(mimes[pos]);
            }
        }
    }
}