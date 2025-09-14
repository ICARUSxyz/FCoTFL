import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class file {

    public void emptyFile(String filePath) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
            writer.write(" ");
            writer.close();
            System.out.println("ファイルを白紙にしました。");
        } catch (Exception e) {
            System.out.println("エラーが発生しました: "+ e.getMessage());
            e.printStackTrace();
        }
    }

    public boolean viewFile(String filePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String firstLine = reader.readLine();

            if (firstLine == null || firstLine.trim().isEmpty()) {
                System.out.println("ファイルの一行目は空です。");
                return false;
            } else {
                System.out.println("ファイルの一行目には内容が含まれています。");
                return true;
            }

        } catch (IOException e) {
            System.out.println("ファイルの読み込み中にエラーが発生しました: " + e.getMessage());
            return false; // エラーが発生した場合もfalseを返す
        }
    }
}