import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class file {

    public static String readFile(String filePath) throws IOException {
        String data = null;
        
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            data = br.readLine();
        } 
        return data;
    }

    public void writeFile(String charge, String filePath) {
        
        try {
            // ファイルに書き込む。
            BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
            writer.write(charge);
            writer.close();

            System.out.println("ファイルに書き込みました: " + filePath);
        } catch (IOException e) {
            System.out.println("エラーが発生しました: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public void writeFile2(String charge, String filePath, String message) {
        try {
            // ファイルを追記モードで開く
            BufferedWriter writer = new BufferedWriter(new FileWriter(filePath, true));
            
            // 現在の日付と時間を取得
            LocalDateTime now = LocalDateTime.now();
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            String formattedDate = now.format(formatter);

            // 追記する前に改行を追加する
            writer.newLine();

            // chargeと日付をファイルに書き込む
            writer.write(formattedDate + ": " + charge + message);
            writer.close();

            System.out.println("ファイルに書き込みました: " + filePath);
        } catch (IOException e) {
            System.out.println("エラーが発生しました: " + e.getMessage());
            e.printStackTrace();
        }
    }
}