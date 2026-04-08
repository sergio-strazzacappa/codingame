import java.util.Scanner;

class Solution {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner in = new Scanner(System.in);

        String lon = in.next();
        String lat = in.next();

        int n = in.nextInt();

        String names[] = new String[n];
        String longs[] = new String[n];
        String lats[] = new String[n];

        if (in.hasNextLine()) {
            in.nextLine();
        }

        for (int i = 0; i < n; i++) {
            String defib = in.nextLine();
            int sep = 0;
            names[i] = "";
            longs[i] = "";
            lats[i] = "";

            for (int j = 0; j < defib.length(); j++) {
                if (defib.charAt(j) == ';') {
                    sep++;
                }

                if (sep == 1) {
                    names[i] += defib.charAt(j);
                }
                if (sep == 4) {
                    if (defib.charAt(j) == ',') {
                        longs[i] += '.';
                    } else {
                        longs[i] += defib.charAt(j);
                    }
                }
                if (sep == 5) {
                    if (defib.charAt(j) == ',') {
                        lats[i] += '.';
                    } else {
                        lats[i] += defib.charAt(j);
                    }
                }
            }
            names[i] = names[i].substring(1, names[i].length());
            longs[i] = longs[i].substring(1, longs[i].length());
            lats[i] = lats[i].substring(1, lats[i].length());
        }

        double long_defibs[] = new double[n];
        double lat_defibs[] = new double[n];

        for (int i = 0; i < n; i++) {
            long_defibs[i] = Double.parseDouble(longs[i]);
            lat_defibs[i] = Double.parseDouble(lats[i]);

            long_defibs[i] = long_defibs[i] * Math.PI / 180;
            lat_defibs[i] = lat_defibs[i] * Math.PI / 180;
        }

        String userLon = "";
        String userLat = "";

        for (int i = 0; i < lon.length(); i++) {
            if (lon.charAt(i) == ',') {
                userLon += '.';
            } else {
                userLon += lon.charAt(i);
            }
        }

        for (int i = 0; i < lat.length(); i++) {
            if (lat.charAt(i) == ',') {
                userLat += '.';
            } else {
                userLat += lat.charAt(i);
            }
        }

        double userLongitude = Double.parseDouble(userLon) * Math.PI / 180;
        double userLatitude = Double.parseDouble(userLat) * Math.PI / 180;

        double distance = 0;
        double minDistance = 0;
        int minPos = 0;

        for (int i = 0; i < n; i++) {
            double x = (long_defibs[i] - userLongitude) * Math.cos((userLatitude + lat_defibs[i]) / 2);
            double y = lat_defibs[i] - userLatitude;
            distance = Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2)) * 6371;

            if (i == 0) {
                minDistance = distance;
            } else {
                if (distance < minDistance) {
                    minDistance = distance;
                    minPos = i;
                }
            }
        }
        System.out.println(names[minPos]);
    }
}