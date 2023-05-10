import java.net.URL;
import java.io.BufferedInputStream;
import java.io.FileOutputStream;

public class DownloadFile {
    private static final String FILE_URL = "https://cs.nyu.edu/~av2783/pl_hw4_q5.txt";
    private static final String BKP_FILE_URL = "https://cs.nyu.edu/~av2783/pl_hw4_q5_bkp.txt";
    private static final String FILE_NAME = "pl_hw4_q5_local_copy.txt";

    public static void main(String args[]) {
        // Reorganizing here to move the variables up
        BufferedInputStream in = null;
        byte[] dataBuffer = new byte[1024];
        int bytesRead;

        try {
            // Try the first FILE_URL
            in = new BufferedInputStream(new URL(FILE_URL).openStream());

        } catch (java.io.IOException e) {
            // If an exception is thrown, use the backup file URL
            // Only IOException is necessary as java.net.MalformedURLException is a subclass
            // of IOException
            try {
                in = new BufferedInputStream(new URL(BKP_FILE_URL).openStream());
            } catch (java.io.IOException e2) {
                // If both failed we're really screwed
                System.out.println(e.getMessage());
                System.exit(-1);
            }
        }

        try (FileOutputStream fileOutputStream = new FileOutputStream(FILE_NAME)) {
            while ((bytesRead = in.read(dataBuffer, 0, 1024)) != -1) {
                fileOutputStream.write(dataBuffer, 0, bytesRead);
            }
        } catch (java.io.FileNotFoundException e) {
            // We can't find the file!
            System.out.println(e.getMessage());
        } catch (java.io.IOException e) {
            // We had an IO error!
            System.out.println(e.getMessage());
        }
    }
}